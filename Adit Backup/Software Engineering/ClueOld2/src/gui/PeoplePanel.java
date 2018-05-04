package gui;

import java.awt.GridLayout;

import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class PeoplePanel extends JPanel {
	private JCheckBox peopleCheckBox;
	
	public PeoplePanel() {
		
		setLayout(new GridLayout(0,2));
		
		peopleCheckBox = new JCheckBox("Miss Scarlet");
		add(peopleCheckBox);
		peopleCheckBox = new JCheckBox("Colonel Mustard");
		add(peopleCheckBox);
		peopleCheckBox = new JCheckBox("Mrs. White");
		add(peopleCheckBox);
		peopleCheckBox = new JCheckBox("Professor Plum");
		add(peopleCheckBox);
		peopleCheckBox = new JCheckBox("Mr. Green");
		add(peopleCheckBox);
		peopleCheckBox = new JCheckBox("Mrs. Peacock");
		add(peopleCheckBox);
		
		setBorder(new TitledBorder (new EtchedBorder(), "People"));
	}
	

}
