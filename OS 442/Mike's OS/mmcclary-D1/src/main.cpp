#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <sstream>
#include "structs.h"

using namespace std;
priority_queue <Event, vector<Event>, LowerArrivalTime> EventQueue;



int main(int argc, char* argv[]){
string filename;
if(argv[1] != NULL) filename = argv[1];

ifstream eventFile(filename);

if(!eventFile.is_open()){
	cerr << "Error opening file" << endl;
}

int numProcesses;
int threadOverhead;
int processOverhead;
string line;
eventFile >> numProcesses >> threadOverhead >> processOverhead; // reads in basical overall data
vector<Process> processVector;
for(int i = 0; i < numProcesses; i++){ //loop through to get the number of processes
	getline(eventFile,line);
	while(line.empty()){
		getline(eventFile,line);
	}
	int type;
		Process p;		//make a new process
		stringstream ss(line);
		ss >> p.processNumber >> type >> p.numThreads;  //read in the process variables
		p.pt = static_cast<Process::ProcType>(type);
		for(int j = 0; j < p.numThreads; j++){ //make threads
			getline(eventFile,line);
			while(line.empty()){
				getline(eventFile,line);
			}
			Thread t;
			stringstream ss2(line);
			ss2 >> t.arrivalTime >> t.numBursts; //read in thread variables

			for(int k = 0; k < t.numBursts-1; k++){//make bursts
				Burst b;
				getline(eventFile, line);
				stringstream ss3(line);
				ss3 >> b.cpuTime >> b.ioTime;
				t.bursts.push_back(b);
			}//end threads loop
			Burst b;
			getline(eventFile, line);
			stringstream ss4(line);
			ss4 >> b.cpuTime;
			//add to current thread
			t.bursts.push_back(b);
			p.threads.push_back(t);
		} // end thread loop
		processVector.push_back(p);	
		
} //end process loop
eventFile.close();
for(int i = 0; i < processVector.size(); i++){
	for(int j=0; j < processVector[i].numThreads; j++){
		Event e;
		e.time = processVector[i].threads[j].arrivalTime;
		e.et = Event::EventType::THREAD_ARRIVED;
		e.t = processVector[i].threads[j];
		e.p = processVector[i];
		e.threadNumber = j;
		e.processNumber = i;
		EventQueue.push(e);

	}
}
while(!EventQueue.empty()){
	string ets;
	string processType;
	Event e = EventQueue.top();
	switch(e.et){
		case 0: ets = "THREAD_ARRIVED";
		       break;
	}
	switch(e.p.pt){
		case 0:
			processType = "SYSTEM";
			break;
		case 1:
			processType = "INTERACTIVE";
			break;
		case 2: 
			processType = "NORMAL";
			break;
		case 3:
			processType = "BATCH";
			break;
	}
	cout << "Time: " << e.time << endl;	
	cout << "EVENT TYPE: " << ets << endl;
	cout << "Thread " << e.threadNumber << " in process " << e.processNumber << endl;
	cout << "Thread arrived" << endl;
	EventQueue.pop();
	cout << endl;
}
return 0;
}
