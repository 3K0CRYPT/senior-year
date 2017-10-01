#include "load_average_info.h"
#include <fstream>
#include <iostream>

using namespace std;


LoadAverageInfo get_load_average() {
  // TODO: implement me
  LoadAverageInfo loadavg;

ifstream loadavg_file(PROC_ROOT "/loadavg");

if (!loadavg_file) {
	cerr << "Unable to read from /proc/loadavg";
	return loadavg;
}

loadavg_file
	>> loadavg.one_min
	>> loadavg.five_mins
	>> loadavg.fifteen_mins;

loadavg_file.close();

  return loadavg;
}
