#include "box.h"
#include <cmath>
Box::Box(){
	height = DEFAULT_DIMENSION, depth = DEFAULT_DIMENSION, width = DEFAULT_DIMENSION;
}
Box::Box(int h, int w, int d) {
	height = ((h>0) ? h : DEFAULT_DIMENSION); width = ((w>0) ? w : DEFAULT_DIMENSION); depth = ((d>0) ? d : DEFAULT_DIMENSION);
}
int Box::GetHeight(){
	return height;
}
int Box::GetDepth(){
	return depth;
}
int Box::GetWidth(){
	return width;
}
void Box::SetWidth(int w){
	width = ((w>0) ? w : DEFAULT_DIMENSION);
}
void Box::SetHeight(int h){
	height = ((h>0) ? h : DEFAULT_DIMENSION);
}
void Box::SetDepth(int d){
	depth = ((d>0) ? d : DEFAULT_DIMENSION);
}
int Box::Volume(){
	return height*width*depth;
}