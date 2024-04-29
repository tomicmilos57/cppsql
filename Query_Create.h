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
		Query_Create(std::vector<std::string> tokens) : Query(tokens){
			if(!(lower(tokens[0]) == "create" && lower(tokens[1]) == "table")) throw std::string("Wrong Fromat");
			tableName = tokens[2];
			for(int i = 3; i < tokens.size(); i++) columnsName.push_back(tokens[i]);
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
