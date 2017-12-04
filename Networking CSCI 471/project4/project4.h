//
//  project4.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef project4_h
#define project4_h

// System include files
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <pcap/pcap.h>

// Include files specific to this project.
#include "resultsC.h"

// Prototype for the packet processor, called once for each packet.
void pk_processor(u_char *, const struct pcap_pkthdr *, const u_char *);

// Garbage needed for the debugging functions.
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>

#define TRACE BOOST_LOG_TRIVIAL(trace) << "TRACE: " 
#define DEBUG BOOST_LOG_TRIVIAL(debug)  << "DEBUG: " 
#define INFO BOOST_LOG_TRIVIAL(info)   << "INFO: " 
#define WARNING BOOST_LOG_TRIVIAL(warning) << "WARNING: " 
#define ERROR BOOST_LOG_TRIVIAL(error)  << "ERROR: " 
#define FATAL BOOST_LOG_TRIVIAL(fatal)  << "FATAL: " 
#define ENDL  " (" << __FILE__ << ":" << __LINE__ << ")"

#endif
