#include <iostream> //print
#include <fstream>  //read file
#include <string>   //no char array nonsense
#include <map>      //prevent duplicate edges
#include <vector>   //no pointer nonsense

using namespace std;
typedef map<string, map<string, int> > network;

static int usage(const char *message) {
  cerr << message << endl << "usage: find_route <filename> <origin> <destination>\n";
  return 1;
}

 struct node {
    string city;
    int cost;
    node *next;
  };

int main(int argc, char *argv[]) {
  if (argc != 4) return usage("Improper argument format.");
  string s = argv[1];
  string origin = argv[2];
  string destination = argv[3];
  ifstream file;
  file.open(argv[1]);
  if (!file) return usage(("Unable to open \"" + s + '"').c_str());
  
  network input;
  
  // Build map network so we can easily construct a graph from it
  while (file >> s) {
    if (s == "END") break;
    string cityA = s;
    file >> s;
    string cityB = s;
    file >> s;
    int cost = stoi(s);
    input[cityA][cityB] = cost;
    // input[cityB][cityA] = cost; //Probably not necessary
  }
  file.close();
  
  if (input.find(origin) == input.end()) return usage(("City \""+origin+"\" not present in input file.").c_str());
  if (input.find(destination) == input.end()) return usage(("City \""+destination+"\" not present in input file.").c_str());
  
  for (auto& city : input) {
    // cout << city.first << endl;
    for (auto& neighbors : city.second) {
      // cout << "\t" << neighbors.first << ", " << neighbors.second << endl;
    }
  }

}