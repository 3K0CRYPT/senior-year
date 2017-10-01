/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "flag_parser/flag_parser.h"
#include "physical_address/physical_address.h"
#include "virtual_address/virtual_address.h"
#include "process/process.h"
#include "frame/frame.h"
#include "page_table/page_table.h"
#include "page/page.h"
#include "simulation/simulation/h"
#include <iostream>
#include <stdio.h>
using namespace std;


/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  // TODO: implement me
  FlagOptions flags;
  int num_processes;
  if(!parse_flags(argc, argv, &flags)) {
  	 cout << "Could not parse flags" << endl;
  	 print_usage();
  	 return 0;
  }
  ifstream in(flags.filename.c_str());
  fscanf(in, "%d\n", &num_processes);
  for(int i = 0; i < num_processes; i++) {
  	
  }
  return EXIT_SUCCESS;
}
