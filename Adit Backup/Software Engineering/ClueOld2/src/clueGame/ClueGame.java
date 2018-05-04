package clueGame;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

import gui.DetectiveNotes;

public class ClueGame extends JFrame {
	public static final int WIDTH = 10;
	public static final int HEIGHT = 750;
	public static final int SQUARE_SIZE = 40;
	private Board clueBoard;
	public ClueGame(){
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Clue Game");
		clueBoard = new Board();
		clueBoard = new Board("ourClueLayout.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		clueBoard.initialize();
		setSize(SQUARE_SIZE * (clueBoard.numColumns + 1) - (int)(0.5*SQUARE_SIZE), SQUARE_SIZE * (clueBoard.numRows + 1) + (int)(0.5*SQUARE_SIZE));
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		menuBar.add(createFileMenu());
		
		add(clueBoard, BorderLayout.CENTER);
	}
	

	private JMenu createFileMenu() {
		JMenu menu = new JMenu("File");
		menu.add(createFileDetectiveNotes());
		menu.add(createFileExitItem());
		return menu;
	}

	private JMenuItem createFileDetectiveNotes() {
		JMenuItem item = new JMenuItem("Detective Notes");
		class MenuItemListener implements ActionListener {
			public void actionPerformed(ActionEvent e) {
				DetectiveNotes detective = new DetectiveNotes();
				detective.setVisible(true);
			}
		}
		item.addActionListener(new MenuItemListener());

		return item;
	}
	private JMenuItem createFileExitItem()
	{
		JMenuItem item = new JMenuItem("Exit");
		class MenuItemListener implements ActionListener {
			public void actionPerformed(ActionEvent e)
			{
				System.exit(0);
			}
		}
		item.addActionListener(new MenuItemListener());

		return item;
	}


	public static void main(String[] args) {
		ClueGame clueGame = new ClueGame();
		clueGame.setVisible(true);
	}
}
