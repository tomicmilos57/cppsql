#include <vector>
#include <string>
#include "Table.h"

class Database{
	private:
		std::vector<Table> tables;
	public:
		Database(){} //We can have complex constructor for importing database
		void createTable(std::string name, std::vector<std::string> column_name){
			tables.push_back(Table(name, column_name));
		}
		void printTable(){
			tables[0].print_Table();
		}
		void insertTable(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert){
			tables[0].insert_into(where_to_insert, what_to_insert);
		}
};
