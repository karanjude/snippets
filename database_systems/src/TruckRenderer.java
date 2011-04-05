import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.sql.SQLException;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.Leading;


public class TruckRenderer {
	private final class TruckComponent extends Panel {

		private final Truck truck;

		public TruckComponent(Truck truck) {
			this.truck = truck;
		}

		@Override
		public void paint(Graphics g) {
			super.paint(g);
//			g.setColor(Color.YELLOW);
//
//			Point p1 = truck.getPoint();
//			Point p2 = new Point(p1.x - 5, p1.y + 10);
//			Point p3 = new Point(p1.x + 5, p1.y + 10);
//
//			int[] xs = { p1.x, p2.x, p3.x };
//			int[] ys = { p1.y, p2.y, p3.y };
//			Polygon triangle = new Polygon(xs, ys, xs.length);
//
//			g.fillRect(p1.x, p1.y, 10, 10);
		}
	}

	private Trucks trucks;

	public TruckRenderer() throws ClassNotFoundException, SQLException {
		QueryExecutior queryExecutior = new QueryExecutior();
		trucks = new Trucks(queryExecutior);
		trucks.load(queryExecutior);
	}

	public void render(Graphics g) {
		// trucks.render(g);
	}

	public void addTrucks(final ImagePanel imagePanel) {
		Insets insets = imagePanel.getInsets();
		for (final Truck truck : trucks.getTrucks()) {
			TruckComponent truckComponent = new TruckComponent(truck);
			truckComponent.addMouseMotionListener(new MouseMotionListener() {
				
				@Override
				public void mouseMoved(MouseEvent arg0) {
					imagePanel.updateTruckInfo(truck);
				}
				
				@Override
				public void mouseDragged(MouseEvent arg0) {
				}
			});
			
			imagePanel.add(truckComponent);
			Dimension size = truckComponent.getPreferredSize();
			Point p1 = truck.getPoint();
			truckComponent.setBounds(p1.x + insets.left, p1.y + insets.top, size.width,
					size.height);
			truckComponent.setBackground(Color.YELLOW);
		}
	}

}
