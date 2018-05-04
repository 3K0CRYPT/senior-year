#include "save.h"
#include <fstream>
#include <iostream>
using namespace std;
static const string SAVE_PATH = "src/save/save.txt";
bool save(int level, int healthup, int laserup, int coolup, bool win){
	ofstream out(SAVE_PATH);
	if (out.fail()) { return false; }
	else {
		out << level << endl << healthup << endl << laserup << endl << coolup << endl << win;
		out.close();
		return true;
	}
}

bool load(int& level, int& healthup, int& laserup, int& coolup, bool& win){
	ifstream in(SAVE_PATH);
	if (in.fail()) { 
		cout << "No save file detected, starting with defaults...\n"; 
		level = 10, healthup = 0, laserup = 0, coolup = 0, win = false;
		return false; }
	else {
		while (!in.eof()) {
			in >> level >> healthup >> laserup >> coolup >> win;
		}
		return true;
	}
}