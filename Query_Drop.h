#ifndef Query_Drop_h
#define Query_Drop_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
#include <regex>
class Query_Drop : public Query{
	private:
		std::string tableName;
	public:
		Query_Drop(std::vector<std::string> tokens);
		void execute(std::vector<Table> *tables);
};
#endif
