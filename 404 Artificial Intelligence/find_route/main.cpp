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
    // input[cityB][cityA] = cost; //Probably not necessary
  }
  file.close();

  if (input.find(origin) == input.end())
    return usage(("City \"" + origin + "\" not present in input file.").c_str());
  if (input.find(destination) == input.end())
    return usage(("City \"" + destination + "\" not present in input file.").c_str());

  //map<string, map<string, int> > network;
  //map<string, int>

  map<string, int> start = input[origin];
  map<string, int> visited;
  map<string, pair<string, int>> path;
  pq q;

  // path[origin] = make_pair("",-1);

  // for (auto &t : start)
  // {
  //   q.emplace(t); //start by queuing origin's neighbors
  //   path[t.first] = make_pair(origin, t.second);
  //   visited[t.first] = t.second;
  // }

  q.emplace(make_pair(origin, 0));

  //The magic!
  while (!q.empty())
  {
    auto city = q.top();
    q.pop();
    // cout << "Exploring: " << city.first << endl;
    for (auto neighbor : input[city.first])
    {
      // cout << "\t" << neighbor.first << endl;
      if (neighbor.first == destination)
      {
        // cout << "We found it! " << neighbor.first << " = " << destination << endl;
        path[neighbor.first] = make_pair(city.first, neighbor.second);

       //Retrace path
        int total_cost = 0;
        vector<pair<string, int>> inverted;
        auto current = path[destination];
        inverted.push_back(current);
        while (path.find(current.first) != path.end())
        {
          inverted.push_back(current);
          current = path[current.first];
        }

        int i = inverted.size() - 1;
        cout << origin << " to " << inverted[i].first << ", " << inverted[i].second << " km\n";
        auto last = inverted[i];
        i--;

        for (i; i > 0; i--)
        {
          cout << last.first << "to " << inverted[i].first << ", " << inverted[i].second << " km\n";
          last = inverted[i];
        }

        cout << inverted[0].first << " to " << destination << ", " <<input[inverted[0].first][destination] << " km\n";

        return 0;
      }
      if (visited.find(neighbor.first) == visited.end())
      // if (visited[neighbor.first] < neighbor.second)
      {
        q.emplace(neighbor);
        visited[neighbor.first] = neighbor.second;
        path[neighbor.first] = make_pair(city.first, neighbor.second);
      }
      else if (visited[neighbor.first] > neighbor.second) {
        q.emplace(neighbor);
        visited[neighbor.first] = neighbor.second;
        path[neighbor.first] = make_pair(city.first, neighbor.second);
      }
    }
  }

  cout << "Guess we couldn't find it :(\n";
  return 1;
};
