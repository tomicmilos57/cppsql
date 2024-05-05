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
		Query_Delete(std::vector<std::string> tokens) : Query(tokens){
			if(!(lower(tokens[0]) == "delete" && lower(tokens[1]) == "from")) throw std::string("Wrong Fromat");
			tableName = tokens[2];//check if this token exists before accesing it or use .at and throw exception
			if(lower(tokens[3]) != "where") throw std::string("Where where?!?");
			int i = 4;
			where = Where::read_where(i, tokens, 1);
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't a table with that name ";
			tablePointer->_delete(where);
		}
};
#endif
