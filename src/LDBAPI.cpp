/*
 * LDBAPI.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: marcos
 */

#include "LDBAPI.h"
#include "curses.h"
#include "menu.h"

namespace std {

LDBAPI::LDBAPI(string name) {
	lattes = new LattesDB(name);
}

void LDBAPI::mainMenu() {
	ITEM **main_menu_items;
	int c;
	MENU *main_menu;
	WINDOW *main_menu_win;
	int i;
	string main_options[] { "Adicionar XML", "Adicionar Diretorio",
			"Buscar pelo nome do pesquisador",
			"Buscar pelo instituto do pesquisador", "Exit", "\0" };
	int main_options_size = 6;

	/* Initialize curses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	/* Create items */
	main_menu_items = new ITEM*[main_options_size];
	for (i = 0; i < main_options_size; ++i)
		main_menu_items[i] = new_item(main_options[i].c_str(), "\0");

	/* Create menu */
	main_menu = new_menu((ITEM **) main_menu_items);

	/* Create the window to be associated with the menu */
	main_menu_win = newwin(10, 40, 4, 4);
	keypad(main_menu_win, TRUE);

	/* Set main window and sub window */
	set_menu_win(main_menu, main_menu_win);
	set_menu_sub(main_menu, derwin(main_menu_win, 8, 38, 1, 1));

	/* Print a border around the main window and print a title */
	box(main_menu_win, 0, 0);
	mvprintw(2, 4, "Lattes Database");
	refresh();

	/* Post the menu */
	post_menu(main_menu);
	wrefresh(main_menu_win);

	while ((c = wgetch(main_menu_win)) != KEY_F(2)) {
		switch (c) {
			case KEY_DOWN:
				menu_driver(main_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(main_menu, REQ_UP_ITEM);
				break;
		}

		wrefresh(main_menu_win);
	}

	/* Unpost and free all the memory taken up */
	unpost_menu(main_menu);
	free_menu(main_menu);
	for (i = 0; i < main_options_size; ++i)
		free_item(main_menu_items[i]);
	endwin();
}

void LDBAPI::searchMenu() {
	char mesg[]="Enter a string: ";		/* message to be appeared on the screen */
	char str[80];
	int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */

	//initscr();				/* start the curses mode */
	 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	 mvprintw(0,0,"%s",mesg);
	                     		/* print the message at the center of the screen */
	 getstr(str);
	 lattes.get_all();
	 mvprintw(LINES - 2, 0, "You Entered: %s", str);
	 getch();
	 endwin();
}

LDBAPI::~LDBAPI() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
