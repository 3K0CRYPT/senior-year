package clueGame;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Random;
import java.util.Set;

import java.awt.Color;

public class ComputerPlayer extends Player {
	public char lastInitial;
	public Solution suggestion;
	public ComputerPlayer(String playerName, int row, int column, Color color) {
		super(playerName, row, column, color);
		lastInitial = ' ';
		suggestion = new Solution();
		// TODO Auto-generated constructor stub
	}

	public void makeAccusation() {
		
	}
	
	public void MakeSuggestion(Board board, BoardCell location) {
		//location.getInitial()
		//handleSuggestion(Solution suggestion, String accusingPlayer, BoardCell clicked)
		String roomName = "";
		for(Card c : board.cards){
			if(c.getType() == CardType.ROOM && c.getCardName().charAt(0) == location.getInitial()){
				roomName = c.getCardName();
				break;
			}
		}
		suggestion.setRoom(roomName);
		/*
		List<Card> possibleCards = new ArrayList<Card>();
		possibleCards = board.cards;
		possibleCards.removeAll(board.cardsSeen);
		possibleCards.removeAll(cards);
		
		List<Card> possibleCards = new ArrayList<Card>();
		possibleCards = board.cards;
		for (Iterator<Card> iterator = possibleCards.iterator(); iterator.hasNext(); ) {
		    Card c = iterator.next();
		    for (Card i : board.cardsSeen) {
		    	if(c == i){
		        	iterator.remove();
		    	}
		    }
		    for (Card i : cards) {
		    	if(c == i){
		        	iterator.remove();
		    	}
		    }
		}
		
		ArrayList<Card> possibleCards = new ArrayList<Card>();
		possibleCards = board.cards;
		for(int i = 0; i < board.cardsSeen.size(); i++){
			if(possibleCards.contains(board.cardsSeen.get(i))){
				possibleCards.remove(board.cardsSeen.get(i));
			}
		}
		for(int i = 0; i < cards.size(); i++){
			if(possibleCards.contains(cards.get(i))){
				possibleCards.remove(cards.get(i));
			}
		}
		
		
		@SuppressWarnings("unchecked")
		ArrayList<Card> clone = (ArrayList<Card>) possibleCards.clone();
		for(Card c : board.cardsSeen){
			if(possibleCards.contains(c)){
				clone.remove(c);
			}
			else {
				//possibleCards.add(c);
			}
		}
		for(Card c : cards){
			if(possibleCards.contains(c)){
				clone.remove(c);
			}
			else {
				//possibleCards.add(c);
			}
		}
		possibleCards = (ArrayList<Card>) clone.clone();
		*/
		//System.out.println(possibleCards.size());
		Random rand = new Random();
		while(true){
			int n = rand.nextInt(board.cards.size());
			if(board.cards.get(n).getType() == CardType.PERSON && !board.cardsSeen.contains(board.cards.get(n)) && !cards.contains(board.cards.get(n))){
				suggestion.setPerson(board.cards.get(n).getCardName());
				break;
			}
		}
		while(true){
			int n = rand.nextInt(board.cards.size());
			if(board.cards.get(n).getType() == CardType.WEAPON && !board.cardsSeen.contains(board.cards.get(n)) && !cards.contains(board.cards.get(n))){
				suggestion.setWeapon(board.cards.get(n).getCardName());
				break;
			}
		}
		/*
		Random rand = new Random();
		while(true){
			int n = rand.nextInt(possibleCards.size());
			if(possibleCards.get(n).getType() == CardType.PERSON){
				suggestion.setPerson(possibleCards.get(n).getCardName());
				break;
			}
		}
		while(true){
			int n = rand.nextInt(possibleCards.size());
			if(possibleCards.get(n).getType() == CardType.WEAPON){
				suggestion.setWeapon(possibleCards.get(n).getCardName());
				break;
			}
		}
		board.handleSuggestion(suggestion, this.getPlayerName(), location);
		*/
	}
	
	public BoardCell pickLocation(Set<BoardCell> targets) {
		// TODO Auto-generated method stub
		
		Random rand = new Random();
		int counter = 0;
		for(BoardCell s : targets){
			if(s.getInitial() != lastInitial && s.getInitial() != 'W' ){
				lastInitial = s.getInitial();
				return s;
			}
		}
		int n = rand.nextInt(targets.size());
		/*
		for (BoardCell s : targets){
			if(s.getInitial() == lastInitial && s.getInitial != 'W'){
			}
			else if(n == counter) {
				lastInitial = s.getInitial();
				return s;
			}
			counter++;// better way to do it
		}
		return null;
		*/
		for (BoardCell s : targets){
			if(n == counter) {
				return s;
			}
			counter++;
		}
		return null;
	}
	public char getInitial(){
		return lastInitial;
	}
	public void setInital(char lastInital){
		this.lastInitial = lastInitial;
	}
	
}
