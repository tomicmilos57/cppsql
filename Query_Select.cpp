#include "Query_Select.h"
Query_Select::Query_Select(std::vector<std::string> tokens) : Query(tokens){
	if(lower(tokens.at(0)) != "select") throw std::string("Wrong Fromat");
	int i = 1;
	read_columns(i, "from", columns, 0, 0);
	if(lower(tokens.at(i++)) != "from") throw std::string("Where is from keyword?!?!");
	tableName = tokens.at(i++);
	std::string column1;
	std::string sign;
	std::string column2;
	if(i < tokens.size() && lower(tokens.at(i)) != "where"){ //Person p - reading p
		abbreviation = tokens.at(i);
		i++;
		if(!(lower(tokens.at(i)) == "inner" && lower(tokens.at(i + 1)) == "join")) throw std::string("After the table name, there should be its abbreviation, or Where keyword");
		innerjoin = true;
		i += 2;
		tableName2 = tokens.at(i++);
		abbreviation2 = tokens.at(i++);
		if(lower(tokens.at(i++)) != "on")throw std::string("Missing ON keyword");
		column1 = tokens.at(i++);
		sign = tokens.at(i++);
		column2 = tokens.at(i++);
		viewWhere.insertCondition(column1, sign, column2);
	}
	where = Where::read_where(i, tokens, 1);
}
void Query_Select::execute(std::vector<Table> *tables){
	Table* tablePointer = nullptr;
	for(Table& table : *tables){
		if(table.getName() == tableName){tablePointer = &table; break;}
	}
	if(tablePointer == nullptr) throw std::string("There isn't a table with that name ");
	if(this->innerjoin){
		Table* tablePointer2 = nullptr;
		for(Table& table : *tables){
			if(table.getName() == tableName2){tablePointer2 = &table; break;}
		}
		if(tablePointer2 == nullptr) throw std::string("There isn't a table with that name ");
		Table::innerjoin(*tablePointer, *tablePointer2, columns, abbreviation, abbreviation2, viewWhere, where);
	}else{
		tablePointer->select(columns, where);
	}
}

