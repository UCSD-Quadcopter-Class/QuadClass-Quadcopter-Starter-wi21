//-*- c++ -*-
#include "quad_remote.h"
#include "MenuItem.hpp"

void knobs_update();
void knob_pressed(bool);
void btn1_pressed(bool);
void btn2_pressed(bool);

void btn_up_pressed(bool down);
void btn_down_pressed(bool down);
void btn_left_pressed(bool down);
void btn_right_pressed(bool down);
void btn_center_pressed(bool down);



unsigned char R = 128;
unsigned char G = 128;
unsigned char B = 128;
unsigned int C = 5;

MenuItem<unsigned char> r("R", R, 16);
MenuItem<unsigned char> g("G", G, 16);
MenuItem<unsigned char> b("B", B, 16);
MenuItem<unsigned int> c("C", C, 1);


BaseMenuItem * menu[] = {
	&r, &g, &b, &c
};

#define MENU_LENGTH (sizeof(menu)/sizeof(void*))

void update_color()
{
	lcd.setBacklight(R, G, B);
	//lcd.setContrast(C);
}

void setup() {

	const int RADIO_CHANNEL = 25;        // Channel for radio communications (can be 11-26)
	const int SERIAL_BAUD = 9600;        // Baud rate for serial port

	Serial.begin(SERIAL_BAUD);           // Start up serial
	quad_remote_setup();

	knobs_update_cb = knobs_update; 
	knob1_btn_cb = knob_pressed;
	btn1_cb = btn1_pressed;
	btn2_cb = btn2_pressed;
	btn_up_cb =  btn_up_pressed;
	btn_down_cb = btn_down_pressed;
	btn_left_cb =  btn_left_pressed;
	btn_right_cb = btn_right_pressed;
	btn_center_cb =  btn_center_pressed;
	update_lcd(menu, lcd);
}


bool update_needed = false;

void update_menu() {
	if (update_needed) {
		update_lcd(menu, lcd);
		update_needed = false;
	}
}

void loop() {
	update_menu();
}

void knobs_update() {
	menu_item_add(menu, knob1.getCurrentPos())
	knob1.setCurrentPos(0);
	update_needed = true;
}

void btn1_pressed(bool down) {
}

void btn2_pressed(bool down) {
}

void knob_pressed(bool down) {
}


void btn_up_pressed(bool down) {
	if (down) {
		next_menu_item(menu, MENU_LENGTH);
		update_needed = true;
		knob1.setCurrentPos(0);
		delay(1);
	}
}

void btn_down_pressed(bool down) {
	if (down) {
		prev_menu_item(menu, MENU_LENGTH);
		update_needed = true;
		knob1.setCurrentPos(0);
		delay(1);
	}
}

void btn_left_pressed(bool down) {
	if (down) {
		menu_item_add(menu, -1);
		update_needed = true;
		delay(1);
	}
}

void btn_right_pressed(bool down) {
	if (down) {
		menu_item_add(menu, 1);
		update_needed = true;
		delay(1);
	}
}

	
void btn_center_pressed(bool down) {
	if (down) {
		update_color();
	}
}
