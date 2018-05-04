package gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class RoomGuessPanel extends JPanel {
	private JComboBox<String> roomBox;
	
	
	public RoomGuessPanel() {
		roomBox = createComboBox();
		setLayout(new GridLayout(2, 1));
		add(roomBox);	
	
		//ComboListener listener = new ComboListener();
		//peopleBox.addActionListener(listener);
		//toCity.addActionListener(listener);

		setBorder(new TitledBorder (new EtchedBorder(), "Room Guess"));
	}
	
	
	public JComboBox<String> createComboBox() {
		JComboBox<String> combo = new JComboBox<String>();
		combo.addItem("Kitchen");
		combo.addItem("Dining Room");
		combo.addItem("Lounge");
		combo.addItem("Ballroom");
		combo.addItem("Conservatory");
		combo.addItem("Hall");
		combo.addItem("Library");
		combo.addItem("Billiard Room");
		combo.addItem("Study");
		combo.addItem("unsure");
		return combo;

	}

}