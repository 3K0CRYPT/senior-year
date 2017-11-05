#include "includes.h"

// ***************************************************************************
// * ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose
// *
// * These are the functions you need to fill in.
// ***************************************************************************
#include <queue>
queue<pkt> q;
bool seq = true;
bool ACKed = true;

pkt make_pkt(struct msg message) {
  struct pkt packet;
  packet.seqnum = (int)(seq = !seq);
  packet.acknum = 1;
  packet.checksum = 0;
  bcopy(message.data,packet.payload,20);
  std::cout << "\tNew pkt: " << packet << std::endl;
  return packet;
}

// ***************************************************************************
// * Called from layer 5, passed the data to be sent to other side 
// ***************************************************************************
void A_output(struct msg message)
{
  std::cout << "Layer 4 on side A has recieved a message from the application that should be sent to side B: " << message << std::endl;

  
  struct pkt packet;
  packet.seqnum = 1;
  packet.acknum = 1;
  packet.checksum = 0;
  bcopy(message.data,packet.payload,20);

  simulation->tolayer3(A,packet);
}



// ***************************************************************************
// // called from layer 3, when a packet arrives for layer 4 on side B 
// ***************************************************************************
void B_input(struct pkt packet)
{
  std::cout << "Layer 4 on side B has recieved a packet from layer 3 sent over the network from side A:" << packet << std::endl;

  struct pkt response;
  response.seqnum = 1;
  response.acknum = 1;
  response.checksum = 0;
  bcopy(("ACK").data(),response.payload,20);
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
  std::cout << "Layer 4 on side B has recieved a message from the application that should be sent to side A: " << message << std::endl;
}



// ***************************************************************************
// * Called from layer 3, when a packet arrives for layer 4 on side A
// ***************************************************************************
void A_input(struct pkt packet)
{
  std::cout << "Layer 4 on side A has recieved a packet sent over the network from side B:" << packet << std::endl;
  struct msg message;
  bcopy(packet.payload,message.data,20);
  simulation->tolayer5(B,message);
  
  std::cout << packet.payload << std::endl;
  if (std::to_string(packet.payload) == "ACK") std::cout << "Omega dicks\n";
  if (!q.empty()) {
    simulation->tolayer5(A,q.front());
    q.pop();
  }
  
}
