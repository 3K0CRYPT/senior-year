package clueGame;
import clueGame.Board;


import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Random;

public class Player {
	
	private String playerName;
	private int row;
	private int column;
	private Color color;
	public ArrayList<Card> cards;
	Player(String playerName, int row, int column, Color color){
		this.playerName = playerName;
		this.row = row;
		this.column = column;
		this.color = color;
		cards = new ArrayList<Card>();
	}
	public void draw(Graphics g){
		g.setColor(color);
		g.fillOval(column * ClueGame.SQUARE_SIZE, row * ClueGame.SQUARE_SIZE , ClueGame.SQUARE_SIZE, ClueGame.SQUARE_SIZE);
		g.setColor(Color.black);
		g.drawOval(column * ClueGame.SQUARE_SIZE, row * ClueGame.SQUARE_SIZE , ClueGame.SQUARE_SIZE, ClueGame.SQUARE_SIZE);
	}
	public String getPlayerName() {
		return playerName;
	}
	public int getRow() {
		return row;
	}
	public int getColumn() {
		return column;
	}
	public Color getColor() {
		return color;
	}
	@Override
	public String toString() {
		return "Player [playerName=" + playerName + ", row=" + row + ", column=" + column + ", color=" + color + "]";
	}
	public Card disproveSuggestion(Solution suggestion) {
		ArrayList<Card> tempCards = new ArrayList<Card>();
		for (Card c : cards) {
			if (c.getCardName() == suggestion.getPerson()){
				tempCards.add(c);
			}
			if (c.getCardName() == suggestion.getWeapon()){
				tempCards.add(c);
			}
			if (c.getCardName() == suggestion.getRoom()){
				tempCards.add(c);
			}
		}
		if (tempCards.size() == 0) {
			return null;
		}
		else {
			Random rand = new Random();
			int n = rand.nextInt(tempCards.size());
			return tempCards.get(n);
		}
		
		
	}
	
}
