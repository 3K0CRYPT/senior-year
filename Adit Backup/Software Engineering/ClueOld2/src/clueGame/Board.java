package clueGame;

import java.awt.Color;
import java.awt.Graphics;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

import javax.swing.JPanel;

public class Board extends JPanel{
	public static int numRows;
	public static int numColumns;
	public static int BOARD_SIZE = 50;
	public static int NUM_PLAYERS = 6;
	public static int NUM_CARDS = 21;
	BoardCell[][] board;
	static Map<Character, String> rooms;

	Map<BoardCell, LinkedList<BoardCell>> adjMatrix;
	private Set<BoardCell> visited;
	Set<BoardCell> targets;
	String boardConfigFile;
	String roomConfigFile;
	String cardConfigFile;

	public static ArrayList<Card> cards;
	public ArrayList<Card> cardsSeen;
	public ArrayList<Player> players;	
	public Solution solution;


	public Board() {
		this.boardConfigFile = "ClueLayout.csv";
		this.roomConfigFile = "ClueLegend.txt";
		this.cardConfigFile = "PlayerandCardConfig.txt";
	}

	public Board(String boardFileName, String roomFileName) {
		this.boardConfigFile = boardFileName;
		this.roomConfigFile = roomFileName;
		this.cardConfigFile = "PlayerandCardConfig.txt";
	}

	public Board(String boardFileName, String roomFileName, String cardConfigFile) {
		this.boardConfigFile = boardFileName;
		this.roomConfigFile = roomFileName;
		this.cardConfigFile = cardConfigFile;
	}

	// initialize() will call loadRoomConfig() and loadBoardConfig()
	public void initialize() {
		rooms = new HashMap<Character, String>();
		visited = new HashSet<BoardCell>();
		targets = new HashSet<BoardCell>();
		adjMatrix = new HashMap<BoardCell, LinkedList<BoardCell>>();
		cards = new ArrayList<Card>();
		cardsSeen = new ArrayList<Card>();
		players = new ArrayList<Player>();		
		solution = new Solution();
		try {
			loadRoomConfig();
		}
		catch (BadConfigFormatException b) {
			System.out.println("BadConfigFormatException");
		}
		catch (FileNotFoundException f) {
			System.out.println("FileNotFoundException");
		}

		try {
			loadBoardConfig();
		}
		catch (FileNotFoundException | BadConfigFormatException e) {
			e.printStackTrace();
		}
		try {
			loadConfigFiles();
		} catch (FileNotFoundException | BadConfigFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		calcAdjacencies();
	}

	public void paintComponent(Graphics g){
		super.paintComponent(g);	
		for(int i = 0; i < numRows; i++){
			for(int j = 0; j < numColumns; j++){
				board[i][j].draw(g);
				repaint();
			}
		}
		for(Player p : players){
			p.draw(g);
		}
	}

	public void loadRoomConfig() throws BadConfigFormatException, FileNotFoundException {
		FileReader reader = new FileReader(roomConfigFile);
		@SuppressWarnings("resource")
		Scanner scanner = new Scanner(reader);
		while (scanner.hasNextLine()) {
			String next = scanner.nextLine();
			String[] parts = next.split(",");

			if (parts.length != 3) {
				throw new BadConfigFormatException();
			}

			rooms.put(parts[0].charAt(0), parts[1].substring(1));
		}
		scanner.close();
	}

	public void loadBoardConfig() throws BadConfigFormatException, FileNotFoundException {
		board = new BoardCell[BOARD_SIZE][BOARD_SIZE];
		numColumns = 0;
		numRows = 0;
		System.out.println(board.length);
		FileReader reader = new FileReader(boardConfigFile);
		@SuppressWarnings("resource")
		Scanner scanner = new Scanner(reader);
		int r = 0; int c = 0;
		while (scanner.hasNextLine()) {
			String next = scanner.nextLine();
			String[] parts = next.split(",");

			if (numColumns == 0) {numColumns = parts.length;}
			else if (numColumns != parts.length) { throw new BadConfigFormatException();}

			for (int i = 0; i < parts.length; ++i) {
				//System.out.println(parts[i].charAt(0));
				//System.out.println("Cell: " + x + ", " + y);
				//System.out.println("r = " + r + ", c = " + c);

				if (!rooms.containsKey(parts[i].charAt(0))) {
					throw new BadConfigFormatException();
				}

				board[r][c] = new BoardCell(r, c, parts[i].charAt(0));
				if (Character.toString(parts[i].charAt(0)).equals("W")) {
					board[r][c].setWalkway(true);
				}
				else {
					board[r][c].setRoom(true);
				}

				if (parts[i].length() > 1 && parts[i].charAt(1) != 'N') {
					board[r][c].setDoorway(true);
					if (parts[i].charAt(1) == 'U') {
						board[r][c].setDoorDirection(DoorDirection.UP);
					}
					if (parts[i].charAt(1) == 'D') {
						board[r][c].setDoorDirection(DoorDirection.DOWN);
					}
					if (parts[i].charAt(1) == 'L') {
						board[r][c].setDoorDirection(DoorDirection.LEFT);
					}
					if (parts[i].charAt(1) == 'R') {
						board[r][c].setDoorDirection(DoorDirection.RIGHT);
					}
				}
				if (parts[i].length() > 1 &&  parts[i].charAt(1) == 'N') { 
					board[r][c].setNameBoolean(true);
				}
				
				c++;
			}			
			c = 0;
			r++;
			numRows++;			
		}
		scanner.close();
	}

	public void calcAdjacencies() {

		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numColumns; ++j) {

				BoardCell currentCell = getCellAt(i, j);
				LinkedList<BoardCell> currentAdjacentCells = new LinkedList<BoardCell>();

				// For doorway cells
				if (currentCell.isDoorway()) {
					if(currentCell.getDoorDirection().equals(DoorDirection.UP)) {
						currentAdjacentCells.add(getCellAt(i - 1, j));
					}
					if(currentCell.getDoorDirection().equals(DoorDirection.DOWN)) {
						currentAdjacentCells.add(getCellAt(i + 1, j));
					}
					if(currentCell.getDoorDirection().equals(DoorDirection.LEFT)) {
						currentAdjacentCells.add(getCellAt(i, j - 1));
					}
					if(currentCell.getDoorDirection().equals(DoorDirection.RIGHT)) {
						currentAdjacentCells.add(getCellAt(i, j + 1));
					}
					adjMatrix.put(currentCell, currentAdjacentCells);
					continue;
				}

				if (i < numRows - 1) {
					BoardCell downCell = getCellAt(i + 1, j);
					if ((!currentCell.isRoom() || currentCell.isDoorway()) && downCell.isWalkway() || (downCell.isDoorway() && !currentCell.isDoorway() && downCell.getDoorDirection().equals(DoorDirection.UP))) {
						currentAdjacentCells.add(getCellAt(i + 1, j));
					}
				}
				if (i > 0) {
					BoardCell upCell = getCellAt(i - 1, j);
					if ((!currentCell.isRoom() || currentCell.isDoorway()) && upCell.isWalkway() || (upCell.isDoorway() && !currentCell.isDoorway() && upCell.getDoorDirection().equals(DoorDirection.DOWN))) {
						currentAdjacentCells.add(getCellAt(i - 1, j));
					}
				}
				if (j < numColumns - 1) {
					BoardCell rightCell = getCellAt(i, j + 1);
					if ((!currentCell.isRoom() || currentCell.isDoorway()) && rightCell.isWalkway() || (rightCell.isDoorway() && !currentCell.isDoorway() && rightCell.getDoorDirection().equals(DoorDirection.LEFT))) {
						currentAdjacentCells.add(getCellAt(i, j + 1));
					}
				}
				if (j > 0) {
					BoardCell leftCell = getCellAt(i, j - 1);
					if ((!currentCell.isRoom() || currentCell.isDoorway()) && leftCell.isWalkway() || (leftCell.isDoorway() && !currentCell.isDoorway() && leftCell.getDoorDirection().equals(DoorDirection.RIGHT))) {
						currentAdjacentCells.add(getCellAt(i, j - 1));
					}
				}

				adjMatrix.put(currentCell, currentAdjacentCells);
			}
		}
	}


	public LinkedList<BoardCell> getAdjList(int row, int column) {
		return adjMatrix.get(getCellAt(row, column));
	}

	public BoardCell getCellAt(int row, int column) {
		return board[row][column];
	}

	public void calcTargets(int row, int column, int steps) {
		targets.clear();
		findTargets(row, column, steps);
	}

	public void findTargets(int row, int column, int steps) {
		BoardCell startCell = getCellAt(row, column);
		visited.add(startCell);
		findAllTargets(startCell, steps);
		visited.remove(startCell);
	}

	public void findAllTargets(BoardCell startCell, int pathLength) {
		// Get cells adjacent to the current one
		LinkedList<BoardCell> adjCells = new LinkedList<BoardCell>(getAdjList(startCell.getRow(), startCell.getColumn()));
		for (BoardCell c: visited) {
			if (adjCells.contains(c)) {
				adjCells.remove(c);
			}
		}

		for (BoardCell c: adjCells) {
			visited.add(c);
			if (pathLength == 1 || c.isDoorway()) {
				targets.add(c);
			}
			else {
				findTargets(c.getRow(), c.getColumn(), pathLength - 1);
			}
			visited.remove(c);
		}
	}

	public Set<BoardCell> getTargets() {
		return targets;
	}

	public static Map<Character, String> getRooms() {
		return rooms;
	}

	public int getNumRows() {
		return numRows;
	}

	public int getNumColumns() {
		return numColumns;
	}


	public void loadConfigFiles() throws FileNotFoundException, BadConfigFormatException {
		FileReader file = new FileReader(cardConfigFile);
		Scanner sc = new Scanner(file);
		String[] config = new String[NUM_CARDS];
		int i = 0;
		while(sc.hasNext()){
			config[i] = sc.nextLine();
			i++; // this will be rows
		}
		for (int j = 0; j < i;  j++) {
			Character cardType = config[j].charAt(0);
			if(cardType == 'P'){
				String s = config[j];
				String[] tokens = s.split("/");
				//token[1] is name, 2 is row, 3 is column, and 4 is a string name of the color.
				//The possible colors are white, red, green, Yellow, blue, and purple so we must account for each of those.
				if(j == 0){
					HumanPlayer player = new HumanPlayer(tokens[1], Integer.parseInt(tokens[2]), Integer.parseInt(tokens[3]), convertColor(tokens[4]));
					players.add(player);
				}
				else{
					ComputerPlayer player = new ComputerPlayer(tokens[1],Integer.parseInt(tokens[2]),Integer.parseInt(tokens[3]),convertColor(tokens[4]));
					players.add(player);
				}
				

				cards.add(new Card(tokens[1], cardType));
			}
			else{
				if (-1 == config[j].indexOf(",", 2) || config[j].length() < config[j].indexOf(",", 2)) {
					throw new BadConfigFormatException("There was an error configuring the following line in the config file:\n" + config[j]);
				}
				else {
					String stringTemp = config[j].substring(3, config[j].indexOf(",", 2));
					cards.add(new Card(stringTemp, cardType));
				}
			}
		}

		//The following will deal the cards to the Case file and then will deal the remaining cards to the players.		
		ArrayList<Card> tempcards = new ArrayList<Card>(cards); 
		Random rand = new Random();
		while(true){
			int n = rand.nextInt(21);
			if(tempcards.get(n).getType() == CardType.PERSON){
				solution.setPerson(cards.get(n).getCardName());
				break;
			}
		}
		while(true){
			int n = rand.nextInt(21);
			if(cards.get(n).getType() == CardType.ROOM){				
				solution.setRoom(cards.get(n).getCardName());
				break;
			}
		}
		while(true){
			int n = rand.nextInt(21);
			if(cards.get(n).getType() == CardType.WEAPON){				
				solution.setWeapon(cards.get(n).getCardName());
				break;
			}
		}

		tempcards = new ArrayList<Card>(cards);
		for (int i1 = 0; i1<tempcards.size(); i1++) {
			if (solution.getPerson().equals(tempcards.get(i1).getCardName()) || solution.getRoom().equals(tempcards.get(i1).getCardName()) || solution.getWeapon().equals(tempcards.get(i1).getCardName())) {
				continue;
			}
			players.get(i1 % 6).cards.add(tempcards.get(i1));
		}
	}

	public void selectAnswer() {

	}

	public Card handleSuggestion(Solution suggestion, String accusingPlayer, BoardCell clicked) {

		int counter = 0;
		int startPlayer = 0;
		Card finalReturnCard = null;
		//ArrayList<Player> playersTemp = players;
		for (Player p : players) {
			if (p.getPlayerName() == accusingPlayer) {
				counter++;
				break;
			}
			counter++;
		}
		for (int counter2 = counter; counter2 < counter + 5; counter2++) {
			finalReturnCard = this.players.get(counter2%6).disproveSuggestion(suggestion);
			if (finalReturnCard != null) {
				cardsSeen.add(finalReturnCard);
				return finalReturnCard;
			}
		}

		return finalReturnCard;
	}

	public boolean checkAccusation(Solution accusation) {
		if(solution.checkTheSame(accusation)){
			return true;
		}
		else {
			return false;
		}
	}

	public Color convertColor(String strColor) {
		Color color; 
		try {     
			// We can use reflection to convert the string to a color
			Field field = Class.forName("java.awt.Color").getField(strColor.trim());     
			color = (Color)field.get(null); } 
		catch (Exception e) {  
			color = null; // Not defined } 
		}
		return color;
	}
}
