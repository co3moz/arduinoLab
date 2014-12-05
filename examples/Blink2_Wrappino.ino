// We calling Wrappino.cpp that creates everything what we need for us
#include "Wrappino.cpp"

// This is an Wrappino made class. When we use inheritance, that automaticly defines everything what we need again.
// I want to make Blinker class so i created it.
class Blink : public Wrappino {
private:
	// pin and status info is not needed to open from other classes 
	int pin;
	int status;
public:
	// This is a constructor. We collecting pin info when instance created
	Blink(int pin) {
		this-> pin = pin;
		status = 0;
	}
	
	// This is a virtual method called setup and we override it. So Now it does what we want when setup is calling
	void setup() {
		pinMode(pin, OUTPUT);
	}
	
	// Again this is a virtual method called loop and we override it. So Now it does what we want when loop is calling
	void loop() {
		digitalWrite(pin, status ^= 1);
		
		// this delay functions is a member function not global. delay's only Blink
		delay(500);
	}
};

// This time we didn't use pointers to create objects and we didn't define void setup and void loop too.
// It's all automatic..
Blink blink(3);