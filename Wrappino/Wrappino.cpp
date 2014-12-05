#include "Wrappino.h"
#include "WrappinoNode.h"

// defining WrappinoNode...
WrappinoNode::WrappinoNode() {
	this-> next = NULL;
	this-> wrappino = NULL;
}

WrappinoNode::~WrappinoNode() {
	if(this-> wrappino != NULL) {
		delete wrappino;
	}

	if(this-> next != NULL) {
		delete next;
	} 
}

WrappinoNode* WrappinoNode::add(Wrappino* wrappino) {
	if(this-> wrappino == NULL) {
		this-> wrappino = wrappino;
		return this;
	}
	
	if(this-> next == NULL) {
		this-> next = new WrappinoNode(); 
	}
	
	return this-> next-> add(wrappino); 
}

void WrappinoNode::setup() {
	if(this-> wrappino != NULL) {
		this-> wrappino-> setup();
	}
	
	if(this-> next != NULL) {
		this-> next-> setup();
	}
}

void WrappinoNode::loop() {
	if(this-> wrappino != NULL) {
		this-> wrappino-> _loop();
	}
	
	if(this-> next != NULL) {
		this-> next-> loop();
	}
}

// This guy is defining first WrappinoNode so we can use it when we creating Wrappino objects
WrappinoNode* Wrappino::node = new WrappinoNode();

// defining Wrappino...
Wrappino::Wrappino() {
	work = true;
	timing = millis();
	node-> add(this);
}

void Wrappino::_loop()  {
	if(work) {
		if(timing < millis()) {
			loop();
		}
	}
}

void Wrappino::delay(unsigned long time) {
	unsigned long now = millis();
	if(timing < now) {
		timing = now + time;
	} else {
		timing += time;
	}
}

// wrapping original setup and loop
void setup() {
	Wrappino::node-> setup();
}

void loop() {
	Wrappino::node-> loop();
}
