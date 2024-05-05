#ifndef Query_Delete_h
#define Query_Delete_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
#include <regex>
class Query_Delete : public Query{
	private:
		std::string tableName;
		Where where;
	public:
		Query_Delete(std::vector<std::string> tokens);
		void execute(std::vector<Table> *tables);
};
#endif
