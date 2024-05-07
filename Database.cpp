#include "Database.h"
void Database::execute(std::string strQuery){
	Query *query;
	try {
		auto tokens =  tokenizer.tokenize(strQuery);	
		query = parser.parse(tokens);
		try {
			query->execute(&tables);
			sqlFile.append(strQuery + ";\n");
		}
		catch(std::string e) {std::cout << e << std::endl;}
		catch(const std::runtime_error& re){std::cerr << "Runtime error: " << re.what() << std::endl;}
		catch(const std::exception& ex){std::cerr << "Error occurred: " << ex.what() << std::endl;}
		catch(...){std::cout << "Unknown Exception Cought" << std::endl;}
		if(query != nullptr)delete query;
	} catch(std::string e){std::cout << e << std::endl;}
}
void Database::printTable(){
	std::for_each(tables.begin(), tables.end(), [](auto t){t.print_Table();});
}
void Database::save_sql(){
	std::ofstream output;
	output.open("output.sql");
	output << sqlFile;
	output.close();
}
void Database::save(std::ofstream& os){
	os << tables.size() << std::endl;
	for(Table& table : tables){
		table.save(os);
	}
}
void Database::load(std::ifstream& os){
	std::cout << "Loading" << std::endl;
	int num_of_tables;
	os >> num_of_tables;
	for(int i = 0; i < num_of_tables; i++){
		tables.push_back(Table(os));
	}
}
