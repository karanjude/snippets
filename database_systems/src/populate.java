import java.io.File;
import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Map.Entry;

public class populate {
	public static void main(String[] args) throws IOException,
			ClassNotFoundException, SQLException {

		String animalsFile = args[0];
		String trucksFile = args[1];
		String vaccinesFile = args[2];

		System.out.println(new File(animalsFile).getAbsolutePath());
		System.out.println(new File(trucksFile).getAbsolutePath());
		System.out.println(new File(vaccinesFile).getAbsolutePath());

		QueryExecutior queryExecutior = null;
		queryExecutior = new QueryExecutior();

		DbCreator dbCreator = new DbCreator();
		dbCreator.createDb(queryExecutior);

		TextFileReader textReader = new TextFileReader(animalsFile);
		HashMap<String, Animal> animals = null;
		animals = textReader.readAnimalsInformation();

		System.out.println(animals.size());

		textReader = new TextFileReader(vaccinesFile);
		HashMap<String, Vaccine> vaccines = null;
		vaccines = textReader.readVaccineInformation();

		System.out.println(vaccines.size());

		textReader = new TextFileReader(trucksFile);
		HashMap<String, Truck> trucks = null;
		trucks = textReader.readTruckInformation();

		System.out.println(trucks.size());

		populateAnimals(animals, queryExecutior);
		populateVaccines(vaccines, queryExecutior);
		populateTrucks(trucks, queryExecutior);

		queryExecutior.close();
	}

	private static void populateTrucks(HashMap<String, Truck> trucks,
			QueryExecutior queryExecutior) throws ClassNotFoundException,
			SQLException {
		for (Entry<String, Truck> entry : trucks.entrySet()) {
			Truck truck = entry.getValue();
			String sql = truck.sql();
			System.out.println(sql);
			queryExecutior.insertQuery(sql);
			for (String vaccineAnimalSql : truck.vaccineMappingSql()) {
				System.out.println(vaccineAnimalSql);
				queryExecutior.insertQuery(vaccineAnimalSql);
			}
		}

	}

	private static void populateVaccines(HashMap<String, Vaccine> vaccines,
			QueryExecutior queryExecutior) throws ClassNotFoundException,
			SQLException {
		for (Entry<String, Vaccine> entry : vaccines.entrySet()) {
			Vaccine vaccine = entry.getValue();
			String sql = vaccine.sql();
			System.out.println(sql);
			queryExecutior.insertQuery(sql);
			for (String vaccineAnimalSql : vaccine.animalMappingSql()) {
				System.out.println(vaccineAnimalSql);
				queryExecutior.insertQuery(vaccineAnimalSql);
			}

		}
	}

	private static void populateAnimals(HashMap<String, Animal> animals,
			QueryExecutior queryExecutior) throws ClassNotFoundException,
			SQLException {
		for (Entry<String, Animal> entry : animals.entrySet()) {
			String sql = entry.getValue().sql();
			System.out.println(sql);
			queryExecutior.insertQuery(sql);
		}

	}
}
