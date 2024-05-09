#include "Query_Insert.h"
Query_Insert::Query_Insert(std::vector<std::string> tokens_) : Query(tokens_){
	if(!(lower(tokens.at(0)) == "insert" && lower(tokens.at(1)) == "into" && tokens.at(3) == "("))
		throw std::string("Wrong Fromat");
	tableName = tokens.at(2);
	int i = 4;//check if i = 3 is (
	read_columns(i, ")", where_to_insert, false, false);
	if(lower(tokens.at(++i)) != "values") throw std::string("Cannot find VALUES");
	if(lower(tokens.at(++i)) != "(") throw std::string("Cannot find second parentheses");
	read_columns(++i, ")", what_to_insert, true, true);
}
void Query_Insert::execute(std::vector<Table> *tables){
	Table* tablePointer = nullptr;
	for(Table& table : *tables){
		if(table.getName() == tableName){tablePointer = &table; break;}
	}
	if(tablePointer == nullptr) throw "There isn't table with that name ";
	tablePointer->insert_into(where_to_insert,what_to_insert);
}

