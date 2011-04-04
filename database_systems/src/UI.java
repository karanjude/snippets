import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

import org.dyno.visual.swing.layouts.Constraints;
import org.dyno.visual.swing.layouts.GroupLayout;
import org.dyno.visual.swing.layouts.Leading;
import org.dyno.visual.swing.layouts.Trailing;

//VS4E -- DO NOT REMOVE THIS LINE!
public class UI extends JFrame {

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
	private JLabel mousecoordsLabel;
	private ImagePanel imagePanel;

	private static final String PREFERRED_LOOK_AND_FEEL = "javax.swing.plaf.metal.MetalLookAndFeel";

	private void initComponents() {
		setLayout(new GroupLayout());
		add(getJLabel0(), new Constraints(new Leading(2, 133, 10, 10), new Leading(0, 80, 12, 12)));
		add(getJLabel1(), new Constraints(new Leading(0, 102, 12, 12), new Leading(76, 67, 10, 10)));
		add(getJLabel3(), new Constraints(new Leading(75, 10, 10), new Trailing(12, 382, 382)));
		add(getJLabel4(), new Constraints(new Leading(292, 10, 10), new Trailing(12, 353, 353)));
		add(getMousecoordsLabel(), new Constraints(new Leading(290, 88, 10, 10), new Trailing(12, 12, 379, 382)));
		add(getJButton1(), new Constraints(new Leading(518, 142, 12, 12), new Trailing(30, 358, 358)));
		add(getJButton0(), new Constraints(new Leading(517, 143, 12, 12), new Trailing(67, 15, 271)));
		add(getJPanel1(), new Constraints(new Leading(312, 10, 10), new Trailing(39, 103, 15, 271)));
		add(getJPanel2(), new Constraints(new Leading(156, 504, 10, 10), new Leading(3, 300, 10, 10)));
		add(getJPanel0(), new Constraints(new Leading(22, 259, 10, 10), new Trailing(45, 99, 103, 315)));
		setSize(664, 449);
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

	private ImagePanel getJPanel2() {
		if (imagePanel == null) {
			imagePanel = new ImagePanel();
			imagePanel.setFocusable(true);
			imagePanel.setEnabled(true);
			imagePanel.setVisible(true);
			imagePanel.setDoubleBuffered(true);
			imagePanel.setVerifyInputWhenFocusTarget(true);
			imagePanel.setRequestFocusEnabled(true);
			imagePanel.setOpaque(true);
			imagePanel.setLayout(new GroupLayout());
			imagePanel.addMouseMotionListener(new MouseMotionAdapter() {
	
				public void mouseMoved(MouseEvent event) {
					imagePanelMouseMotionMouseMoved(event);
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
			jPanel1.add(getJCheckBox0(), new Constraints(new Leading(15, 8, 8),
					new Leading(33, 8, 8)));
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
			jPanel0.add(getJRadioButton2(), new Constraints(new Leading(5, 8, 8), new Leading(70, 10, 10)));
			jPanel0.add(getJRadioButton1(), new Constraints(new Leading(5, 8, 8), new Leading(36, 8, 8)));
			jPanel0.add(getJRadioButton0(), new Constraints(new Leading(5, 8, 8), new Leading(12, 20, 8, 8)));
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

	public UI() {
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
				UI frame = new UI();
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

}
