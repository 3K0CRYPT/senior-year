#pragma once
#include <string>


enum class ReplacementStrategy {
  FIFO,
  LRU
};

struct FlagOptions {

  std::string filename;

  ReplacementStrategy strategy = ReplacementStrategy::FIFO;
  bool verbose = false;

  int max_frames = 10;
};

void print_usage();

bool parse_flags(int argc, char** argv, FlagOptions& flags);
