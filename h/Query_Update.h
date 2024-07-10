#ifndef Query_Update_h
#define Query_Update_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
#include <regex>
class Query_Update : public Query{
	private:
		std::string tableName;
		Set set;
		Where where;
	public:
		Query_Update(std::vector<std::string> tokens);
		void execute(std::vector<Table> *tables);
};
#endif
