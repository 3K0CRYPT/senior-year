package maze3;

import java.awt.*;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;
public class CreateGraph {
	private String input = "src/input";
	public char start = '@', end;
	private Map<Character, PublicNode> graph;

	public CreateGraph() {
		super();
		graph = new HashMap();
		try {
			FileReader reader = new FileReader(input);
			Scanner in = new Scanner(reader);
			in.nextLine();
			String line = "";
			char s;
			char e;
			char l;
			char t;

			while (in.hasNextLine()) {
				line = in.nextLine();
				s = line.charAt(0);
				e = line.charAt(2);
				l = line.charAt(4);
				t = line.charAt(6);

				if (!graph.containsKey(s)) graph.put(s, new PublicNode(s));
				if (!graph.containsKey(e)) graph.put(e, new PublicNode(e));
				graph.get(s).mateColors.put(e, l);
				graph.get(e).mateColors.put(s, l);
				graph.get(s).mateTypes.put(e, t);
				graph.get(e).mateTypes.put(s, t);
			}
			start = graph.keySet().toString().charAt(1);
			end = graph.keySet().toString().charAt(graph.keySet().toString().length() - 2);
			in.close();
		} catch (FileNotFoundException e) {	e.printStackTrace(); }
	}

	public String search() {
		Queue<ArrayList<Character[]>> q = new LinkedList<ArrayList<Character[]>>();
		Set<String> Visited = new HashSet();

		/////// First queue push
		PublicNode node = graph.get(start);		
		// Only node connected to start, i.e. second node
		node = graph.get(node.mateColors.keySet().toString().charAt(1));																
																		
		Character[] _nq = { node.name, node.mateColors.get(start), node.mateTypes.get(start), start };
		ArrayList<Character[]> bs = new ArrayList();
		bs.add(_nq);
		q.add(bs);
		///////

		ArrayList<Character[]> actualpath = new ArrayList(); // Return the final
																// path from
																// start to end

		boolean found = false; // Holds if the BFS found the end node

		while (!q.isEmpty()) { // The BFS
			ArrayList<Character[]> path = q.poll(); // dequeue front node and
													// evaluate it

			Character[] n = path.get(path.size() - 1);

			// Stopping condition, i.e. current node is our destination
			if (n[0] == end) {
				found = true;
				actualpath = path;
				break;
			}

			PublicNode no = graph.get(n[0]);

			// Otherwise, enqueue any unvisited children if any
			if (no.mateColors.isEmpty()) continue;
			
			// Check for valid children
			for (char dest : no.mateColors.keySet()) {
				// If the neighbor is valid:
				if (dest != n[3] && (no.mateColors.get(dest) == n[1] || no.mateTypes.get(dest) == n[2])) {

					// Make a copy of original path					
					ArrayList<Character[]> newpath = new ArrayList<Character[]>();
					newpath.addAll(path);

					// Append this node to the current path
					Character[] _push = { dest, graph.get(dest).mateColors.get(n[0]), graph.get(dest).mateTypes.get(n[0]), n[0] };
					String _s = "";
					for (char c : _push) _s += c;
					if (Visited.contains(_s)) continue;
					else Visited.add(_s);

					newpath.add(_push);

					// Enqueue this newly expanded path
					q.add(newpath);
				}
			}
		}

		// If we found the end, then we output the path
		if (found) {
			String output = String.valueOf(start);
			for (Character[] _n : actualpath) output += " " + _n[0];
			return output;
		} else return "No path found.";
	}

	public void print() { for (PublicNode key : graph.values()) System.out.println(key); }

	public static void main(String[] args) {
		CreateGraph test = new CreateGraph();
		test.print();
		System.out.println("Path: " + test.search());
	}

}
