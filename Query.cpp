#include "Query.h"
#include <string>
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

