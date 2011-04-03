import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Map.Entry;

public class populate {
	public static void main(String[] args) throws IOException,
			ClassNotFoundException, SQLException, URISyntaxException {

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

		queryExecutior
				.insertQuery("insert into user_sdo_geom_metadata values('ANIMALS','SHAPE',SDO_DIM_ARRAY(SDO_DIM_ELEMENT('X', 0, 500, 0.005),SDO_DIM_ELEMENT('Y', 0, 500, 0.005) ),NULL)");

		queryExecutior
				.ddlQuery("create index animal_location_index on animals (shape) indextype is mdsys.spatial_index");

		queryExecutior
				.insertQuery("insert into user_sdo_geom_metadata values('TRUCKS','SHAPE',SDO_DIM_ARRAY(SDO_DIM_ELEMENT('X', 0, 500, 0.005),SDO_DIM_ELEMENT('Y', 0, 500, 0.005) ),NULL)");

		queryExecutior
				.ddlQuery("create index truck_location_index on trucks (shape) indextype is mdsys.spatial_index");

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
