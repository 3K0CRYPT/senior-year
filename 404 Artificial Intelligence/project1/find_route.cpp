#include <iostream> //print
#include <fstream>  //read file
#include <string>   //no char array nonsense
#include <map>      //prevent duplicate edges
#include <vector>   //no pointer nonsense
#include <queue>    //priority queue

using namespace std;

class ComparisonClass
{
public:
  bool operator()(pair<string, int> a, pair<string, int> b)
  {
    return a.second < b.second;
  }
};

typedef map<string, map<string, int>> network;
typedef priority_queue<pair<string, int>, vector<pair<string, int>>, ComparisonClass> pq;

static int usage(const char *message)
{
  cerr << message << endl
       << "usage: find_route <filename> <origin> <destination>\n";
  return 1;
}

int main(int argc, char *argv[])
{
  if (argc != 4)
    return usage("Improper argument format.");
  string s = argv[1];
  string origin = argv[2];
  string destination = argv[3];
  ifstream file;
  file.open(argv[1]);
  if (!file)
    return usage(("Unable to open \"" + s + '"').c_str());

  network input;

  // Build map network so we can easily construct a graph from it
  while (file >> s)
  {
    if (s == "END")
      break;
    string cityA = s;
    file >> s;
    string cityB = s;
    file >> s;
    int cost = stoi(s);
    input[cityA][cityB] = cost;
    input[cityB][cityA] = cost; //Probably not necessary
  }
  file.close();

  if (input.find(origin) == input.end())
    return usage(("City \"" + origin + "\" not present in input file.").c_str());
  if (input.find(destination) == input.end())
    return usage(("City \"" + destination + "\" not present in input file.").c_str());

  map<string, int> start = input[origin];
  map<string, int> visited;
  map<string, pair<string, int>> path;
  pq q;

  q.emplace(make_pair(origin, 0));

  //The magic!
  while (!q.empty())
  {
    auto city = q.top();
    q.pop();
    for (auto neighbor : input[city.first])
    {
      int cost_so_far = neighbor.second + city.second;
      auto it = visited.find(neighbor.first);
      if (it == visited.end() || it->second > cost_so_far)
      {
        q.emplace(make_pair(neighbor.first, cost_so_far));
        visited[neighbor.first] = cost_so_far;
        path[neighbor.first] = make_pair(city.first, neighbor.second);
      }
    }
  }

  if (visited.find(destination) == visited.end())
  {
    cout << "distance: infinity\nroute:\nnone";
    return 1;
  }

  //Retrace path
  int total_cost = 0;
  vector<string> inverted = {destination};

  auto current = path[destination];

  while (current.first != origin)
  {
    total_cost += current.second;
    inverted.push_back(current.first);
    current = path[current.first];
  }
  inverted.push_back(origin);
  
  total_cost += input[inverted[inverted.size()-1]][inverted[inverted.size()-2]];
  
  cout << "distance: " << total_cost << "km\nroute:\n";

  int i = inverted.size() - 1;
  for (i; i > 0; i--) {
    cout << inverted[i] << " to " << inverted[i-1] << ", " << input[inverted[i]][inverted[i-1]] << " km\n";
  }

  return 0;
};