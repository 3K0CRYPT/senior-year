package gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;


public class DetectiveNotes extends JDialog {
	public DetectiveNotes() {
		setSize(new Dimension(550, 600));
		setLayout(new GridLayout(0,2));
		setTitle("Detective Notes");
		//setDefaultCloseOperation(JDialog.EXIT_ON_CLOSE);		
		// Create DisplayPanel first
		//DisplayPanel dp = new DisplayPanel();
		//add(dp, BorderLayout.SOUTH);
		
		PeoplePanel pPanel = new PeoplePanel();
		add(pPanel, BorderLayout.CENTER);
		PersonGuessPanel pgPanel = new PersonGuessPanel();
		add(pgPanel, BorderLayout.CENTER);
		RoomsPanel rPanel = new RoomsPanel();
		add(rPanel, BorderLayout.EAST);
		RoomGuessPanel rgPanel = new RoomGuessPanel();
		add(rgPanel, BorderLayout.CENTER);
		WeaponsPanel wPanel = new WeaponsPanel();
		add(wPanel, BorderLayout.EAST);
		WeaponGuessPanel wgPanel = new WeaponGuessPanel();
		add(wgPanel, BorderLayout.CENTER);
	}

	//public static void main(String[] args) {
	//	DetectiveNotes gui = new DetectiveNotes();
	//	gui.setVisible(true);
	//}
}