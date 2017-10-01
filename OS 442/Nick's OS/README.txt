README

Creator: Nicholas Zustak

Noteworthy Files 
-src/info/cpu_info.cpp
	This file contains methods to retrieve information about each processor on the system, including time measurements in teach state. See associated cpu_info.h for descriptions.
-src/info/memory_info.cpp
	This file contains methods to retrieve information about the memory usage on the system, including swap memory, total memory, memory used in the kernel, memory used by user, etc. See associated memory_info.h for descriptions.
-src/info/system_info.cpp
	This file contains methods to retrieve information about the system itself, including system uptime, including load averages, number of processes, threads, etc. See associated system_info.h. Pulls information from -src/info/memory_info. 
-src/info/process_info.cpp
	This file contains methods to retrieve information about the processes running on the system. There are many, many different pieces of information about each process to be pulled. See associated process_info.h for a description of all of them.

I spent 40+ hours on this project. 

The terminal size shouldn’t matter; the minimum size opened on the Alamode machines will be fine.

