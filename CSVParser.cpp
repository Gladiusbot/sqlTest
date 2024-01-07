#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Timer.h"

int main() {
  try {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    const std::string db_host = "172.17.0.2";
    const std::string db_user = "root";
    const std::string db_password = "123456";
    const std::string db_name = "BILLS";

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(db_host, db_user, db_password);
    con->setSchema(db_name);
    stmt = con->createStatement();

    // csv file
    const std::string csv_file_path = "./csvFiles/data_1.csv";
    std::ifstream csv_file(csv_file_path);
    if (!csv_file.is_open()) {
      std::cerr << "Failed to open CSV file." << std::endl;
      return 1;
    }

    // parse
    std::string line;
    // skip first line
    getline(csv_file, line);
    // create timer, report time on dtor
    Timer t;
    while (getline(csv_file, line)) {
      std::istringstream iss(line);
      std::string column1, column2, column3;

      getline(iss, column1, ',');
      getline(iss, column2, ',');
      getline(iss, column3);
      if (column3.at(column3.size() - 1) == '\r') {
        column3.pop_back();
      }

      // insert into db
      std::string query = "INSERT INTO BILLS VALUES('" + column1 + "', '" +
                          column2 + "', '" + column3 + "')";
      // std::cout << query << std::endl;
      stmt->execute(query);
    }
    std::cout << "Data insert finished." << std::endl;
  } catch (sql::SQLException &e) {
    std::cerr << "MySQL Errot: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}