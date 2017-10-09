#pragma once

enum burstType {CPU, IO};

const char* burstType_str[] = {"CPU", "IO"};

struct Burst {
	burstType type;
	int cpuTime;
	int ioTime;
};
