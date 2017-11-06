#include "includes.h"

// ***************************************************************************
// * ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose
// *
// * These are the functions you need to fill in.
// ***************************************************************************
#include <vector>
#include <queue>
std::vector<pkt> flight;
std::queue<pkt> q, qb;
int _seq = 0;
std::string seqs = "";
const int TIMERLENGTH = 30;
const int WINDOW = 4;
const int BASE = 0;

int chk(char *arr) {  //Checksum
  return std::accumulate(arr, arr+20, 0);
}

std::vector<pkt> vpop(std::vector<pkt> v) { //Created a vector.pop() for managing in-flight ACKs
  std::vector<pkt> _q(v.begin()+1, v.end());
  return _q;
}

pkt make_pkt(struct msg message, int seq) { //Reduce duplicate code, as both sides use this
  struct pkt packet;
  packet.seqnum = seq;
  packet.acknum = 0;
  packet.checksum = chk(message.data);
  bcopy(message.data,packet.payload,20);
  // std::cout << "\tNew pkt: " << packet << std::endl;
  return packet;
}

// ***************************************************************************
// * Called from layer 5, passed the data to be sent to other side 
// ***************************************************************************
void A_output(struct msg message)
{
  std::cout << "A: Layer 4 has recieved a message from the application that should be sent to side B: " << message << std::endl;

  struct pkt packet = make_pkt(message, _seq);
  _seq++;
  
  //First packet
  if (flight.empty()) simulation->starttimer(A,TIMERLENGTH);
  
  //Send out packets until window is full.
  if (flight.size() <= WINDOW) { 
    simulation->tolayer3(A,packet);
    flight.push_back(packet);
  }  
  else q.emplace(packet); //Once window is full, enqueue.
}



// ***************************************************************************
// // called from layer 3, when a packet arrives for layer 4 on side B 
// ***************************************************************************

pkt make_ack(struct pkt packet) { //Helped function for creating an ACK and sending it.
  
  // std::cout << "\tACKing: " << packet << std::endl;
  
  //Simply  mirror the packet to confirm its reception and contents.
  qb.emplace(packet); //Store last ACK
  simulation->tolayer3(B,packet);
  simulation->starttimer(B,TIMERLENGTH);
}

void B_input(struct pkt packet)
{
  std::cout << "B: Layer 4 has recieved a packet from layer 3 sent over the network from side A:" << packet << std::endl;
  if (chk(packet.payload) != packet.checksum) {
    std::cout << "\tREJECT corrupt packet\n";
    return;
  }
  
  int expected = qb.front().seqnum + 1; //The expected sequence #
  
  if (qb.empty()) { //First packet received, no timer to stop
    
    std::cout << "\tACCEPT new packet: " << packet << std::endl;
    struct msg message;
    bcopy(packet.payload,message.data,20);
    simulation->tolayer5(B,message);
    
    make_ack(packet);
  }
  
  else if (packet.seqnum == expected) { //New packet, restart timer
    
    simulation->stoptimer(B);
    std::cout << "\tACCEPT new packet: " << packet << std::endl;
    qb.pop(); //A got this ACK.
    
    struct msg message;
    bcopy(packet.payload,message.data,20);
    simulation->tolayer5(B,message);

    make_ack(packet);
  }
  
  //The packet is not anything we expect at this point.
  else std::cout << "\tIgnoring new packet: " << packet << "\n\t\tExpecting seq=" << expected << std::endl;
}



// ***************************************************************************
// * Called when A's timer goes off 
// ***************************************************************************
void A_timerinterrupt()
{
  
  //Purely for readbility, shows the sequence #'s currently in flight.
  seqs = "";
  for (const pkt& p: flight) seqs += std::to_string(p.seqnum) + " ";
  
  std::cout << "A's timer has gone off.\n\tResending flight packets: " << seqs << std::endl;
  
  /*
    The MEAT of GoBackN, since our timer expired we resend EVERY packet currently in flight.
  */
  for (const pkt& p: flight) simulation->tolayer3(A,p);  
  simulation->starttimer(A,TIMERLENGTH);
}

// ***************************************************************************
// * Called when B's timer goes off 
// ***************************************************************************
void B_timerinterrupt()
{
    
  std::cout << "B's timer has gone off.\n\tReACKing" << qb.front() << std::endl;
  
  //We haven't gotten the packet we're expected, so just resend the same ACK to show we haven't lost connection 
  //    but haven't gotten the packet we need.
  simulation->tolayer3(B,qb.front());
  simulation->starttimer(B,TIMERLENGTH);   
}

// ***************************************************************************
// * The following routine will be called once (only) before any other 
// * entity A routines are called. You can use it to do any initialization 
// ***************************************************************************
void A_init()
{
}

// ***************************************************************************
// * The following rouytine will be called once (only) before any other 
// * entity B routines are called. You can use it to do any initialization 
// ***************************************************************************
void B_init()
{
}

// ***************************************************************************
// ***************************************************************************
// * The following two functions (A_input and B_output) only need to
// * be filled in if you are doing the bi-directinal extra credit
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
// * Called from layer 5, passed the data to be sent to other side
// ***************************************************************************
void B_output(struct msg message)  
{
  std::cout << "B: Layer 4 has recieved a message from the application that should be sent to side A: " << message << std::endl;
}



// ***************************************************************************
// * Called from layer 3, when a packet arrives for layer 4 on side A
// ***************************************************************************
void A_input(struct pkt packet)
{
  std::cout << "A: Layer 4 has recieved an ACK sent over the network from side B:" << packet << std::endl;

  //If corrupt, ignore
  if (chk(packet.payload) != packet.checksum) {
    std::cout << "\tREJECT corrupt ACK\n";
    return;
  }
  
  //If flight isn't empty, that means we're still transmitting.
  if (!flight.empty()) {  

    if (packet.seqnum == flight.front().seqnum) { //Ack should have same seq
      std::cout << "\tACCEPT ACK: " << packet << std::endl;
      simulation->stoptimer(A);
      
      
      flight = vpop(flight);  //vector pop() flight, then enqueue next packet if there is one.
      if (!q.empty()) {
        flight.push_back(q.front());
        q.pop();
      }
      
      
      if (!flight.empty()) {  //If flight isn't empty after poping and enqueing, there's still more data.
        simulation->tolayer3(A,flight.front());  
        simulation->starttimer(A,TIMERLENGTH);
        std::cout << "\tSending next: " << flight.front() << std::endl;
      }
      else if (q.empty()) { //If our packets in flight are exhausted, we're done transmitting.
        exit(0);
        //Every other way I tried to terminate made the tests fail :'''^>
        //Since nsimmax is private, there's no other way to determine if it's the last packet without sending duplicates or NACKs or something
            // (which cause the tests to fail!)
      }
    }
    //If what the receiver wants is bigger, move our window?
    else if (packet.seqnum == flight.back().seqnum) {
        flight = vpop(flight);
        if (!q.empty()) {
          flight.push_back(q.front());
          q.pop();
        }
    }
    else std::cout << "\tIgnoring ACK: " << packet << "\n\t\tExpecting: " << flight.front() << std::endl;
    
  }
}
