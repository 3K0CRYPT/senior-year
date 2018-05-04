package gui;

import java.awt.GridLayout;

import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class WeaponsPanel extends JPanel {
	private JCheckBox weaponCheckBox;
	
	public WeaponsPanel() {
		setLayout(new GridLayout(0,2));
		weaponCheckBox = new JCheckBox("Candlestick");
		add(weaponCheckBox);
		weaponCheckBox = new JCheckBox("Knife");
		add(weaponCheckBox);
		weaponCheckBox = new JCheckBox("Lead Pope");
		add(weaponCheckBox);
		weaponCheckBox = new JCheckBox("Revolver");
		add(weaponCheckBox);
		weaponCheckBox = new JCheckBox("Rope");
		add(weaponCheckBox);
		weaponCheckBox = new JCheckBox("Wrench");
		add(weaponCheckBox);
		
		setBorder(new TitledBorder (new EtchedBorder(), "Weapons"));
	}
	

}
