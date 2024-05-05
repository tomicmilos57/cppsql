#ifndef Query_Select_h
#define Query_Select_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
class Query_Select : public Query{
	private:
		std::string tableName;
		std::vector<std::string> columns;
		Set set;
		Where where;
	public:
		Query_Select(std::vector<std::string> tokens);
		void execute(std::vector<Table> *tables);
};
#endif
