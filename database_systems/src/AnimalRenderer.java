import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
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

import javax.swing.JButton;
import javax.swing.JPanel;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.Leading;

public class AnimalRenderer {
	private final class AnimalComponent extends JPanel {
		private final Animal animal;

		public AnimalComponent(Animal animal) {
			this.animal = animal;
		}

		@Override
		public void paint(Graphics g) {
			super.paint(g);
			Color c = Color.RED;

			if (animalsInSelectedRegion != null
					&& animalsInSelectedRegion.size() != 0
					&& animalsInSelectedRegion.containsKey(animal.id)) {
				c = Color.GREEN;
			}
			int w = this.getWidth();
			int h = this.getHeight();
			BufferedImage i = new BufferedImage(w, h,
					BufferedImage.TYPE_INT_ARGB);
			Graphics g1 = i.getGraphics();
			g1.setColor(c);

			Point p1 = animal.getPoint();
			Point p2 = new Point(p1.x - 5, p1.y + 10);
			Point p3 = new Point(p1.x + 5, p1.y + 10);

			int[] xs = { w / 2, w, 0 };
			int[] ys = { 0, h, h };
			Polygon triangle = new Polygon(xs, ys, xs.length);
			g1.fillPolygon(triangle);

			Graphics2D g2 = (Graphics2D) g;
			float[] scales = { 1f, 1f, 1f, 1f };
			float[] offsets = new float[4];
			RescaleOp rop = new RescaleOp(scales, offsets, null);
			g2.drawImage(i, rop, 0, 0);

		}

	}

	private Animals animals;
	private HashMap<Integer, Animal> animalsInSelectedRegion = new HashMap<Integer, Animal>();

	public AnimalRenderer() throws ClassNotFoundException, SQLException {
		QueryExecutior queryExecutior = new QueryExecutior();
		animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
	}

	public void render(Graphics g) {
		// animals.render(g);

	}

	private Animal selectedAnimal;

	public void addAnimals(final ImagePanel imagePanel) {
		for (final Animal animal : animals.getAnimals()) {
			AnimalComponent animalComponent = new AnimalComponent(animal);
			animalComponent.setOpaque(false);
			imagePanel.add(animalComponent);
			animalComponent.addMouseMotionListener(new MouseMotionListener() {

				@Override
				public void mouseMoved(MouseEvent e) {
					imagePanel.updateAnimalInfo(animal);

				}

				@Override
				public void mouseDragged(MouseEvent e) {
					// TODO Auto-generated method stub

				}
			});

			animalComponent.addMouseListener(new MouseListener() {

				@Override
				public void mouseReleased(MouseEvent e) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mousePressed(MouseEvent e) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseExited(MouseEvent e) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseEntered(MouseEvent e) {
					// TODO Auto-generated method stub

				}

				@Override
				public void mouseClicked(MouseEvent e) {
					selectedAnimal = animal;
				}
			});

			Insets insets = imagePanel.getInsets();
			Dimension size = animalComponent.getPreferredSize();
			Point p1 = animal.getPoint();
			animalComponent.setBounds(p1.x - 4 + insets.left, p1.y - 4
					+ insets.top, 8, 8);
			// animalComponent.setBackground(Color.RED);
		}

	}

	public String rangeQuery(int startx, int starty, int endx, int endy)
			throws SQLException {
		StringBuilder sql = new StringBuilder();
		animalsInSelectedRegion = animals.inRegion(startx, starty, endx, endy,
				sql);
		return sql.toString();
	}

	public void clearRangeQuery() {
		animalsInSelectedRegion.clear();
	}

	public void findVaccineCoverageQuery(int startx, int starty, int endx,
			int endy, Truck selectedTruck, StringBuilder r) throws SQLException {
		animalsInSelectedRegion = animals.CoveredByVaccineInARegion(startx,
				starty, endx, endy, selectedTruck, r);
	}

	public Animal getSelectedAnimal() {
		return selectedAnimal;
	}

}
