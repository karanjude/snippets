import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.sql.SQLException;

public class AnimalRenderer {
	private Animals animals;

	public AnimalRenderer() throws ClassNotFoundException, SQLException {
		QueryExecutior queryExecutior = new QueryExecutior();
		animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
	}

	public void render(Graphics g) {
		animals.render(g);


	}

}
