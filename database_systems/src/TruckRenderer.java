import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.sql.SQLException;

public class TruckRenderer {
	private Trucks trucks;

	public TruckRenderer() throws ClassNotFoundException, SQLException {
		QueryExecutior queryExecutior = new QueryExecutior();
		trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
	}

	public void render(Graphics g) {
		trucks.render(g);
	}

}
