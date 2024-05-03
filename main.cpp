#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include "Database.h"
#include <cmath>

int main(){
	std::cout << "SQL" << std::endl;
	Database database;
	while(1){
		std::cout << "0. Exit\n1. Insert Query\n2. Start Test\n3. PrintTree\n";
		int decision;
		std::cin >> decision;
		if(!decision) break;
		if(decision == 1){
			std::string query;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, query);
			database.execute(query);
		}
		if(decision == 2){
			std::ifstream test("Input.txt");
			std::string query;
			while(std::getline(test, query))database.execute(query);
		}
		if(decision == 3){
			database.printTable();
		}
	}

	std::cout << "Program ended" << std::endl;
	return 0;
}
