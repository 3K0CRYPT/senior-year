#pragma once

struct Burst {
	enum Burst_Type {CPU, IO};
	Burst_Type type;

	int total_time;
	int remaining_time;
};