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
			std::cout << "Creating Table" << std::endl;
			this->name = name;
			this->columns_name = columns_name;
			std::cout << "Created columns_name" << std::endl;
			std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
					this->table.push_back(new std::vector<std::string>());
					});
			std::cout << "Creating Table" << std::endl;
		}

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
			/*std::cout << "Printing Table" << std::endl;
			  int maxlen = 0;
			  std::for_each(this->columns_name.begin(), this->columns_name.end(),[this, &maxlen](std::string s)mutable{
			  if((*table[s]).size() > maxlen) maxlen = (*table[s]).size();
			  });
			  std::string matrix[maxlen][columns_name.size()];
			  for(int i = 0; i < columns_name.size(); i++){
			  for(int j = 0; j < (*table[columns_name[i]]).size(); j++){
			  matrix[j][i] = (*table[columns_name[i]])[j];
			  }
			  }
			  for(std::string s : columns_name){ std::cout << s << '\t';}
			  std::cout << '\n';
			  for(int i = 0; i < columns_name.size(); i++){
			  for(int j = 0; j < maxlen; j++){
			  std::cout << matrix[i][j] << '\t';
			  }
			  std::cout << '\n';
			  }
			  std::cout << "Table Printed" << std::endl;*/
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
			/*if(where_to_insert.size() != what_to_insert.size()) throw "Error: " + std::to_string(what_to_insert.size())
			  + " valuses for " + std::to_string(where_to_insert.size()) + " columns"; 
			  std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			  if(!column.count(s)) throw "Error: Table " + this->name + " has no column named " + s;});
			//if(std::find(table[where_to_insert]->begin(), table[where_to_insert]->end(), what_to_insert)
			//		== table[where_to_insert]->end()) throw "Error: Table " + this->name + " has no column named " + where_to_insert;

			std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
			//za svaku kolonu u mapi proveriti da li se naziv te kolone nalazi u where_to_insert i ako se nalazi
			//dodati what_to_insert, u suprotnom dodati ""

			});	*/			
		}

		/*
		   ~Table(){
		   std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
		   delete this->table[s];
		   });
		   }*/
};

