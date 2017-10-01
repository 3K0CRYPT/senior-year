#include "load_average_info.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


LoadAverageInfo get_load_average() {
  // TODO: implement me
  ifstream fp("./proc/loadavg");

  if(!fp.is_open()){
	  cout << "RIP" << endl;
  return LoadAverageInfo();}
  LoadAverageInfo la;
  string line;
  while (getline(fp,line)){
	stringstream ss(line);
  	ss >> la.one_min >> la.five_mins >> la.fifteen_mins;
	
  } 
		  fp.close();

  return la;
}
