#ifndef Query_h
#define Query_h

#include "Table.h"
#include <string>
#include <vector>
class Query{
	protected: 
		std::vector<std::string> tokens;
	public:
		Query(std::vector<std::string> tokens) : tokens(tokens){}
		void virtual execute(std::vector<Table> *tables){}
	protected:
		void read_csv_until_delim(int& i, std::string delim, std::vector<std::string>& columns, bool last){
			for(int j = 0; i < tokens.size() && lower(tokens[i]) != delim; i++, j++) {
				if(j%2==0)columns.push_back(tokens[i]);	
				if(j%2==1)if(!(tokens[i] == "," || lower(tokens[i]) == delim)) throw std::string("Wrong Fromat in parentheses: " + tokens[i]);
			}
			if(last){
				if(i == tokens.size()) throw(std::string("No closing parentheses"));
				if(!((i+1 == tokens.size() && tokens[i] == ")") || (i+2 == tokens.size() && tokens[i+1] == ";"))) throw std::string("Too many symbols at the end of the query");
			}
		}
		std::string lower(std::string str){
			for(int i = 0; i < str.size(); i++){
				str[i] = std::tolower(str[i]);
			}
			return str;
		}

};
#endif
