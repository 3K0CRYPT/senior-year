# Project 3
Created by Nicholas Zustak

A simulation of a trivial OS memory manager.

Files in the Simulation
inputs/*
	The simulation files. sim_1 and belady files reference process_1,
	process_2, and process_3; these are parsed and run by ./mem-sim
src/physical_address/*
	Contains an implementation of a physical address class. Has both frame and 
	offset portions. Used for display purposes, mostly.
src/virtual_address/*
	Contains an implementation of a virtual address class. Virtual addresses are 
	read in from the process input files, and the simulation converts them to 
	physical addresses
src/page/*
	Implementation of a page class. A page is a chunk of a process that holds 
	data. In this simulation, the data is just nonsensical chars read in from 
	the input file.
src/frame/*
	A frame structure. It represents a frame held in main memory by the OS.
	It holds a page, as well as the process corresponding to that page, to
	imitate an OS data structure/reference table.
src/page_table/*
	A class for representing the page table held by a process. Doesn’t hold 
	actual page objects; rather, it holds a “row” vector, which uses page
	numbers as indices. The row holds information about the page, including
	its presence in the frame, which frame, when it was loaded in, and when
	it was last accessed.
src/process/*
	A representation of a process, who’s sole purpose is to hold pages and a 
	page table. It also keeps track of how many pages are in main memory (through
	use of its page table) and how many faults it has experienced.
src/flag_parser/*
	A class designed for parsing the flags input by the user when running the 
 	program. Flags include replacement strategy (LRU or FIFO), max frame size, 
	and output (option for verbose). Helper class for main.cpp
src/simulation/*
	Wraps everything together. Includes functions for performing memory accesses 
	given virtual addresses and for handling page faults, and finally for 
	displaying all the results 
mem-sim
	This is the executable file that calls on main.cpp and runs the Simulation.


There are no real interesting features to this program. I do go out of my way 
to display the char that was accessed from the virtual memory, though, on 
verbose output. It doesn’t run on my Mac as it stands; there was a lot of translating 
I had to do once I brought it into Alamode. C++ is finicky.

I spent approximately 30 hours on this assignment. I appreciate the starter code and testing suite.


Belady’s anomaly (BA)

BA is the phenomenon in which the rate of page faults increase as a process is given
more frames, for certain replacement algorithms. Intuitively, one would think that 
if there are more frames for pages to occupy, there would be less swapping out of 
pages, and thus less faults. However, upon simulating this memory manager (and in
real life operating systems), for a First In First Out replacement strategy (where 
you swap out page added the earliest of all the current pages), the fault rate appears to increase with frame size. Sometimes.

To see this anomaly, after making the program with “make”, type:
./mem-sim -v —strategy FIFO —max-frames 5 inputs/belady
And look at the fault rates.
Then type
./mem-sim -v —strategy FIFO —max-frames 6 inputs/belady
And look at the fault rates.

This seems to occur because increasing the number of frames changes the rate in which
pages are swapped out. With more frames, recently requested pages can remain at the bottom of the queue for a longer time, and with some sets of page requests, this can 
result in more faults.






