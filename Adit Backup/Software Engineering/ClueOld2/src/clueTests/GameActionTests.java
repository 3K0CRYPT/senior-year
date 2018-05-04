package clueTests;

import static org.junit.Assert.*;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;


import org.junit.BeforeClass;
import org.junit.Test;

import clueGame.Board;
import clueGame.BoardCell;
import clueGame.ComputerPlayer;
import clueGame.Player;
import clueGame.Solution;
import clueGame.Card;
import clueGame.CardType;

public class GameActionTests {
	
	private static Board board;
	private static int TOTAL_CARDS = 21;
	private static int NUM_PEOPLE = 6;
	private static int NUM_ROOMS = 9;
	private static int NUM_WEAPONS = 6;
	
	@BeforeClass
	public static void setUp() {
		board = new Board("ourClueLayout.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		board.initialize();
		
	}	
	
	@Test
	public void testAccusations() {
		//create actual solutions plus test accusation that is correct
		board.solution.setPerson("Bob");
		board.solution.setRoom("Bathroom");
		board.solution.setWeapon("Stick");
		Solution accusation = new Solution();
		accusation.setPerson("Bob");
		accusation.setRoom("Bathroom");
		accusation.setWeapon("Stick");
		assertTrue(board.checkAccusation(accusation));
		
		//the person is now wrong
		board.solution.setPerson("Bill");
		assertFalse(board.checkAccusation(accusation));
		
		//the person is now correct but the room is incorrect
		accusation.setPerson("Bob");
		accusation.setRoom("Laundry Room");
		assertFalse(board.checkAccusation(accusation));
		
		//the room is correct again but the weapon is incorrect
		accusation.setRoom("Bathroom");
		accusation.setWeapon("Computer");
		assertFalse(board.checkAccusation(accusation));
	}
	@Test
	public void testSelectTargetLocation() {
		ComputerPlayer player = new ComputerPlayer("Jeff", 18, 4, Color.orange);
		//Note the last initial is set to the ' ' character so the player will want to re-enter the room.
		board.calcTargets(player.getRow(), player.getColumn(), 3);
		BoardCell selected = player.pickLocation(board.getTargets());
		assertEquals(selected, board.getCellAt(18, 3));
		//This tests that the selected BoardCell is in fact the room that we should enter.
		
		//This sets the players lastInitial to be the initial of the nearest room so the choice of which room the player enters should be random.
		player.setInital('T');
		board.calcTargets(player.getRow(), player.getColumn(), 3);
		Set<BoardCell> selectedTargets = new HashSet<BoardCell>();
		BoardCell selectedTarget = new BoardCell(0,0,' ');
		for(int x = 0; x < 1000; x++){
			selectedTarget = player.pickLocation(board.getTargets());
			selectedTargets.add(selectedTarget);
		}
		assertEquals(board.getTargets().size(), selectedTargets.size()); 
		
		//testing a room with no doorways to enter
		selectedTargets.clear();
		ComputerPlayer player2 = new ComputerPlayer("Jeff", 5, 1, Color.orange);
		board.calcTargets(player2.getRow(), player2.getColumn(), 3);
		for(int x = 0; x < 1000; x++){
			selectedTarget = player2.pickLocation(board.getTargets());
			selectedTargets.add(selectedTarget);
		}
		System.out.println(selectedTargets);
		assertEquals(board.getTargets().size(), selectedTargets.size());
		
	}
	@Test
	public void testingDisproveMethods() {
		//3 tests for 3 different cards to return.
		// the have two correct choose one randomly
		//order 
		Card mustardCard = new Card("Colonel Mustard", 'P');
		Card knifeCard = new Card("Knife", 'W');
		Card revolverCard = new Card("Revolver", 'W');
		Card ropeCard = new Card("Rope", 'W');
		Card wrenchCard = new Card("Wrench", 'W');
		Card scarlettCard = new Card("Miss Scarlett", 'P');
		Card plumCard = new Card("Professor Plum", 'P');
		Card foyerCard = new Card("Foyer", 'R');
		Card studyCard = new Card("Study", 'R');
		Card kitchenCard = new Card("Kitchen", 'R');
		Card observatoryCard = new Card("Observatory", 'R');
		//The possible suggestion that we will make will Mustard in the study with the knife.
		Solution possibleSolution = new Solution();
		possibleSolution.setPerson("Colonel Mustard");
		possibleSolution.setRoom("Study");
		possibleSolution.setWeapon("Knife");
		for(Player p : board.players){
			p.cards.clear();
		}
		board.players.get(2).cards.add(observatoryCard);
		board.players.get(2).cards.add(wrenchCard);
		board.players.get(2).cards.add(foyerCard);
		board.players.get(2).cards.add(mustardCard);
		assertEquals(mustardCard, board.players.get(2).disproveSuggestion(possibleSolution)); //returns only one correct
		possibleSolution.setPerson("Billy");
		possibleSolution.setWeapon("Wrench");
		assertEquals(wrenchCard, board.players.get(2).disproveSuggestion(possibleSolution));
		possibleSolution.setWeapon("Knife");
		possibleSolution.setRoom("Foyer");
		assertEquals(foyerCard, board.players.get(2).disproveSuggestion(possibleSolution));
		
		//run through a loop 100 times and if it selects either knife or mustard at least once then their respected booleans will be set true
		possibleSolution.setPerson("Colonel Mustard");
		possibleSolution.setRoom("Study");
		possibleSolution.setWeapon("Knife");
		Card tempCard;
		board.players.get(2).cards.add(knifeCard);
		boolean knifeTrue = false;
		boolean mustardTrue = false;
		for (int i = 0; i < 100; i++) {
			tempCard = board.players.get(2).disproveSuggestion(possibleSolution);
			if (tempCard == knifeCard) {
				knifeTrue = true;
			}
			if (tempCard == mustardCard){
				mustardTrue = true;
			}
		}
		assertTrue(mustardTrue && knifeTrue);
		
		//The following test is used to ensure that the cards will loop in a specific order.
		//It tests this by making sure that the mustard card is returned every time.  This should happen if the loop goes in the correct order.
		//The correct order would be 0,1,2,3,4 (0 indexed).
		BoardCell clicked = new BoardCell(0,0,' ');
		for(Player p : board.players){
			p.cards.clear();
		}
		board.players.get(1).cards.add(observatoryCard);
		board.players.get(1).cards.add(wrenchCard);
		board.players.get(1).cards.add(foyerCard);
		board.players.get(1).cards.add(mustardCard);
		board.players.get(2).cards.add(studyCard);
		board.players.get(3).cards.add(studyCard);
		board.players.get(4).cards.add(studyCard);
		assertEquals(mustardCard, board.handleSuggestion(possibleSolution, board.players.get(5).getPlayerName(), clicked));
		
		
		for(Player p : board.players){
			p.cards.clear();
		}
		//This test ensures that if only the accusing player can disprove the suggestion then the return result will be null.
		board.players.get(2).cards.add(observatoryCard);
		board.players.get(2).cards.add(wrenchCard);
		board.players.get(2).cards.add(foyerCard);
		board.players.get(2).cards.add(mustardCard);
		assertEquals(null, board.handleSuggestion(possibleSolution, board.players.get(2).getPlayerName(), clicked)); //returns null no other players have any cards 
		
		//This test is used to ensure that the human can disprove a suggestion.
		for(Player p : board.players){
			p.cards.clear();
		}
		board.players.get(0).cards.add(observatoryCard);
		board.players.get(0).cards.add(wrenchCard);
		board.players.get(0).cards.add(foyerCard);
		board.players.get(0).cards.add(mustardCard);
		assertEquals(mustardCard, board.handleSuggestion(possibleSolution, board.players.get(2).getPlayerName(), clicked)); //The human should return the mustard card to disprove the suggestion. 
		
		
		//This test is used to ensure that the human can disprove a suggestion.
		for(Player p : board.players){
			p.cards.clear();
		}
		board.players.get(2).cards.add(observatoryCard);
		board.players.get(2).cards.add(wrenchCard);
		board.players.get(2).cards.add(foyerCard);
		board.players.get(2).cards.add(mustardCard);
		assertEquals(mustardCard, board.handleSuggestion(possibleSolution, board.players.get(0).getPlayerName(), clicked)); //The human should return the mustard card to disprove the suggestion. 
		
		//This test is used to ensure that the human can disprove a suggestion.
		for(Player p : board.players){
			p.cards.clear();
		}
		board.players.get(0).cards.add(observatoryCard);
		board.players.get(0).cards.add(wrenchCard);
		board.players.get(0).cards.add(foyerCard);
		board.players.get(0).cards.add(mustardCard);
		board.players.get(1).cards.add(observatoryCard);
		board.players.get(1).cards.add(wrenchCard);
		board.players.get(1).cards.add(foyerCard);
		board.players.get(1).cards.add(mustardCard);
		board.players.get(3).cards.add(observatoryCard);
		board.players.get(3).cards.add(wrenchCard);
		board.players.get(3).cards.add(foyerCard);
		board.players.get(3).cards.add(mustardCard);
		board.players.get(4).cards.add(observatoryCard);
		board.players.get(4).cards.add(wrenchCard);
		board.players.get(4).cards.add(foyerCard);
		board.players.get(4).cards.add(mustardCard);
		board.players.get(5).cards.add(observatoryCard);
		board.players.get(5).cards.add(wrenchCard);
		board.players.get(5).cards.add(foyerCard);
		board.players.get(5).cards.add(mustardCard);
		possibleSolution.setPerson("Professor Plum");
		possibleSolution.setRoom("Billiards Room");
		possibleSolution.setWeapon("Rope");
		assertEquals(null, board.handleSuggestion(possibleSolution, board.players.get(2).getPlayerName(), clicked)); //The human should return the mustard card to disprove the suggestion. 
		
		
	}
	
	@Test
	public void testingComputerSuggestions() {
		
		ComputerPlayer player = new ComputerPlayer("Jeff", 18, 3, Color.orange);
		for(int i = 0; i < board.cards.size(); i++){
			if(i != 0 && i != 13 && i != 14 && i != 20){
				board.cardsSeen.add(board.cards.get(i));
			}
		}
		
		
		player.cards.add(new Card("Aquarium", 'R'));
		Solution correctSuggestion = new Solution();
		correctSuggestion.setPerson("Colonel Mustard");
		correctSuggestion.setRoom("Theater");
		correctSuggestion.setWeapon("Wrench");
		player.MakeSuggestion(board, board.getCellAt(player.getRow(), player.getColumn()));
		//more specific tests for the correct suggestion comparison... our computer managed to corrupt our IDE so we spent way too long trying to fix code that wasn't broken..
		assertEquals(correctSuggestion.getPerson(), player.suggestion.getPerson());
		assertEquals(correctSuggestion.getRoom(), player.suggestion.getRoom());
		assertEquals(correctSuggestion.getWeapon(), player.suggestion.getWeapon());
		
		
		
		//given that the test above works this next text will just be making sure that if another character is removed from the "seen" collection 
		//that the computer will randomly pick one or the other as a suggestion
		boolean scarlettTrue = false;
		boolean mustardTrue = false;
		System.out.println(board.cardsSeen.get(0));
		board.cardsSeen.remove(0); //Miss Scarlett
		for (int i = 0; i < 100; i++) {
			player.MakeSuggestion(board, board.getCellAt(player.getRow(), player.getColumn()));
			System.out.println(player.suggestion.getPerson());
			if (player.suggestion.getPerson().equals("Miss Scarlett")) {
				scarlettTrue = true;
			}
			if (player.suggestion.getPerson().equals("Colonel Mustard")){
				mustardTrue = true;
			}
		}
		assertTrue(mustardTrue && scarlettTrue); //tests that mustard and scarlet were both a suggestion at least once
		
		
	}



}
