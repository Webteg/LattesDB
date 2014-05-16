#include "pugixml.hpp"

#include <iostream>

int main()
{
//[code_load_file
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("xmlLattes/0455487141833418.xml");

    std::cout << "Load result: " << result.description() << ", nome do pesquisador: " << doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute("NOME-COMPLETO").value() << std::endl;
//]
}

// vim:et
