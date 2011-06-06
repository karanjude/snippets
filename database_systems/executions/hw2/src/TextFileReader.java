import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashMap;

public class TextFileReader {
	private String file;

	public TextFileReader(String fileName) {
		file = fileName;
	}

	public ArrayList<String> sql() throws IOException {
		ArrayList<String> result = new ArrayList<String>();
		BufferedReader stream = null;

		stream = new BufferedReader(new FileReader(new File(file)));

		try {
			String line = "";
			while ((line = stream.readLine()) != null) {
				result.add(line);
			}
		} finally {
			stream.close();
		}
		return result;
	}

	public HashMap<String, Animal> readAnimalsInformation() throws IOException {
		HashMap<String, Animal> result = new HashMap<String, Animal>();
		BufferedReader stream = null;

		stream = new BufferedReader(new FileReader(new File(file)));

		try {
			String line = "";
			while ((line = stream.readLine()) != null) {
				Animal animal = new Animal(line);
				result.put(animal.id(), animal);
			}
		} finally {
			stream.close();
		}

		return result;
	}

	public HashMap<String, Vaccine> readVaccineInformation() throws IOException {
		HashMap<String, Vaccine> result = new HashMap<String, Vaccine>();
		BufferedReader stream = null;

		stream = new BufferedReader(new FileReader(new File(file)));

		try {
			String line = "";
			while ((line = stream.readLine()) != null) {
				Vaccine vaccine = new Vaccine(line);
				result.put(vaccine.id(), vaccine);
			}
		} finally {
			stream.close();
		}
		return result;
	}

	public HashMap<String, Truck> readTruckInformation() throws IOException {
		HashMap<String, Truck> result = new HashMap<String, Truck>();
		BufferedReader stream = null;

		stream = new BufferedReader(new FileReader(new File(file)));

		try {
			String line = "";
			while ((line = stream.readLine()) != null) {
				Truck truck = new Truck(line);
				result.put(truck.id(), truck);
			}
		} finally {
			stream.close();
		}
		return result;
	}

	public ConnectionInfo connectionInfo() throws IOException {
		BufferedReader stream = null;
		ConnectionInfo result = new ConnectionInfo();

		stream = new BufferedReader(new FileReader(new File(file)));

		try {
			String line = "";
			int i = 0;
			while ((line = stream.readLine()) != null) {
				i++;
				switch (i) {
				case 1:
					result.host = line.trim();
					break;
				case 2:
					result.port = line.trim();
					break;
				case 3:
					result.dbname = line.trim();
					break;
				case 4:
					result.username = line.trim();
					break;
				case 5:
					result.password = line.trim();
					break;

				default:
					break;
				}
			}
		} finally {
			stream.close();
		}

		return result;
	}

}
