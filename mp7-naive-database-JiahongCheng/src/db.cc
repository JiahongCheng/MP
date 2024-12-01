#include "db.hpp"

#include <vector>

void Database::CreateTable(const std::string& table_name) {
  tables_.insert({table_name, new DbTable()});
}
void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("not Exist");
  }
  delete tables_.at(table_name);
  tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
  return *tables_.at(table_name);
}

Database::Database(const Database& rhs) {
  for (const auto& [name, table_ptr] : rhs.tables_) {
    tables_.insert({name, new DbTable(*table_ptr)});
  }
}
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (auto [name, table_ptr] : rhs.tables_) {
    DbTable& tmp = *table_ptr;
    if (tmp.ReturnRow().empty()) {
      tables_.insert({name, new DbTable()});
    } else {
      tables_.insert({name, new DbTable(*table_ptr)});
    }
  }
  return *this;
}

Database::~Database() {
  for (auto& [name, table] : tables_) {
    delete table;
  }
}

