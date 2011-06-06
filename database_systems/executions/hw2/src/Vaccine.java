import java.util.ArrayList;
import java.util.HashMap;

public class Vaccine {

	private String id;
	private String name;
	private ArrayList<String> animals;

	public Vaccine(String vaccineString) {
		String[] parts = vaccineString.split(",");
		this.id = parts[0].trim();
		this.name = parts[1].trim();
		this.animals = new ArrayList<String>();
		String[] vaccinesForAnimals = parts[2].trim().split(":");
		for (String animal : vaccinesForAnimals) {
			animals.add(animal.trim());
		}
	}

	public String id() {
		return this.id;
	}

	public String sql() {
		return String.format("insert into vaccines values('%s','%s')", this.id,
				this.name);
	}

	public ArrayList<String> animalMappingSql() {
		ArrayList<String> animalMappingSqls = new ArrayList<String>();
		for (String animal : animals) {
			animalMappingSqls.add(String.format(
					"insert into vaccine_animals values('%s','%s')", this.id,
					animal.trim()));
		}
		return animalMappingSqls;
	}
}
