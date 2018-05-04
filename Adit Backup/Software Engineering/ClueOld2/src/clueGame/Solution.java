package clueGame;

public class Solution {
	private String person;
	private String room;
	private String weapon;
	
	public Solution() {
		super();
	}
	public String getPerson() {
		return person;
	}
	public void setPerson(String person) {
		this.person = person;
	}
	public String getRoom() {
		return room;
	}
	public void setRoom(String room) {
		this.room = room;
	}
	public String getWeapon() {
		return weapon;
	}
	public void setWeapon(String weapon) {
		this.weapon = weapon;
	}
	public boolean checkTheSame(Solution accusation) {
		if(accusation.getPerson() == person && accusation.getRoom() == room && accusation.getWeapon() == weapon) {
			return true;
		}
		else{
			return false;
		}
	}
	
}
