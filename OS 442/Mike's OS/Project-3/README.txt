Name: Michael McClary
CWID: 10633330
Default files: the only one added is my belady sim file, which I'll talk about later
So, in no particular order, these are the implemented files
-flag_parser - reads through the command line flags and sets the appropriate values
-frame - sets the values and functions for frames
-page - creates a page and sets all the correct attributes
-page_table - sets all of the necessary values and functions
-physical_address - creates proper output and translations
-process - implements process functions
-simulation - does the meat of the work, implements test functions
-virtual_address - translates decimal to binary string and proper outputs

Unusual/interesting features
-Has very similar output to the professor's

Approx number of hours spent
15? Definitely less than the other 2

Belady's Anomaly
	Belady's anomaly is an interesting feature that occurs when you increase the number of available frames,
but also increase the number of page faults. Logically, this shouldn't happen, since more frames would most likely
mean less replacing (page faults). It can only occur in FIFO algorithms. 

To show how Belady's anomaly works in my program, use the input file belady_sim. The command line should look like:
./mem-sim inputs/belady_sim
This uses the second process image to show an ordering that demonstrates Belady's anomaly when the frames ar increased.
I would guess that this anomaly occurs with FIFO because the FIFO algorithm is kind of lazy, as in it just takes
the oldest frame and replaces it, and at a median number of frames this becomes suboptimal.

Thanks for a great semester!!!
