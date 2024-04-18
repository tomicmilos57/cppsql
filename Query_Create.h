#ifndef Query_Create_h
#define Query_Create_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
#include <regex>
class Query_Create : public Query{
	private:
		std::string tableName;
		std::vector<std::string> columnsName;
	public:
		Query_Create(std::string query){
			//std::cout << "Inside Query_create constuctor with "  <<  query  << "\n";
			//std::string query = "    CREATE   TabLe beton      (  sa  firma    ,   gazda    ,   palta   )  ;";
			std::regex reg("^\\s*[Cc][Rr][Ee][Aa][Tt][Ee]\\s*[Tt][Aa][Bb][Ll][Ee]\\s*(\\w+)\\s*\\((.*)\\)\\s*;?$");
			if ( regex_match(query, reg) ){
				//std::cout << "Query matches regex \n";
				std::smatch m;
				regex_search(query, m, reg);

				//std::cout << "Table name " << m.str(1) << " " << std::endl;
				tableName = m.str(1);
				std::string temp = m.str(2);
				std::replace(temp.begin(), temp.end(), ',', ' ');
				std::regex subreg("(\\w+)");
				std::smatch submatch;
				while (regex_search(temp, submatch, subreg)){
					//std::cout << submatch.str(1) << std::endl;
					columnsName.push_back(submatch.str(1));
					temp = submatch.suffix();
				}
			}
		}
		void execute(std::vector<Table> *tables){
			std::for_each(tables->begin(), tables->end(), [this](auto s){ //Checking if tableName already exists
					if(this->tableName == s.getName())throw "Error: " + tableName + " already exists";
					});
			Table t(tableName, columnsName);
			tables->push_back(t);
		}
};
#endif
