package gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class PersonGuessPanel extends JPanel {
	private JComboBox<String> peopleBox;
	
	//TODO: Read in meanu items from file
	
	public PersonGuessPanel() {
		peopleBox = createComboBox();
		setLayout(new GridLayout(2, 1));
		add(peopleBox);	
	
		setBorder(new TitledBorder (new EtchedBorder(), "Person Guess"));
	}
	
	
	public JComboBox<String> createComboBox() {
		JComboBox<String> combo = new JComboBox<String>();
		combo.addItem("Miss Scarlet");
		combo.addItem("Colonel Mustard");
		combo.addItem("Mrs. White");
		combo.addItem("Professor Plum");
		combo.addItem("Mr. Green");
		combo.addItem("Mrs. Peacock");
		combo.addItem("unsure");
		return combo;

	}

}
