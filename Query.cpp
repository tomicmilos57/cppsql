#include "Query.h"
#include "Query_Update.h"
void Query::read_columns(int& i, std::string lastToken, std::vector<std::string>& columns, bool last, bool byValue){
	for(int j = 0; i < tokens.size() && lower(tokens[i]) != lastToken; i++, j++) {
		if(j%2==0){
			if(byValue){
				if(!(*tokens[i].begin() == '\'' && *tokens[i].rbegin() == '\''))throw std::string("No such column: " + tokens[i]);
				tokens[i] = tokens[i].substr(1, tokens[i].size() - 2);
			}
			columns.push_back(tokens[i]);	
		}
		if(j%2==1)if(!(tokens[i] == "," || lower(tokens[i]) == lastToken)) throw std::string("Wrong Fromat in parentheses: " + tokens[i]);
	}
	if(last){
		if(i == tokens.size()) throw(std::string("No closing parentheses"));
		if(!((i+1 == tokens.size() && tokens[i] == ")") || (i+2 == tokens.size() && tokens[i+1] == ";"))) throw std::string("Too many symbols at the end of the query");
	}
}
std::string Query::lower(std::string str){
	for(int i = 0; i < str.size(); i++){
		str[i] = std::tolower(str[i]);
	}
	return str;
}
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
#include "Query_Delete.h"
Query_Delete::Query_Delete(std::vector<std::string> tokens) : Query(tokens){	
	if(!(lower(tokens.at(0)) == "delete" && lower(tokens.at(1)) == "from")) throw std::string("Wrong Fromat");
	tableName = tokens.at(2);//check if this token exists before accesing it or use .at and throw exception
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
#include "Query_Drop.h"
Query_Drop::Query_Drop(std::vector<std::string> tokens) : Query(tokens){
	if(!(lower(tokens.at(0)) == "drop" && lower(tokens.at(1)) == "table" && tokens.size() == 3)) throw std::string("Wrong Fromat");
	tableName = tokens.at(2);
}
void Query_Drop::execute(std::vector<Table> *tables){
	for(auto it = tables->begin(); it != tables->end(); ++it){
		if((*it).getName() == tableName){
			tables->erase(it);
			return;
		}
	}
	throw std::string("Nothing to remove");
	//tables[tableName].drop
}
#include "Query_Insert.h"
Query_Insert::Query_Insert(std::vector<std::string> tokens_) : Query(tokens_){
	/*if(!(lower(tokens.at(0)) == "insert" && lower(tokens.at(1)) == "into" && tokens.at(3) == "(")
			&& std::find_if(
				begin(tokens),
				end(tokens),
				[this](std::string obj){return obj == lower("values");}) 
			!= end(tokens))
		throw std::string("Wrong Fromat");*/
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
#include "Query_Select.h"
Query_Select::Query_Select(std::vector<std::string> tokens) : Query(tokens){
	if(lower(tokens.at(0)) != "select") throw std::string("Wrong Fromat");
	int i = 1;
	read_columns(i, "from", columns, 0, 0);
	if(lower(tokens.at(i++)) != "from") throw std::string("Where is from keyword?!?!");
	tableName = tokens.at(i++);
	where = Where::read_where(i, tokens, 1);
}
void Query_Select::execute(std::vector<Table> *tables){
	Table* tablePointer = nullptr;
	for(Table& table : *tables){
		if(table.getName() == tableName){tablePointer = &table; break;}
	}
	if(tablePointer == nullptr) throw std::string("There isn't a table with that name ");
	tablePointer->select(columns, where);
}
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
