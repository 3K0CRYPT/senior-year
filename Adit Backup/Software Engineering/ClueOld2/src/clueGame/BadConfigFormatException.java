package clueGame;

public class BadConfigFormatException extends Exception {
	public BadConfigFormatException() {
		super();
	}
	public BadConfigFormatException(String string){//, String secondString){
		super(string);
	}
}
