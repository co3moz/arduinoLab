// We dont allow to wrappino handling void setup and void loop automaticly
#define WRAPPINO_SETUP
#define WRAPPINO_LOOP

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

// Now we need to create blink we can use not pointer version. Just i did this way.
Blink* blink;

// When we say #define WRAPPINO_SETUP that means WRAPPINO will not call setup by itself. Now it drops the 
// Control to you. We create setup and starting some serial connection and when some data comes we create Blink as
// What data came from serial.
// In down below we called WRAPPINO_SETUP that automaticly calls Wrappino's calling diagram and every wrappino class
void setup() {
	Serial.begin(9600);
	
	while(!Serial.available()) delay(10);
	blink = new Blink(Serial.read() - '0');
	
	WRAPPINO_SETUP;
}

// Same as Setup 
void loop() {
	WRAPPINO_LOOP;
}