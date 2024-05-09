#include "Query_Create.h"
Query_Create::Query_Create(std::vector<std::string> tokens) : Query(tokens){
	if(!(lower(tokens.at(0)) == "create" && lower(tokens.at(1)) == "table") && tokens.at(3) != "(") throw std::string("Wrong Fromat");
	tableName = tokens.at(2);
	int i = 4;
	read_columns(i, ")", columnsName, true, false);
}
void Query_Create::execute(std::vector<Table> *tables){
	std::for_each(tables->begin(), tables->end(), [this](auto s){ //Checking if tableName already exists
			if(this->tableName == s.getName())throw "Error: " + tableName + " already exists";
			});
	Table t(tableName, columnsName);
	tables->push_back(t);
}

