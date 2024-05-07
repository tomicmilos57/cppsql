#include "Where.h"
bool Where::conditionTrue(std::vector<std::vector<std::string>> table, int row, const std::vector<std::string> columnName) const {
	bool condition = true;
	for(auto pair : pairs){
		int i = 0;
		for(; i < columnName.size(); i++){//finding the index of a column
			if(columnName[i] == pair->columnName) break;
		}
		if(i == columnName.size()) throw std::string("Cannot find the column " + pair->columnName);
		if(!pair->match((table[i])[row])){
			condition = false;
			break;
		}
	}
	return condition;
}
bool Where::conditionTrue(std::vector<std::string> const & row, std::vector<std::string> const & columnName)const{
	int index1 = -1;
	int index2 = -1;
	bool condition = true;
	for(auto pair : pairs){
		for(int i = 0; i < columnName.size(); i++){
			if(columnName[i] == pair->columnName)index1 = i;
			if(columnName[i] == pair->value)index2 = i;
		}
		if(index1 == -1 || index2 == -1) throw std::string("Cannot find the columns " + pair->columnName + " " + pair->value);
		if(!pair->match_eachother(row[index1], row[index2])){
			condition = false;
			break;
		}
	}
	return condition;
}
void Where::insertCondition(std::string col1, std::string sign, std::string col2){
	if(sign == "="){
		Equals *e = new Equals();
		e->columnName = col1;
		e->value = col2;
		push_back(e);
		return;
	}
	if(sign == "<>"){
		NotEqual *e = new NotEqual();
		e->columnName = col1;
		e->value = col2;
		push_back(e);
		return;
	}
}
Where Where::read_where(int& i, const std::vector<std::string>& tokens, bool last){
	if((tokens.size() <= i) || (tokens.size() - 1 == i) && tokens[i] == ";"){//if there isn't "where" token
		return TrueWhere();
	}
	if(lower(tokens[i]) != "where") throw std::string("Where is where?!?!");
	i++;
	Where where;
	Where::Condition* cond;
	std::string columnName;
	std::string val;
	//std::cout << i << " " << tokens[i] << std::endl;
	for(int j = 0; i < tokens.size() && tokens[i] != ";"; i++, j++) {
		if(j%4==0){columnName = tokens[i]; continue;}	
		if(j%4==1){
			if(tokens[i] != "=" && tokens[i] != "<>"){where.dealocate(); throw std::string("Wrong Fromat with equals sign");}
			if(tokens[i] == "=") {cond = new Where::Equals();where.push_back(cond);}
			if(tokens[i] == "<>") {cond = new Where::NotEqual();where.push_back(cond);}
			continue;
		}
		if(j%4==2){
			if(!(*tokens[i].begin() == '\'' && *tokens[i].rbegin() == '\'')){where.dealocate();throw std::string("No such column: " + tokens[i]);}
			std::string temp = tokens[i].substr(1, tokens[i].size() - 2);
			val = temp;
			cond->columnName = columnName;
			cond->value = val;
			continue;}
		if(j%4==3)if(lower(tokens[i]) != "and"){// || lower(tokens[i]) == "or" 
			where.dealocate();
			throw std::string("Wrong Fromat");
		}
	}
	if(last){
		if(!((i+1 == tokens.size() && tokens[i] == ";" || i == tokens.size()))){where.dealocate(); throw std::string("Too many symbols at the end of the query");}
	}
	return where;
}
void Where::dealocate(){
	int size = this->pairs.size();
	for(int i = 0; i < size; i++){
		delete pairs.back();
		pairs.pop_back();
	}
}
void Where::print(){
	//std::for_each(pairs.begin(), pairs.end(), [](Condition* c){std::cout << c->columnName << " " << c->value << std::endl;});
	for(Condition* c : pairs){
		std::cout << c->columnName << " " << c->value << std::endl;
	}
}
std::string Where::lower(std::string str){//make this function global f
	for(int i = 0; i < str.size(); i++){
		str[i] = std::tolower(str[i]);
	}
	return str;
}
