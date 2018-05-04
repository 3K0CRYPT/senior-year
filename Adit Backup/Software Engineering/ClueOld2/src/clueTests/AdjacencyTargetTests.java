package clueTests;

import static org.junit.Assert.*;

import java.util.LinkedList;
import java.util.Set;

import org.junit.BeforeClass;
import org.junit.Test;

import clueGame.Board;
import clueGame.BoardCell;

public class AdjacencyTargetTests {

	private static Board board;
	
	@BeforeClass
	public static void setUp() {
		board = new Board("ourClueLayout.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		board.initialize();
	}
	
	// Adjacency tests
	@Test
	public void testOnlyWalkways() { // DARK GREEN on spreadsheet
		LinkedList<BoardCell> testList = board.getAdjList(1, 6);
		assertEquals(3, testList.size());
		assertTrue(testList.contains(board.getCellAt(0, 6)));
		assertTrue(testList.contains(board.getCellAt(2, 6)));
		assertTrue(testList.contains(board.getCellAt(1, 7)));
		
		testList = board.getAdjList(6, 14);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(5, 14)));
		assertTrue(testList.contains(board.getCellAt(7, 14)));
		assertTrue(testList.contains(board.getCellAt(6, 13)));
		assertTrue(testList.contains(board.getCellAt(6, 15)));
		
		testList = board.getAdjList(15, 8);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(14, 8)));
		assertTrue(testList.contains(board.getCellAt(16, 8)));
		assertTrue(testList.contains(board.getCellAt(15, 7)));
		assertTrue(testList.contains(board.getCellAt(15, 9)));
	}
	
	@Test
	public void testEdges() { // PURPLE on spreadsheet
		LinkedList<BoardCell> testList = board.getAdjList(5, 0);
		assertEquals(3, testList.size());
		assertTrue(testList.contains(board.getCellAt(4, 0)));
		assertTrue(testList.contains(board.getCellAt(6, 0)));
		assertTrue(testList.contains(board.getCellAt(5, 1)));
		
		testList = board.getAdjList(0, 14);
		assertEquals(2, testList.size());
		assertTrue(testList.contains(board.getCellAt(1, 14)));
		assertTrue(testList.contains(board.getCellAt(0, 15)));
		
		testList = board.getAdjList(8, 21);
		assertEquals(0, testList.size());
		
		testList = board.getAdjList(21, 12);
		assertEquals(0, testList.size());
	}
	
	@Test
	public void testBesideRoomNotDoorway() { // RED on spreadsheet
		LinkedList<BoardCell> testList = board.getAdjList(15, 2);
		assertEquals(3, testList.size());
		assertTrue(testList.contains(board.getCellAt(16, 2)));
		assertTrue(testList.contains(board.getCellAt(15, 1)));
		assertTrue(testList.contains(board.getCellAt(15, 3)));
		
		testList = board.getAdjList(14, 16);
		assertEquals(2, testList.size());
		assertTrue(testList.contains(board.getCellAt(15, 16)));
		assertTrue(testList.contains(board.getCellAt(14, 15)));
	}
	
	@Test
	public void testDoorwayWithNeededDirection() { // DARK BLUE on spreadsheet
		LinkedList<BoardCell> testList = board.getAdjList(5, 10);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(4, 10)));
		assertTrue(testList.contains(board.getCellAt(6, 10)));
		assertTrue(testList.contains(board.getCellAt(5, 9)));
		assertTrue(testList.contains(board.getCellAt(5, 11)));
		
		testList = board.getAdjList(4, 17);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(3, 17)));
		assertTrue(testList.contains(board.getCellAt(5, 17)));
		assertTrue(testList.contains(board.getCellAt(4, 16)));
		assertTrue(testList.contains(board.getCellAt(4, 18)));
		
		testList = board.getAdjList(11, 15);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(10, 15)));
		assertTrue(testList.contains(board.getCellAt(12, 15)));
		assertTrue(testList.contains(board.getCellAt(11, 14)));
		assertTrue(testList.contains(board.getCellAt(11, 16)));
		
		testList = board.getAdjList(16, 13);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCellAt(15, 13)));
		assertTrue(testList.contains(board.getCellAt(17, 13)));
		assertTrue(testList.contains(board.getCellAt(16, 12)));
		assertTrue(testList.contains(board.getCellAt(16, 14)));
	}
	
	@Test
	public void testAtDoorways() { // BROWN on spreadsheet
		LinkedList<BoardCell> testList = board.getAdjList(18, 3);
		assertEquals(1, testList.size());
		assertTrue(testList.contains(board.getCellAt(18, 4)));
		
		testList = board.getAdjList(19, 17);
		assertEquals(1, testList.size());
		assertTrue(testList.contains(board.getCellAt(19, 16)));
	}
	
	// Target tests
	@Test
	public void testWalkways() { // BLACK on spreadsheet
		board.calcTargets(5, 20, 3);
		Set<BoardCell> testTargets = board.getTargets();
		assertEquals(7, testTargets.size());
		assertTrue(testTargets.contains(board.getCellAt(4, 18)));
		assertTrue(testTargets.contains(board.getCellAt(4, 20)));
		assertTrue(testTargets.contains(board.getCellAt(5, 17)));
		assertTrue(testTargets.contains(board.getCellAt(5, 19)));
		assertTrue(testTargets.contains(board.getCellAt(5, 21)));
		assertTrue(testTargets.contains(board.getCellAt(6, 18)));
		assertTrue(testTargets.contains(board.getCellAt(6, 20)));
		
		board.calcTargets(7, 9, 2);
		testTargets = board.getTargets();
		assertEquals(7, testTargets.size());
		assertTrue(testTargets.contains(board.getCellAt(5, 9)));
		assertTrue(testTargets.contains(board.getCellAt(6, 8)));
		assertTrue(testTargets.contains(board.getCellAt(6, 10)));
		assertTrue(testTargets.contains(board.getCellAt(7, 7)));
		assertTrue(testTargets.contains(board.getCellAt(7, 11)));
		assertTrue(testTargets.contains(board.getCellAt(8, 8)));
		assertTrue(testTargets.contains(board.getCellAt(9, 9)));
		
		board.calcTargets(17, 20, 4);
		testTargets = board.getTargets();
		assertEquals(7, testTargets.size());
		assertTrue(testTargets.contains(board.getCellAt(17, 16)));
		assertTrue(testTargets.contains(board.getCellAt(16, 17)));
		assertTrue(testTargets.contains(board.getCellAt(15, 18)));
		assertTrue(testTargets.contains(board.getCellAt(17, 18)));
		assertTrue(testTargets.contains(board.getCellAt(16, 19)));
		assertTrue(testTargets.contains(board.getCellAt(15, 20)));
		assertTrue(testTargets.contains(board.getCellAt(16, 21)));
		
		board.calcTargets(15, 6, 1);
		testTargets = board.getTargets();
		assertEquals(4, testTargets.size());
		assertTrue(testTargets.contains(board.getCellAt(14, 6)));
		assertTrue(testTargets.contains(board.getCellAt(16, 6)));
		assertTrue(testTargets.contains(board.getCellAt(15, 5)));
		assertTrue(testTargets.contains(board.getCellAt(15, 7)));
	}
	
	@Test
	public void testEnterRoom() { // PINK on spreadsheet
		board.calcTargets(10, 8, 3);
		Set<BoardCell> testTargets = board.getTargets();
		assertEquals(12, testTargets.size());
		// Walkway(s)
		assertTrue(testTargets.contains(board.getCellAt(7, 8)));
		assertTrue(testTargets.contains(board.getCellAt(8, 7)));
		assertTrue(testTargets.contains(board.getCellAt(8, 9)));
		assertTrue(testTargets.contains(board.getCellAt(9, 8)));
		assertTrue(testTargets.contains(board.getCellAt(10, 7)));
		assertTrue(testTargets.contains(board.getCellAt(10, 9)));
		assertTrue(testTargets.contains(board.getCellAt(11, 8)));
		assertTrue(testTargets.contains(board.getCellAt(12, 7)));
		assertTrue(testTargets.contains(board.getCellAt(12, 9)));
		assertTrue(testTargets.contains(board.getCellAt(13, 8)));
		// Door(s)
		assertTrue(testTargets.contains(board.getCellAt(10, 6)));
		assertTrue(testTargets.contains(board.getCellAt(11, 6)));
		
		board.calcTargets(19, 16, 2);
		testTargets = board.getTargets();
		assertEquals(5, testTargets.size());
		// Walkway(s)
		assertTrue(testTargets.contains(board.getCellAt(17, 16)));
		assertTrue(testTargets.contains(board.getCellAt(18, 15)));
		assertTrue(testTargets.contains(board.getCellAt(20, 15)));
		assertTrue(testTargets.contains(board.getCellAt(21, 16)));
		// Door(s)
		assertTrue(testTargets.contains(board.getCellAt(19, 17)));
	}
	
	@Test
	public void testLeaveRoom() { // LIGHT GREEN on spreadsheet
		board.calcTargets(4, 12, 3);
		Set<BoardCell> testTargets = board.getTargets();
		assertEquals(6, testTargets.size());
		assertTrue(testTargets.contains(board.getCellAt(5, 10)));
		assertTrue(testTargets.contains(board.getCellAt(5, 14)));
		assertTrue(testTargets.contains(board.getCellAt(6, 11)));
		assertTrue(testTargets.contains(board.getCellAt(6, 13)));
		assertTrue(testTargets.contains(board.getCellAt(7, 12)));
		assertTrue(testTargets.contains(board.getCellAt(4, 11)));
		
		board.calcTargets(10, 16, 2);
		testTargets = board.getTargets();
		assertTrue(testTargets.contains(board.getCellAt(9, 15)));
		assertTrue(testTargets.contains(board.getCellAt(10, 14)));
		assertTrue(testTargets.contains(board.getCellAt(11, 15)));
	}

}
