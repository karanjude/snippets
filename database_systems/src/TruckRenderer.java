import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.awt.image.RescaleOp;
import java.sql.SQLException;
import java.util.HashMap;

import javax.swing.JPanel;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.Leading;

public class TruckRenderer {
	private Truck selectedTruck;

	private final class TruckComponent extends JPanel {

		private final Truck truck;

		public TruckComponent(Truck truck) {
			this.truck = truck;
		}

		public void paint(Graphics g) {
			super.paint(g);
			Color c = Color.YELLOW;
			if (trucksInSelectedRegion != null
					&& trucksInSelectedRegion.size() != 0
					&& trucksInSelectedRegion.containsKey(truck.id)) {
				c = Color.ORANGE;
			}
			int w = this.getWidth();
			int h = this.getHeight();
			BufferedImage i = new BufferedImage(w, h,
					BufferedImage.TYPE_INT_ARGB);
			Graphics g1 = i.getGraphics();
			g1.setColor(c);

			Point p1 = truck.getPoint();
			g1.fillOval(0, 0, w, h);
			Graphics2D g2 = (Graphics2D) g;
			float[] scales = { 1f, 1f, 1f, 1f };
			float[] offsets = new float[4];
			RescaleOp rop = new RescaleOp(scales, offsets, null);
			g2.drawImage(i, rop, 0, 0);
		}
	}

	private Trucks trucks;
	private HashMap<Integer, Truck> trucksInSelectedRegion = new HashMap<Integer, Truck>();

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
			truckComponent.setOpaque(false);
			truckComponent.addMouseMotionListener(new MouseMotionListener() {

				@Override
				public void mouseMoved(MouseEvent arg0) {
					imagePanel.updateTruckInfo(truck);
				}

				@Override
				public void mouseDragged(MouseEvent arg0) {
				}
			});

			truckComponent.addMouseListener(new MouseListener() {

				@Override
				public void mouseReleased(MouseEvent arg0) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mousePressed(MouseEvent arg0) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseExited(MouseEvent arg0) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseEntered(MouseEvent arg0) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseClicked(MouseEvent arg0) {
					selectedTruck = truck;
				}
			});

			imagePanel.add(truckComponent);
			Dimension size = truckComponent.getPreferredSize();
			Point p1 = truck.getPoint();
			truckComponent.setBounds(p1.x + insets.left, p1.y + insets.top,
					size.width, size.height);
			truckComponent.setBackground(Color.YELLOW);
		}
	}

	public Truck getSelectedTruck() {
		return selectedTruck;
	}

	public String rangeQuery(int startx, int starty, int endx, int endy)
			throws SQLException {
		StringBuilder sql = new StringBuilder();
		trucksInSelectedRegion = trucks.inRegion(startx, starty, endx, endy,
				sql);
		return sql.toString();
	}

	public void clearRangeQuery() {
		trucksInSelectedRegion.clear();
	}

	public void findNearestVaccineSuppliesQuery(int startx, int starty,
			int endx, int endy, Animal selectedAnimal, StringBuilder r)
			throws SQLException {
		trucksInSelectedRegion = trucks
				.NearestVaccineSuppliedByTrucksForAnimal(startx, starty, endx,
						endy, selectedAnimal, r);
	}

}
