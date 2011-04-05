import java.awt.Color;
import java.awt.LayoutManager;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionAdapter;
import java.sql.SQLException;

import javax.swing.ButtonGroup;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.border.LineBorder;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.GroupLayout;
import org.dyno.visual.swing.layouts.Leading;
import org.dyno.visual.swing.layouts.Trailing;

//VS4E -- DO NOT REMOVE THIS LINE!
public class UI extends JFrame {

	public class MainRenderer {

	}

	private static final long serialVersionUID = 1L;

	private JTextArea nodeInfoLabel;
	private JTextArea sqlQueryLabel;
	private JRadioButton rangeRadionButton;
	private JRadioButton findVaccinationCoveragejRadioButton;
	private JRadioButton findNearestVaccineSuppliesjRadioButton;
	private JPanel jPanel0;
	private JLabel jLabel2;
	private JCheckBox animalCheckBox;
	private JCheckBox jCheckBox1;
	private JPanel jPanel1;
	private JButton submitButton;
	private JButton clearButton;
	private JLabel jLabel3;
	private JLabel jLabel4;
	private JLabel mousecoordsLabel;
	private ImagePanel imagePanel;

	private JRadioButton findVaccinationCoverageRadioButton;

	private JRadioButton nearestVaccineSuppliesRadioButton;

	private JRadioButton rangeRadioButton;

	private static final String PREFERRED_LOOK_AND_FEEL = "javax.swing.plaf.metal.MetalLookAndFeel";

	private AnimalRenderer animalRenderer;

	private TruckRenderer truckRenderer;

	private void initComponents() throws ClassNotFoundException, SQLException {
		setLayout(new GroupLayout());
		add(getJLabel0(), new Constraints(new Leading(2, 133, 10, 10),
				new Leading(0, 80, 12, 12)));
		add(getSqlQueryLabel(), new Constraints(new Leading(0, 133, 12, 12),
				new Leading(76, 80, 12, 12)));
		add(getJLabel3(), new Constraints(new Leading(75, 10, 10),
				new Trailing(12, 382, 382)));
		add(getJLabel4(), new Constraints(new Leading(292, 10, 10),
				new Trailing(12, 353, 353)));
		add(getMousecoordsLabel(), new Constraints(
				new Leading(290, 88, 10, 10), new Trailing(12, 12, 379, 382)));
		add(getJPanel2(), new Constraints(new Leading(156, 504, 10, 10),
				new Leading(3, 300, 10, 10)));
		add(getJPanel0(), new Constraints(new Leading(22, 259, 10, 10),
				new Trailing(45, 99, 103, 315)));
		add(getJPanel1(), new Constraints(new Leading(312, 10, 10),
				new Trailing(45, 15, 315)));
		add(getClearButton(), new Constraints(new Leading(518, 143, 12, 12),
				new Leading(343, 10, 10)));
		add(getsubmitButton(), new Constraints(new Leading(518, 142, 12, 12),
				new Trailing(45, 380, 380)));
		setSize(664, 449);
	}

	private JCheckBox getAnimalCheckBox() {
		if (animalCheckBox == null) {
			animalCheckBox = new JCheckBox();
			animalCheckBox.setText("Animals");
		}
		return animalCheckBox;
	}

	private JLabel getMousecoordsLabel() {
		if (mousecoordsLabel == null) {
			mousecoordsLabel = new JLabel();
			mousecoordsLabel.setText("0,0");
		}
		return mousecoordsLabel;
	}

	private JLabel getJLabel5() {
		if (mousecoordsLabel == null) {
			mousecoordsLabel = new JLabel();
			mousecoordsLabel.setText("0,0");
		}
		return mousecoordsLabel;
	}

	private ImagePanel getJPanel2() throws ClassNotFoundException, SQLException {
		if (imagePanel == null) {
			animalRenderer = new AnimalRenderer();
			truckRenderer = new TruckRenderer();
			imagePanel = new ImagePanel(animalRenderer, truckRenderer, this);
			imagePanel.setFocusable(true);
			imagePanel.setEnabled(true);
			imagePanel.setVisible(true);
			imagePanel.setDoubleBuffered(true);
			imagePanel.setVerifyInputWhenFocusTarget(true);
			imagePanel.setRequestFocusEnabled(true);
			imagePanel.setOpaque(true);
			imagePanel.setLayout(null);
			imagePanel.addAnimals();
			imagePanel.addTrucks();
			imagePanel.addMouseMotionListener(new MouseMotionAdapter() {

				public void mouseMoved(MouseEvent event) {
					if (imagePanel.drawingRectangle()) {
						imagePanel.setEndXY(event.getX(), event.getY());
						imagePanel.repaint();
					}
					imagePanelMouseMotionMouseMoved(event);
				}
			});
			imagePanel.addMouseListener(new MouseListener() {

				@Override
				public void mouseReleased(MouseEvent e) {
					if (!imagePanel.drawingRectangle()) {
						imagePanel.startDrawingRectangle();
						imagePanel.setStartXY(e.getX(), e.getY());
						imagePanel.repaint();
					} else {
						imagePanel.stopDrawingRectangle();
						imagePanel.repaint();
					}

				}

				@Override
				public void mousePressed(MouseEvent e) {
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
					// TODO Auto-generated method stub

				}
			});
		}
		return imagePanel;
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

	private JButton getClearButton() {
		if (clearButton == null) {
			clearButton = new JButton();
			clearButton.setText("Clear");
			clearButton.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					imagePanel.clearSelectionRectangle();
				}
			});
		}
		return clearButton;
	}

	private void populateSqlQueryLabel(String rangeQuery) {
		String sqlText = sqlQueryLabel.getText();
		sqlText += "\n" + rangeQuery;
		sqlQueryLabel.setText(sqlText);
	}

	private JButton getsubmitButton() {
		if (submitButton == null) {
			submitButton = new JButton();
			submitButton.setText("Submit Query");
			submitButton.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					if (rangeRadioButton.isSelected()) {
						try {
							imagePanel.rangeQuery();
						} catch (SQLException e1) {
							e1.printStackTrace();
						}
					}
				}

			});
		}
		return submitButton;
	}

	private JPanel getJPanel1() {
		if (jPanel1 == null) {
			jPanel1 = new JPanel();
			jPanel1.setBorder(new LineBorder(Color.black, 1, false));
			jPanel1.setLayout(new GroupLayout());
			jPanel1.add(getAnimalCheckBox(), new Constraints(new Leading(15, 8,
					8), new Leading(33, 8, 8)));
			jPanel1.add(getJCheckBox1(), new Constraints(new Leading(15, 8, 8),
					new Leading(64, 10, 10)));
			jPanel1.add(getJLabel2(), new Constraints(new Leading(19, 10, 10),
					new Leading(12, 12, 12)));
		}
		return jPanel1;
	}

	private JCheckBox getJCheckBox1() {
		if (jCheckBox1 == null) {
			jCheckBox1 = new JCheckBox();
			jCheckBox1.setText("Trucks");
		}
		return jCheckBox1;
	}

	private JCheckBox getJCheckBox0() {
		if (animalCheckBox == null) {
			animalCheckBox = new JCheckBox();
			animalCheckBox.setText("jCheckBox0");
		}
		return animalCheckBox;
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
			jPanel0.setBorder(new LineBorder(Color.black, 1, false));
			jPanel0.setLayout(new GroupLayout());
			ButtonGroup buttonGroup = new ButtonGroup();
			findVaccinationCoverageRadioButton = getfindVaccinationCoverageRadioButton();
			nearestVaccineSuppliesRadioButton = getFindNearestVaccineSuppliesRadioButton();
			rangeRadioButton = getRangeRadioButton();

			buttonGroup.add(rangeRadioButton);
			buttonGroup.add(findVaccinationCoverageRadioButton);
			buttonGroup.add(nearestVaccineSuppliesRadioButton);

			jPanel0.add(findVaccinationCoverageRadioButton, new Constraints(
					new Leading(5, 8, 8), new Leading(70, 10, 10)));

			jPanel0.add(nearestVaccineSuppliesRadioButton, new Constraints(
					new Leading(5, 8, 8), new Leading(36, 8, 8)));

			jPanel0.add(rangeRadioButton, new Constraints(new Leading(5, 8, 8),
					new Leading(12, 20, 8, 8)));
		}
		return jPanel0;
	}

	private JRadioButton getFindNearestVaccineSuppliesRadioButton() {
		if (findNearestVaccineSuppliesjRadioButton == null) {
			findNearestVaccineSuppliesjRadioButton = new JRadioButton();
			findNearestVaccineSuppliesjRadioButton
					.setText("Find Nearest Vaccine Supplies");
		}
		return findNearestVaccineSuppliesjRadioButton;
	}

	private JRadioButton getfindVaccinationCoverageRadioButton() {
		if (findVaccinationCoveragejRadioButton == null) {
			findVaccinationCoveragejRadioButton = new JRadioButton();
			findVaccinationCoveragejRadioButton
					.setText("Find Vaccination Coverage");
		}
		return findVaccinationCoveragejRadioButton;
	}

	private JRadioButton getRangeRadioButton() {
		if (rangeRadionButton == null) {
			rangeRadionButton = new JRadioButton();
			rangeRadionButton.setSelected(true);
			rangeRadionButton.setText("Range");
		}
		return rangeRadionButton;
	}

	private JTextArea getSqlQueryLabel() {
		if (sqlQueryLabel == null) {
			sqlQueryLabel = new JTextArea();
			sqlQueryLabel.setText("Sql Query Here");
		}
		return sqlQueryLabel;
	}

	private JTextArea getJLabel0() {
		if (nodeInfoLabel == null) {
			nodeInfoLabel = new JTextArea();
			nodeInfoLabel.setText("Node Info Here");
		}
		return nodeInfoLabel;
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

	public UI() throws ClassNotFoundException, SQLException {
		initComponents();
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
				UI frame = null;
				try {
					frame = new UI();
				} catch (ClassNotFoundException e) {
					e.printStackTrace();
				} catch (SQLException e) {
					e.printStackTrace();
				}
				frame.setDefaultCloseOperation(UI.EXIT_ON_CLOSE);
				frame.setTitle("UI");
				frame.getContentPane().setPreferredSize(frame.getSize());
				frame.pack();
				frame.setLocationRelativeTo(null);
				frame.setVisible(true);
			}
		});
	}

	private void imagePanelMouseMotionMouseMoved(MouseEvent event) {
		Point mousePoint = event.getPoint();
		mousecoordsLabel.setText(mousePoint.x + "," + mousePoint.y);
	}

	public void updateTruckInfo(Truck truck) {
		StringBuilder builder = new StringBuilder();
		builder.append("Name:" + truck.name());
		builder.append("\r\n");
		builder.append("Location:" + truck.x() + "  , " + truck.y());
		nodeInfoLabel.setText(builder.toString() + "\n" + "bbb");
	}

	public void updateAnimalInfo(Animal animal) {
		StringBuilder builder = new StringBuilder();
		builder.append("Name:" + animal.name());
		builder.append("\r\n");
		builder.append("Location:" + animal.x() + "  , " + animal.y());
		nodeInfoLabel.setText(builder.toString() + "\n");

	}

}
