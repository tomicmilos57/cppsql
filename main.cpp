#include <iostream>
#include <string>
#include "Database.h"
#include <cmath>

int main(){
	std::cout << "SQL" << std::endl;
	Database database;
	while(1){
		std::cout << "0. Exit\n1. Insert Query\n2. ----\n3. PrintTree\n";
		int decision;
		std::cin >> decision;
		if(!decision) break;
		if(decision == 1){
			std::string query;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, query);
			//std::cout << "The line you entered\n" << query << std::endl;
			database.execute(query);
		}
		if(decision == 3){
			database.printTable();
		}
	}

	std::cout << "Program ended" << std::endl;
	return 0;
}
