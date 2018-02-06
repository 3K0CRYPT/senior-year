1. Michael Bartlet 10603355
2. C++
3. x64 Windows 10 (also successfully compiled on Raspbian aka Debian)
4. A single file that contains all methods/members
5. To compile:

Make sure you have build-essential with g++ installed. Commands to use aptitude to install it (on Debian-based Linux):
	sudo apt-get update
	sudo apt-get install build-essential
	
The included Makefile should be sufficient, so simplying run "make" from terminal in the project's directory to compile to a binary.

IF THE MAKEFILE FAILS: Using g++, run in a teriminal in the directory:
	g++ -std=c++14 find_route.cpp -o find_route

To execute the resulting binary in terminal:
	./find_route input1.txt Bremen Frankfurt

***I've included an .exe compiled on x64 Windows 10 if all else fails.
If even this fails, shoot me an e-mail at mbartlet@mines.edu and I can give more specific instructions