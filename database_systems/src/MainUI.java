import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.sql.SQLException;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

import org.dyno.visual.swing.layouts.Bilateral;
import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.GroupLayout;
import org.dyno.visual.swing.layouts.Leading;
import org.dyno.visual.swing.layouts.Trailing;

class ImagePanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private BufferedImage image;
	private final AnimalRenderer animalRenderer;
	private final TruckRenderer truckRenderer;
	private final UI ui;
	private int startx;
	private int starty;
	private int endx;
	private int endy;
	private boolean isDrawingRectangle;
	private boolean showDrawingRectangle;
	private boolean stopDrawingRectangle;

	public ImagePanel(AnimalRenderer animalRenderer,
			TruckRenderer truckRenderer, UI ui) {
		this.ui = ui;
		this.animalRenderer = animalRenderer;
		this.truckRenderer = truckRenderer;
		try {
			File landjpg = new File("land.jpg");
			System.out.println(landjpg.exists());
			image = ImageIO.read(landjpg);
		} catch (IOException ex) {
			// handle exception...
		}

	}

	public void paintComponent(Graphics g) {
		g.drawImage(image, 0, 0, null); // see javadoc for more info on the
		// parameters
		if (showDrawingRectangle) {
			g.setColor(Color.BLUE);
			int width = Math.abs(endx - startx);
			int height = Math.abs(endy - starty);
			g.drawRect(startx, starty - height, width, height);
			System.out.println(startx + " " + starty + " " + endx + " " + endy);
		}
		// renderer.render(g);
		// truckRenderer.render(g);

		// g.fillRect(50, 50, 70, 70);
	}

	@Override
	public void repaint() {
		super.repaint();
		paintChildren();
	}

	public void addAnimals() {
		this.animalRenderer.addAnimals(this);
	}

	public void addTrucks() {
		this.truckRenderer.addTrucks(this);
	}

	public void updateTruckInfo(Truck truck) {
		ui.updateTruckInfo(truck);
	}

	public void updateAnimalInfo(Animal animal) {
		ui.updateAnimalInfo(animal);
	}

	public void setStartXY(int x, int y) {
		this.startx = x;
		this.starty = y;
	}

	public void setEndXY(int x, int y) {
		this.endx = x;
		this.endy = y;
	}

	public boolean drawingRectangle() {
		return isDrawingRectangle;
	}

	public void startDrawingRectangle() {
		showDrawingRectangle = true;
		isDrawingRectangle = true;
	}

	public void stopDrawingRectangle() {
		isDrawingRectangle = false;
	}

	public void clearSelectionRectangle() {
		showDrawingRectangle = false;
		startx = starty = endx = endy = 0;
		animalRenderer.clearRangeQuery();
		truckRenderer.clearRangeQuery();
		repaint();
	}

	public String rangeQuery(boolean animalSelected, boolean truckSelected)
			throws SQLException {
		String sql = "";
		if (animalSelected)
			sql += animalRenderer.rangeQuery(startx, starty, endx, endy);
		if (truckSelected)
			sql += "\n" + truckRenderer.rangeQuery(startx, starty, endx, endy);
		repaint();
		return sql;
	}

	public String findNearestVaccineSuppliesQuery() throws SQLException {
		Animal selectedAnimal = animalRenderer.getSelectedAnimal();
		StringBuilder r = new StringBuilder();
		if (null != selectedAnimal) {
			truckRenderer.findNearestVaccineSuppliesQuery(startx, starty, endx,
					endy, selectedAnimal, r);
			repaint();
		}
		return r.toString();
	}

	public String findVaccineCoverageQuery() throws SQLException {
		Truck selectedTruck = truckRenderer.getSelectedTruck();
		StringBuilder r = new StringBuilder();
		if (null != selectedTruck) {
			animalRenderer.findVaccineCoverageQuery(startx, starty, endx, endy,
					selectedTruck, r);
			repaint();
		}
		return r.toString();
	}

	private void paintChildren() {
		for (int i = 0; i < this.getComponents().length; i++) {
			Component component = this.getComponent(i);
			component.repaint();
		}
	}

}
