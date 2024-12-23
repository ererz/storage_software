#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include <vector>

class database {
    private:
      char name;
      int exit;
      sqlite3 *db;

    public:
        database() {
            name = ' ';
        };
        database(char database_name) {
            name = database_name;
        };

        void setName(char database_name){
            this->name = database_name;
        };
        char getName(){
            return this->name;
        };
        void printName() {
            std::cout << "Database name: " << name << std::endl;
        };
        struct column {
            std::string name;
            std::string type;
            bool is_primary_key = false;
            bool is_foreign_key = false;
            std::string foreign_key_table = "";
            std::string foreign_key_column = "";
        };
        bool setup_connection();
        bool close_connection(){
            sqlite3_close(db);
            free(db);
            name = '\0';
            exit = 0;
            return true;
        };
        bool create_table(std::string *table_name, const std::vector<column>& columns);
        bool insert_data(std::string *table_name, const std::vector<std::string>& data);
        bool update_data(std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data);
        bool delete_data(std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data);
        bool select_data(std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data);

        ~database(){
            sqlite3_close(db);
        };
};



#endif //DATABASE_H
