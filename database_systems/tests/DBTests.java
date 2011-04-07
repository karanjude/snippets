import java.util.HashMap;
import java.util.List;

import junit.framework.TestCase;

public class DBTests extends TestCase {
	public void testAnimalsInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Animals animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
		assertEquals(100, animals.count());
	}


	public void testTrucksInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
		assertEquals(30, trucks.count());
	}
	
	public void testTrucksVaccineInDB() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
		Truck truck = trucks.getTrucks().get(0);
		trucks.loadTruckVaccines(truck);
		List<String> vaccines = truck.vaccines();
		assertTrue(vaccines.size() > 0);

	}
	

	public void testAnimalsInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Animals animals = new Animals(queryExecutior);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Animal> animalsInRegion = animals.inRegion(0,0,100,100,r);
		assertEquals(27, animalsInRegion.size());
	}
	
	public void testTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Truck> trucksInRegion = trucks.inRegion(0,0,100,100,r);
		assertEquals(4, trucksInRegion.size());
	}
	
	public void testAnimalsCoveredByVaccineInRegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Animals animals = new Animals(queryExecutior);
		Truck truck = new Truck(3);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Animal> animalsInRegion = animals.CoveredByVaccineInARegion(0,0,100,100, truck,r);
		assertEquals(4, animalsInRegion.size());
	}

	public void testNearestVaccineSuppliedByTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		Animals animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
		Animal animal = animals.getAnimals().get(3);
		StringBuilder r = new StringBuilder();
		HashMap<Integer, Truck> trucksInRegion = trucks.NearestVaccineSuppliedByTrucksForAnimal(0,0,100,100, animal,r);
		assertEquals(1, trucksInRegion.size());
	}

	
}
