package gui;

import java.awt.GridLayout;

import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class RoomsPanel extends JPanel {
	private JCheckBox roomCheckBox;
	
	public RoomsPanel() {
		setLayout(new GridLayout(0,2));
		roomCheckBox = new JCheckBox("Kitchen");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Dining Room");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Lounge");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Ballroom");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Conservatory");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Hall");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Study");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Library");
		add(roomCheckBox);
		roomCheckBox = new JCheckBox("Billiard Room");
		add(roomCheckBox);
		
		setBorder(new TitledBorder (new EtchedBorder(), "Rooms"));
	}
	

}