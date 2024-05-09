#include "Query_Update.h"

Query_Update::Query_Update(std::vector<std::string> tokens) : Query(tokens){
	if(!(lower(tokens.at(0)) == "update" && lower(tokens.at(2)) == "set")) throw std::string("Wrong Fromat");
	tableName = tokens.at(1);
	int i = 3;
	set = Set::read_set(i, "where", tokens, 0);
	where = Where::read_where(i, tokens, 1);
}
void Query_Update::execute(std::vector<Table> *tables){
	Table* tablePointer = nullptr;
	for(Table& table : *tables){
		if(table.getName() == tableName){tablePointer = &table; break;}
	}
	if(tablePointer == nullptr) throw "There isn't a table with that name ";
	tablePointer->update(set, where);
}
