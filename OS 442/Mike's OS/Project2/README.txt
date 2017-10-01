Name: Michael McClary
CWID: 10633330

Full disclosure, the priority queue doesn't quite work, and the custom doesn't work at all. This project was incredibly hard, and without help there's no way I could implement these myself. I tried really, really hard, but fixing bugs and working out the logic was too hard. 
Otherwise, my project isn't cool at all. Nor interesting. It's just sad.

Files:
Besides the makefile, all of the files are contained within /src
algorithms.h - contains the meat of the project, here is where all of the functions for actually running the simulations lie
flags.h - Was going to hold more information for flags, but most of them got pushed to functions.h. Flags.h currently only holds the output for the help flag.
functions.h - contains generic functions, such as reading in the file, processing flags (this is where the things from flags.h would be put), and outputting the metrics and eventQueue.
main.cpp - Main. Simply calls the helper functions (as defined in functions.h) and has some logic for determining which algorithm to use.
structs.h - A collection of structs for various things, such as processes/threads/bursts/events, includes the struct I used to store metrics and the function to sort the priority queue.

I spent approximately 30 hours on this project, and still didn't get near completion. I got stuck on the priority queue and decided it would be best to turn in an incomplete program rather than take 20% to my grade and still potentially not fix the issues. As such, there is no Custom algorithm, it defaults to fcfs.

CUSTOM ALGORITHM: None, see above. Defaults to fcfs. I'm sorry, this was just too hard of an assignment for me, and using multiple queues is really what made it so hard. That's why priority and custom don't work.


