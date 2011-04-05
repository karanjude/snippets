import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

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
	private final AnimalRenderer renderer;
	private final TruckRenderer truckRenderer;
	private final UI ui;
	private int startx;
	private int starty;
	private int endx;
	private int endy;
	private boolean isDrawingRectangle;

	public ImagePanel(AnimalRenderer animalRenderer,
			TruckRenderer truckRenderer, UI ui) {
		this.ui = ui;
		this.renderer = animalRenderer;
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
		if (isDrawingRectangle) {
			g.setColor(Color.BLUE);
			int width = Math.abs(endx - startx);
			int height = Math.abs(endy - starty);
			g.drawRect(startx, starty, width, height);
			System.out.println(startx + " " + starty + " " + endx + " " + endy);
		}
		// renderer.render(g);
		// truckRenderer.render(g);

		// g.fillRect(50, 50, 70, 70);
	}

	public void addAnimals() {
		this.renderer.addAnimals(this);
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
		isDrawingRectangle = true;
	}

	public void stopDrawingRectangle() {
		isDrawingRectangle = false;
	}

}

// VS4E -- DO NOT REMOVE THIS LINE!
public class MainUI extends JFrame {

	private static final long serialVersionUID = 1L;
	private JLabel jLabel0;
	private JLabel jLabel1;
	private JRadioButton jRadioButton0;
	private JRadioButton jRadioButton2;
	private JRadioButton jRadioButton1;
	private JPanel jPanel0;
	private JLabel jLabel2;
	private JCheckBox jCheckBox0;
	private JCheckBox jCheckBox1;
	private JPanel jPanel1;
	private JButton jButton1;
	private JButton jButton0;
	private JLabel jLabel3;
	private JLabel jLabel4;
	private JLabel jLabel5;
	// private ImagePanel imagePanel;
	private static final String PREFERRED_LOOK_AND_FEEL = "javax.swing.plaf.metal.MetalLookAndFeel";

	public MainUI() {
		initComponents();
	}

	private void initComponents() {
		setLayout(new GroupLayout());
		add(getJLabel0(), new Constraints(new Leading(2, 133, 10, 10),
				new Leading(0, 80, 12, 12)));
		add(getJLabel1(), new Constraints(new Leading(0, 102, 12, 12),
				new Leading(76, 67, 10, 10)));
		add(getJPanel0(), new Constraints(new Leading(5, 137, 10, 10),
				new Leading(271, 99, 10, 10)));
		add(getJPanel1(), new Constraints(new Leading(144, 147, 10, 10),
				new Leading(270, 100, 12, 12)));
		add(getJButton1(), new Constraints(new Leading(309, 12, 12),
				new Leading(316, 12, 12)));
		add(getJButton0(), new Constraints(new Bilateral(309, 0, 71),
				new Leading(279, 10, 10)));
		add(getJLabel3(), new Constraints(new Leading(75, 10, 10),
				new Trailing(12, 382, 382)));
		add(getJLabel4(), new Constraints(new Leading(292, 10, 10),
				new Trailing(12, 353, 353)));
		add(getJLabel5(), new Constraints(new Leading(290, 88, 10, 10),
				new Trailing(12, 12, 379, 382)));
		// add(getJPanel2(), new Constraints(new Leading(120, 306, 10, 10),
		// new Leading(3, 256, 39, 39)));
		setSize(434, 406);
	}

	// private JPanel getJPanel2() {
	// if (imagePanel == null) {
	// imagePanel = new ImagePanel();
	// imagePanel.setLayout(new GroupLayout());
	// }
	// return imagePanel;
	// }

	private JLabel getJLabel5() {
		if (jLabel5 == null) {
			jLabel5 = new JLabel();
			jLabel5.setText("0,0");
		}
		return jLabel5;
	}

	private JLabel getJLabel4() {
		if (jLabel4 == null) {
			jLabel4 = new JLabel();
		}
		return jLabel4;
	}

	private JLabel getJLabel3() {
		if (jLabel3 == null) {
			jLabel3 = new JLabel();
			jLabel3.setText("Current Coordinates (X,Y)");
		}
		return jLabel3;
	}

	private JButton getJButton0() {
		if (jButton0 == null) {
			jButton0 = new JButton();
			jButton0.setText("Clear");
		}
		return jButton0;
	}

	private JButton getJButton1() {
		if (jButton1 == null) {
			jButton1 = new JButton();
			jButton1.setText("Submit Query");
		}
		return jButton1;
	}

	private JPanel getJPanel1() {
		if (jPanel1 == null) {
			jPanel1 = new JPanel();
			jPanel1.setLayout(new GroupLayout());
			jPanel1.add(getJLabel2(), new Constraints(new Leading(12, 12, 12),
					new Leading(10, 10, 10)));
			jPanel1.add(getJCheckBox0(), new Constraints(new Leading(15, 8, 8),
					new Leading(33, 8, 8)));
			jPanel1.add(getJCheckBox1(), new Constraints(new Leading(15, 8, 8),
					new Leading(64, 10, 10)));
		}
		return jPanel1;
	}

	private JCheckBox getJCheckBox1() {
		if (jCheckBox1 == null) {
			jCheckBox1 = new JCheckBox();
			jCheckBox1.setText("jCheckBox1");
		}
		return jCheckBox1;
	}

	private JCheckBox getJCheckBox0() {
		if (jCheckBox0 == null) {
			jCheckBox0 = new JCheckBox();
			jCheckBox0.setText("jCheckBox0");
		}
		return jCheckBox0;
	}

	private JLabel getJLabel2() {
		if (jLabel2 == null) {
			jLabel2 = new JLabel();
			jLabel2.setText("Active Features");
		}
		return jLabel2;
	}

	private JPanel getJPanel0() {
		if (jPanel0 == null) {
			jPanel0 = new JPanel();
			jPanel0.setLayout(new GroupLayout());
			jPanel0.add(getJRadioButton0(), new Constraints(new Leading(5, 10,
					10), new Leading(8, 8, 8)));
			jPanel0.add(getJRadioButton2(), new Constraints(
					new Leading(5, 8, 8), new Leading(70, 10, 10)));
			jPanel0.add(getJRadioButton1(), new Constraints(
					new Leading(5, 8, 8), new Leading(41, 10, 10)));
		}
		return jPanel0;
	}

	private JRadioButton getJRadioButton1() {
		if (jRadioButton1 == null) {
			jRadioButton1 = new JRadioButton();
			jRadioButton1.setSelected(true);
			jRadioButton1.setText("Find Nearest Vaccine Supplies");
		}
		return jRadioButton1;
	}

	private JRadioButton getJRadioButton2() {
		if (jRadioButton2 == null) {
			jRadioButton2 = new JRadioButton();
			jRadioButton2.setSelected(true);
			jRadioButton2.setText("Find Vaccination Coverage");
		}
		return jRadioButton2;
	}

	private JRadioButton getJRadioButton0() {
		if (jRadioButton0 == null) {
			jRadioButton0 = new JRadioButton();
			jRadioButton0.setSelected(true);
			jRadioButton0.setText("Range");
		}
		return jRadioButton0;
	}

	private JLabel getJLabel1() {
		if (jLabel1 == null) {
			jLabel1 = new JLabel();
			jLabel1.setText("jLabel1");
		}
		return jLabel1;
	}

	private JLabel getJLabel0() {
		if (jLabel0 == null) {
			jLabel0 = new JLabel();
			jLabel0.setText("jLabel0");
		}
		return jLabel0;
	}

	private static void installLnF() {
		try {
			String lnfClassname = PREFERRED_LOOK_AND_FEEL;
			if (lnfClassname == null)
				lnfClassname = UIManager.getCrossPlatformLookAndFeelClassName();
			UIManager.setLookAndFeel(lnfClassname);
		} catch (Exception e) {
			System.err.println("Cannot install " + PREFERRED_LOOK_AND_FEEL
					+ " on this platform:" + e.getMessage());
		}
	}

	/**
	 * Main entry of the class. Note: This class is only created so that you can
	 * easily preview the result at runtime. It is not expected to be managed by
	 * the designer. You can modify it as you like.
	 */
	public static void main(String[] args) {
		installLnF();
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				MainUI frame = new MainUI();
				frame.setDefaultCloseOperation(MainUI.EXIT_ON_CLOSE);
				frame.setTitle("MainUI");
				frame.getContentPane().setPreferredSize(frame.getSize());
				frame.pack();
				frame.setLocationRelativeTo(null);
				frame.setVisible(true);
			}
		});
	}

}
