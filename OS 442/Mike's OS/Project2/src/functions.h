#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
#include "structs.h"
#include "flags.h"
#include<getopt.h>
#include<iomanip>

enum algorithmType {FCFS, RR = 1, PRIORITY, CUSTOM};
algorithmType selectedAlgorithm;
bool per_thread, verbose;




vector<Process> populateProcess(string filename, Metrics &m){ //read in the file and populate the processes vector
ifstream eventFile(filename);
if(!eventFile.is_open()){
        cerr << "Error opening file" << endl;
}

int numProcesses;
int threadOverhead;
int processOverhead;
string line;
eventFile >> numProcesses >> m.threadOverhead >> m.processOverhead; // reads in basical overall data
vector<Process> processVector;
for(int i = 0; i < numProcesses; i++){ //loop through to get the number of processes
        getline(eventFile,line);
        while(line.empty()){
                getline(eventFile,line);
        }   
        int type;
                Process p;              //make a new process
                stringstream ss(line);
                ss >> p.processId >> type >> p.numThreads;  //read in the process variables
                p.pt = static_cast<Process::ProcType>(type);
		switch(p.pt){
			case 0: m.st.numThreads = p.numThreads;
				break;
			case 1: m.it.numThreads = p.numThreads;
				break;
			case 2: m.nt.numThreads = p.numThreads;
				break;
			case 3: m.bt.numThreads = p.numThreads;
				break;
		}

                for(int j = 0; j < p.numThreads; j++){ //make threads
        		getline(eventFile,line);
                        while(line.empty()){
                                getline(eventFile,line);
                        }
                        Thread t;
                        stringstream ss2(line);
                        ss2 >> t.arrivalTime >> t.numBursts; //read in thread variables
			t.parentId = p.processId;
			t.threadNum=j;
			t.ts = Thread::ThreadState::NEW;

                        for(int k = 0; k < t.numBursts-1; k++){//make bursts
                                Burst cpub;
				Burst iob;
                                getline(eventFile, line);
                                stringstream ss3(line);
				int cpuTime,ioTime;
                                ss3 >> cpuTime >> ioTime;
				
				cpub.type = Burst::BurstType::CPU;
				cpub.totalTime = cpuTime;
				cpub.remainingTime = cpuTime;
                                t.bursts.push_back(cpub);

				iob.type = Burst::BurstType::IO;
				iob.totalTime = ioTime;
				iob.remainingTime = ioTime;
				t.bursts.push_back(iob);
                        }//end threads loop
                        Burst b;
                        getline(eventFile, line);
                        stringstream ss4(line);
                        ss4 >> b.totalTime;
			b.remainingTime = b.totalTime;
			b.type = Burst::Burst::CPU;
                        //add to current thread
                        t.bursts.push_back(b);
                        p.threads.push_back(t);
                } // end thread loop
                processVector.push_back(p);     
                
} //end process loop
eventFile.close();
//cout << "returning!";
return processVector;
} //done with reading in the file


void processFlags(int argc, char** argv){ //process the user inputted flags
const char* const short_options = "t::v::a:h";
const option long_options[] = {
	{"per_thread", no_argument, 0, 't'},
	{"verbose", no_argument, 0, 'v'},
	{"algorithm", required_argument, 0, 'a'},
	{"help", no_argument, 0, 'h'}
	};
int optionNum = 0;
int opt;

while(true) {
opt = getopt_long(argc, argv, short_options, long_options, &optionNum);
if (opt == -1)
	break;
switch (opt){
	case 't':
		{
		printf("Flag: Thread");
		per_thread = true;
		}
	break;
	case 'v':
		{
		printf("Flag: Verbose");
		verbose = true;
		}
	break;
	case 'a':
		{
		printf("Flag: Algorithm\n");
		string selectedAlg = argv[optind-1];
		if (selectedAlg == "FCFS")
			selectedAlgorithm = FCFS;
		else if (selectedAlg == "RR"){
			selectedAlgorithm = RR;}
		else if (selectedAlg == "PRIORITY")
			selectedAlgorithm = PRIORITY;
		else if (selectedAlg == "CUSTOM")
			selectedAlgorithm = CUSTOM;
		else {
			printf("FCFS defaulted");
			selectedAlgorithm = FCFS;
		}
		}
	break;
	case 'h':
	default:
		help();
	break;

}
}
}

void printEvents(priority_queue<Event, vector<Event>, LowerArrivalTime> EventQueue){

while(!EventQueue.empty()){
        string ets;
        string processType;
	string eventDescription;
        Event e = EventQueue.top();
        switch(e.et){
	                case 0: ets = "THREAD_ARRIVED";
				eventDescription = "Thread has arrived";
	                       break;
			case 1: ets = "THREAD_DISPATCH_COMPLETED";
				eventDescription = "Thread switched from READY to RUNNING";
				break;
			case 2: ets = "PROCESS_DISPATCH_COMPLETED";
				eventDescription = "Processes switched";
				break;
			case 3: ets = "CPU_BURST_COMPLETED";
				eventDescription = "Thread switched from RUNNING to BLOCKED";
				break;
			case 4: ets = "IO_BURST_COMPLETED";
				eventDescription = "Thread switched from BLOCKED to RUNNING";
				break;
			case 5: ets = "THREAD_COMPLETED";
				eventDescription = "Thread completed";
				break;
			case 6: ets = "THEAD_PREEMPTED";
				break;
			case 7: ets = "DISPATCHER_INVOKED";
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
        cout << "Thread " << e.t.threadNum << " in process " << e.p.processId;
	cout << " [" << processType << "] " << endl;;
	cout << eventDescription << endl; 
        EventQueue.pop();
        cout << endl;
}
}

void printMetrics(Metrics &m){
cout << "Simulation complete!" << endl;
cout << "SYSTEM THREADS" << endl;
	cout << "\tTotal Count: " << m.st.numThreads << endl;
	double start = double(m.st.art) / double(m.st.numThreads);
	cout << "\tAvg Response time: " << setprecision(4) << start << endl;
	double statt = double(m.st.att) / double(m.st.numThreads);
	cout << "\tAvg turnaround time: " << statt << endl;

cout << "\nINTERACTIVE THREADS" << endl;
	cout << "\tTotal Count: " << m.it.numThreads << endl;
	double itart = double(m.it.art) / double(m.it.numThreads);
	cout << "\tAvg Response time: " << setprecision(4) << itart << endl;
	double itatt = double(m.it.att) / double(m.it.numThreads);
	cout << "\tAvg turnaround time: " << setprecision(4) << itatt << endl;

cout << "\nNORMAL THREADS" << endl;
	cout << "\tTotal Count: " << m.nt.numThreads << endl;
	double ntart = double(m.nt.art) / double(m.nt.numThreads);
	cout << "\tAvg Response time: " << m.nt.art << endl;
	double ntatt = double(m.nt.att) / double(m.nt.numThreads);
	cout << "\tAvg turnaround time: " << setprecision(4) << ntatt << endl;

cout << "\nBATCH THREADS" << endl;
	cout << "\tTotal Count: " << m.bt.numThreads << endl;
	double btart = double(m.bt.art) / double(m.bt.numThreads);
	cout << "\tAvg Response time: " << m.bt.art << endl;
	double btatt = double(m.bt.att) / double(m.bt.numThreads);
	cout << "\tAvg turnaround time: " << setprecision(4) << btatt << endl;

cout << "\nTotal elapsed time: " << m.totalTime << endl;
cout << "Total service time: " << m.serviceTime << endl;
cout << "Total I/O time: " << m.ioTime << endl;
cout << "Total dispatch time: " << m.overhead << endl;
cout << "Total idle time: " << m.CPUIdle << endl;
m.CPUUtil = double(m.serviceTime + m.overhead)/double(m.totalTime) *100;
cout << "CPU utilization: " << setprecision(4) << m.CPUUtil << "%" << endl;
m.CPUEffic = double(m.serviceTime)/double(m.totalTime) *100;
cout << "CPU efficiency: " << setprecision(4) << m.CPUEffic << "%" << endl;

}


void printPerThread(Metrics &m, vector<Process> p){
for(int i = 0; i < p.size(); i++){
	string processType;
        switch(p[i].pt){
	                case 0:
	                        processType = "[SYSTEM]";
	                        break;
	                case 1:
	                        processType = "[INTERACTIVE]";
	                        break;
	                case 2: 
	                        processType = "[NORMAL]";
	                        break;
	                case 3:
	                        processType = "[BATCH]";
	                        break;
	        }
	cout << "PROCESS " << i << " " << processType;
	for(int j=0; j < p[i].threads.size(); j++){
		cout << "\nTHREAD: " << j << ": ";
		cout << "\tARRIVED: " << p[i].threads[j].arrivalTime;
		int cpu=0, burst=0;
		for(int z = 0; z < p[i].threads[j].bursts.size();z++){
			if(p[i].threads[j].bursts[z].type == Burst::BurstType::CPU){
			       	cpu += p[i].threads[j].bursts[z].totalTime;
			}
			else {
				burst += p[i].threads[j].bursts[z].totalTime;
			}
	
		}
		cout << "\tCPU: " << cpu;
		cout << "\tI/O: " << burst;		
        switch(p[i].pt){
	                case 0:
	                        cout << "\tTRT: " << m.st.art;
				cout << "\tEND: " << m.st.att;
	                        break;
	                case 1:
	                        processType = "INTERACTIVE";
	                        cout << "\tTRT: " << m.it.art;
				cout << "\tEND: " << m.it.att;
	                        break;
	                case 2: 
	                        processType = "NORMAL";
	                        cout << "\tTRT: " << m.nt.art;
				cout << "\tEND: " << m.nt.att;
	                        break;
	                case 3:
	                        processType = "BATCH";
	                        cout << "\tTRT: " << m.bt.art;
				cout << "\tEND: " << m.bt.att;
	                        break;
	        }
	
	}
	cout << endl << endl;
}

}
