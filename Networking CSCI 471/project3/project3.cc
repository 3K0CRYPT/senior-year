#include "includes.h"

// ***************************************************************************
// * ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose
// *
// * These are the functions you need to fill in.
// ***************************************************************************
#include <queue>
std::queue<pkt> q;
std::queue<pkt> qb;
bool seq = false;
bool expected = true;
bool ACKed = true;
char _ack[20] = "ACK                ";
const int TIMERLENGTH = 30;

pkt make_pkt(struct msg message, int seq) {
  struct pkt packet;
  packet.seqnum = (int)seq;
  packet.acknum = 0;
  packet.checksum = 1;
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

  struct pkt packet = make_pkt(message, seq);
  seq = !seq;

  if (q.empty()) { 
    simulation->tolayer3(A,packet);
    simulation->starttimer(A,TIMERLENGTH);
  }  
  q.emplace(packet);
}



// ***************************************************************************
// // called from layer 3, when a packet arrives for layer 4 on side B 
// ***************************************************************************
pkt make_ack(struct msg message, int seq) {
  
  struct pkt response = make_pkt(message, seq);
  std::cout << "\tACKing: " << response << std::endl;
  
  qb.emplace(response); //Store last ACK
  simulation->tolayer3(B,response);
  simulation->starttimer(B,TIMERLENGTH);
}

void B_input(struct pkt packet)
{
  std::cout << "B: Layer 4 has recieved a packet from layer 3 sent over the network from side A:" << packet << std::endl;
  packet.payload[20] = '\0';  //Replace garbage with proper nullterminator.
  
  //Send ACK for most recent packet
  
  
  if (qb.empty()) {
    struct msg message;
    bcopy(packet.payload,message.data,20);
    simulation->tolayer5(B,message);
    
    make_ack(message, packet.seqnum);
  }
  
  else if (packet.seqnum != qb.front().seqnum) { //New packet
    qb.pop(); //A got this ACK.
    
    struct msg message;
    bcopy(packet.payload,message.data,20);
    simulation->tolayer5(B,message);
    
    make_ack(message, packet.seqnum);
  }
    else std::cout << "Ignoring new packet: " << packet << "\n\t\tExpecting: " << qb.front() << std::endl;
}



// ***************************************************************************
// * Called when A's timer goes off 
// ***************************************************************************
void A_timerinterrupt()
{
  std::cout << "\tA's timer has gone off.\n\tResending: " << q.front() << std::endl;
  
  simulation->tolayer3(A,q.front());  
  simulation->starttimer(A,TIMERLENGTH);
}

// ***************************************************************************
// * Called when B's timer goes off 
// ***************************************************************************
void B_timerinterrupt()
{
    std::cout << "\tB's timer has gone off.\n\tReACKing" << qb.front() << std::endl;
    
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
  struct msg message;
  bzero(message.data,20);
  bcopy(packet.payload,message.data,20);
  message.data[20] = '\0';  //Replace garbage with proper nullterminator.
  // simulation->tolayer5(A,message);
  
  if (!q.empty()) {
    q.front().payload[20] = '\0'; //Replace garbage with proper nullterminator.

    // if (packet.seqnum == q.front().seqnum) std::cout << "\tSequence # are equal! (" << q.front().seqnum << ")\n";
    // if (strcmp(message.data,q.front().payload) == 0) std::cout << "\tPayloads are equal! (" << q.front().payload << ")\n";

    if ((packet.seqnum == q.front().seqnum) && (strcmp(message.data,q.front().payload) == 0)) { //Ack should have same payload + seq
      simulation->stoptimer(A);
      q.pop();
      if (!q.empty()) {
        std::cout << "\tSending: " << q.front();
        simulation->tolayer3(A,q.front());  
        simulation->starttimer(A,TIMERLENGTH);
      }
    }
    else std::cout << "\tIgnoring ACK: " << packet << "\n\t\tExpecting: " << q.front() << std::endl;
    
  }
  else {
    // std::cout << "Last ack?\n";
  }
  

}
