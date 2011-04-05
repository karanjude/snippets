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
import java.util.HashMap;

import javax.swing.JButton;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.Leading;

public class AnimalRenderer {
	private final class AnimalComponent extends Panel {
		private final Animal animal;

		public AnimalComponent(Animal animal) {
			this.animal = animal;
		}

		@Override
		public void paint(Graphics g) {
			super.paint(g);
			if (animalsInSelectedRegion != null
					&& animalsInSelectedRegion.size() != 0
					&& animalsInSelectedRegion.containsKey(animal.id)) {
				this.setBackground(Color.GREEN);
			}
		}
	}

	private Animals animals;
	private HashMap<Integer, Animal> animalsInSelectedRegion;

	public AnimalRenderer() throws ClassNotFoundException, SQLException {
		QueryExecutior queryExecutior = new QueryExecutior();
		animals = new Animals(queryExecutior);
		animals.load(queryExecutior);
	}

	public void render(Graphics g) {
		// animals.render(g);

	}

	public void addAnimals(final ImagePanel imagePanel) {
		for (final Animal animal : animals.getAnimals()) {
			AnimalComponent animalComponent = new AnimalComponent(animal);
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

			Insets insets = imagePanel.getInsets();
			Dimension size = animalComponent.getPreferredSize();
			Point p1 = animal.getPoint();
			animalComponent.setBounds(p1.x + insets.left, p1.y + insets.top,
					size.width, size.height);
			animalComponent.setBackground(Color.RED);
		}

	}

	public String rangeQuery(int startx, int starty, int endx, int endy)
			throws SQLException {
		animalsInSelectedRegion = animals.inRegion(startx, starty, endx, endy);
		return "";
	}

}
