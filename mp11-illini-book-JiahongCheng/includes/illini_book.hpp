#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <utilities.hpp>
#include <set>
#include <queue>


class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

  //helper

private:
  std::map<int, std::list<std::pair<int, std::string>>> adj_;
  std::vector<int> people_;
  std::vector<std::string> related_;
};

#endif
