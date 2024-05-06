#include "Table.h"
#include <sstream>
Table::Table(std::string name, std::vector<std::string>& columns_name){ //Throw exception if columns have the same name
	this->name = name;
	this->columns_name = columns_name;//Throw exception if columns are empty in query_parser
	std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			this->table.push_back(std::vector<std::string>());
			});
}

void Table::save(std::ofstream& os){
	os << name << std::endl;
	os << size<< std::endl;
	os << columns_name.size()<< std::endl;
	for(std::string& column : columns_name){
		os << column<< std::endl;
	}
	for(std::vector<std::string> column : table){
		for(std::string cell : column){
			if(cell != "")
				os << cell<< std::endl;
			else
				os << "NULL" << std::endl;
		}
	}
}
Table::Table(std::ifstream& os){
	os >> this->name;
	os >> this->size;
	int num_of_colums;
	os >> num_of_colums;
	for(int i = 0; i < num_of_colums; i++){
		std::string temp;
		os >> temp;
		columns_name.push_back(temp);
	}
	for(int i = 0; i < num_of_colums; i++){
		std::vector<std::string> temp;
		for(int j = 0; j < this->size; j++){
			std::string tempstr;
			os >> tempstr;
			if(tempstr == "NULL") tempstr = "";
			temp.push_back(tempstr);
		}
		table.push_back(temp);
	}
}
void Table::print_Table(){
	/*std::cout << "___________________________________________\n" + name << std::endl;
	std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			std::cout << std::setw(15) <<  s << '\t';
			});
	std::cout << '\n';*/
	std::stringstream print;
	print_columns(print, columns_name, name);

	for(int x = 0; x < this->size; x++){
		for(int y = 0; y < columns_name.size(); y++){
			print << std::setw(15) << (table[y])[x];
		}
		print << '\n';
	}
	print << "___________________________________________"  << std::endl;
	std::cout << print.str();
}
void Table::print_columns(std::ostream& os, std::vector<std::string>const & columns_name, std::string const & name){
	os << "___________________________________________\n" + name << std::endl;
	std::for_each(columns_name.begin(), columns_name.end(),[&os](std::string s){
			os << std::setw(15) <<  s << '\t';
			});
	os << '\n';

}
void Table::select(std::vector<std::string> columnsToSelect, Where& where) const{
	if(columnsToSelect.size() == 1 && columnsToSelect[0] == "*") columnsToSelect = columns_name;
	std::stringstream print;
	print_columns(print, columnsToSelect, name);
	for(int i = 0; i < size; i++){
		if(where.conditionTrue(table, i, columns_name)){
			for(auto str : columnsToSelect){
				int j = 0;
				for(; j < columns_name.size(); j++){//finding the index of a column
					if(columns_name[j] == str) break;
				}
				if(j == columns_name.size()) throw std::string("Cannot find the column " + str);
				print << std::setw(15) << (table[j])[i] << "\t"; //this should append to a string and print a string at the end
			}
		print << "\n";
		}
	}
	print << "___________________________________________"  << std::endl;
	std::cout << print.str();
}
void Table::insert_into(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert){
	if(where_to_insert.size() != what_to_insert.size()) throw "Error"; //throw this in parser
	for(int i = 0; i < table.size(); i++){
		bool addnull = true;
		for(int j = 0; j < where_to_insert.size(); j++){
			if(columns_name[i] == where_to_insert[j]){
				table[i].push_back(what_to_insert[j]);
				addnull = false;
				break;
			}
		}
		if(addnull) table[i].push_back("");
	}
	size++;
}
void Table::update(Set& set, Where& where){
	for(int i = 0; i < size; i++){
		if(where.conditionTrue(table, i, columns_name)){
			set.set(table, i, columns_name);
		}
	}
}

void Table::_delete(Where& where){
	for(int i = 0; i < size; i++){
		if(where.conditionTrue(table, i, columns_name)){
			for(int j = 0; j < columns_name.size(); j++){//finding the index of a column
				(table[j]).erase((table[j]).begin() + i);
			}
			size--;
		}
	}
}
