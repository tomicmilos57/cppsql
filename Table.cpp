#include "Table.h"
#include <iterator>
#include <sstream>
Table::Table(std::string name, std::vector<std::string> const & columns_name){ //Throw exception if columns have the same name
	this->name = name;
	this->columns_name = columns_name;//Throw exception if columns are empty in query_parser
	std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			this->table.push_back(std::vector<std::string>());
			});
}
Table::Table(Table const & t1, Table const & t2, std::string abbr1, std::string abbr2, Where const & viewWhere){//for inner join
	this->name = "INNER JOIN";
	for(std::string str : t1.columns_name){
		this->columns_name.push_back(abbr1 + "." + str);
	}
	for(std::string str : t2.columns_name){
		this->columns_name.push_back(abbr2 + "." + str);
	}
	std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			this->table.push_back(std::vector<std::string>());
			});
	for(int i = 0; i < t1.size; i++){
		std::vector<std::string> row1;
		for(int k = 0; k < t1.table.size(); k++)row1.push_back(t1.table[k][i]);
		for(int j = 0; j < t2.size; j++){
			std::vector<std::string> row2;
			for(int k = 0; k < t2.table.size(); k++)row2.push_back(t2.table[k][j]);
			std::vector<std::string> temp;
			temp.insert(temp.end(), row1.begin(), row1.end() );
			temp.insert(temp.end(), row2.begin(), row2.end() );
			if(viewWhere.conditionTrue(temp, columns_name))this->insert_into(this->columns_name, temp);
		}
	}

}
void Table::save_sql(std::ofstream& os)const{
	std::stringstream create;
	create << "CREATE TABLE " << this->name << " ";
	std::stringstream columns;
	columns << "(";
	for(int i = 0; i < columns_name.size(); i++){
		columns << columns_name[i];
		if(i < columns_name.size() - 1)columns << ", ";
	}
	columns << ")";
	create << columns.str() << ";";
	os << create.str() << std::endl;
	std::stringstream insert_template;
	insert_template << "INSERT INTO " << this->name << " " << columns.str() << " VALUES (";
	for(int i = 0; i < this->size; i++){
		std::stringstream insert;
		insert << insert_template.str();
		for(int j = 0; j < columns_name.size(); j++){
			insert << "\'" << table[j][i] << "\'";
			if(j < columns_name.size() - 1)insert << ", ";
		}
		insert << ");" << std::endl;
		os << insert.str();
	}
}
void Table::save(std::ofstream& os) const {
	os << name << std::endl;
	os << size<< std::endl;
	os << columns_name.size()<< std::endl;
	for(std::string const & column : columns_name){
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
void Table::print_Table() const {
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
void Table::select(std::vector<std::string> const & columnsSelect, Where const & where) const{
	std::vector<std::string> columnsToSelect = columnsSelect;
	if(columnsSelect.size() == 1 && columnsSelect[0] == "*") columnsToSelect = columns_name;
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

void Table::innerjoin(Table const & Table1, Table const & Table2, std::vector<std::string> const & columns,
		std::string abbreviation1, std::string abbreviation2, Where& viewWhere, Where& where){
	Table view(Table1, Table2, abbreviation1, abbreviation2, viewWhere);
	view.select(columns, where);
}
void Table::insert_into(std::vector<std::string> const & where_to_insert, std::vector<std::string> const & what_to_insert){
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

void Table::_delete(Where const & where){
	for(int i = 0; i < size; i++){
		if(where.conditionTrue(table, i, columns_name)){
			for(int j = 0; j < columns_name.size(); j++){//finding the index of a column
				(table[j]).erase((table[j]).begin() + i);
			}
			i--;
			size--;
		}
	}
}
