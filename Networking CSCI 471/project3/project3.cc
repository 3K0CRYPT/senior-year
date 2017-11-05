#include "includes.h"

// ***************************************************************************
// * ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose
// *
// * These are the functions you need to fill in.
// ***************************************************************************
#include <queue>
std::queue<pkt> q;
bool seq = false;
bool expected = true;
bool ACKed = true;
char _ack[20] = "ACK                ";
const int TIMERLENGTH = 10;

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
    starttimer(A,TIMERLENGTH);
  }  
  q.emplace(packet);
}



// ***************************************************************************
// // called from layer 3, when a packet arrives for layer 4 on side B 
// ***************************************************************************
void B_input(struct pkt packet)
{
  std::cout << "B: Layer 4 has recieved a packet from layer 3 sent over the network from side A:" << packet << std::endl;

  struct msg ack;
  bzero(ack.data,20);
  bcopy(packet.payload,ack.data,20);
  
  struct pkt response = make_pkt(ack, packet.seqnum);
  // std::cout << "\tACKing: " << response << std::endl;
  simulation->tolayer3(B,response);
  
  struct msg message;
  bcopy(packet.payload,message.data,20);
  simulation->tolayer5(B,message);
}



// ***************************************************************************
// * Called when A's timer goes off 
// ***************************************************************************
void A_timerinterrupt()
{
  std::cout << "Side A's timer has gone off." << std::endl;
}

// ***************************************************************************
// * Called when B's timer goes off 
// ***************************************************************************
void B_timerinterrupt()
{
    std::cout << "Side B's timer has gone off." << std::endl;
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
      stoptimer(A);
      q.pop();
      if (!q.empty()) {
        simulation->tolayer3(A,q.front());  
        starttimer(A,TIMERLENGTH);
      }
    }
  }
  else {
    // std::cout << "Last ack?\n";
  }
  

}
