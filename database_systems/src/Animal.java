public class Animal {

	private int id;
	private String name;
	private int x;
	private int y;

	public Animal(String animalString) {
		String[] parts = animalString.split(",");
		this.id = Integer.parseInt(parts[0].trim());
		this.name = parts[1];
		this.x = Integer.parseInt(parts[2].trim());
		this.y = Integer.parseInt(parts[3].trim());
	}

	public String name() {
		return this.name;
	}

	public String id() {
		return new Integer(this.id).toString();
	}

	public String sql() {
		return String.format("insert into animals values(%d,'%s',SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(%d,%d,NULL),NULL,NULL))", new Integer(this.id), this.name, 
				new Integer(this.x), new Integer(this.y));
	}

}
