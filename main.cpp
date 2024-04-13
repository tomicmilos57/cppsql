#include <iostream>
#include "Database.h"

void test_table_generator(Database& database){
	std::vector<std::string> columns;
	columns.push_back("Kompanija");
	columns.push_back("Gazda");
	columns.push_back("Prihod");
	columns.push_back("BrojRadnika");
	database.createTable("Beton", columns);
	std::vector<std::string> whereinsert;
	//Grikom Matija
	whereinsert.push_back("Kompanija");
	whereinsert.push_back("Gazda");
	std::vector<std::string> toinsert;
	toinsert.push_back("Matija");
	toinsert.push_back("Grikom");
	database.insertTable(whereinsert, toinsert);
	//Betonplus
	whereinsert.clear();
	whereinsert.push_back("Kompanija");
	whereinsert.push_back("Gazda");
	whereinsert.push_back("Prihod");
	whereinsert.push_back("BrojRadnika");
	toinsert.clear();
	toinsert.push_back("Betonplus");
	toinsert.push_back("Unknown");
	toinsert.push_back("100M");
	toinsert.push_back("150");
	database.insertTable(whereinsert, toinsert);
	//Marmil
	whereinsert.clear();
	whereinsert.push_back("Kompanija");
	whereinsert.push_back("Gazda");
	whereinsert.push_back("Prihod");
	whereinsert.push_back("BrojRadnika");
	toinsert.clear();
	toinsert.push_back("Marmil");
	toinsert.push_back("MarkoMilan");
	toinsert.push_back("10M");
	toinsert.push_back("50");
	database.insertTable(whereinsert, toinsert);
	//Niciforovic
	whereinsert.clear();
	whereinsert.push_back("Kompanija");
	whereinsert.push_back("BrojRadnika");
	toinsert.clear();
	toinsert.push_back("Niciforovic");
	toinsert.push_back("15");
	database.insertTable(whereinsert, toinsert);
	//Lafarge
	whereinsert.clear();
	whereinsert.push_back("Kompanija");
	whereinsert.push_back("Gazda");
	whereinsert.push_back("BrojRadnika");
	toinsert.clear();
	toinsert.push_back("Lafarge");
	toinsert.push_back("Vucic");
	toinsert.push_back("200");
	database.insertTable(whereinsert, toinsert);
}

int main(){
	std::cout << "SQL" << std::endl;
	Database database;
	while(1){
		std::cout << "0. Exit\n1. CreateTable\n2. InsetInto\n3. PrintTree\n";
		int decision;
		std::cin >> decision;
		if(!decision) break;
		if(decision == 1){
			test_table_generator(database);
			/*std::vector<std::string> names;
			names.push_back("Kompanija");
			names.push_back("Gazda");
			database.createTable("Beton", names);
			database.printTable();*/
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
