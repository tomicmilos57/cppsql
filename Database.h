#ifndef Database_h
#define Database_h
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "Tokenizer.h"
#include "Parser.h"
#include <fstream>
class Database{
	private:
		std::vector<Table> tables;
		Tokenizer tokenizer;
		Parser parser;
	public:
		Database(){} //We can have complex constructor for importing database
		void execute(std::string query){
			try {
				auto tokens =  tokenizer.tokenize(query);	
				Query *query = parser.parse(tokens);
				try {query->execute(&tables);}
				catch(std::string e) {std::cout << e << std::endl;}
				catch(const std::runtime_error& re){std::cerr << "Runtime error: " << re.what() << std::endl;}
				catch(const std::exception& ex){std::cerr << "Error occurred: " << ex.what() << std::endl;}
				catch(...){std::cout << "Unknown Exception Cought" << std::endl;}
				if(query != nullptr)delete query;

			} catch(std::string e){std::cout << e << std::endl;}

		}
		void printTable(){
			std::for_each(tables.begin(), tables.end(), [](auto t){t.print_Table();});
		}
		void insertTable(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert){
			tables[0].insert_into(where_to_insert, what_to_insert);
		}
};
#endif
