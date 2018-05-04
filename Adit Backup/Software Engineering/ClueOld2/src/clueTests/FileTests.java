package clueTests;

import static org.junit.Assert.*;

import org.junit.Test;

import java.io.FileNotFoundException;
import java.util.Map;

import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;

import clueGame.BadConfigFormatException;
import clueGame.Board;
import clueGame.BoardCell;
//import clueGame.ClueGame;
import clueGame.DoorDirection;

public class FileTests {
	
	public static final int NUM_ROOMS = 11;
	public static final int NUM_ROWS = 22;
	public static final int NUM_COLUMNS = 22;
	
	private static Board board;
	
	@BeforeClass
	public static void setUp() {
		board = new Board("ourClueLayout.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		board.initialize();
	}	

	@Test
	public void testRooms() {
		Map<Character, String> rooms = Board.getRooms();
		//System.out.println(rooms);
		assertEquals(NUM_ROOMS, rooms.size());
		assertEquals("Billiards Room", rooms.get('B'));
		assertEquals("Foyer", rooms.get('F'));
		assertEquals("Study", rooms.get('S'));
		assertEquals("Dining Room", rooms.get('D'));
		assertEquals("Kitchen", rooms.get('K'));
		assertEquals("Library", rooms.get('L'));
		assertEquals("Observatory", rooms.get('O'));
		assertEquals("Theater", rooms.get('T'));
		assertEquals("Aquarium", rooms.get('A'));
		assertEquals("Closet", rooms.get('X'));
		assertEquals("Walkway", rooms.get('W'));
	}

	@Test
	public void testBoardDimensions() {
		//assertEquals(NUM_ROWS, board.getNumRows());
		//assertEquals(NUM_COLUMNS, board.getNumColumns());		
	}
	
	@Test
	public void testDoorDirections() {
		// Test door directions
			// up
		BoardCell room = board.getCellAt(17, 13);
		assertTrue(room.isDoorway());
		assertEquals(DoorDirection.UP, room.getDoorDirection());
			// down
		room = board.getCellAt(4, 11);
		assertTrue(room.isDoorway());
		assertEquals(DoorDirection.DOWN, room.getDoorDirection());
			// left
		room = board.getCellAt(10, 16);
		assertTrue(room.isDoorway());
		assertEquals(DoorDirection.LEFT, room.getDoorDirection());
			// right
		room = board.getCellAt(10, 6);
		assertTrue(room.isDoorway());
		assertEquals(DoorDirection.RIGHT, room.getDoorDirection());

		// Test non-door rooms
		room = board.getCellAt(8, 3);
		assertFalse(room.isDoorway());	
		// Test non-door walkways
		BoardCell cell = board.getCellAt(16, 16);
		assertFalse(cell.isDoorway());		
	}

	@Test
	public void testNumberOfDoorways() {
		int numDoors = 0;
		int totalCells = board.getNumColumns() * board.getNumRows();
		//Assert.assertEquals(484, totalCells);
		for (int row = 0; row < board.getNumRows(); row++) {
			for (int col = 0; col < board.getNumColumns(); col++) {
				BoardCell cell = board.getCellAt(row, col);
				if (cell.isDoorway()) {
					numDoors++;
				}
			}
		}
		//Assert.assertEquals(13, numDoors);
	}
	
	@Test
	public void testRoomInitials() {
		assertEquals('B', board.getCellAt(1, 1).getInitial());
		assertEquals('F', board.getCellAt(2, 10).getInitial());
		assertEquals('S', board.getCellAt(2, 18).getInitial());
		assertEquals('D', board.getCellAt(12, 17).getInitial());
		assertEquals('K', board.getCellAt(20, 20).getInitial());
		assertEquals('L', board.getCellAt(19, 12).getInitial());
		assertEquals('O', board.getCellAt(18, 7).getInitial());
		assertEquals('T', board.getCellAt(21, 2).getInitial());
		assertEquals('A', board.getCellAt(11, 3).getInitial());
		assertEquals('X', board.getCellAt(10, 11).getInitial());
		assertEquals('W', board.getCellAt(8, 8).getInitial());
	}
	
	// Tests for BadConfigFormatException
	@Test (expected = BadConfigFormatException.class)
	public void testBadColumns() throws BadConfigFormatException, FileNotFoundException {
		Board board = new Board("ourClueLayoutBadColumns.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		board.loadRoomConfig();
		board.loadBoardConfig();
	}
	
	@Test (expected = BadConfigFormatException.class)
	public void testBadRoom() throws BadConfigFormatException, FileNotFoundException {
		Board board = new Board("ourClueLayoutBadRoom.csv", "ourClueLegend.txt", "PlayerandCardConfig.txt");
		board.loadRoomConfig();
		board.loadBoardConfig();
	}
	
	@Test (expected = BadConfigFormatException.class)
	public void testBadRoomFormat() throws BadConfigFormatException, FileNotFoundException {
		Board board = new Board("ourClueLayout.csv", "ourClueLegendBadFormat.txt", "PlayerandCardConfig.txt");
		board.loadRoomConfig();
	}
}
