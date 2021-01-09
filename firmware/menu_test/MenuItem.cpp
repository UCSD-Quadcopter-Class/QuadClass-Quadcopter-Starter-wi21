#include"MenuItem.hpp"
#include"SerLCD.h"

int current_menu_row = 0;

void update_lcd(BaseMenuItem **menu, SerLCD & lcd) {
        lcd.clear();
        lcd.home();
        lcd.print(current_menu_row);
	lcd.print(" ");
	lcd.print(menu[current_menu_row]->name);
	lcd.print(" ");
	menu[current_menu_row]->print_value(lcd);
}

void next_menu_item(BaseMenuItem ** menu, int len) {
	current_menu_row++;
	if (current_menu_row >= len) {
		current_menu_row = 0;
	}
}
void prev_menu_item(BaseMenuItem **menu, int len ) {
	current_menu_row--;
	if (current_menu_row < 0) {
		current_menu_row = len - 1;
	}
}

void menu_item_add(BaseMenuItem** menu, int i) {
	menu[current_menu_row]->add(i);
}
