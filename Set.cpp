#include "Set.h"
void Set::set(std::vector<std::vector<std::string>>& table, int row, const std::vector<std::string> columnName){
	for(auto pair : pairs){
		int i = 0;
		for(; i < columnName.size(); i++){//finding the index of a column
			if(columnName[i] == pair->columnName) break;
		}
		if(i == columnName.size()) throw std::string("Cannot find the column");
		(table[i])[row] = pair->value;
	}
}
void Set::print(){
	//std::for_each(pairs.begin(), pairs.end(), [](ChangeTo c){std::cout << c.columnName << " " << c.value << std::endl;});
	for(ChangeTo* c : pairs){
		std::cout << c->columnName << " " << c->value << std::endl;
	}
}
void Set::push_back(ChangeTo* change){
	pairs.push_back(change);
}
Set Set::read_set(int& i, std::string delim, const std::vector<std::string>& tokens, bool last){
	Set s;
	Set::ChangeTo* vec; 
	for(int j = 0; i < tokens.size() && lower(tokens[i]) != delim; i++, j++) {
		if(j%4==0){vec = new Set::ChangeTo();vec->columnName = tokens[i];}	
		if(j%4==1)if(tokens[i] != "=") throw std::string("Wrong Fromat with equals sign");
		if(j%4==2){
			if(!(*tokens[i].begin() == '\'' && *tokens[i].rbegin() == '\''))throw std::string("No such column: " + tokens[i]);
			vec->value = tokens[i].substr(1, tokens[i].size() - 2);
			s.push_back(vec);}
		if(j%4==3){if(!(tokens[i] == "," || lower(tokens[i]) == delim))throw std::string("Wrong Fromat in parentheses");}
	}
	if(last){
		if(i == tokens.size()) throw(std::string("No closing parentheses"));
		if(!((i+1 == tokens.size() && tokens[i] == ")") || (i+2 == tokens.size() && tokens[i+1] == ";"))) throw std::string("Too many symbols at the end of the query");
	}
	return s;
}
std::string Set::lower(std::string str){//make this function global f
	for(int i = 0; i < str.size(); i++){
		str[i] = std::tolower(str[i]);
	}
	return str;
}

