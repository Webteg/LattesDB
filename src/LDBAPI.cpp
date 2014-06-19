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

	/* Create items */
	main_menu_items = new ITEM*[main_options_size];
	for (i = 0; i < main_options_size; ++i) {
		main_menu_items[i] = new_item(main_options[i].c_str(), "\0");
	}
	int op0 = 0, op1 = 1, op2 = 2, op3 = 3, op4 = 4;
	set_item_userptr(main_menu_items[0], (void*) &op0);

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
		case 10:
			int option = *((int*) item_userptr(current_item(main_menu)));

			/**/
			LDBRegister reg;
			reg.readXML("xmlLattes/0455487141833418.xml");
			/**/
			mvaddch(0, 0, option);
			refresh();
			switch (option) {
			case 0:
				/***/
				showRegisterData(reg);
				/**/
				wrefresh(main_menu_win);
			}
			box(main_menu_win, 0, 0);
			mvprintw(2, 4, "Lattes Database");
			post_menu(main_menu);
			pos_menu_cursor(main_menu);
			break;
		}
		refresh();
		wrefresh(main_menu_win);
	}

	/* Unpost and free all the memory taken up */
	unpost_menu(main_menu);
	free_menu(main_menu);
	for (i = 0; i < main_options_size; ++i)
		free_item(main_menu_items[i]);
	endwin();
}

void LDBAPI::showRegisterData(LDBRegister reg) {
	ITEM **itens;
	WINDOW* showRegisterData;
	MENU *reg_menu;
	vector<string> reg_data;
	int i;

	reg_data.push_back("Pesquisador: " + reg.get_name());
	reg_data.push_back("Instituição: " + reg.get_institution());

	reg_data.push_back("Publicações em periódicos:");

	i = 0;
	for(string journal : reg.get_journals()) {
		reg_data.push_back(journal);
		reg_data.push_back("Número de co-autores: " + std::to_string(journal[i]));
		i++;
	}

	reg_data.push_back("Publicações em eventos:");

	i = 0;
	for(string event : reg.get_events()) {
		reg_data.push_back(event);
		reg_data.push_back("Número de co-autores: " + std::to_string(event[i]));
		i++;
	}

	reg_data.push_back("\0");
	int size = reg_data.size();
	itens = new ITEM*[size];
	for (i = 0; i < size; i++) {
		itens[i] = new_item(reg_data[i].c_str(), "\0");
	}

	/* Create menu */
	reg_menu = new_menu((ITEM **) itens);

	/* Create the window to be associated with the menu */
	showRegisterData = newwin(10, 40, 4, 4);
	keypad(showRegisterData, TRUE);

	/* Set main window and sub window */
	set_menu_win(reg_menu, showRegisterData);
	set_menu_sub(reg_menu, derwin(showRegisterData, 8, 38, 1, 1));

	post_menu(reg_menu);
	wrefresh(showRegisterData);

	char c;
	while ((c = wgetch(showRegisterData)) != 10) {
		switch (c) {
		case KEY_DOWN:
			menu_driver(reg_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(reg_menu, REQ_UP_ITEM);
			break;
		}
			refresh();
			wrefresh(showRegisterData);
	}

	/* Unpost and free all the memory taken up */
	unpost_menu(reg_menu);
	free_menu(reg_menu);
	for (i = 0; i < size; ++i)
		free_item(itens[i]);
	endwin();
}

void LDBAPI::addXMLMenu() {
	WINDOW* addXMLWin;
	char buffer[512];
	addXMLWin = newwin(LINES, COLS, 0, 0);
	echo();
	mvwprintw(addXMLWin, 5, 10, "Digite o nome do arquivo XML:");
	mvwscanw(addXMLWin, 6, 10, buffer);
	noecho();
	string file_name = buffer;
	wrefresh(addXMLWin);
	wclear(addXMLWin);
	//função
	mvwprintw(addXMLWin, 5, 10, "Arquivo inserido com sucesso!");
	mvwprintw(addXMLWin, 6, 6, "Pressione qualquer tecla para continuar");
	wrefresh(addXMLWin);
	wgetch(addXMLWin);
	wclear(addXMLWin);
	wrefresh(addXMLWin);
	delwin(addXMLWin);
	endwin();
	endwin();
}

LDBAPI::~LDBAPI() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
