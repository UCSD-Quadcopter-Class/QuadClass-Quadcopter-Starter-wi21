#ifndef MENU_ITEM_INCLUDED
#define MENU_ITEM_INCLUDED

#include"SerLCD.h"

class BaseMenuItem {
public:
	const char * name;
	BaseMenuItem(const char * name) : name(name) {}
	virtual void print_value(SerLCD & lcd) = 0;
	virtual void add(int c) = 0;
};

template<class T>
class MenuItem :public BaseMenuItem {
public:
	T & value;
	T delta;
	virtual void print_value(SerLCD & lcd) {
		lcd.print(value);
	}
	virtual void add(int c) {
		value += c * delta;
	}
	MenuItem(const char *name, T & value, T delta): BaseMenuItem(name), value(value), delta(delta) {}
	
};

extern void update_lcd(BaseMenuItem **menu, SerLCD & lcd);
extern int current_menu_row ;
extern void next_menu_item(BaseMenuItem**menu, int len);
extern void prev_menu_item(BaseMenuItem**menu, int len);
extern void menu_item_add(BaseMenuItem** menu, int i);

#endif
