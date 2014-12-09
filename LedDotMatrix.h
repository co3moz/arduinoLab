#include "Arduino.h"
		

class LedDotMatrix {
	private:
	byte clk;
	byte cs;
	byte din;
	
	byte* graph;
	
	void push(unsigned char data) {
		digitalWrite(cs,LOW);		
		for(unsigned char i=8; i>=1; i--) {		  
			digitalWrite(clk, LOW);
			digitalWrite(din, data & 0x80);
			data = data<<1;
			digitalWrite(clk, HIGH);
		}                                 
	}
	
	void push(unsigned char address, unsigned char data) {
		digitalWrite(cs,LOW);
		push(address);
		push(data);
		digitalWrite(cs,HIGH);
	}
		
	public:
	LedDotMatrix(byte clk, byte cs, byte din) {
		this-> clk = clk;
		this-> cs = cs;
		this-> din = din;

		graph = new byte[8];
		
		clear();
		
		pinMode(clk, OUTPUT);
		pinMode(cs, OUTPUT);
		pinMode(din, OUTPUT);
		
		push(0x09, 0x00);
		push(0x0a, 0x03);
		push(0x0b, 0x07);
		push(0x0c, 0x01);
		push(0x0f, 0x00);
	}
	
	~LedDotMatrix() {
		delete[] graph;
	}
	
	void clear() {
		// graph dizesini 0'a eşitle
		for(byte i = 0;i<8;i++) {
			graph[i] = 0;
		}
	}
	
	void setVerticalPixel(byte x, byte y, byte a) {
		// 0-7 arasını kabul et
		x &= 7;
		y &= 7;
		
		//o biti 0 yap
		graph[y] &= ~(1 << x);
        
		//eğer o bitin 1 olması isteniyorsa 1 yap.
		if(a) graph[y] | 1 << x;
	}
	
	void setHorizontalPixel(byte x, byte y, byte a) {
		return setVerticalPixel(y, x, a);
	}
	
	void setVerticalPixel(byte pixel, byte a) {
		//doğrusal sayıyı 2 boyutlu sayıya çevir.
		setVerticalPixel(pixel >> 3, pixel % 8);
	}
	
	
	void setHorizontalPixel(byte pixel, byte a){
		setHorizontalPixel(pixel >> 3, pixel % 8);
	}
	
	void setVerticalLine(byte line, byte a) {
		//graph doğrudan dikey çıkışı verdiğinden graph'ın n'inci satırını
		//a'a eşitlememiz yetiyor.
		graph[line] = a;
	}
	
	void setHorizontalLine(byte line, byte a) {
		//graph yatay çıkışı vermediğinden line'i tektek ayarlıyoruz.
		setVerticalPixel(0, line, a&1);
		setVerticalPixel(1, line, a&2);
		setVerticalPixel(2, line, a&4);
		setVerticalPixel(3, line, a&8);
		setVerticalPixel(4, line, a&16);
		setVerticalPixel(5, line, a&32);
		setVerticalPixel(6, line, a&64);
		setVerticalPixel(7, line, a&128);
	}
	
	void setVertical(byte* a) {
		for(int i = 0; i<8; i++) {
			setVerticalLine(i, a[i]);
		}
	}
	
	void setHorizontal(byte* a) {
		for(int i = 0; i<8; i++) {
			setHorizontalLine(i, a[i]);
		}
	}
	
	void transpoze() {
		byte* temp = new byte[8];
		for(int i = 0;i<8;i++) {
			
		}
		
	}
	
	byte* getGraph() {
		return graph;
	}
	
	void pushGraph() {
		for(int i = 0; i<8; i++) {
			push(i+1, graph[i]);
		}
	}
};