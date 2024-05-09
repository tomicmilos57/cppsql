#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include "Database.h"
#include <cmath>


int main(){
	std::cout << "SQL" << std::endl;
	while(1){
	Database database;
		std::cout << "0. Exit\n1. Create new file\n2. Open .sql file\n3. Open .sqlpp file" << std::endl;
		int dec;
		std::string file_name;
		std::cin >> dec;
		while (std::cin.fail()){
			std::cout << "Please enter an integer" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> dec;
		}
		if(!dec) break;
		if(dec == 2 || dec == 3){
			std::cout << "Enter file name" << std::endl;
			std::cin >> file_name;
		}
		if(dec == 2){
			std::ifstream test(file_name);//throw error if doesnt exist
			std::string query;
			while(std::getline(test, query))database.execute(query);
		}
		if(dec == 3){
			std::ifstream os;
			os.open(file_name);
			database.load(os);
			os.close();
		}
		if(dec > 0 && dec < 4)while(1){
			std::cout << "0. Detach Database\n1. Insert Query\n2. Save\n3. PrintTree\n";
			int decision;
			std::cin >> decision;
			while (std::cin.fail()){
				std::cout << "Please enter an integer" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> decision;
			}
			if(!decision) break;
			if(decision == 1){
				std::string query;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, query);
				database.execute(query);
			}
			if(decision == 2){
				std::cout << "1. Save as .sql\n2. Save as .sqlpp\n" << std::endl;
				int dec;
				std::cin >> dec;
				std::string file_name;
				std::cout << "Enter file name (Without extension)" << std::endl;
				std::cin >> file_name;
				if(dec==1){
					std::ofstream os;
					os.open(file_name + ".sql");
					database.save_sql(os);
					os.close();
				}
				if(dec==2){
					std::ofstream os;
					os.open(file_name + ".sqlpp");
					database.save(os);
					os.close();
				}
			}
			if(decision == 3){
				database.printTable();
			}
		}
	}
	std::cout << "Program ended" << std::endl;
	return 0;
}
