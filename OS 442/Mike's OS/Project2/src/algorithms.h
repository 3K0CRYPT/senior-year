#include<iostream>
#include<stdlib.h>
#include<queue>
#include<sstream>

priority_queue<Event, vector<Event>, LowerArrivalTime> fcfsAlgorithm(vector<Process> processes, Metrics &m){
priority_queue<Event, vector<Event>, LowerArrivalTime> eventQueue;
queue<Thread> ready_queue;
queue<Thread> blocked_threads;
int simTime = 0;
bool simComplete = false;

while(!simComplete){//begin fcfs sim
for (int i = 0; i < processes.size(); i++){//if at the current time, add the thread to ready queue
	for (int j = 0; j < processes[i].threads.size(); j++){
	if (processes[i].threads[j].arrivalTime == simTime){
		ready_queue.push(processes[i].threads[j]);
		Event newEvent;
		newEvent.time = simTime;
		newEvent.et = Event::EventType::THREAD_ARRIVED;
		newEvent.p = processes[i];
		newEvent.t = processes[i].threads[j];
		eventQueue.push(newEvent);
		}
	}
}


//remove from blocked queue and add to ready queue if applicable
if(!blocked_threads.empty()){ //if not empty
	if (blocked_threads.front().bursts.front().remainingTime != 0){ //if burst isn't done, decrement by 1
		blocked_threads.front().bursts.front().remainingTime -= 1;
		m.ioTime++;
	}
	else {
		blocked_threads.front().bursts.erase(blocked_threads.front().bursts.begin());//else, remove burst from thread
		Event newEvent;
		newEvent.et = Event::EventType::IO_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[blocked_threads.front().parentId];
		newEvent.t = blocked_threads.front();
		eventQueue.push(newEvent);

		Event newEvent2;
		newEvent2.et = Event::EventType::THREAD_DISPATCH_COMPLETED;
		newEvent2.time = simTime;
		newEvent2.p = processes[blocked_threads.front().parentId];
		newEvent2.t = blocked_threads.front();
		eventQueue.push(newEvent2);
		simTime += m.threadOverhead;
		m.overhead += m.threadOverhead;

		ready_queue.push(blocked_threads.front());//add thread back to ready queue
		blocked_threads.pop();
	}
}


//run burst for first thread in ready queue
if (!ready_queue.empty()){
if(ready_queue.front().bursts.front().remainingTime != 0 && ready_queue.front().bursts.front().type == Burst::BurstType::CPU){//if not done and is CPU burst
	if(ready_queue.front().threadNum == 0 && ready_queue.front().bursts.front().totalTime == ready_queue.front().bursts.front().remainingTime){
		switch(ready_queue.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	ready_queue.front().bursts.front().remainingTime -= 1;//decrement remaining time by 1
	m.serviceTime++;
}
else { //ayy burst is complete
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue.front().parentId];
		newEvent.t = ready_queue.front();
		eventQueue.push(newEvent);
		ready_queue.front().bursts.erase(ready_queue.front().bursts.begin());//remove burst from thread
	if(ready_queue.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue.front().parentId];
		newEvent.t = ready_queue.front();
		eventQueue.push(newEvent);
		switch(ready_queue.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue.pop();
		if(!ready_queue.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}



//now we need to check if the next burst is an io burst
if(!ready_queue.empty()){
if (ready_queue.front().bursts.front().type == Burst::BurstType::IO){
	blocked_threads.push(ready_queue.front());
	ready_queue.front().bursts.erase(ready_queue.front().bursts.begin());
	ready_queue.pop();	
}
}
}
if(ready_queue.empty() && blocked_threads.empty()){ //if both queues are empty, we're done!!
		simComplete = true;
		m.totalTime = simTime;
		}

		else{
			simTime++;
		}
} //end of sim
return eventQueue;
}//end of fcfs



priority_queue<Event, vector<Event>, LowerArrivalTime> rrAlgorithm(vector<Process> processes, Metrics &m){
priority_queue<Event, vector<Event>, LowerArrivalTime> eventQueue;
int timeQuantum = 3;
int threadslice = 0;
queue<Thread> ready_queue;
queue<Thread> blocked_threads;
int simTime = 0;
bool simComplete = false;

while(!simComplete){
for (int i = 0; i < processes.size(); i++){//if at the current time, add the thread to ready queue
	for (int j = 0; j < processes[i].threads.size(); j++){
	if (processes[i].threads[j].arrivalTime == simTime){
		ready_queue.push(processes[i].threads[j]);
		Event newEvent;
		newEvent.time = simTime;
		newEvent.et = Event::EventType::THREAD_ARRIVED;
		newEvent.p = processes[i];
		newEvent.t = processes[i].threads[j];
		eventQueue.push(newEvent);
		}
	}
}


if(!blocked_threads.empty()){ //if not empty
	if (blocked_threads.front().bursts.front().remainingTime > 0){ //if burst isn't done, decrement by 1
		blocked_threads.front().bursts.front().remainingTime -= 1;
		m.ioTime += 1;
	}
	else {
		m.ioTime += blocked_threads.front().bursts.front().remainingTime;
		blocked_threads.front().bursts.front().remainingTime = 0;
		blocked_threads.front().bursts.erase(blocked_threads.front().bursts.begin());//else, remove burst from thread
		Event newEvent;
		newEvent.et = Event::EventType::IO_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[blocked_threads.front().parentId];
		newEvent.t = blocked_threads.front();
		eventQueue.push(newEvent);

		Event newEvent2;
		newEvent2.et = Event::EventType::THREAD_DISPATCH_COMPLETED;
		newEvent2.time = simTime;
		newEvent2.p = processes[blocked_threads.front().parentId];
		newEvent2.t = blocked_threads.front();
		eventQueue.push(newEvent2);
		simTime += m.threadOverhead;
		m.overhead += m.threadOverhead;

		ready_queue.push(blocked_threads.front());//add thread back to ready queue
		blocked_threads.pop();
	}
}
if (!ready_queue.empty()){
if(ready_queue.front().bursts.front().remainingTime > 0 && ready_queue.front().bursts.front().type == Burst::BurstType::CPU){//if not done and is CPU burst
	if(ready_queue.front().threadNum == 0 && ready_queue.front().bursts.front().totalTime == ready_queue.front().bursts.front().remainingTime){
		switch(ready_queue.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	if(threadslice != timeQuantum){
		ready_queue.front().bursts.front().remainingTime -= 1;//decrement remaining tme by 1
		m.serviceTime += 1;
		threadslice++;
	}
	else{
		if(ready_queue.front().bursts.front().remainingTime == 0){
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue.front().parentId];
		newEvent.t = ready_queue.front();
		eventQueue.push(newEvent);
		ready_queue.front().bursts.erase(ready_queue.front().bursts.begin());//remove burst from thread
			
		}
		threadslice = 0;
	}
	
}
else { //ayy burst is complete
		m.serviceTime += ready_queue.front().bursts.front().remainingTime;
		ready_queue.front().bursts.front().remainingTime = 0;//set remaining time to 0
		
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue.front().parentId];
		newEvent.t = ready_queue.front();
		eventQueue.push(newEvent);
		ready_queue.front().bursts.erase(ready_queue.front().bursts.begin());//remove burst from thread
	if(ready_queue.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue.front().parentId];
		newEvent.t = ready_queue.front();
		eventQueue.push(newEvent);
		switch(ready_queue.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue.pop();
		if(!ready_queue.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}}
if(!ready_queue.empty()){
if (ready_queue.front().bursts.front().type == Burst::BurstType::IO){
	blocked_threads.push(ready_queue.front());
	ready_queue.front().bursts.erase(ready_queue.front().bursts.begin());
	ready_queue.pop();	
}
}
if(ready_queue.empty() && blocked_threads.empty()){ //if both queues are empty, we're done!!
		simComplete = true;
		m.totalTime = simTime;
		}

		else{
			simTime++;
		}

}//end of sim complete
return eventQueue;
}





priority_queue<Event, vector<Event>, LowerArrivalTime> priorityAlgorithm(vector<Process> processes, Metrics &m){
priority_queue<Event, vector<Event>, LowerArrivalTime> eventQueue;
queue<Thread> ready_queue0;
queue<Thread> ready_queue1;
queue<Thread> ready_queue2;
queue<Thread> ready_queue3;
vector<Thread> blocked_threads;
int simTime = 0;
bool simComplete = false;
//blocked_threads.clear();

while(!simComplete){
for (int i = 0; i < processes.size(); i++){//if at the current time, add the thread to the appropriate ready queue
	for (int j = 0; j < processes[i].threads.size(); j++){
	if (processes[i].threads[j].arrivalTime == simTime){
		switch(processes[i].pt){
			case 0: ready_queue0.push(processes[i].threads[j]);
				break;
			case 1: ready_queue1.push(processes[i].threads[j]);
				break;
			case 2: ready_queue2.push(processes[i].threads[j]);
				break;
			case 3: ready_queue3.push(processes[i].threads[j]);
				break;
		}
		Event newEvent;
		newEvent.time = simTime;
		newEvent.et = Event::EventType::THREAD_ARRIVED;
		newEvent.p = processes[i];
		newEvent.t = processes[i].threads[j];
		eventQueue.push(newEvent);
		}
	}
}//end of arrival adding

if(!blocked_threads.empty()){
	cout << "NOT EMPTY!";
	for(int i =0; i < blocked_threads.size(); i++){
		if(blocked_threads[i].bursts.front().remainingTime > 0){//if io burst is not done
			blocked_threads.front().bursts[i].remainingTime -= 1;
			m.ioTime++;
			}
		else {//ioburst is done
		switch(processes[blocked_threads.front().parentId].pt){
		case 0:	ready_queue0.push(blocked_threads[i]);
			break;
		case 1: ready_queue1.push(blocked_threads[i]);
			break;
		case 2: ready_queue2.push(blocked_threads[i]);
			break;
		case 3: ready_queue3.push(blocked_threads[i]);
			break;
		}
		blocked_threads[i].bursts.erase(blocked_threads[i].bursts.begin()); //remove burst from thread
		}	
		
	}
} //end of io check
//check each queue
if(!ready_queue0.empty()){
	if(ready_queue0.front().bursts.front().remainingTime > 0 && ready_queue0.front().bursts.front().type == Burst::BurstType::CPU){
	if(ready_queue0.front().threadNum == 0 && ready_queue0.front().bursts.front().totalTime == ready_queue0.front().bursts.front().remainingTime){
		switch(ready_queue0.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	ready_queue0.front().bursts.front().remainingTime -= 1;//decrement remaining time by 1
	m.serviceTime++;
	
	}
	else if (ready_queue0.front().bursts.front().remainingTime > 0 && ready_queue0.front().bursts.front().type == Burst::BurstType::IO){
		//blocked_threads.push_back(ready_queue0.front());
	ready_queue0.front().bursts.erase(ready_queue0.front().bursts.begin());
		printf("\nIn here");
	
	}
else { //ayy burst is complete
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue0.front().parentId];
		newEvent.t = ready_queue0.front();
		eventQueue.push(newEvent);
		ready_queue0.front().bursts.erase(ready_queue0.front().bursts.begin());//remove burst from thread
	if(ready_queue0.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue0.front().parentId];
		newEvent.t = ready_queue0.front();
		eventQueue.push(newEvent);
		switch(ready_queue0.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue0.pop();
		if(!ready_queue0.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}
/*if(!ready_queue0.empty()){
if (ready_queue0.front().bursts.front().type == Burst::BurstType::IO){
	blocked_threads.push_back(ready_queue0.front());
	ready_queue0.front().bursts.erase(ready_queue0.front().bursts.begin());
	ready_queue0.pop();	
}
}*/

}//end of RQ0
else if(!ready_queue1.empty()){
	if(ready_queue1.front().bursts.front().remainingTime > 0 && ready_queue1.front().bursts.front().type == Burst::BurstType::CPU){
	if(ready_queue1.front().threadNum == 0 && ready_queue1.front().bursts.front().totalTime == ready_queue1.front().bursts.front().remainingTime){
		switch(ready_queue1.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	ready_queue1.front().bursts.front().remainingTime -= 1;//decrement remaining time by 1
	m.serviceTime++;
	
	}
else { //ayy burst is complete
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue1.front().parentId];
		newEvent.t = ready_queue1.front();
		eventQueue.push(newEvent);
		ready_queue1.front().bursts.erase(ready_queue1.front().bursts.begin());//remove burst from thread
	if(ready_queue1.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue1.front().parentId];
		newEvent.t = ready_queue1.front();
		eventQueue.push(newEvent);
		switch(ready_queue1.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue1.pop();
		if(!ready_queue1.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}
if(!ready_queue1.empty()){
if (ready_queue1.front().bursts.front().type == Burst::BurstType::IO){
	//blocked_threads.push_back(ready_queue1.front());
	ready_queue1.front().bursts.erase(ready_queue1.front().bursts.begin());
	ready_queue1.pop();	
}
}

}//end of RQ1
else if(!ready_queue2.empty()){
	if(ready_queue2.front().bursts.front().remainingTime > 0 && ready_queue2.front().bursts.front().type == Burst::BurstType::CPU){
	if(ready_queue2.front().threadNum == 0 && ready_queue2.front().bursts.front().totalTime == ready_queue2.front().bursts.front().remainingTime){
		switch(ready_queue2.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	ready_queue2.front().bursts.front().remainingTime -= 1;//decrement remaining time by 1
	m.serviceTime++;
	
	}
else { //ayy burst is complete
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue2.front().parentId];
		newEvent.t = ready_queue2.front();
		eventQueue.push(newEvent);
		ready_queue2.front().bursts.erase(ready_queue2.front().bursts.begin());//remove burst from thread
	if(ready_queue2.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue2.front().parentId];
		newEvent.t = ready_queue2.front();
		eventQueue.push(newEvent);
		switch(ready_queue2.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue2.pop();
		if(!ready_queue2.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}

}//end of RQ2
else if(!ready_queue3.empty()){
	if(ready_queue3.front().bursts.front().remainingTime > 0 && ready_queue3.front().bursts.front().type == Burst::BurstType::CPU){
	if(ready_queue3.front().threadNum == 0 && ready_queue3.front().bursts.front().totalTime == ready_queue3.front().bursts.front().remainingTime){
		switch(ready_queue3.front().parentId){
			case 0: m.st.art += simTime;
				break;
			case 1: m.it.art += simTime;
				break;
			case 2: m.nt.art += simTime;
				break;
			case 3: m.bt.art += simTime;
				break;
		}
		}
	ready_queue3.front().bursts.front().remainingTime -= 1;//decrement remaining time by 1
	m.serviceTime++;
	
	}
else { //ayy burst is complete
		Event newEvent;
		newEvent.et = Event::EventType::CPU_BURST_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue3.front().parentId];
		newEvent.t = ready_queue3.front();
		eventQueue.push(newEvent);
		ready_queue3.front().bursts.erase(ready_queue3.front().bursts.begin());//remove burst from thread
	if(ready_queue3.front().bursts.empty()){//if the thread at the beginning is out of bursts, remove it
		Event newEvent;
		newEvent.et = Event::EventType::THREAD_COMPLETED;
		newEvent.time = simTime;
		newEvent.p = processes[ready_queue3.front().parentId];
		newEvent.t = ready_queue3.front();
		eventQueue.push(newEvent);
		switch(ready_queue3.front().parentId){
			case 0: m.st.att += simTime;
				break;
			case 1: m.it.att += simTime;
				break;
			case 2: m.nt.att += simTime;
				break;
			case 3: m.bt.att += simTime;
				break;
		}
		ready_queue3.pop();
		if(!ready_queue3.empty()){
			simTime += m.processOverhead;
			m.overhead += m.processOverhead;
		}

	}
}

}//end of RQ3

if(blocked_threads.empty() && ready_queue0.empty() && ready_queue1.empty() && ready_queue2.empty() && ready_queue3.empty()){
		simComplete = true;
		m.totalTime = simTime;
		}
		else {
		simTime++;
		}

}//end of simulation
return eventQueue;
}

priority_queue<Event, vector<Event>, LowerArrivalTime> customAlgorithm(vector<Process> processes, Metrics &m){
priority_queue<Event, vector<Event>, LowerArrivalTime> eventQueue;
queue<Thread> ready_queue;
queue<Thread> blocked_threads;
int simTime = 0;
bool simComplete = false;
while(!simComplete){





}//end of simulation
return eventQueue;
}
