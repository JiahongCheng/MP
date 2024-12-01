#include "illini_book.hpp"

// Your code here!

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream people_input{people_fpath};
    int person = 0;
    while (people_input.good()) {
        people_input >> person;
        if (people_input.fail()) {
            people_input.clear();
            people_input.ignore(1, '\n');
        } else {
            people_.push_back(person);
        }
    }
    std::ifstream relations_input{relations_fpath};
    std::set<std::string> unique_relation;
    std::string current;
    while (std::getline(relations_input, current)) {
        std::vector<std::string> split_line = utilities::Split(current, ',');
        int person1 = std::stoi(split_line.at(0));
        int person2 = std::stoi(split_line.at(1));
        std::string relation = split_line.at(2);

        adj_[person1].emplace_back(std::pair<int, std::string>(person2, relation));
        adj_[person2].emplace_back(std::pair<int, std::string>(person1, relation));

        unique_relation.insert(relation);
    }
    for (const auto &relation_type : unique_relation) {
        related_.push_back(relation_type);
    }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    bool related = true; if (GetRelated(uin_1, uin_2) == -1) { related = false; }
    return related;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    bool related = true; if (GetRelated(uin_1, uin_2, relationship) == -1) { related = false; }
    return related;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::queue<int> queue_node;
    std::map<int, int> map_distance;
    map_distance[uin_1] = 0;
    queue_node.push(uin_1);

    while (!queue_node.empty()) {
        int node_current = queue_node.front();
        queue_node.pop();
        
        if (adj_.find(node_current) != adj_.cend()) {
            const auto& list_neighbors = adj_.find(node_current)->second;
            
            for (const auto& neighbor : list_neighbors) {
                int node_next = neighbor.first;
                const std::string& relation = neighbor.second;
                
                if (map_distance.find(node_next) != map_distance.end()) {
                    continue;
                }

                for (const auto& target_relation : related_) {
                    if (relation == target_relation) {
                        map_distance[node_next] = map_distance[node_current] + 1;
                        queue_node.push(node_next);
                        break;
                    }
                }
            }
        }
    }

    if (map_distance.find(uin_2) == map_distance.cend()) {
        return -1;
    }
    return map_distance[uin_2];
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::queue<int> node_queue;
    std::map<int, int> distance_map;
    std::vector<std::string> target_relationships = {relationship};

    distance_map[uin_1] = 0;
    node_queue.push(uin_1);

    while (!node_queue.empty()) {
        int current_node = node_queue.front();
        node_queue.pop();

        if (adj_.find(current_node) != adj_.cend()) {
            const auto& neighbor_list = adj_.find(current_node)->second;

            for (const auto& neighbor : neighbor_list) {
                int next_node = neighbor.first;
                const std::string& current_relationship = neighbor.second;

                if (distance_map.find(next_node) != distance_map.end()) {
                    continue;
                }

                for (const auto& target_relationship : target_relationships) {
                    if (current_relationship == target_relationship) {
                        distance_map[next_node] = distance_map[current_node] + 1;
                        node_queue.push(next_node);
                        break;
                    }
                }
            }
        }
    }

    if (distance_map.find(uin_2) == distance_map.cend()) {
        return -1;
    }
    return distance_map[uin_2];
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::queue<int> node_queue;
    std::map<int, int> distance_map;
    std::vector<int> result_nodes;
    distance_map[uin] = 0;
    node_queue.push(uin);
    while (!node_queue.empty()) {
        int current_node = node_queue.front();
        node_queue.pop();
        if (adj_.find(current_node) != adj_.cend()) {
            const auto& neighbor_list = adj_.find(current_node)->second;
            for (const auto& neighbor : neighbor_list) {
                int next_node = neighbor.first;
                const std::string& current_relationship = neighbor.second;
                if (distance_map.find(next_node) != distance_map.end()) {
                    continue;
                }
                for (const auto& target_relationship : related_) {
                    if (current_relationship == target_relationship) {
                        distance_map[next_node] = distance_map[current_node] + 1;
                        node_queue.push(next_node);
                        break;
                    }
                }
            }
        }
    }
    for (const auto& node_dist_pair : distance_map) {
        if (node_dist_pair.second == n) {
            result_nodes.push_back(node_dist_pair.first);
        }
    }
    return result_nodes;
}

size_t IlliniBook::CountGroups() const {
    std::map<int, bool> person_visited;
    size_t num_groups = 0;
    for (const int kPerson : people_) {
        if (person_visited.find(kPerson) == person_visited.cend()) {
            num_groups++;
            std::queue<int> node_queue; std::map<int, int> distance_map; distance_map[kPerson] = 0; node_queue.push(kPerson);
            while (!node_queue.empty()) {
                int current_node = node_queue.front();
                node_queue.pop();
                if (adj_.find(current_node) != adj_.cend()) {
                    const auto& neighbor_list = adj_.find(current_node)->second;
                    for (const auto& neighbor : neighbor_list) {
                        int next_node = neighbor.first;
                        const std::string& current_relationship = neighbor.second;
                        if (distance_map.find(next_node) != distance_map.end()) {
                            continue;
                        }
                        for (const auto& target_relationship : related_) {
                            if (current_relationship == target_relationship) {
                                distance_map[next_node] = distance_map[current_node] + 1;
                                node_queue.push(next_node);
                                break;
                            }
                        }
                    }
                }
            }
            person_visited[kPerson] = true;
            for (const auto& node_dist_pair : distance_map) {
                if (person_visited[node_dist_pair.first]) {
                    continue;
                }
                person_visited[node_dist_pair.first] = true;
            }
        }
    }
    return num_groups;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int, bool> person_visited;
    std::vector<std::string> target_relationships{relationship};
    size_t num_groups = 0;
    for (const int kPerson : people_) {
        if (person_visited.find(kPerson) == person_visited.cend()) {
            num_groups++; std::queue<int> node_queue; std::map<int, int> distance_map; distance_map[kPerson] = 0; node_queue.push(kPerson);
            while (!node_queue.empty()) {
                int current_node = node_queue.front();
                node_queue.pop();
                if (adj_.find(current_node) != adj_.cend()) {
                    const auto& neighbor_list = adj_.find(current_node)->second;
                    for (const auto& neighbor : neighbor_list) {
                        int next_node = neighbor.first;
                        const std::string& current_relationship = neighbor.second;
                        if (distance_map.find(next_node) != distance_map.end()) {
                            continue;
                        }
                        for (const auto& target_relationship : target_relationships) {
                            if (current_relationship == target_relationship) {
                                distance_map[next_node] = distance_map[current_node] + 1;
                                node_queue.push(next_node);
                                break;
                            }
                        }
                    }
                }
            }
            person_visited[kPerson] = true;
            for (const auto& node_dist_pair : distance_map) {
                if (person_visited[node_dist_pair.first]) {
                    continue;
                }
                person_visited[node_dist_pair.first] = true;
            }
        }
    }
    return num_groups;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int, bool> visited;
    size_t group_count = 0;
    for (const int kPerson : people_) {
        if (visited.find(kPerson) == visited.cend()) {
            group_count++; std::queue<int> queue; std::map<int, int> distance; distance[kPerson] = 0; queue.push(kPerson);
            while (!queue.empty()) {
                int current = queue.front(); queue.pop();
                if (adj_.find(current) != adj_.cend()) {
                    const auto& neighbors = adj_.find(current)->second;
                    for (const auto& neighbor : neighbors) {
                        int next = neighbor.first;
                        const std::string& rel = neighbor.second;
                        if (distance.find(next) != distance.end()) {
                            continue;
                        }
                        for (size_t i = 0; i < relationships.size(); i++) {
                            if (rel == relationships[i]) {
                                distance[next] = distance[current] + 1;
                                queue.push(next);
                                break;
                            }
                        }
                    }
                }
            }
            visited[kPerson] = true;
            for (const auto& node_dist_pair : distance) {
                if (visited[node_dist_pair.first]) {
                    continue;
                }
                visited[node_dist_pair.first] = true;
            }
        }
    }
    return group_count;
}