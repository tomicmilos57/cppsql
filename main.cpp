#include <iostream>
#include "Database.h"

int main(){
	std::cout << "SQL" << std::endl;
	Database database;
	while(1){
		std::cout << "0. Exit\n1. CreateTable\n2. InsetInto\n3. PrintTree\n";
		int decision;
		std::cin >> decision;
		if(!decision) break;
		if(decision == 1){
			std::vector<std::string> names;
			names.push_back("Kompanija");
			names.push_back("Gazda");
			database.createTable("Beton", names);
			database.printTable();
		}
		if(decision == 2){
			std::vector<std::string> whereinsert;
			whereinsert.push_back("Kompanija");
			whereinsert.push_back("Gazda");
			std::vector<std::string> toinsert;
			toinsert.push_back("Matija");
			toinsert.push_back("Grikom");
			database.insertTable(whereinsert, toinsert);
		}

		if(decision == 3){
			database.printTable();
		}
	}

	std::cout << "Program ended" << std::endl;
	return 0;
}
