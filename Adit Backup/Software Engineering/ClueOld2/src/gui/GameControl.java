package gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class GameControl extends JPanel {
	private JTextField name;
	
	public GameControl() {
		setLayout(new GridLayout(2,0));
		//GridBagConstraints constraints = new GridBagConstraints();
        //constraints.anchor = GridBagConstraints.WEST;
        //constraints.insets = new Insets(10, 10, 10, 10);
        
		JPanel panel = new JPanel();
		panel.add(createTurnPanel());
		panel.add(createPlayerPanel());
		panel.add(createAccusationPanel());
		panel.setLayout(new GridLayout(1,0));
		add(panel, BorderLayout.CENTER);
		
		panel = new JPanel();
		panel.add(createDiePanel());
		panel.add(createGuessPanel());
		panel.add(createResultPanel());
		add(panel, BorderLayout.SOUTH);
		
	}
	
	private JPanel createTurnPanel() {
	 	JPanel panel = new JPanel();
	 	JLabel nameLabel = new JLabel("Whose turn?");
		name = new JTextField(16);
		name.setEditable(false);
		panel.add(nameLabel);
		panel.add(name);
		return panel;
	}
	
	private JPanel createDiePanel() {
	 	JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,2));
	 	JLabel nameLabel = new JLabel("Roll");
		name = new JTextField(4);
		name.setEditable(false);
		
		panel.add(nameLabel);
		panel.add(name);
		panel.setBorder(new TitledBorder (new EtchedBorder(), "Die"));
		return panel;
	}
	
	private JPanel createGuessPanel() {
	 	JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(2,1));
	 	JLabel nameLabel = new JLabel("Guess");
		name = new JTextField(30);
		panel.add(nameLabel);
		name.setEditable(false);
		panel.add(name);
		panel.setBorder(new TitledBorder (new EtchedBorder(), "Guess"));
		return panel;
	}
	
	private JPanel createResultPanel() {
	 	JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,1));
	 	JLabel nameLabel = new JLabel("Response");
		name = new JTextField(10);
		panel.add(nameLabel);
		name.setEditable(false);
		panel.add(name);
		panel.setBorder(new TitledBorder (new EtchedBorder(), "Guess Result"));
		return panel;
	}
	
	
	private JPanel createPlayerPanel() {
		JButton player = new JButton("Next player");
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,2));
		panel.add(player);
		return panel;
	}
	
	private JPanel createAccusationPanel() {
		JButton accusation = new JButton("Make an accusation");
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,1));
		panel.add(accusation);
		return panel;
	}
	
	
	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("Clue Game");
		frame.setSize(800, 200);
		GameControl gui = new GameControl();
		frame.add(gui);
		frame.setVisible(true);
	}

}
