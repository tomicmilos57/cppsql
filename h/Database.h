#ifndef Database_h
#define Database_h
#include <algorithm>
#include <iterator>
#include <ostream>
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
		Database(){}
		void execute(std::string strQuery);
		void printTable();
		void save_sql(std::ofstream& os);
		void save(std::ofstream& os);
		void load(std::ifstream& os);
};
#endif
