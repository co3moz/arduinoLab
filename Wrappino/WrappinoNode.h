#ifndef WRAPPINONODE_H
#define WRAPPINONODE_H
#include "Arduino.h"

class Wrappino;
class WrapppinoNode;

class WrappinoNode {
private:
	WrappinoNode* next;
	Wrappino* wrappino;
public:
	WrappinoNode();
	~WrappinoNode();

	WrappinoNode* add(Wrappino*);
	
	void setup();
	void loop();
};
#endif