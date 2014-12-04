#include "Arduino.h"

void setup(void);
void loop(void);

class WrappinoNode {
public:
	WrappinoNode* next;
	Wrappino* Wrappino;
	
	WrappinoNode() {
		this-> next = NULL;
		this-> Wrappino = NULL;
	}
	
	~WrappinoNode() {
		if(this-> Wrappino != NULL) {
			delete Wrappino;
		}

		if(this-> next != NULL) {
			delete next;
		} 
	}

	WrappinoNode* add(Wrappino* Wrappino) {
		if(this-> Wrappino == NULL) {
			this-> Wrappino = Wrappino;
			return this;
		}
		return this-> next-> add(Wrappino); 
	}
	
	void setup() {
		if(this-> Wrappino != NULL) {
			Wrappino-> setup();
		}
		
		if(this-> next != NULL) {
			this-> next-> setup();
		}
	}
	
	void loop() {
		if(this-> Wrappino != NULL) {
			Wrappino-> _loop();
		}
		
		if(this-> next != NULL) {
			this-> next-> loop();
		}
	}
}

class Wrappino {
	unsigned long timing;
	bool work;
public:
	static WrappinoNode* node;
	Wrappino() {
		work = true;
		timing = millis();
		node-> add(this);
	}

	virtual void setup(void);

	virtual void loop(void);
	
	void _loop(void) {
		if(work) {
			if(timing < millis()) {
				loop();
			}
		}
	}
	
	void delay(unsigned long time) {
		unsigned long now = millis();
		if(timing < now) {
			timing = now + time;
		} else {
			timing += time;
		}
	}
};
Wrappino::node = new WrappinoNode();

void setup() {
	Wrappino::node-> setup();
}

void loop() {
	Wrappino::node-> loop();
}

// Example of Blinker with using Wrappino
class Blinker : public Wrappino {
private:
	int blink = HIGH;
	int blinkPin = 3;
public:
	void setup() {
		pinMode(blinkPin, OUTPUT);
	}
	
	void loop() {
		digitalWrite(blinkPin, blink ^= 1);
		delay(1000);
	}
}
