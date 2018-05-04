// CSCI 261 Homework 06: Grade calculations || Author: Michael Bartlett
#include <iostream> // For cin, cout, etc.
#include <string>   // For string class
#include <iomanip>
#include <fstream>

using namespace std;
string Grade(double grade){
	if (grade >= 90.0) { return "A"; }
	else if (grade >= 80.0) { return "B"; }
	else if (grade >= 70.0) { return "C"; }
	else if (grade >= 60.0) { return "D"; }
	else { return "F"; }
}
int c261 = 0, c262 = 0, c306 = 0, c442 = 0, c562 = 0, c565 = 0, c580 = 0;
void classCount(int input){
	if (input == 261) c261++;
	if (input == 262) c262++;
	if (input == 306) c306++;
	if (input == 442) c442++;
	if (input == 562) c562++;
	if (input == 565) c565++;
	if (input == 580) c580++;
}
void main() {
	ifstream record("record.txt");
	ofstream output("output.txt");
	if (record.fail() || output.fail()) { cerr << "Error opening file(s)."; exit(1); }
	string line, first;
	int count = 0,course;
	double avg = 0;
	while (!record.eof()) {
		record >> line;
		//name:
		if (count == 0 || (count % 9) == 0) { output << "Name: "; }
		//first name
		else if (count == 1 || (count - 1) % 9 == 0) {	first = line; }
		//last name
		else if (count == 2 || (count - 2) % 9 == 0) { 
			if (first.length() > 0) { output << line << ", " << first << "\n"; first.clear(); }
		}
		//First class
		else if (count == 3 || (count - 3) % 9 == 0) {
			course = atoi((line.substr((line.find('-') + 1), 3)).c_str());
			classCount(course);
		}
		//First Grade
		else if (count == 4 || (count - 4) % 9 == 0) { avg += double(stod(line)); }
		//Second Class
		else if (count == 5 || (count - 5) % 9 == 0) {
			course = atoi((line.substr((line.find('-') + 1), 3)).c_str());
			classCount(course);
		}
		//Second Grade
		else if (count == 6 || (count - 6) % 9 == 0) { avg += double(stod(line)); }
		//Third class
		else if (count == 7 || (count - 7) % 9 == 0) {
			course = atoi((line.substr((line.find('-') + 1), 3)).c_str());
			classCount(course);
		}
		//Third grade
		else if (count == 8 || (count - 8) % 9 == 0) {
			avg += double(stod(line));
			avg /= 3.0;
			output << setprecision(5) << "Average Score: " << (round((avg*100))/100) << endl << "Grade: " << Grade(avg) << endl << endl;
			avg = 0.0;
		}
		count++;
	}
	output << "There are " << (c261 + c262 + c306 + c442) << " instances of students taking undergraduate level courses.\n";
	output << "There are " << (c562 + c565 + c580) << " instances of students taking graduate level courses.\n\n";
	output << "CSCI-261: Programming Concepts (C++) has " << c261 << " students.\n";
	output << "CSCI-262: Data Structures has " << c262 << " students.\n";
	output << "CSCI-306: Software Engineering has " << c306 << " students.\n";
	output << "CSCI-442: Operating Systems has " << c442 << " students.\n";
	output << "CSCI-562: Applied Algorithms & Data Structures has " << c562 << " students.\n";
	output << "CSCI-565: Distributed Computing Systems has " << c565 << " students.\n";
	output << "CSCI-580: Advanced High Performance Computing has " << c580 << " students.";
	record.close(); output.close();
}