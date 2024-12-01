#include "illini_book.hpp"

int main() {

  return 0;
}

// Allowed headers: Only the following header files are allowed to be #included in your solution files
// "illini_book.hpp" "utilities.hpp" "fstream" "list" "map" "queue" "set" "string" "utility" "vector"

//Rewrite this function so that the duplicate checking software cannot find out

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream ifsone{people_fpath};
    int value = 0;
    while(ifsone.good()) {
        ifsone >> value;
        if (ifsone.fail()) {
            ifsone.clear();
            ifsone.ignore(1, '\n');
        } else {
            everyone_.push_back(value);
        }
    }
    std::ifstream ifstwo{relations_fpath};
    std::set<std::string> relationship;
    for (std::string line; std::getline(ifstwo, line); line = "") {
        std::vector<std::string> vect = utilities::Split(line, ',');
        int key = std::stoi(vect.at(0));
        int num = std::stoi(vect.at(1));
        adj_[key].push_back(std::pair<int, std::string> (num, vect.at(2)));
        adj_[num].push_back(std::pair<int, std::string> (key, vect.at(2)));
        
        relationship.insert(vect.at(2));
    }
    std::set<std::string>::iterator iter;
    for (iter = relationship.begin(); iter != relationship.end(); iter++) {
        related_.push_back(*iter);
    }
}

IlliniBook::~IlliniBook() {
    Clear();
}

void IlliniBook::Clear() {}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    bool related = true; if (GetRelated(uin_1, uin_2) == -1) { related = false; }
    return related;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    bool related = true; if (GetRelated(uin_1, uin_2, relationship) == -1) { related = false; }
    return related;
}
std::map<int, int> IlliniBook::Helperbfs(int start, std::vector<std::string> relationships) const {
    std::queue<int> que;
    std::map<int, int> pathmap;
    pathmap[start] = 0; 
    que.push(start);
    while(!que.empty()) {
        if (adj_.find(que.front()) != adj_.cend()) {
            std::list<std::pair<int, std::string>> list = adj_.find(que.front()) -> second;
            for (const auto& iter:list) {
                if (pathmap.find(iter.first) != pathmap.end()) {
                    continue;
                }
                    for (size_t x = 0; x < relationships.size(); x++) {
                        if (iter.second == relationships[x]) {
                            pathmap[iter.first] == pathmap[que.front()] + 1;
                            que.push(iter.first);
                            break;
                        }
                    }
            }
        }
        que.pop();
    }
    return pathmap;
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::map<int, int> map = Helperbfs(uin_1, related_);
    if (map.find(uin_2) == map.cend()) {
        return -1;
    }
    return map[uin_2];
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::vector<std::string> vect;
    vect.push_back(relationship);
    std::map<int, int> map = Helperbfs(uin_1, vect);
    if(map.find(uin_2) == map.cend()) {
        return -1;
    }
    return map[uin_2];
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> nodelist;
    std::map<int, int> map = Helperbfs(uin, related_);
    for (const auto& iter:map) {
        if (iter.second == n) {
            nodelist.push_back(iter.first);
        }
    }
    return nodelist;
}
size_t IlliniBook::CountGroups() const {
    std::map<int, bool> judge;
    size_t groupnum = 0;
    for (size_t i = 0; i < everyone_.size(); i++) {
        if (judge.find(everyone_[i]) == judge.cend()) {
            groupnum++;
            std::map<int, int> map = Helperbfs(everyone_.at(i), related_);
            judge[everyone_.at(i)] = true;
            for (const auto& iter:map) {
                if (judge[iter.first]) {
                    continue;
                }
                judge[iter.first] = true;
            }
        }
    }
    return groupnum;
}
size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int, bool> judge;
    std::vector<std::string> vect;
    vect.push_back(relationship);
    size_t groupnum = 0; 
    for (size_t i = 0; i < everyone_.size(); i++) {
        if (judge.find(everyone_[i]) == judge.cend()) {
            groupnum++;
            std::map<int, int> map = Helperbfs(everyone_.at(i), vect);
            judge[everyone_.at(i)] = true;
            for (const auto& iter: map) {
                if (judge[iter.first]) {
                    continue;
                }
                judge[iter.first] = true;
            }
        }
    }
    return groupnum;
}
size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int, bool> judge;
    size_t groupnum = 0; 
    for (size_t i = 0; i < everyone_.size(); i++) {
        if (judge.find(everyone_[i]) == judge.cend()) {
            groupnum++;
            std::map<int, int> map = Helperbfs(everyone_.at(i), relationships);
            judge[everyone_.at(i)] = true;
            for (const auto& iter: map) {
                if (judge[iter.first]) {
                    continue;
                }
                judge[iter.first] = true;
            }
        }
    }
    return groupnum;
}



//Merge Helperbfs into GetRelated, and rewrite this function, so that the duplicate checking software cannot find it out, but do not modify the function of the function.


std::map<int, int> IlliniBook::Helperbfs(int start, std::vector<std::string> relationships) const {
    std::queue<int> que;
    std::map<int, int> pathmap;
    pathmap[start] = 0; 
    que.push(start);
    while(!que.empty()) {
        if (adj_.find(que.front()) != adj_.cend()) {
            std::list<std::pair<int, std::string>> list = adj_.find(que.front()) -> second;
            for (const auto& iter:list) {
                if (pathmap.find(iter.first) != pathmap.end()) {
                    continue;
                }
                    for (size_t x = 0; x < relationships.size(); x++) {
                        if (iter.second == relationships[x]) {
                            pathmap[iter.first] == pathmap[que.front()] + 1;
                            que.push(iter.first);
                            break;
                        }
                    }
            }
        }
        que.pop();
    }
    return pathmap;
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::map<int, int> map = Helperbfs(uin_1, related_);
    if (map.find(uin_2) == map.cend()) {
        return -1;
    }
    return map[uin_2];
}