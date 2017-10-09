#include "includes.h"

#define argNone 0
#define argReq 1
#define argOpt 2

using namespace std;

string fileName;
int processQuantity, switchOverhead_thread, switchOverhead_process;
priority_queue<Event, vector<Event>, Prioritized> PQ;
bool h_flag, t_flag, v_flag, a_flag = false;

void argHandler(int argc, char *argv[]) {
	fileName = argv[argc - 1];
	for (int i = 1; i < argc-1; i++) {
		if (string(argv[i]).compare("-h") == 0 || string(argv[i]).compare("--help") == 0) h_flag = true;
		if (string(argv[i]).compare("-v") == 0 || string(argv[i]).compare("--verbose") == 0) v_flag = true;
		if (string(argv[i]).compare("-a") == 0 || string(argv[i]).compare("--algorithm") == 0) {
			cout << "Test: " << argv[i+1][0] << endl;
			a_flag = true;
		}
		if (string(argv[i]).compare("-t") == 0 || string(argv[i]).compare("--per-thread") == 0) t_flag = true;
	}
}

int main(int argc, char *argv[]) {
	argHandler(argc, argv);

	// argHandler populates filename, create ifstream
	ifstream file(fileName);

	if (file.fail()) cerr << "Error opening " << fileName << endl;

	vector<Process> processes;

	// Amalgamate data in specified/expected order
	file >> processQuantity >> switchOverhead_thread >> switchOverhead_process;
	string l;

	for (int i = 0; i < processQuantity; i++)	{
		Process process;
		
		getline(file, l); //Read in the line
		if (l.empty()) while (l.empty() | file.eof()) getline(file, l); //Until it's not empty
		stringstream ss(l);	//Create stream from line
		ss >> process.processID >> process.inttype >> process.threadQuantity;

		process.state = static_cast<priorityState>(process.inttype);
		for (int j = 0; j < process.threadQuantity; j++) {
			//Run the same general procedure for data feeding
			Thread thread;

			getline(file, l);
			if (l.empty()) while (l.empty() | file.eof()) getline(file, l);
			stringstream _ss(l);
			
			_ss >> thread.arriveTime >> thread.burstQuantity;
			for (int k = 0; k < thread.burstQuantity - 1; k++) {
				Burst burst;
				getline(file, l);
				stringstream __ss(l);
				__ss >> burst.cpuTime >> burst.ioTime;
				thread.bursts.push_back(burst);
			}
			
			Burst final;
			getline(file, l);
			stringstream ___ss(l);
			___ss >> final.cpuTime;
			thread.bursts.push_back(final);
			process.threads.push_back(thread);
		}
		processes.push_back(process);
	}
	file.close();
	for (u_int i = 0; i < processes.size(); i++)	{
		for (int j = 0; j < processes[i].threadQuantity; j++) {
			Event event;
			event.time = processes[i].threads[j].arriveTime;
			event.type = eventType::THREAD_ARRIVED; //This deliverable only deals with arrived threads
			event.thread = processes[i].threads[j];
			event.process = processes[i];
			event.threadNum = j;
			event.processNum = i;
			PQ.push(event);
		}
	}

	if (h_flag) cout << "help flag triggered." << endl;
	if (a_flag) cout << "algorithm flag triggered." << endl;
	if (t_flag) cout << "thread flag triggered." << endl;
	if (v_flag) cout << "verbose flag triggered." << endl;
	
	
	cout << "========================" << endl;
	cout << "||  Processed Events  ||" << endl;
	cout << "========================" << endl;
	while (!PQ.empty())
	{
		string eventtype;
		string state;
		Event event = PQ.top();

		eventtype = "THREAD_ARRIVED";
		switch (event.process.state) {
		case priorityState::SYSTEM:
			state = "SYSTEM";
			break;
		case priorityState::INTERACTIVE:
			state = "INTERACTIVE";
			break;
		case priorityState::NORMAL:
			state = "NORMAL";
			break;
		case priorityState::BATCH:
			state = "BATCH";
			break;
		}
		cout << "TIME:\t" << event.time << endl;
		cout << "TYPE:\t" << eventtype << endl;
		cout << "PROCESS TYPE:\t" << state << endl;
		cout << "Thread " << event.threadNum << " in process " << event.processNum << endl;
		cout << endl
			 << endl;
		PQ.pop();
	}

	return 0;
}
