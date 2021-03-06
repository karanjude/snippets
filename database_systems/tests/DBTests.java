import java.util.HashMap;
import java.util.List;

import junit.framework.TestCase;

public class DBTests extends TestCase {

	private ConnectionInfo connectionInfo;

	@Override
	protected void setUp() throws Exception {
		connectionInfo = new ConnectionInfo();
		connectionInfo.host = "localhost";
		connectionInfo.port = "1521";
		connectionInfo.dbname = "XE";
		connectionInfo.username = "jude";
		connectionInfo.password = "jude";
	}

	public void testAnimalsInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Animals animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
		assertEquals(100, animals.count());
	}

	public void testTrucksInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Trucks trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
		assertEquals(30, trucks.count());
	}

	public void testTrucksVaccineInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Trucks trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
		Truck truck = trucks.getTrucks().get(0);
		List<String> vaccines = truck.vaccines();
		System.out.println(truck.id);
		assertEquals(3, vaccines.size());
		assertEquals("influenza", vaccines.get(0));
		assertEquals("FCV", vaccines.get(1));
		assertEquals("FIP", vaccines.get(2));

	}

	public void testAnimalsInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Animals animals = new Animals(queryExecutior);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Animal> animalsInRegion = animals.inRegion(0, 0, 100,
				100, r);
		assertEquals(27, animalsInRegion.size());
	}

	public void testTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Trucks trucks = new Trucks(queryExecutior);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Truck> trucksInRegion = trucks.inRegion(0, 0, 100,
				100, r);
		assertEquals(4, trucksInRegion.size());
	}

	public void testAnimalsCoveredByVaccineInRegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Animals animals = new Animals(queryExecutior);
		Truck truck = new Truck(3);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Animal> animalsInRegion = animals
				.CoveredByVaccineInARegion(0, 0, 100, 100, truck, r);
		assertEquals(4, animalsInRegion.size());
	}

	public void testNearestVaccineSuppliedByTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior(connectionInfo);
		Trucks trucks = new Trucks(queryExecutior);
		Animals animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
		Animal animal = animals.getAnimals().get(3);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Truck> trucksInRegion = trucks
				.NearestVaccineSuppliedByTrucksForAnimal(0, 0, 100, 100,
						animal, r);
		assertEquals(1, trucksInRegion.size());
	}

}
