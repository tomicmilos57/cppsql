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
			set = read_set(i, "where", 0);
			where = read_where(++i, 1);
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't a table with that name ";
			tablePointer->update(set, where);
		}
	private:
		Set read_set(int& i, std::string delim, bool last){
			Set s;
			Set::ChangeTo* vec; 
			for(int j = 0; i < tokens.size() && lower(tokens[i]) != delim; i++, j++) {
				if(j%4==0){vec = new Set::ChangeTo();vec->columnName = tokens[i];}	
				if(j%4==1)if(tokens[i] != "=") throw std::string("Wrong Fromat with equals sign");
				if(j%4==2){vec->value = tokens[i];s.push_back(vec);}
				if(j%4==3){if(!(tokens[i] == "," || lower(tokens[i]) == delim))throw std::string("Wrong Fromat in parentheses");}
			}
			if(last){
				if(i == tokens.size()) throw(std::string("No closing parentheses"));
				if(!((i+1 == tokens.size() && tokens[i] == ")") || (i+2 == tokens.size() && tokens[i+1] == ";"))) throw std::string("Too many symbols at the end of the query");
			}
			return s;
		}
		Where read_where(int& i, bool last){
			Where where;
			Where::Condition* cond;
			std::string columnName;
			std::string val;
			for(int j = 0; i < tokens.size() && tokens[i] != ";"; i++, j++) {
				if(j%4==0){columnName = tokens[i]; continue;}	
				if(j%4==1){
					if(tokens[i] != "=" && tokens[i] != "<>") throw std::string("Wrong Fromat with equals sign");
					if(tokens[i] == "=") {cond = new Where::Equals();}
					if(tokens[i] == "<>") {cond = new Where::NotEqual();}
					continue;
				}
				if(j%4==2){val = tokens[i];
					cond->columnName = columnName;
					cond->value = val;
					where.push_back(cond);
					continue;}
				if(j%4==3)if(lower(tokens[i]) != "and")// || lower(tokens[i]) == "or" 
					throw std::string("Wrong Fromat");
			}
			if(last){
				if(!((i+1 == tokens.size() && tokens[i] == ";" || i == tokens.size()))) throw std::string("Too many symbols at the end of the query");
			}
			return where;
		}
};
#endif
