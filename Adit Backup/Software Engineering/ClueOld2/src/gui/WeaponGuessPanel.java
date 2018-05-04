package gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class WeaponGuessPanel extends JPanel {
	private JComboBox<String> weaponBox;
	
	
	public WeaponGuessPanel() {
		weaponBox = createComboBox();
		setLayout(new GridLayout(2, 1));
		add(weaponBox);	
	
		//ComboListener listener = new ComboListener();
		//peopleBox.addActionListener(listener);
		//toCity.addActionListener(listener);

		setBorder(new TitledBorder (new EtchedBorder(), "Weapon Guess"));
	}
	
	
	public JComboBox<String> createComboBox() {
		JComboBox<String> combo = new JComboBox<String>();
		combo.addItem("Candlestick");
		combo.addItem("Knife");
		combo.addItem("Lead Pipe");
		combo.addItem("Revolver");
		combo.addItem("Rope");
		combo.addItem("Wrench");
		combo.addItem("unsure");
		return combo;

	}

}