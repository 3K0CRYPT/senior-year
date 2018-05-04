#pragma once
class Box {
public:
	Box();
	Box(int h, int w, int d);
	int GetHeight();
	int GetDepth();
	int GetWidth();
	void SetWidth(int w);
	void SetHeight(int h);
	void SetDepth(int d);
	int Volume();
	static const int DEFAULT_DIMENSION = 1;
private:
	int height, width, depth;
};