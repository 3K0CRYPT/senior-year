#include <stdlib.h>
#pragma once

enum burstType {CPU, IO};

const char* btypes[] = {"CPU", "IO"};

struct Burst {
	burstType type;
	int cpuTime;
	int ioTime;
};
