import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

import oracle.spatial.geometry.JGeometry;
import oracle.sql.STRUCT;

public class Trucks {

	private HashMap<Integer, Truck> trucks = new HashMap<Integer, Truck>();
	private final QueryExecutior queryExecutior;

	public Trucks(QueryExecutior queryExecutior) {
		this.queryExecutior = queryExecutior;
	}

	public void load(QueryExecutior queryExecutior) throws SQLException {
		ResultSet result = queryExecutior.selectQuery(loadSql());
		processRecordRow(result, trucks);
	}

	private void processRecordRow(ResultSet result,
			HashMap<Integer, Truck> resultMap) throws SQLException {
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
				Truck truck = new Truck(id, name, point);
				loadTruckVaccines(truck);
				resultMap.put(new Integer(id), truck);
				//System.out.println(id + "," + name + "," + point);
			}
		} finally {
			try {
				result.close();
			} catch (Exception ignore) {
			}
		}

	}

	private String loadSql() {
		return "select * from trucks";
	}

	public int count() {
		return trucks.size();
	}

	public HashMap<Integer, Truck> inRegion(int x1, int y1, int x2, int y2, StringBuilder rsql)
			throws SQLException {
		HashMap<Integer, Truck> r = new HashMap<Integer, Truck>();
		String sql = String
				.format(
						"select t.id , t.name , t.shape from trucks t where sdo_filter(t.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3),sdo_ordinate_array(%s,%s,%s,%s))) = 'TRUE'",
						x1, y1, x2, y2);
		rsql.append(" ").append(sql);
		ResultSet result = queryExecutior.selectQuery(sql);
		processRecordRow(result, r);
		return r;
	}

	public HashMap<Integer, Truck> NearestVaccineSuppliedByTrucksForAnimal(
			int x1, int y1, int x2, int y2, Animal animal, StringBuilder rsql) throws SQLException {
		int trucksInRegion = inRegion(x1, y1, x2, y2, rsql).size();

		HashMap<Integer, Truck> r = new HashMap<Integer, Truck>();
		String sql = String
				.format(
						"select * from trucks  where id in ((select distinct t.id from trucks t, truck_vaccines tv where t.id = tv.id and tv.vaccine_id in (select va.id from vaccine_animals va where va.name = '%s'))) and sdo_nn(shape, sdo_geometry(2011,NULL,sdo_point_type(%s,%s,NULL),NULL,NULL), 'sdo_num_res=%s') = 'TRUE'",
						animal.name(), animal.x(), animal.y(), trucksInRegion);
		ResultSet result = queryExecutior.selectQuery(sql);
		processRecordRow(result, r);
		return r;
	}

	public void render(Graphics g) {
		g.setColor(Color.YELLOW);
		for (Entry<Integer, Truck> truck : trucks.entrySet()) {
			Point p1 =  truck.getValue().getPoint();
			Point p2 = new Point(p1.x - 5, p1.y + 10);
			Point p3 = new Point(p1.x + 5, p1.y + 10);

			int[] xs = { p1.x, p2.x, p3.x };
			int[] ys = { p1.y, p2.y, p3.y };
			Polygon triangle = new Polygon(xs, ys, xs.length);

			g.fillPolygon(triangle);
		}
	}

	public ArrayList<Truck> getTrucks() {
		ArrayList<Truck> result = new ArrayList<Truck>();
		for (Entry<Integer, Truck> truck : trucks.entrySet()) {
			result.add(truck.getValue());
		}
		return result;
	}

	public void loadTruckVaccines(Truck truck) throws SQLException {
		String sql = String.format("select v.name from truck_vaccines tv , vaccines v where v.id=tv.vaccine_id and tv.id = %s", truck.id());
		// select v.name from truck_vaccines tv , vaccines v where v.id=tv.vaccine_id and tv.id =
		ResultSet result = queryExecutior.selectQuery(sql);
		try {
			while (result.next()) {
				String vaccine = result.getString(1);
				truck.addVaccine(vaccine);
			}
		} finally {
			try {
				result.close();
			} catch (Exception ignore) {
			}
		}

	}
}
