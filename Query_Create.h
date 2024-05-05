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
		Query_Create(std::vector<std::string> tokens);
		void execute(std::vector<Table> *tables);
};
#endif
