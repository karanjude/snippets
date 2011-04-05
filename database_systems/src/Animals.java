import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.geom.Point2D;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

import oracle.spatial.geometry.JGeometry;
import oracle.sql.STRUCT;

public class Animals {
	private HashMap<Integer, Animal> animals = new HashMap<Integer, Animal>();
	private final QueryExecutior queryExecutior;

	public Animals(QueryExecutior queryExecutior) {
		this.queryExecutior = queryExecutior;
	}

	public void load(QueryExecutior queryExecutior) throws SQLException {
		ResultSet result = queryExecutior.selectQuery(loadAnimalSql());
		processRecordRow(result, animals);
	}

	private void processRecordRow(ResultSet result,
			HashMap<Integer, Animal> resultMap) throws SQLException {
		int id;
		String name;
		JGeometry point;
		STRUCT st;
		try {
			while (result.next()) {
				id = result.getInt(1);
				name = result.getString(2);
				st = (STRUCT) result.getObject(3);
				point = JGeometry.load(st);
				resultMap.put(new Integer(id), new Animal(id, name, point));
				System.out.println(id + "," + name + "," + point);
			}
		} finally {
			try {
				result.close();
			} catch (Exception ignore) {
			}
		}
	}

	private String loadAnimalSql() {
		return "select * from animals";
	}

	public int count() {
		return animals.size();
	}

	public HashMap<Integer, Animal> inRegion(int x1, int y1, int x2, int y2)
			throws SQLException {
		HashMap<Integer, Animal> r = new HashMap<Integer, Animal>();
		String sql = String
				.format(
						"select a.id , a.name , a.shape from animals a where sdo_filter(a.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(%s,%s,%s,%s))) = 'TRUE'",
						x1, y1, x2, y2);
		ResultSet result = queryExecutior.selectQuery(sql);
		processRecordRow(result, r);
		return r;

	}

	public HashMap<Integer, Animal> CoveredByVaccineInARegion(int x1, int y1,
			int x2, int y2, Truck truck) throws SQLException {
		HashMap<Integer, Animal> r = new HashMap<Integer, Animal>();
		String sql = String
				.format(
						"select a.id , a.name , a.shape from animals a where sdo_filter(a.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(%s,%s,%s,%s))) = 'TRUE' and a.name in(select va.name from vaccines v , vaccine_animals va where v.id=va.id and v.id in (select tv.vaccine_id from trucks t, truck_vaccines tv where tv.id = t.id and t.id = %s))",
						x1, y1, x2, y2, truck.id());
		ResultSet result = queryExecutior.selectQuery(sql);
		processRecordRow(result, r);
		return r;
	}

	public void render(Graphics g) {
		g.setColor(Color.RED);
		for (Entry<Integer, Animal> animal : animals.entrySet()) {
			Point p1 =  animal.getValue().getPoint();
			Point p2 = new Point(p1.x - 5, p1.y + 10);
			Point p3 = new Point(p1.x + 5, p1.y + 10);

			int[] xs = { p1.x, p2.x, p3.x };
			int[] ys = { p1.y, p2.y, p3.y };
			Polygon triangle = new Polygon(xs, ys, xs.length);

			g.fillPolygon(triangle);
		}
	}

	public ArrayList<Animal> getAnimals() {
		ArrayList<Animal> result = new ArrayList<Animal>();
		for (Entry<Integer, Animal> animal : animals.entrySet()) {
			result.add(animal.getValue());
		}
		return result;
	}

}
