/**
 * This file contains the implementations of the builtin functions provided by
 * the shell (or will, once you've finished implementing them all).
 */

#include "shell.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <dirent.h>
#include <cstdlib>
#include <readline/history.h>

using namespace std;


int Shell::com_ls(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
    
 
  if (argv.size() <= 1) {
      argv.push_back("."); // use current directory by default
  }
    // argv should always have size of at least 1
    
  DIR* directory = opendir(argv[1].c_str()); // this tries to open the directory
    
  if(!opendir(argv[1].c_str())) {
      cout << "Error opening directory" << endl;
      return 1;
  }

    // Prints out everything in the directory
  for (dirent* current = readdir(directory); current; current = readdir(directory)) {
    cout << current->d_name << endl;
  }
    
  return 0;
}


int Shell::com_cd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  
  struct stat info; // hold directory info
  
  if(argv.size() == 1) {
      return 0; // get out, nothing entered
  }

  {
    const char *dir = argv[1].c_str();
    if (stat(dir, &info) != 0) {
      dir = (argv[1] + argv[2]).c_str(); // concatenate all arguments
      if (stat(dir, &info) != 0) {
          cout << "Error: can't see directory" << endl;
      }
    }
    else if (info.st_mode & S_IFDIR) {
        
      if(chdir(argv[1].c_str())!=0) {
            perror(argv[1].c_str());
            return -1;
        }
    }
    else {
      cout << "Can't change to nonexistent directory" << endl;
    }  
  }
    
  return 0;
}


int Shell::com_pwd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  char charbuffer[FILENAME_MAX];
  char *directory = getcwd(charbuffer, sizeof(charbuffer));
  if (directory) {
    cout << directory << endl;
  }
  return 0;
}


int Shell::com_alias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
    // for no arguments
  if(argv.size() == 1){
    for(map<string,string>::iterator i = aliases.begin(); 
        i != aliases.end(); 
        ++i) {
      printf("%s = %s\n",i->first.c_str(),i->second.c_str());
    }
    return 0;
  }
    
  // otherwise,
    
  string first="";
  int i = 0; // multiple loops will use i
      // use it to reference all arguments
  for(; i < argv[1].length(); i++){

    if(argv[1][i] != '='){
      first+=argv[1][i];
    } // concatenate all non '='
    else break;
      
  }
    
  if(i == argv[1].length()){
    printf("Error: not properly assigned\n");
    return 1;
  }
  i++;
  string second= "";
  for(; i < argv[1].length(); i++){
    second+=argv[1][i];
  }
  aliases[first]=second;
  return 0;
}


int Shell::com_unalias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
    // check for alias flag
    // unalias specific alias
  if(argv[1]!="-a") {
    for(int i = 1; i < argv.size(); i++){
      if(aliases.count(argv[i])==0){
        cout << "Error: alias not found." << endl;
        return 1;
      }
      else if(argv[i] == "-a"){
        cout << "Error: do not use -a flag for an existing alias" << endl;
        return 2;
      }
      aliases.erase(argv[i]); // unalias
    }
    return 0;
  }
  else if (argv.size() != 2) { 
    cout << "Error: do not use -a flag for an existing alias" << endl;
    return 2;
  }
    // Failing all this, clear all aliases
  aliases.clear();
    
  return 0;
}



int Shell::com_echo(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  for (int i = 1; i < argv.size(); i++) {
    cout << argv[i] << " ";
  }
  cout << endl;
  return 0;
}


int Shell::com_history(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  HIST_ENTRY** historylist = history_list();
    
    for( int i = 0; i < history_length; i++) {
        printf("%d: %s\n", i + history_base, historylist[i]->line);
    }
    
  return 0;
}


int Shell::com_exit(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  exit(EXIT_SUCCESS);
  return 0;
}
