package clueGame;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

public class BoardCell {
	private int row;
	private int column;
	private char initial;
	private DoorDirection doorDirection;
	public static final int DOOR_THICKNESS = 5;
	boolean walkway = false;
	boolean room = false;
	boolean doorway = false;
	boolean name = false;
	
	public void setNameBoolean(Boolean bool){
		name = bool;
	}
	@Override
	public String toString() {
		return "BoardCell [row=" + row + ", column=" + column + "]" + initial;
	}

	public void setDoorDirection(DoorDirection doorDirection) {
		this.doorDirection = doorDirection;
	}

	public void setWalkway(boolean walkway) {
		this.walkway = walkway;
	}

	public void setRoom(boolean room) {
		this.room = room;
	}

	public void setDoorway(boolean doorway) {
		this.doorway = doorway;
	}
	
	public BoardCell(int row, int column, char i) {
		this.row = row;
		this.column = column;
		this.initial = i;
	}
	
	public void draw(Graphics g){
		if(walkway == true){
			g.setColor(Color.yellow);
			g.fillRect((Integer)(column * ClueGame.SQUARE_SIZE), (Integer)(row * ClueGame.SQUARE_SIZE), ClueGame.SQUARE_SIZE, ClueGame.SQUARE_SIZE);
			g.setColor(Color.black);
			g.drawRect((Integer)(column * ClueGame.SQUARE_SIZE), (Integer)(row * ClueGame.SQUARE_SIZE), ClueGame.SQUARE_SIZE, ClueGame.SQUARE_SIZE);
			
		}
		else{
			g.setColor(Color.gray);
			g.fillRect((Integer)(column * ClueGame.SQUARE_SIZE), (Integer)(row * ClueGame.SQUARE_SIZE), ClueGame.SQUARE_SIZE, ClueGame.SQUARE_SIZE);
		}
		if(doorway == true){
			g.setColor(Color.blue);
			if(doorDirection == DoorDirection.UP){
				g.fillRect((Integer)(column * ClueGame.SQUARE_SIZE), (Integer)(row * ClueGame.SQUARE_SIZE), (Integer)(ClueGame.SQUARE_SIZE), DOOR_THICKNESS);
			}
			else if(doorDirection == DoorDirection.LEFT){
				g.fillRect((Integer)((column * ClueGame.SQUARE_SIZE)), (Integer)(row * ClueGame.SQUARE_SIZE), DOOR_THICKNESS, ClueGame.SQUARE_SIZE);
			}
			else if(doorDirection == DoorDirection.RIGHT){
				g.fillRect((Integer)((column * ClueGame.SQUARE_SIZE) + ClueGame.SQUARE_SIZE - DOOR_THICKNESS), (Integer)(row * ClueGame.SQUARE_SIZE), DOOR_THICKNESS,  ClueGame.SQUARE_SIZE);
			}
			else{
				g.fillRect((Integer)((column * ClueGame.SQUARE_SIZE)), (Integer)(row * ClueGame.SQUARE_SIZE + ClueGame.SQUARE_SIZE - DOOR_THICKNESS), ClueGame.SQUARE_SIZE, DOOR_THICKNESS);
			}
		}
		if(name == true) {
			for(Card c : Board.cards){
				if(c.getType() == CardType.ROOM && c.getCardName().charAt(0) == initial){
					g.setColor(Color.BLACK);
					g.setFont(new Font("TimesRoman", Font.PLAIN, 20));
					g.drawString(c.getCardName(), column * ClueGame.SQUARE_SIZE, row * ClueGame.SQUARE_SIZE - DOOR_THICKNESS);
				}
			}	
		}
	}
	
	public boolean isWalkway() {
		return walkway;
	}
	
	public boolean isRoom() {
		return room;
	}
	
	public boolean isDoorway() {
		return doorway;
	}
	
	public DoorDirection getDoorDirection() {
		return doorDirection;
	}
	
	public char getInitial() {
		return initial;
	}
	
	public int getRow() {
		return row;
	}
	
	public int getColumn() {
		return column;
	}
}
