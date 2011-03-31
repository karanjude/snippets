import java.util.ArrayList;

public class Truck {

	private int id;
	private String name;
	private int x;
	private int y;
	private ArrayList<String> vaccines;

	public Truck(String truckString) {
		String[] parts = truckString.split(",");
		this.id = Integer.parseInt(parts[0].trim());
		this.name = parts[1].trim();
		this.x = Integer.parseInt(parts[2].trim());
		this.y = Integer.parseInt(parts[3].trim());
		String[] vaccines = parts[4].trim().split(":");
		this.vaccines = new ArrayList<String>();
		for (String vaccine : vaccines) {
			this.vaccines.add(vaccine.trim());
		}
	}

	public String id() {
		return new Integer(this.id).toString();
	}

	public String sql() {
		return String
				.format(
						"insert into trucks values(%d,'%s',SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(%d,%d,NULL),NULL,NULL))",
						new Integer(this.id), this.name, new Integer(this.x),
						new Integer(this.y));
	}

	public ArrayList<String> vaccineMappingSql() {
		ArrayList<String> vaccineMappingSqls = new ArrayList<String>();
		for (String vaccine : vaccines) {
			vaccineMappingSqls.add(String.format(
					"insert into truck_vaccines values('%s','%s')", new Integer(
							this.id), vaccine.trim()));
		}
		return vaccineMappingSqls;
	}

}
