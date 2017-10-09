/**
 * This file contains implementations of the functions that provide
 * tab-completion for the shell.
 *
 * You will need to finish the implementations of the completion functions,
 * though you're spared from implementing the high-level readline callbacks with
 * their weird static variables...
 */

#include "shell.h"
#include <cstdlib>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <dirent.h>

using namespace std;

extern char** environ;

void Shell::get_env_completions(const char* text, vector<string>& matches) {
  // TODO: implement
    for (char **env = environ; *env; ++env) {
        string dname = *env;
        if(dname.find(text)) {
            matches.push_back(dname);
        }
    }
}


void Shell::get_command_completions(const char* text, vector<string>& matches) {
  // TODO: implement
    string path = "";
    vector<string> paths;
    for (const char* env = getenv("PATH"); *env; ++env) {
        if(*env == ':') {
            paths.push_back(path);
            path = "";
            continue;
        }
        path += *env;
    }
    for(auto dir : paths) {
        DIR *direct;
        struct dirent *ent;
        // http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
        if ((direct = opendir(dir.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (direct)) != NULL) {
                string dname = ent->d_name;
                if(dname.find(text)) {
                    matches.push_back(dname);
                }
            }
            closedir (direct);
        } else {
            /* could not open directory */
            std::cout << dir.c_str();
            perror ("Tab error");
        }
    }
}


char** Shell::word_completion(const char* text, int start, int end) {
  char** matches = NULL;

  if (text[0] == '$') {
    matches = rl_completion_matches(text, env_completion_generator);
  } else if (start == 0) {
    matches = rl_completion_matches(text, command_completion_generator);
  } else {
    // We get directory matches for free (thanks, readline!).
  }

  return matches;
}


char* Shell::env_completion_generator(const char* text, int state) {
  // A list of all the matches.
  // Must be static because this function is called repeatedly.
  static vector<string> matches;

  // If this is the first time called, construct the matches list with
  // all possible matches.
  if (state == 0) {
    getInstance().get_env_completions(text, matches);
  }

  // Return a single match (one for each time the function is called).
  return pop_match(matches);
}


char* Shell::command_completion_generator(const char* text, int state) {
  // A list of all the matches.
  // Must be static because this function is called repeatedly.
  static vector<string> matches;

  // If this is the first time called, construct the matches list with
  // all possible matches.
  if (state == 0) {
    getInstance().get_command_completions(text, matches);
  }

  // Return a single match (one for each time the function is called).
  return pop_match(matches);
}


char* Shell::pop_match(vector<string>& matches) {
  if (matches.size() > 0) {
    const char* match = matches.back().c_str();

    // Delete the last element.
    matches.pop_back();

    // We need to return a copy, because readline deallocates when done.
    char* copy = (char*) malloc(strlen(match) + 1);
    strcpy(copy, match);

    return copy;
  }

  // No more matches.
  return NULL;
}
