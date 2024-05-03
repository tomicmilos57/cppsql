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
		Query_Update(std::vector<std::string> tokens) : Query(tokens){
			if(!(lower(tokens[0]) == "update" && lower(tokens[2]) == "set")) throw std::string("Wrong Fromat");
			tableName = tokens[1];
			int i = 3;
			set = Set::read_set(i, "where", tokens, 0);
			where = Where::read_where(++i, tokens, 1);
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't a table with that name ";
			tablePointer->update(set, where);
		}
};
#endif
