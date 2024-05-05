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
		Query_Select(std::vector<std::string> tokens) : Query(tokens){
			if(lower(tokens[0]) != "select") throw std::string("Wrong Fromat");
			int i = 1;
			read_columns(i, "from", columns, 0, 0);
			if(lower(tokens[i++]) != "from") throw std::string("Where is from keyword?!?!");
			tableName = tokens[i++];
			if(lower(tokens[i]) != "where") throw std::string("Where is where?!?!");
			where = Where::read_where(++i, tokens, 1);
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw std::string("There isn't a table with that name ");
			tablePointer->select(columns, where);
		}
};
#endif
