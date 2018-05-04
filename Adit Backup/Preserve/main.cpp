/* CSCI 261 Lab03B: Triangles Classifier + Options Menu
*
* Author:Michael Bartlett
*
* The goal of this lab is to practice the use of if-else statements to classify triangles based on their sides.
* It will also teach you how to correctly compare double values for equality using a tolerance factor and
* the use of a menu of options using the switch statement.
*/

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <string>   // For string class
#include <cmath>    // For math functions

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants or global variables below this comment.
const double TOLERANCE = 0.0001;

// Must have a function named "main", which is the starting point of a C++ program.
int main() {
	int option;                     // to store the user's option (1-5)
	double inputA, inputB, inputC;  // to store user's side measurements
	double a, b, c;
	double hyp, smal, med;          // to copy side measurements such that c >= a and c >= b
	bool isTriangle = false;        // states that side measuremenst can actually be use as sides of a triangle

	do {
		// show the menu 
		cout << "\n1. Enter measurements\n";
		cout << "2. Print measurements\n";
		cout << "3. Check triangle feasibility\n";
		cout << "4. Classify triangle\n";
		cout << "5. Exit\n";

		// read user's choice
		cout << "Please, choose an option: ";
		cin >> option;

		// ignore option if not 1-5
		if (option < 1 || option > 5) {
			cout << "Invalid option!\n";
			continue;
		}
		/******** INSERT YOUR CODE BELOW HERE ********/
		switch (option)
		{
		case 1: 
			cout << "Input 3 side lengths: "; cin >> inputA >> inputB >> inputC; 
			if (inputA <= 0 || inputB <= 0 || inputC <= 0) { cout << "!!Invalid mesaurement!!"; return false; }
			else {
				inputA = fabs(inputA), inputB = fabs(inputB), inputC = fabs(inputC);
				a = fabs(inputA), b = fabs(inputB), c = fabs(inputC);
				hyp = a, med = b, smal = c;
				//rank sides from largest to smallest
				if (hyp < b) { hyp = b; }
				if (hyp < c) { hyp = c; }
				if (smal > a) { smal = a; }
				if (smal > b) { smal = b; }
				if (hyp > c && smal < c) { med = c; }
				if (hyp > a && smal < a) { med = a; }
			}
			break;
		case 2: 
			cout << "\nSide A: " << hyp << "\nSide B: " << med << "\nSide C: " << smal << endl; break;
		case 3: 
			if (smal + med <= hyp || smal + hyp <= med || hyp + med <= smal) {
				cout << "Error: Not a triangle.\n"; break;
			}
			else { cout << "This is a valid triangle." << endl; isTriangle = true; break; }
		case 4: 
			if (isTriangle) {
				if (smal*smal + med*med - hyp*hyp <= TOLERANCE && smal*smal + med*med - hyp*hyp >= -1 * TOLERANCE) {
					cout << "This is a right triangle." << endl;
				}
				else if (pow(smal, 2) + pow(med, 2) - pow(hyp, 2) < TOLERANCE) {
					cout << "This is an obtuse triangle." << endl;
				}
				else {
					cout << "This is an acute triangle." << endl;
				}
			}
			else { cout << "Cannot determine invalid triangle." << endl; }
			break;
		default:
			break;
		}



		/******** INSERT YOUR CODE ABOVE HERE ********/
	} while (option != 5);

	return EXIT_SUCCESS; // signals the operating system that our program ended OK.
}