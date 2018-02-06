#include <fstream>   //read file
#include <iostream>  //print
#include <map>       //easily get cost between 2 cities
#include <queue>     //priority queue
#include <string>    //no char array nonsense
#include <vector>    //no pointer nonsense

using namespace std;

// So our priority queue knows how to prioritize smaller paths
class ComparisonClass {
 public:
  bool operator()(pair<string, int> a, pair<string, int> b) {
    return a.second > b.second;
  }
};

// So I can easily change what data structure the input is
typedef map<string, map<string, int>> network;
typedef priority_queue<pair<string, int>, vector<pair<string, int>>, ComparisonClass> pq;

// Error message for when improper arguments are given.
static int usage(const char* message) {
  cerr << message << endl << "usage: find_route <filename> <origin> <destination>\n";
  return 1;
}

// Main function
int main(int argc, char* argv[]) {
  // Gather inputs to the function and make sure they're in a valid format
  if (argc != 4) return usage("Improper argument format.");
  string s = argv[1], origin = argv[2], destination = argv[3];
  ifstream file;
  file.open(argv[1]);
  if (!file) return usage(("Unable to open \"" + s + '"').c_str());

  network input; //Initialize our city network/map

  // Build map network so we can easily get cost between 2 cities
  while (file >> s) {
    if (s == "END") break;
    string cityA = s;
    file >> s;
    string cityB = s;
    file >> s;
    int cost = stoi(s);
    
    // Map the two cities as neighbors with the cost
    input[cityA][cityB] = cost; 
    input[cityB][cityA] = cost;
  }
  file.close();

  // Trivial and/or error checks
  if (input.find(origin) == input.end()) return usage( ("City \"" + origin + "\" not present in input file.").c_str() );
  if (input.find(destination) == input.end()) return usage( ("City \"" + destination + "\" not present in input file.").c_str() );
  if (origin == destination) { 
    cout << "distance: 0 km\nroute:\n" << origin << " to " << origin << ", 0 km\n";
    return 0;
  }

  map<string, int> visited;             // Keep track of minimum cost to a city
  map<string, pair<string, int>> path;  // Keep track of the path between 2 cities
  pq q;                                 // The priority queue

  q.emplace(make_pair(origin, 0));  // Initialize with origin; just itself is always lowest cost

  unsigned int total_cost = 4294967295;  // Effectively infinity;

  // The magic!
  while (!q.empty()) {
    auto city = q.top();  //dequeue
    q.pop();
    if (city.first == destination) {  //If we popped our destination from the queue, we found the optimal path!
      total_cost = city.second;
      break;
    }
    for (auto neighbor : input[city.first]) {
      int cost_so_far = neighbor.second + city.second;  // This is the cost that will be enqueued and sorted by priority
      auto it = visited.find(neighbor.first);
      if (it == visited.end() || it->second > cost_so_far) {
        // Either we haven't visited this neighbor, or we found a better route to it
        q.emplace(make_pair(neighbor.first, cost_so_far));
        visited[neighbor.first] = cost_so_far;
        path[neighbor.first] = make_pair(city.first, neighbor.second);
      }
    }
  }

  // We didn't find a route
  if (total_cost == 4294967295) {
    cout << "distance: infinity\nroute:\nnone\n";
    return 0;
  }

  // Retrace path
  vector<string> inverted = {destination};
  auto current = path[destination];

  while (current.first != origin) {
    inverted.push_back(current.first);
    current = path[current.first];
  }
  inverted.push_back(origin);

  //Output the cost
  cout << "distance: " << total_cost << " km\nroute:\n";

  //Output the route and the cost of each step
  for (int i = inverted.size() - 1; i > 0; i--) cout << inverted[i] << " to " << inverted[i - 1] << ", " << input[inverted[i]][inverted[i - 1]] << " km\n";

  return 0;
};