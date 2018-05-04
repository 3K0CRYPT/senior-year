package clueGame;

public class Card {
	private String cardName;
	private CardType type;
	public Card(String cardName, Character type){
		this.cardName = cardName;
		if(type == 'P'){
			this.type = CardType.PERSON; 
		}
		else if(type == 'R'){
			this.type = CardType.ROOM; 
		}
		else if(type == 'W'){
			this.type = CardType.WEAPON; 
		}
	}
	public String getCardName() {
		return cardName;
	}
	public CardType getType() {
		return type;
	}
	@Override
	public String toString() {
		return "Card [cardName=" + cardName + ", type=" + type + "]";
	}
	public boolean equals() {
		return false;
		
	}
}
