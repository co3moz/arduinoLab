#define thread(name) unsigned long __time_ ## name = 0; void __function_ ## name ()
#define use_thread(name) if(__time_ ## name < millis()) __function_ ## name ();
#define delay_thread(name, time) __time_ ## name = millis() + time;

