#ifndef Database_h
#define Database_h
#include <algorithm>
#include <vector>
#include <string>
#include "Parser.h"
class Database{
	private:
		std::vector<Table> tables;
	public:
		Database(){} //We can have complex constructor for importing database
		void execute(std::string query){
			Parser parser;
			Query* q = parser.parse(query);
			if(q != nullptr)try {q->execute(&tables);}catch(char const* e) {std::cout << e << std::endl;}
			delete q;
		}
		void printTable(){
			std::for_each(tables.begin(), tables.end(), [](auto t){t.print_Table();});
		}
		void insertTable(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert){
			tables[0].insert_into(where_to_insert, what_to_insert);
		}
};
#endif
