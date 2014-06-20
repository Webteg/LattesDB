/*
 * LDBAPI.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: marcos
 */

#include "LDBAPI.h"
#include "curses.h"
#include "menu.h"
#include <sstream>

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
			"Mostar todos os resultados", "Buscar pelo nome do pesquisador",
			"Buscar pelo instituto do pesquisador",
			"Buscar pelos prefixos do nome e instituto", "Sair", "\0" };
	int main_options_size = 8;

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
	main_menu_win = newwin(9, 44, 4, 4);
	keypad(main_menu_win, TRUE);

	/* Set main window and sub window */
	set_menu_win(main_menu, main_menu_win);
	set_menu_sub(main_menu, derwin(main_menu_win, 8, 42, 1, 1));

	/* Print a border around the main window and print a title */
	box(main_menu_win, 0, 0);
	mvprintw(2, 4, "Lattes Database");
	refresh();

	/* Post the menu */
	post_menu(main_menu);
	wrefresh(main_menu_win);
	vector<string> journals = { "haha", "asdasd" };
	vector<string> events = { "ha2323", "asdasd112" };
	vector<int> jca = { 4, 5 };
	vector<int> eca = { 14, 55 };
	LDBRegister reg2;
	reg2.readXML("xmlLattes/0455487141833418.xml");
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
				showAll();
				break;
			case 3:
				searchName();
				break;
			case 4:
				searchInstitution();
				break;
			case 5:
				searchNameInstitution();
				break;
			case 6:
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
			if (isgraph(c) || c == ' ') {
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
	clear();
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
			if (isgraph(c) || c == ' ') {
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
	clear();
	wrefresh(addDirWin);
	delwin(addDirWin);
	endwin();
	endwin();
}

void LDBAPI::showRegisterData(LDBRegister reg) {

	WINDOW* win;
	int c;
	MENU *menu;
	ITEM** items;
	int i;
	vector<string> reg_data;
	vector<int> journal_coauthors;
	vector<int> event_coauthors;
	stringstream n_publications, n_journal_publications, n_event_publications;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* criando array com itens **************************************/

	reg_data.push_back(
			"Pesquisador: " + LDBRegister::utfToAscii(reg.get_name()));
	reg_data.push_back(
			"Instituicao: " + LDBRegister::utfToAscii(reg.get_institution()));

	reg_data.push_back("Publicacoes em periodicos:");

	i = 0;

	journal_coauthors = reg.get_journal_coauthors();
	for (string journal : reg.get_journals()) {
		stringstream s;
		reg_data.push_back(LDBRegister::utfToAscii(journal));
		s << "     Numero de co-autores: " << journal_coauthors[i];
		reg_data.push_back(s.str());
		i++;
	}

	reg_data.push_back("Publicacoes em eventos:");

	i = 0;
	event_coauthors = reg.get_event_coauthors();
	for (string event : reg.get_events()) {
		reg_data.push_back(LDBRegister::utfToAscii(event));
		stringstream s;
		s << "     Numero de co-autores: " << event_coauthors[i];
		reg_data.push_back(s.str());
		i++;
	}

	n_publications << "Total de publicacoes: " << reg.get_n_publications();
	n_journal_publications << "Numero de publicacoes em periodicos: " << reg.get_n_journals();
	n_event_publications << "Numero de publicacoes em eventos: " << reg.get_n_events();

	int size = reg_data.size();
	items = new ITEM*[size + 1];
	int options[size];

	for (int i = 0; i < size; i++) {
		items[i] = new_item(reg_data[i].c_str(), "\0");
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

	box(win, 0, 0);
	mvwprintw(win, 1, 1, "Dados do pesquisador");
	mvwprintw(win, LINES - 1, 1, "F2 - Retornar ao menu");
	mvwprintw(win, LINES - 4, 1, n_publications.str().c_str());
	mvwprintw(win, LINES - 3, 1, n_journal_publications.str().c_str());
	mvwprintw(win, LINES - 2, 1, n_event_publications.str().c_str());
	pos_menu_cursor(menu);
	post_menu(menu);
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
		}
		wrefresh(win);
	}
	unpost_menu(menu);
	free_menu(menu);
	for (int i = 0; i < size; ++i)
		free_item(items[i]);
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

	stringstream s;
	if (size == 1) {
		s << size << " Resultado";
	} else {
		s << size << " Resultados";
	}

	post_menu(menu);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, s.str().c_str());
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
			if(size > 0) {
				int option = *((int*) item_userptr(current_item(menu)));
				showRegisterData(results[option]);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, s.str().c_str());
				mvwprintw(win, LINES - 2, 1,
						"F2 - Retornar ao menu\t\tENTER - Selecionar Registro");
				pos_menu_cursor(menu);
			}
			break;
		}
		wrefresh(win);
	}
	unpost_menu(menu);
	free_menu(menu);
	clear();
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
		case 32:
			mvaddch(3, 1 + buffer.size(), c);
			buffer.push_back(c);
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
		if (result.get_key().size() != 0) {
			showRegisterData(result);
		} else {
			mvwprintw(searchNameWin, 5, 1, "Nenhum registro encontrado.");
			wrefresh(searchNameWin);
			refresh();
			getch();
		}
	}

	clear();
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
			if (isgraph(c) || isspace(c)) {
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
	clear();
	wrefresh(searchNameWin);
	delwin(searchNameWin);
	endwin();
}

void LDBAPI::searchNameInstitution() {
	WINDOW* searchNameInstitutionWin;
	int c;
	string name;
	string institution;
	searchNameInstitutionWin = newwin(LINES, COLS, 0, 0);
	keypad(searchNameInstitutionWin, TRUE);
	mvwprintw(searchNameInstitutionWin, 1, 1,
			"Digite o prefixo nome do pesquisador:");
	mvdelch(2, 1);
	deleteln();
	wrefresh(searchNameInstitutionWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (name.size() > 0) {
				name.resize(name.size() - 1);
				mvdelch(2, 1 + name.size());
			}
			mvdelch(2, 1 + name.size());
			break;
		default:
			if (isgraph(c) || c == ' ') {
				mvaddch(2, 1 + name.size(), c);
				name.push_back(c);
			}
		}
		wrefresh(searchNameInstitutionWin);
	}
	mvwprintw(searchNameInstitutionWin, 4, 1,
			"Digite o prefixo instituto do pesquisador:");
	mvdelch(5, 1);
	deleteln();
	wrefresh(searchNameInstitutionWin);
	while ((c = getch()) != 10) {
		switch (c) {
		case KEY_BACKSPACE:
			if (institution.size() > 0) {
				institution.resize(institution.size() - 1);
				mvdelch(5, 1 + institution.size());
			}
			mvdelch(5, 1 + institution.size());
			break;
		default:
			if (isgraph(c) || isspace(c)) {
				mvaddch(5, 1 + institution.size(), c);
				institution.push_back(c);
			}
		}
		wrefresh(searchNameInstitutionWin);
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

	order_win = newwin(8, 60, 8, 1);
	keypad(order_win, TRUE);

	set_menu_win(order, order_win);
	mvwprintw(searchNameInstitutionWin, 7, 1,
			"Selecione a ordem na qual os resultados serão mostrados:");
	post_menu(order);
	wrefresh(searchNameInstitutionWin);
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
	result = lattes->get_by_name_and_institution_prefix(name, institution,
			option);
	printResults(result);
	clear();
	wrefresh(searchNameInstitutionWin);
	delwin(searchNameInstitutionWin);
	endwin();
}

void LDBAPI::showAll() {
	int c;
	WINDOW* showAllWin = newwin(LINES, COLS, 0, 0);
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

	order_win = newwin(8, 60, 3, 1);
	keypad(order_win, TRUE);

	set_menu_win(order, order_win);
	mvwprintw(showAllWin, 2, 1,
			"Selecione a ordem na qual os resultados serão mostrados:");
	post_menu(order);
	wrefresh(showAllWin);
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
	vector<LDBRegister> results = lattes->get_all(option);
	printResults(results);
	clear();
	wrefresh(showAllWin);
	delwin(showAllWin);
	endwin();

}

LDBAPI::~LDBAPI() {
	delete lattes;
}

} /* namespace std */
