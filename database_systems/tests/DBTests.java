import java.util.HashMap;

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
	

	public void testAnimalsInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Animals animals = new Animals(queryExecutior);
		HashMap<Integer, Animal> animalsInRegion = animals.inRegion(0,0,100,100);
		assertEquals(27, animalsInRegion.size());
	}
	
	public void testTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		HashMap<Integer, Truck> trucksInRegion = trucks.inRegion(0,0,100,100);
		assertEquals(4, trucksInRegion.size());
	}
	
	public void testAnimalsCoveredByVaccineInRegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Animals animals = new Animals(queryExecutior);
		Truck truck = new Truck(3);
		HashMap<Integer, Animal> animalsInRegion = animals.CoveredByVaccineInARegion(0,0,100,100, truck);
		assertEquals(4, animalsInRegion.size());
	}

	public void testNearestVaccineSuppliedByTrucksInARegion() throws Exception {
		QueryExecutior queryExecutior = new QueryExecutior();
		Trucks trucks = new Trucks(queryExecutior);
		Animal animal = new Animal(3,"rabbit", 50, 50);
		HashMap<Integer, Truck> trucksInRegion = trucks.NearestVaccineSuppliedByTrucksForAnimal(0,0,100,100, animal);;
		assertEquals(2, trucksInRegion.size());
	}

	
}
