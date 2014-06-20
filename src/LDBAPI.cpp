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
			"Buscar pelo instituto do pesquisador", "Sair", "\0" };
	int main_options_size = 6;

	/* Initialize curses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Create items */
	main_menu_items = new ITEM*[main_options_size];
	int op[main_options_size];
	for (i = 0; i < main_options_size; ++i) {
		main_menu_items[i] = new_item(main_options[i].c_str(), "\0");
		op[i] = i;
		set_item_userptr(main_menu_items[i], (void*) &op[i]);
	}

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
	bool exit = true;
	while (exit && (c = wgetch(main_menu_win)) != KEY_F(2)) {
		switch (c) {
		case KEY_DOWN:
			menu_driver(main_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(main_menu, REQ_UP_ITEM);
			break;
		case 10:
			int option = *((int*) item_userptr(current_item(main_menu)));
			switch (option) {
			case 0:
				addXML();
				break;
			case 1:
				addDir();
				break;
			case 2:
				searchName();
				break;
			case 3:
				searchInstitution();
				break;
			case 4:
				exit = false;

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
	lattes->close();
}

void LDBAPI::addXML() {
	WINDOW* addXMLWin;
	int c;
	string buffer;
	addXMLWin = newwin(LINES, COLS, 0, 0);
	keypad(addXMLWin, TRUE);
	mvwprintw(addXMLWin, 5, 10, "Digite o nome do arquivo XML:");
	mvdelch(6, 10);
	deleteln();
	wrefresh(addXMLWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (buffer.size() > 0) {
				buffer.resize(buffer.size() - 1);
				mvdelch(6, 10 + buffer.size());
			}
			mvdelch(6, 10 + buffer.size());
			break;
		default:
			if (isgraph(c)) {
				mvaddch(6, 10 + buffer.size(), c);
				buffer.push_back(c);
			}
		}
		wrefresh(addXMLWin);
	}
	wclear(addXMLWin);
	if (lattes->readXMLFile(buffer))
		mvwprintw(addXMLWin, 5, 10, "Arquivo inserido com sucesso!");
	else
		mvwprintw(addXMLWin, 5, 10, "Arquivo não pode ser aberto.");
	mvwprintw(addXMLWin, 6, 6, "Pressione qualquer tecla para continuar.");
	wrefresh(addXMLWin);
	wgetch(addXMLWin);
	wclear(addXMLWin);
	wrefresh(addXMLWin);
	delwin(addXMLWin);
	endwin();
	endwin();
}

void LDBAPI::addDir() {
	WINDOW* addDirWin;
	int c;
	string buffer;
	addDirWin = newwin(LINES, COLS, 0, 0);
	keypad(addDirWin, TRUE);
	mvwprintw(addDirWin, 5, 10, "Digite o nome do arquivo XML:");
	mvdelch(6, 10);
	deleteln();
	wrefresh(addDirWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (buffer.size() > 0) {
				buffer.resize(buffer.size() - 1);
				mvdelch(6, 10 + buffer.size());
			}
			mvdelch(6, 10 + buffer.size());
			break;
		default:
			if (isgraph(c)) {
				mvaddch(6, 10 + buffer.size(), c);
				buffer.push_back(c);
			}
		}
		wrefresh(addDirWin);
	}
	wclear(addDirWin);
	if (lattes->readXMLDir(buffer))
		mvwprintw(addDirWin, 5, 10, "Diretório inserido com sucesso!");
	else
		mvwprintw(addDirWin, 5, 10, "Diretório não pode ser aberto");
	mvwprintw(addDirWin, 6, 6, "Pressione qualquer tecla para continuar.");
	wrefresh(addDirWin);
	wgetch(addDirWin);
	wclear(addDirWin);
	wrefresh(addDirWin);
	delwin(addDirWin);
	endwin();
	endwin();
}

void LDBAPI::printResults(vector<LDBRegister> results) {
	WINDOW* win;
	int c;
	MENU *menu;
	ITEM** items;
	int size = results.size();
	int options[size];
	items = new ITEM*[size + 1];

	//initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	for (int i = 0; i < size; i++) {
		items[i] = new_item(results[i].get_key().c_str(), "\0");
		options[i] = i;
		set_item_userptr(items[i], (void*) &(options[i]));
	}
	items[size] = new_item("\0", "\0");
	menu = new_menu((ITEM **) items);

	win = newwin(LINES, COLS, 0, 0);
	keypad(win, TRUE);

	set_menu_win(menu, win);
	WINDOW* sub_win = derwin(win, LINES - 3, COLS - 2, 3, 1);
	set_menu_sub(menu, sub_win);

	post_menu(menu);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, "Resultados");
	mvwprintw(win, LINES - 2, 1,
			"F2 - Retornar ao menu\t\tENTER - Selecionar Registro");
	pos_menu_cursor(menu);
	wrefresh(win);

	while ((c = wgetch(win)) != KEY_F(2)) {
		switch (c) {
		case KEY_DOWN:
			menu_driver(menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(menu, REQ_UP_ITEM);
			break;
		case KEY_NPAGE:
			menu_driver(menu, REQ_SCR_DPAGE);
			break;
		case KEY_PPAGE:
			menu_driver(menu, REQ_SCR_UPAGE);
			break;
		case 10:
			int option = *((int*) item_userptr(current_item(menu)));
			//call result FUNÇÃO DO LUIZ
			box(win, 0, 0);
			mvwprintw(win, 1, 1, "Resultados");
			mvwprintw(win, LINES - 2, 1,
					"F2 - Retornar ao menu\t\tENTER - Selecionar Registro");
			pos_menu_cursor(menu);
			break;
		}
		wrefresh(win);
	}
	unpost_menu(menu);
	free_menu(menu);
	for (int i = 0; i < size; ++i)
		free_item(items[i]);
	endwin();
}

void LDBAPI::searchName() {
	WINDOW* searchNameWin;
	int c;
	string buffer;
	searchNameWin = newwin(LINES, COLS, 0, 0);
	keypad(searchNameWin, TRUE);
	mvwprintw(searchNameWin, 1, 1, "Digite o nome pesquisador:");
	mvwprintw(searchNameWin, 2, 1,
			"(Para busca por prefixos acrescente * no final do prefixo)");
	mvdelch(3, 1);
	deleteln();
	wrefresh(searchNameWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (buffer.size() > 0) {
				buffer.resize(buffer.size() - 1);
				mvdelch(3, 1 + buffer.size());
			}
			mvdelch(3, 1 + buffer.size());
			break;
		default:
			if (isgraph(c)) {
				mvaddch(3, 1 + buffer.size(), c);
				buffer.push_back(c);
			}
		}
		wrefresh(searchNameWin);
	}
	if (buffer[buffer.size() - 1] == '*') {
		vector<LDBRegister> result;
		buffer.resize(buffer.size() - 1);
		WINDOW* order_win;
		MENU* order;
		string texts[] = { "Ordem Alfabetica Crescente de Nome",
				"Ordem Alfabetica Decrescente de Nome",
				"Ordem Crescente de Numero Total de Publicacoes",
				"Ordem Decrescente de Numero Total de Publicacoes",
				"Ordem Crescente de Numero de Publicacoes em Periodicos",
				"Ordem Decrescente de Numero de Publicacoes em Periodicos",
				"Ordem Crescente de Numero de Publicacoes em Eventos",
				"Ordem Decrescente de Numero de Publicacoes em Eventos" };
		SORTING_ORDER options[] = { BY_ALPHABETICAL_ORDER,
				BY_ALPHABETICAL_ORDER_REV, BY_N_PUBLICATIONS,
				BY_N_PUBLICATIONS_REV, BY_N_JOURNALS, BY_N_JOURNALS_REV,
				BY_N_EVENTS, BY_N_EVENTS_REV };
		ITEM** items = new ITEM*[9];
		for (int i = 0; i < 8; i++) {
			items[i] = new_item(texts[i].c_str(), "\0");
			set_item_userptr(items[i], (void*) &(options[i]));
		}
		items[8] = new_item("\0", "\0");
		order = new_menu((ITEM **) items);

		order_win = newwin(8, 60, 6, 1);
		keypad(order_win, TRUE);

		set_menu_win(order, order_win);
		mvwprintw(searchNameWin, 5, 1,
				"Selecione a ordem na qual os resultados serão mostrados:");
		post_menu(order);
		wrefresh(searchNameWin);
		wrefresh(order_win);

		while (((c = getch()) != 10)) {
			switch (c) {
			case KEY_DOWN:
				menu_driver(order, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(order, REQ_UP_ITEM);
				break;
			}
			wrefresh(order_win);
		}
		SORTING_ORDER option = *((SORTING_ORDER*) item_userptr(
				current_item(order)));
		result = lattes->get_by_name_prefix(buffer, option);

		printResults(result);

	} else {
		LDBRegister result = lattes->get_by_name_full(buffer);
		//função do LUIS
	}

	wclear(searchNameWin);
	wrefresh(searchNameWin);
	delwin(searchNameWin);
	endwin();
}

void LDBAPI::searchInstitution() {
	WINDOW* searchNameWin;
	int c;
	string buffer;
	searchNameWin = newwin(LINES, COLS, 0, 0);
	keypad(searchNameWin, TRUE);
	mvwprintw(searchNameWin, 1, 1, "Digite o nome do instituto:");
	mvwprintw(searchNameWin, 2, 1,
			"(Para busca por prefixos acrescente * no final do prefixo)");
	mvdelch(3, 1);
	deleteln();
	wrefresh(searchNameWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (buffer.size() > 0) {
				buffer.resize(buffer.size() - 1);
				mvdelch(3, 1 + buffer.size());
			}
			mvdelch(3, 1 + buffer.size());
			break;
		default:
			if (isgraph(c)) {
				mvaddch(3, 1 + buffer.size(), c);
				buffer.push_back(c);
			}
		}
		wrefresh(searchNameWin);
	}

	WINDOW* order_win;
	MENU* order;
	string texts[] = { "Ordem Alfabetica Crescente de Nome",
			"Ordem Alfabetica Decrescente de Nome",
			"Ordem Crescente de Numero Total de Publicacoes",
			"Ordem Decrescente de Numero Total de Publicacoes",
			"Ordem Crescente de Numero de Publicacoes em Periodicos",
			"Ordem Decrescente de Numero de Publicacoes em Periodicos",
			"Ordem Crescente de Numero de Publicacoes em Eventos",
			"Ordem Decrescente de Numero de Publicacoes em Eventos" };
	SORTING_ORDER options[] = { BY_ALPHABETICAL_ORDER,
			BY_ALPHABETICAL_ORDER_REV, BY_N_PUBLICATIONS, BY_N_PUBLICATIONS_REV,
			BY_N_JOURNALS, BY_N_JOURNALS_REV, BY_N_EVENTS, BY_N_EVENTS_REV };
	ITEM** items = new ITEM*[9];
	for (int i = 0; i < 8; i++) {
		items[i] = new_item(texts[i].c_str(), "\0");
		set_item_userptr(items[i], (void*) &(options[i]));
	}
	items[8] = new_item("\0", "\0");
	order = new_menu((ITEM **) items);

	order_win = newwin(8, 60, 6, 1);
	keypad(order_win, TRUE);

	set_menu_win(order, order_win);
	mvwprintw(searchNameWin, 5, 1,
			"Selecione a ordem na qual os resultados serão mostrados:");
	post_menu(order);
	wrefresh(searchNameWin);
	wrefresh(order_win);

	while (((c = getch()) != 10)) {
		switch (c) {
		case KEY_DOWN:
			menu_driver(order, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(order, REQ_UP_ITEM);
			break;
		}
		wrefresh(order_win);
	}
	SORTING_ORDER option = *((SORTING_ORDER*) item_userptr(current_item(order)));
	vector<LDBRegister> result;
	if (buffer[buffer.size() - 1] == '*') {
		buffer.resize(buffer.size() - 1);
		result = lattes->get_by_institution_prefix(buffer);
	} else {
		result = lattes->get_by_institution_full(buffer);
	}
	printResults(result);
	wclear(searchNameWin);
	wrefresh(searchNameWin);
	delwin(searchNameWin);
	endwin();
}

LDBAPI::~LDBAPI() {
	delete lattes;
}

} /* namespace std */
