#include "database.h"

bool database::setup_connection () {
    exit = sqlite3_open(&name, &db);

    if (exit) {
        std::cerr << "error at opening database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    std::cout << "database opened succesfully!" << std::endl;

    return true;
}

bool database::create_table ( std::string *table_name, const std::vector<column>& columns ) {
    char* messageError;
    std::string sql = "";

    sql += "CREATE TABLE " + *table_name + " (";

    for (int i = 0; i < columns.size(); i++) {
        sql += columns[i].name + " " + columns[i].type;
        if (columns[i].is_primary_key) {
            sql += " PRIMARY KEY";
        }
        if (columns[i].is_foreign_key) {
            sql += " FOREIGN KEY (" + columns[i].name + ") REFERENCES " + columns[i].foreign_key_table + "(" + columns[i].foreign_key_column + ")";
        }
        if (i < columns.size() - 1) {
            sql += ", ";
        }
    }

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error at create table: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "Table created successfully!" << std::endl;

    exit = 0;

    return true;
}

bool database::insert_data ( std::string *table_name, const std::vector<std::string>& data ) {
    std::string sql = "";
    char* messageError;

    sql += "INSERT INTO " + *table_name + " VALUES (";

    for (int i = 0; i < data.size(); i++) {
        sql += data[i];
        if (i < data.size() - 1) {
            sql += ", ";
        }
    }

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error at insert data: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "Data inserted successfully!" << std::endl;

    exit = 0;

    return true;
}

bool database::update_data ( std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data ) {
    std::string sql = "";
    char* messageError;

    sql += "UPDATE " + *table_name + " SET ";

    for (int i = 0; i < column.size(); i++) {
        sql += column[i] + " = " + data[i];
        if (i < column.size() - 1) {
            sql += ", ";
        }
    }

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error at update data: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "Data updated successfully!" << std::endl;

    exit = 0;

    return true;
}

bool database::delete_data ( std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data ) {
    std::string sql;
    char* messageError;

    sql += "DELETE FROM " + *table_name + " WHERE ";

    for (int i = 0; i < column.size(); i++) {
        sql += column[i] + " = " + data[i];
        if (i < column.size() - 1) {
            sql += " AND ";
        }
    }

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error at delete data: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "Data deleted successfully!" << std::endl;

    exit = 0;

    return true;
}

bool database::select_data ( std::string *table_name, const std::vector<std::string>& column, const std::vector<std::string>& data ) {
    std::string sql;
    char* messageError;

    sql += "SELECT * FROM " + *table_name;

    if (column.size() > 0) {
        sql += " WHERE ";
        for (int i = 0; i < column.size(); i++) {
            sql += column[i] + " = " + data[i];
            if (i < column.size() - 1) {
                sql += " AND ";
            }
        }
    }

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error at select data: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    exit = 0;

    std::cout << "Data selected successfully!" << std::endl;

    return true;
}