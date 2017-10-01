#include<iostream>

void help(){
printf("\r===================HELP===============\n");
printf("\rOptions:\n");
printf("\r-v OR --verbose: Display information about every event and scheduling decision\n");
printf("\r-t OR --per_thread: Display overall statistics about the simulation\n");
printf("\r-a OR --algorithm ALGORITHM: Allows user to choose the scheduling algorithm\n");
printf("\r-h OR --help: Displays this help message\n");
exit(EXIT_SUCCESS);
}
