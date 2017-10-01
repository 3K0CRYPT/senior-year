/**
 * Contains the main() routine of what will eventually be your version of top.
 */

 #include <cstdlib>
 #include <ncurses.h>
 #include <algorithm> // for sort
 #include <getopt.h>
 #include "info/load_average_info.h"
 #include "info/memory_info.h"
 #include "info/process_info.h"
 #include "info/system_info.h"
 #include <time.h>
 #include <string.h>
 #include <sys/times.h>
 #include <unistd.h>

 #define no_argument 0 // must be defined for getopt
 #define required_argument 1 // ""
 #define optional_argument 2 // ""

 #define sort_PID 1
 #define sort_CPU 2
 #define sort_MEM 3
 #define sort_TIME 4

 int rate = 1000;
 int maxPids = 10;
 int sort_flag = 0;

using namespace std;

void printSysInfo(SystemInfo SI);
void printCPUInfo(vector<CpuInfo> CPUI);
void printPIDs(vector<ProcessInfo> PI, int uptime, int sort_flag);
void onHelp();
void processArgs(int argc, char** argv);


/**
 * Gets a character from the user, waiting for however many milliseconds that
 * were passed to timeout() below. If the letter entered is q, this method will
 * exit the program.
 */
void exit_if_user_presses_q() {
  char c = getch();

  if (c == 'q') {
    endwin();
    exit(EXIT_SUCCESS);
  }
}

SystemInfo SI;
vector<CpuInfo> CPUI;
vector<ProcessInfo> PI;
MemoryInfo MI;
LoadAverageInfo LAI;


/**
 * Entry point for the program.
 */
int main(int argc, char** argv) {
  processArgs(argc, argv);
  // ncurses initialization
  initscr();

  // Don't show a cursor.
  curs_set(FALSE);

  // Set getch to return after 1000 milliseconds; this allows the program to
  // immediately respond to user input while not blocking indefinitely.
  timeout(rate);



  while (true) {
    wclear(stdscr);

    // Display the counter using printw (an ncurses function)
    printw("Nicholas Zustak's top program\n");
    SI = get_system_info();
    CPUI = get_cpu_info();
    LAI = get_load_average();
    MI = get_memory_info();
    PI = get_all_processes(PROC_ROOT);
    printCPUInfo(CPUI);
    printw("\n");
    printSysInfo(SI);
    printw("\n");
    printPIDs(PI, SI.uptime, sort_flag);

    // Redraw the screen.
    refresh();

    // End the loop and exit if Q is pressed
    exit_if_user_presses_q();
  }

  // ncurses teardown
  endwin();

  return EXIT_SUCCESS;
}

void onHelp(){
  printf("\r\nNicholas Zustak's top");
  printf("\r\n-h or --help will show this, the help screen");
  printf("\r\n-d or --delay [DELAY] where [DELAY] is a number, for how long to delay updates in tenths of total_seconds");
  printf("\r\n-s or --sort-key [KEY], where [KEY] is either PID, CPU, MEM, or TIME");
  printf("\r\n\t if PID, sorts the process table by PID in ascending order");
  printf("\r\n\t if CPU, sorts the process table by CPU utilization in descending order");
  printf("\r\n\t if MEM, sorts the process table by memory utilization in descending order");
  printf("\r\n\t if TIME, sorts the process table by total cpu time executed, in descending order");
  endwin();
  exit(EXIT_SUCCESS);
}

void printSysInfo(SystemInfo SI) {
  int total_seconds = SI.uptime;
    int days = total_seconds/(3600*24); // Will floor. Ex, total_seconds less than 86400, days = 0.
    total_seconds = total_seconds - (days*(3600*24)); // Shave off excess seconds
    int hours = total_seconds/3600;
    total_seconds = total_seconds - (hours*3600); // Repeat
    int minutes = total_seconds/60;
    total_seconds = total_seconds - (minutes*60);
    int seconds = total_seconds;

    // Display everything using printw (an ncurses function)
    printw("\nLoad average: %4.2f [1 min], %4.2f [5 min], %4.2f [15 min]", SI.load_average.one_min,
     SI.load_average.five_mins,
     SI.load_average.fifteen_mins );
    printw("\nMemory: %d / %d MB (%d MB free)",
      (SI.memory_info.total_memory-SI.memory_info.free_memory-SI.memory_info.buffers_memory-SI.memory_info.cached_memory)/1000,
     SI.memory_info.total_memory/1000,
     SI.memory_info.free_memory/1000);
    printw("\nTasks: %d, Threads: %d, KernelThreads: %d; %d running",
     SI.num_processes,
     SI.num_threads,
     SI.num_kernel_threads,
     SI.num_running);
    printw("\nUptime: %.2d:%.2d:%.2d:%.2d\n", days, hours, minutes, seconds);
}

void printCPUInfo(vector<CpuInfo> CPUI) {
  // CPU times in "time units". This is fine because we're reporting percentages
  // Cast to double so the ratio can be calculated without flooring
  // proc/stat reports ALL CPUS as cpu, followed by cpu0, cpu1, etc.
  // Totals will be located in the first element of the passed in vector<CpuInfo>

  CpuInfo total = CPUI[0];

  for(int i = 1; i < CPUI.size(); i++) {
    printw("\nCPU %d:\tuser:%2.2f%%\tsystem:%2.2f%%\tidle:%2.2f%%",
      i,
      ((double)CPUI[i].user_time/(double)total.total_time()) * 100.0,
      ((double)CPUI[i].system_time/(double)total.total_time()) * 100.0,
      ((double)CPUI[i].idle_time/(double)total.total_time()) * 100.0);
  }
}

void processArgs(int argc, char** argv) {
  // Will use getopt to ensure proper number of flags are used, if at all
  // Sends errors / help screen if otherwise
  const char* const short_flag = "d:s:h";
  // option constructor (name, has_arg, flag, val), if flag ==0, then val is a unique int describing the option.
  // In this case, an int in the form of a char
  const option long_flag[] = {{"delay", required_argument, 0, 'd'},
                              {"sort-key", required_argument, 0, 's'},
                              {"help", no_argument, 0, 'h'},
                              {0,0,0,0}};
  int val = 0; // will get val from arguments as either 'd', 's', or 'h';
  int opt = 0;
  while(opt != -1) {
    //printw("\n attempting to get flags");
    opt = getopt_long(argc, argv, short_flag, long_flag, &val);

    if(val == -1) {
      // no arguments
      break;
    }
    switch(val) {
      case 'd':
        //printw("Flag d");
        rate = atoi(optarg) * 100;
        break;
      case 'h':
        printw("Flag h");
        onHelp();
        break;
      case 's':
        //printw("Flag s");
        // implement Sort
        if(strncmp(optarg, "PID", 3) == 0)
            sort_flag = 1;
        else if(strncmp(optarg, "CPU", 3) == 0)
            sort_flag = 2;
        else if(strncmp(optarg, "MEM", 3) == 0)
            sort_flag = 3;
        else if(strncmp(optarg, "TIME", 4) == 0)
            sort_flag = 4;
        break;
    }
  }
}

struct PID_ascending
{
    inline bool operator() (const ProcessInfo& PI1, const ProcessInfo& PI2)
    {
        return (PI1.pid < PI2.pid);
    }
};

struct CPU_descending
{
    inline bool operator() (const ProcessInfo& PI1, const ProcessInfo& PI2)
    {
        return (PI1.starttime < PI2.starttime);
    }
};

struct MEM_descending
{
    inline bool operator() (const ProcessInfo& PI1, const ProcessInfo& PI2)
    {
        return (PI1.resident > PI2.resident);
    }
};

struct TIME_descending
{
    inline bool operator() (const ProcessInfo& PI1, const ProcessInfo& PI2)
    {
        return ((PI1.utime + PI1.stime + PI1.cutime + PI1.cstime) >
                (PI2.utime + PI2.stime + PI2.cutime + PI2.cstime));
    }
};


void printPIDs(vector<ProcessInfo> PI, int uptime, int sort_flag) {
  printw("%-5s %-7s %-5s %-7s %-8s %-7s\n", "PID", "RSS", "STATE", "%CPU", "TIME", "COMMAND");
  vector<ProcessInfo> PI_sorted = PI; // ... it will be sorted
  if(sort_flag) {
      if(sort_flag == 1) {
        std::sort(PI.begin(), PI.end(), PID_ascending());
      }
      else if(sort_flag == 2) {
        std::sort(PI.begin(), PI.end(), CPU_descending());
      }
      else if(sort_flag == 3) {
        std::sort(PI.begin(), PI.end(), MEM_descending());
      }
      else if(sort_flag == 4) {
        std::sort(PI.begin(), PI.end(), TIME_descending());
      }
  }
  for(int i = 0; i < maxPids; i++) {
    int sysTicksPerS = sysconf(_SC_CLK_TCK);
    // THESE UNITS DON'T MAKE SENSE BUT IT WORKS
    double processTotalTime = PI_sorted[i].utime + PI_sorted[i].stime + PI_sorted[i].cutime + PI_sorted[i].cstime; // in ticks
    double processUseTime = uptime - ((double)PI_sorted[i].starttime/sysTicksPerS);
    double processCPUPct = ((processTotalTime/sysTicksPerS)/processUseTime) * 100;
    double processTimeSecs = processTotalTime/sysTicksPerS;
    int hours, minutes, seconds;
    hours = processTimeSecs/3600;
    processTimeSecs -= hours*3600;
    minutes = processTimeSecs/60;
    processTimeSecs -= minutes*60;
    seconds = processTimeSecs;
    char buff[10];
    int length = sprintf(buff, "%d:%d:%d", hours, minutes, seconds);
    printw("%5d %7li %5c %8.3f %8s %7s\n",
      PI_sorted[i].pid,
      PI_sorted[i].resident,
      PI_sorted[i].state,
      processCPUPct,
      buff,
      PI_sorted[i].command_line.c_str()
      );
  }
}
