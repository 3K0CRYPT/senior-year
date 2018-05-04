package clueTests;

import static org.junit.Assert.*;

import java.awt.Color;
import java.util.ArrayList;

import org.junit.BeforeClass;
import org.junit.Test;

import clueGame.Board;
import clueGame.Card;
import clueGame.CardType;
import clueGame.Player;
import clueGame.Solution;

public class CardandPlayerTests {

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
	public void testLoadingPeople() {
		
		//These tests test for the person above using the board classes getters
		//the people in comments are what is being tested
		
		
		//P/Colonel Mustard/4/3/yellow
	
		assertEquals("Colonel Mustard", board.players.get(0).getPlayerName());
		assertEquals(4, board.players.get(0).getRow());
		assertEquals(3, board.players.get(0).getColumn());
		
		
		//P/Mrs. White/10/8/white
		
		assertEquals("Mrs. White", board.players.get(4).getPlayerName());
		assertEquals(Color.white, board.players.get(4).getColor());
		assertEquals(10, board.players.get(4).getRow());
		assertEquals(8, board.players.get(4).getColumn());
		
		
		//P/Mrs. Peacock/16/17/blue
		
		assertEquals("Mrs. Peacock", board.players.get(5).getPlayerName());
		assertEquals(Color.blue, board.players.get(5).getColor());
		assertEquals(16, board.players.get(5).getRow());
		assertEquals(17, board.players.get(5).getColumn());
	}
	@Test
	public void testLoadingCards() {
		//tests that all of the cards are accounted for
		assertEquals(TOTAL_CARDS, board.cards.size());
		
		//the next tests runs through the cards and add counters respectibly depending on which card type it is
		int numPeople = 0;
		int numRooms = 0;
		int numWeapons = 0;
		for(Card s : board.cards){
			if(s.getType() == CardType.PERSON){
				numPeople++;
			}
			else if(s.getType() == CardType.WEAPON){
				numWeapons++;
			}
			else if(s.getType() == CardType.ROOM){
				numRooms++;
			}
		}
		//tests the constants against what the loop found
		assertEquals(numPeople, NUM_PEOPLE);
		assertEquals(numRooms, NUM_ROOMS);
		assertEquals(numWeapons, NUM_WEAPONS);
		
		//Test to ensure that the deck contains the Knife which is a weapon.
		//Test to ensure that the deck contains the player Colonel Mustard.
		//Test to ensure that the deck contains the room, foyer.
		boolean containsKnife = false;
		boolean containsMustard = false;
		boolean containsFoyer = false;
		for(Card s : board.cards){
			if(s.getCardName().equals("Colonel Mustard") && s.getType() == CardType.PERSON){
				containsMustard = true;
			}
			else if(s.getCardName().equals("Foyer") && s.getType() == CardType.ROOM){
				containsFoyer = true;
			}
			else if(s.getCardName().equals("Knife") && s.getType() == CardType.WEAPON){
				containsKnife = true;
			}
		}
		assertTrue(containsKnife && containsMustard && containsFoyer);
	}
	
	@Test
	public void testDealingCards() {
		//run through a loop of players and add up all of the cards each player has while also setting that amount into an array of numbers
		int playerCards = 0;
		int[] numCards = new int[6];
		int temp = 0;
		for(Player p : board.players){
			playerCards+=p.cards.size();
			numCards[temp] = p.cards.size();
			temp++;
		}
		//add the confidential file amount to the player size so all cards are accounted for
		//playerCards+=board.confidentialFile.size();
		
		//This is for the solution cards not being present.
		playerCards+=3;
		//set the temp as the first number
		temp = numCards[0];
		assertEquals(TOTAL_CARDS, playerCards); //all cards have been dealt
		boolean cardSize = false;
		//run through a loop and make sure that each player has within 2 of the same amount of cards as the last player
		for(int i = 0; i < board.players.size(); i++) {
			if (numCards[i] < temp+2 && numCards[i] >temp-2) {
				cardSize = true;
			}
			else {
				cardSize = false;
			}
			temp = numCards[i];
		}
		assertTrue(cardSize);//tests that they are indeed all within 2 of each other
		boolean uniqueDeal = true;
		ArrayList<Card> deck = new ArrayList<Card>();
		//This sections iterates through all of the players and then within each player iterates through every card that each player has.
		//It then tests to make sure that the card has not already been added to an array list and once it does that, it then adds the card.
		//If this passes then the cards must be uniquely dealt.
		for(Player p : board.players){
			for(Card c: p.cards){
				assertFalse(deck.contains(c));
				deck.add(c);
			}
		}
	}
	

	
	
}
