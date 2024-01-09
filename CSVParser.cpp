#include <cppconn/prepared_statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Timer.h"
#define FILE_COUNT 10

int insertSQL(const std::string &csv_file_path) {
  try {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *stmt;

    const int batch_size = 10000;
    const std::string db_host = "172.17.0.2";
    const std::string db_user = "root";
    const std::string db_password = "123456";
    const std::string db_name = "BILLS";

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(db_host, db_user, db_password);
    con->setSchema(db_name);
    con->setAutoCommit(false);
    stmt = con->prepareStatement("INSERT INTO BILLS VALUES(?, ?, ?)");

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
    int count = 0;
    std::string batchQuery = "";

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
      stmt->setString(1, column1);
      stmt->setString(2, column2);
      stmt->setString(3, column3);
      stmt->executeUpdate();
      // std::cout << "batch sql:" << batchQuery << "\n\n";
      count = (count + 1) % batch_size;
      if (count == 0) {
        con->commit();
        std::cout << "inserting " << batch_size << " items into sql"
                  << std::endl;
        batchQuery = "";
      }
    }
    if (batchQuery != "") {
      std::cout << batchQuery << std::endl;
      stmt->execute(batchQuery);
      std::cout << "inserting remaining items into sql" << std::endl;
      batchQuery = "";
    }
    std::cout << "Data insert finished." << std::endl;
    con->setAutoCommit(true);
  } catch (sql::SQLException &e) {
    std::cerr << "MySQL Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

std::vector<std::string> generateCSVPaths() {
  std::vector<std::string> v;
  for (int i = 1; i <= FILE_COUNT; i++) {
    std::string s = "./csvFiles/data_";
    if (i < 10) {
      s = s + "0";
    }
    s = s + std::to_string(i) + ".csv";
    v.push_back(move(s));
  }
  return v;
}

int main() {
  // csv file
  std::vector<std::string> csv_files = generateCSVPaths();
  for (const auto &csv_file_path : csv_files) {
    std::cout<<"reading data from "<<csv_file_path<<std::endl;
    insertSQL(csv_file_path);
  }
  return 0;
}
