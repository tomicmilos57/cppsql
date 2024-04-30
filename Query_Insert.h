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
		Query_Insert(std::vector<std::string> tokens_) : Query(tokens_){
			/*
			 if(!(lower(tokens[0]) == "create" && lower(tokens[1]) == "table") && tokens[3] != "(") throw std::string("Wrong Fromat");
			tableName = tokens[2];
			int i = 4;
			read_csv_until_delim(i, ")", columnsName);
			if(i == tokens.size()) throw(std::string("No closing parentheses"));
			if(!((i+1 == tokens.size() && tokens[i] == ")") || (i+2 == tokens.size() && tokens[i+1] == ";"))) throw std::string("Too many symbols at the end of the query");
			 */
			if(!(lower(tokens[0]) == "insert" && lower(tokens[1]) == "into" && tokens[3] == "(")
					&& std::find_if(
						begin(tokens),
						end(tokens),
						[this](std::string obj){return obj == lower("values");}) 
					!= end(tokens))
				throw std::string("Wrong Fromat");
			tableName = tokens[2];
			int i = 4;//check if i = 3 is (
			read_csv_until_delim(i, ")", where_to_insert, false);
			if(lower(tokens[++i]) != "values") throw std::string("Cannot find VALUES");
			if(lower(tokens[++i]) != "(") throw std::string("Cannot find second parentheses");
			read_csv_until_delim(++i, ")", what_to_insert, true);
			/*for(; lower(tokens[i]) != "values"; i++){
				where_to_insert.push_back(tokens[i]);
			}
			i++;
			for(; i < tokens.size(); i++){
				what_to_insert.push_back(tokens[i]);
			}
			if(what_to_insert.size() != where_to_insert.size()) throw std::string("Wrong number of elements");*/
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't table with that name ";
			tablePointer->insert_into(where_to_insert,what_to_insert);
			//try{tablePointer->insert_into(where_to_insert,what_to_insert);}
			//catch(char const* errormessage) {std::cout << errormessage << std::endl;}
		}

};


#endif
