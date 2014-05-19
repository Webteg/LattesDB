#include "pugixml.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <string.h>

int main()
{
//[code_load_file

    pugi::xml_document doc;

    pugi::xml_parse_result result;
    
    
    DIR *pDIR;
	struct dirent *entry;
	/*
	if( pDIR=opendir("./xmlLattes") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
				result = doc.load_file((std::string("xmlLattes/") + entry->d_name).c_str());
				std::cout << doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute("NOME-COMPLETO").value() << "\n";
			}
		}
		closedir(pDIR);
	}
	*/
	result = doc.load_file("xmlLattes/0455487141833418.xml");
	pugi::xml_node works = doc.child("CURRICULO-VITAE").child("PRODUCAO-BIBLIOGRAFICA").child("ARTIGOS-PUBLICADOS");
	for (pugi::xml_node work = works.first_child(); work; work = work.next_sibling()) {
		std::cout << work.child("DADOS-BASICOS-DO-ARTIGO").attribute("TITULO-DO-ARTIGO").value() << "\n";
		
	}
    //std::cout << "Load result: " << result.description() << ", nome do pesquisador: " << doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute("NOME-COMPLETO").value() << std::endl;
    return 0;
//]
}

// vim:et
