#include "arduino.h"

class Eight7SegmentController {
  private:
    byte latch;
    byte data;
    byte clock;
    
    byte* segment;
    
  void show(byte &key, byte a) {
    digitalWrite(latch, LOW); 
    shiftOut(data, clock,MSBFIRST, key); 
    shiftOut(data, clock,MSBFIRST, a); 
    digitalWrite(latch, HIGH); 
    key <<= 1; 
  }
  
  byte getChar(char a) {
    switch(a) {
      case '0':
        return B01000000;
      case '1':
        return B01111001;
      case '2':
        return B00100100;
      case '3':
        return B00110000;
      case '4':
        return B00011001;
      case '5':
        return B00010010;
      case '6':
        return B00000010;
      case '7':
        return B01111000;
      case '8':
        return B00000000;
      case '9':
        return B00010000;
      case '.':
        return B01111111;
      case 'A':
        return B00100011; 
      case 'B':
        return B00000011;
      case 'C':
        return B00100111;
      case 'D':
        return B00100001;
      case 'E':
        return B00000110;
      case 'F':
        return B00001110;
      case 'H':
        return B00001001;
      default:
        return B01111111;
   } 
  }
  
  public:
    Eight7SegmentController(byte latch, byte data, byte clock) {
      this-> latch = latch;
      this-> data = data;
      this-> clock = clock;
      
      segment = new byte[8];
    }
    
    ~Eight7SegmentController() {
      delete[] segment; 
    }
    
    void show8() {
      byte key = 1;
      show(key, segment[0]);
      show(key, segment[1]);
      show(key, segment[2]);
      show(key, segment[3]);
      show(key, segment[4]);
      show(key, segment[5]);
      show(key, segment[6]);
      show(key, segment[7]);
    }
    
    byte getChar(char a, byte dot) {
      return getChar(a) + (dot << 7);
    } 
    
    void number(unsigned long t, byte index = 7) {
      if(index > 7) return;
      do {
        segment[index--] = getChar(byte((t%10) + '0'), 1);
        if(!index) break;
      }
      while(t/=10);
    }
    
    void clear() {
        for(byte i = 0; i<8; i++) {
          segment[i] = getChar(byte(0), 1);
        }
    }
};