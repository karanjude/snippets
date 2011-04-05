import java.awt.Point;
import java.awt.geom.Point2D;

import oracle.spatial.geometry.JGeometry;

public class Animal {

	private int id;
	private String name;
	private int x;
	private int y;
	private JGeometry point;

	public Animal(String animalString) {
		String[] parts = animalString.split(",");
		this.id = Integer.parseInt(parts[0].trim());
		this.name = parts[1].trim();
		this.x = Integer.parseInt(parts[2].trim());
		this.y = Integer.parseInt(parts[3].trim());
	}

	public Animal(int id, String name, JGeometry point) {
		this.id = id;
		this.name = name;
		this.point = point;
	}

	Animal(int i, String string, int j, int k) {
		id = i;
		name = string;
		x = j;
		y = k;
	}

	public String name() {
		return this.name;
	}

	public String id() {
		return new Integer(this.id).toString();
	}

	public String sql() {
		return String
				.format(
						"insert into animals values(%d,'%s',SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(%d,%d,NULL),NULL,NULL))",
						new Integer(this.id), this.name, new Integer(this.x),
						new Integer(this.y));
	}

	public String x() {
		 return new Integer(getPoint().x).toString();
	}

	public String y() {
		 return new Integer(getPoint().y).toString();
	}

	public Point getPoint() {
		Point2D javaPoint = this.point.getJavaPoint();
		return new Point((int) javaPoint.getX(), (int) javaPoint.getY());
	}

}
