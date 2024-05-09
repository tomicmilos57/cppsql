#include "Query_Delete.h"
Query_Delete::Query_Delete(std::vector<std::string> tokens) : Query(tokens){	
	if(!(lower(tokens.at(0)) == "delete" && lower(tokens.at(1)) == "from")) throw std::string("Wrong Fromat");
	tableName = tokens.at(2);
	int i = 3;
	where = Where::read_where(i, tokens, 1);
}
void Query_Delete::execute(std::vector<Table> *tables){
	Table* tablePointer = nullptr;
	for(Table& table : *tables){
		if(table.getName() == tableName){tablePointer = &table; break;}
	}
	if(tablePointer == nullptr) throw "There isn't a table with that name ";
	tablePointer->_delete(where);
}

