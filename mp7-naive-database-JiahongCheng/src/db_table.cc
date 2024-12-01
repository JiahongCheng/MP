#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    if (row_col_capacity_ == 0) ++row_col_capacity_;
    row_col_capacity_ *= 2;
    for (unsigned int r = 0; r < rows_.size(); ++r) {
      void**& row = rows_.at(r);
      CopyAndDeallocateRow(row);
    }
  }
  col_descs_.push_back(col_desc);
  for (auto& [id, row] : rows_) {
    if (col_desc.second == DataType::kString) {
      row[col_descs_.size() - 1] = new std::string("");
    }
    else if (col_desc.second == DataType::kDouble) {
      row[col_descs_.size() - 1] = new double(0.0);
    }
    else if (col_desc.second == DataType::kInt) {
      row[col_descs_.size() - 1] = new int(0);
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size()) {
    throw std::out_of_range("Out Range");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error("Run time");
  }
  for (auto& [id, row] : rows_) {
    delete static_cast<char*>(row[col_idx]);
    for (unsigned int i = col_idx; i < col_descs_.size() - 1; ++i) {
      row[i] = row[i + 1];
    }
    row[col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("");
  }
  void** new_row = new void*[row_col_capacity_];
  int i = 0;
  for (const std::string& s : col_data) {
    DataType dt = col_descs_.at(i).second;
    if (dt == DataType::kDouble) {
      double d = std::stod(s);
      new_row[i] = static_cast<void*>(new double(d));
    } else if (dt == DataType::kInt) {
      int j = std::stoi(s);
      new_row[i] = static_cast<void*>(new int(j));
    } else if (dt == DataType::kString) {
      new_row[i] = static_cast<void*>(new std::string(s));
    }
    ++i;
  }
  rows_.insert({next_unique_id_, new_row});
  ++next_unique_id_;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.count(id) == 0) {
    throw std::invalid_argument("Invalid row ID specified");
  }
  if (!(rows_.contains(id))) {
        throw std::invalid_argument("");
    }
  void** row = rows_[id];
  for (size_t i = 0; i < col_descs_.size(); ++i) {
    DataType dt = col_descs_[i].second;
    if (dt == DataType::kString) {
      delete static_cast<std::string*>(row[i]);
    } else if (dt == DataType::kDouble) {
      delete static_cast<double*>(row[i]);
    } else if (dt == DataType::kInt) {
      delete static_cast<int*>(row[i]);
    }
  }
  delete[] row;
  rows_.erase(id);
}


DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  for (auto [id, rhs_row] : rhs.rows_) {
    void** lhs_row = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      DataType dt = col_descs_.at(i).second;
      if (dt == DataType::kDouble) {
        double d = *static_cast<double*>(rhs_row[i]);
        lhs_row[i] = static_cast<void*>(new double(d));
      }
      else if (dt == DataType::kInt) {
        int j = *static_cast<int*>(rhs_row[i]);
        lhs_row[i] = static_cast<void*>(new int(j));
      }
      else if (dt == DataType::kString) {
        std::string s = *static_cast<std::string*>(rhs_row[i]);
        lhs_row[i] = static_cast<void*>(new std::string(s));
      }
    }
    rows_.insert({id, lhs_row});
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  for (auto& [id, row] : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      DataType dt = col_descs_.at(i).second;
      if (dt == DataType::kDouble) {
        delete static_cast<double*>(row[i]);
      } else if (dt == DataType::kInt) {
        delete static_cast<int*>(row[i]);
      } else if (dt == DataType::kString) {
        delete static_cast<std::string*>(row[i]);
      }
    }
    delete[] row;
  }
  rows_.clear();
  for (auto [id, row] : rhs.rows_) {
    void** lhs_row = new void*[rhs.row_col_capacity_];
    for (unsigned int c = 0; c < rhs.col_descs_.size(); ++c) {
      DataType dt = rhs.col_descs_.at(c).second;
      if (dt == DataType::kInt) {
        int i = *static_cast<int*>(row[c]);
        lhs_row[c] = static_cast<void*>(new int(i));
      } else if (dt == DataType::kDouble) {
        double d = *static_cast<double*>(row[c]);
        lhs_row[c] = static_cast<void*>(new double(d));
      } else if (dt == DataType::kString) {
        std::string s = *static_cast<std::string*>(row[c]);
        lhs_row[c] = static_cast<void*>(new std::string(s));
      }
    }
    rows_.insert({id, lhs_row});
  }
  col_descs_ = rhs.col_descs_;
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  return *this;
}

DbTable::~DbTable() {
  for (auto& [id, row] : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      DataType dt = col_descs_.at(i).second;
      if (dt == DataType::kDouble) {
        delete static_cast<double*>(row[i]);
      } else if (dt == DataType::kInt) {
        delete static_cast<int*>(row[i]);
      } else if (dt == DataType::kString) {
        delete static_cast<std::string*>(row[i]);
      }
    }
    delete[] row;
  }
}

void DbTable::CopyAndDeallocateRow(void**& row) {
  void** tmp = new void*[row_col_capacity_];
  int i = 0;
  if (row[col_descs_.size() - 1] == nullptr) { i = 1; }
  for (unsigned int col = 0; col < col_descs_.size() - i; ++col) {
    DataType type = col_descs_.at(col).second;
    if (type == DataType::kString) {
      std::string& name = *static_cast<std::string*>(row[col]);
      tmp[col] = static_cast<void*>(new std::string(name));
    } else if (type == DataType::kInt) {
      int uin = *static_cast<int*>(row[col]);
      tmp[col] = static_cast<void*>(new int(uin));
    } else if (type == DataType::kDouble) {
      double gpa = *static_cast<double*>(row[col]);
      tmp[col] = static_cast<void*>(new double(gpa));
    }

    if (type == DataType::kDouble) {
      delete static_cast<double*>(row[col]);
    } else if (type == DataType::kInt) {
      delete static_cast<int*>(row[col]);
    } else if (type == DataType::kString) {
      delete static_cast<std::string*>(row[col]);
    }
  }
  delete[] row;
  row = tmp;
  tmp = nullptr;
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  std::string type;
  std::string output;
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    if (table.col_descs_.at(i).second == DataType::kDouble) {
      type = "(double)";
    } else if (table.col_descs_.at(i).second == DataType::kInt) {
      type = "(int)";
    } else if (table.col_descs_.at(i).second == DataType::kString) {
      type = "(std::string)";
    }
    output += table.col_descs_.at(i).first;
    output += type;
    if (i < table.col_descs_.size() - 1) {
      output += ", ";
    }
  }
  os << output;
  for (auto [id, row] : table.rows_) {
    for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
      DataType type = table.col_descs_.at(i).second;
      if (type == DataType::kString) {
        os << *static_cast<std::string*>(row[i]);
      } else if (type == DataType::kInt) {
        os << *static_cast<int*>(row[i]);
      } else if (type == DataType::kDouble) {
        os << *static_cast<double*>(row[i]);
      }
      if (i < table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    if (id < table.rows_.size() - 1) {
      os << std::endl;
    }
  }
  return os;
}