#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
  int externalCount = 0;
  std::cin >> externalCount;
  std::unordered_set<std::string> external;
  for (int i = 0; i < externalCount; ++i) {
    std::string name;
    std::cin >> name;
    external.insert(name);
  }

  int fileCount = 0;
  std::cin >> fileCount;
  std::unordered_map<std::string, std::vector<std::string>> graph;
  std::vector<std::string> units;
  for (int i = 0; i < fileCount; ++i) {
    std::string name;
    int includeCount = 0;
    std::cin >> name >> includeCount;
    std::vector<std::string> includes(static_cast<std::size_t>(includeCount));
    for (std::string &include : includes) {
      std::cin >> include;
    }
    graph[name] = includes;
    if (name.size() >= 4 && name.substr(name.size() - 4) == ".cpp") {
      units.push_back(name);
    }
  }

  int touched = 0;
  for (const std::string &unit : units) {
    std::queue<std::pair<std::string, std::vector<std::string>>> frontier;
    frontier.push({unit, {unit}});
    std::unordered_set<std::string> seen;
    seen.insert(unit);
    bool found = false;
    std::vector<std::string> foundPath;

    while (!frontier.empty() && !found) {
      const int levelSize = static_cast<int>(frontier.size());
      for (int level = 0; level < levelSize && !found; ++level) {
        const auto current = frontier.front();
        frontier.pop();
        const auto it = graph.find(current.first);
        if (it == graph.end()) {
          continue;
        }
        for (const std::string &include : it->second) {
          if (seen.count(include) != 0) {
            continue;
          }
          seen.insert(include);
          std::vector<std::string> path = current.second;
          path.push_back(include);
          if (external.count(include) != 0) {
            found = true;
            foundPath = path;
            break;
          }
          if (graph.count(include) != 0) {
            frontier.push({include, path});
          }
        }
      }
    }

    if (found) {
      ++touched;
      std::cout << unit << " OUI ";
      for (std::size_t i = 0; i < foundPath.size(); ++i) {
        if (i != 0) {
          std::cout << '>';
        }
        std::cout << foundPath[i];
      }
      std::cout << '\n';
    } else {
      std::cout << unit << " NON\n";
    }
  }
  std::cout << "TOUCHEES " << touched << " SUR " << units.size() << '\n';
}
