#ifndef WRAPPINO_H
#define WRAPPINO_H
#include "Arduino.h"

class Wrappino;
class WrapppinoNode;

class Wrappino {
	unsigned long timing;
public:
	bool work;
	static WrappinoNode* node;
	Wrappino();

	virtual void setup();
	virtual void loop();
	
	void _loop();
	void delay(unsigned long);
};
#endif