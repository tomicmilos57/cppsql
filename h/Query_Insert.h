#ifndef Query_Insert_h
#define Query_Insert_h

#include "Query.h"
#include <algorithm>
#include <regex>
class Query_Insert : public Query {
	private:
		std::string tableName;
		std::vector<std::string> where_to_insert;
		std::vector<std::string> what_to_insert;
	public:
		Query_Insert(std::vector<std::string> tokens_);
		void execute(std::vector<Table> *tables);
};


#endif
