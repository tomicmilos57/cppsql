#ifndef Table_h
#define Table_h

#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
class Table{
	private:
		std::string name;
		std::vector<std::string> columns_name;
		std::vector<std::vector<std::string>*> table;
		int size = 0;
		//std::vector<std::string> columns_name;
		//std::map<std::string, std::vector<std::string>*> column;
	public:
		Table(std::string name, std::vector<std::string>& columns_name){ //Throw exception if columns have the same name
			this->name = name;
			this->columns_name = columns_name;//Throw exception if columns are empty
			std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
					this->table.push_back(new std::vector<std::string>());
					});
		}

		std::string getName(){return name;}
		void print_Table(){
			std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
					std::cout << std::setw(15) <<  s << '\t';
					});
			std::cout << '\n';

			for(int x = 0; x < this->size; x++){
				for(int y = 0; y < columns_name.size(); y++){
					std::cout << std::setw(15) << (*table[y])[x];
				}
				std::cout << '\n';
			}
			std::cout << '\n';
		}
		void insert_into(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert){
			if(where_to_insert.size() != what_to_insert.size()) throw "Error";
			for(int i = 0; i < table.size(); i++){
				bool addnull = true;
				for(int j = 0; j < where_to_insert.size(); j++){
					if(columns_name[i] == where_to_insert[j]){
						table[i]->push_back(what_to_insert[j]);
						addnull = false;
						break;
					}
				}
				if(addnull) table[i]->push_back("");
			}
			size++;
		}

		/*
		   ~Table(){
		   std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
		   delete this->table[s];
		   });
		   }*/
};
#endif
