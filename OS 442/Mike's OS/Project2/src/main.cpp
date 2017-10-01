#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include "functions.h"
#include "algorithms.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;
priority_queue <Event, vector<Event>, LowerArrivalTime> EventQueue;



int main(int argc, char* argv[]){

processFlags(argc, argv);

string filename;
Metrics m;
if(argv[1] != NULL){ 
	filename = argv[optind];
}
vector<Process> processes = populateProcess(filename,m);


switch(selectedAlgorithm){
	case FCFS: 
		EventQueue = fcfsAlgorithm(processes, m);
		break;		
	case 1:
		EventQueue = rrAlgorithm(processes, m);
		break;
	case PRIORITY:
		EventQueue = priorityAlgorithm(processes, m);
		break;
	case CUSTOM:
		EventQueue = fcfsAlgorithm(processes, m);
		break;
}
printMetrics(m);
if (verbose){
	printEvents(EventQueue);
}

if(per_thread){
	printPerThread(m, processes);
}
return 0;
}
