package maze3;

import java.awt.*;
import java.util.*;

//WHY THE HELL DID YOU GUYS DO STRICT ENCAPSULATION GOOD LORD

public class PublicNode {
public char name;
public Map<Character,Character> mateColors = new HashMap<Character,Character>();
public Map<Character,Character> mateTypes = new HashMap<Character,Character>();
public PublicNode(char name) {
	super();
	this.name = name;	
}

@Override
public String toString() {
	return "Name: " + name + ", Mates: " + mateColors.keySet().toString();
}
}