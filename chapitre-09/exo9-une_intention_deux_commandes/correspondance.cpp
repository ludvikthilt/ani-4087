#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Action {
  std::string name;
  std::string usage;
};

struct TableResult {
  std::vector<std::string> frameLines;
};

TableResult runTable(int tableNumber, const std::vector<Action>& actions) {
  int mappingCount = 0;
  std::cin >> mappingCount;
  std::unordered_map<std::string, std::string> mapping;
  for (int i = 0; i < mappingCount; ++i) {
    std::string usage;
    std::string command;
    std::cin >> usage >> command;
    mapping[usage] = command;
  }

  std::cout << "TABLE " << tableNumber << '\n';
  for (const Action& action : actions) {
    if (mapping.find(action.usage) == mapping.end())
      std::cout << "INACTIVE " << action.name << '\n';
  }

  int frameCount = 0;
  std::cin >> frameCount;
  std::vector<std::string> previousCommands;
  TableResult result;
  result.frameLines.reserve(static_cast<std::size_t>(frameCount));

  for (int frame = 1; frame <= frameCount; ++frame) {
    int commandCount = 0;
    std::cin >> commandCount;
    std::unordered_set<std::string> held;
    for (int i = 0; i < commandCount; ++i) {
      std::string command;
      std::cin >> command;
      held.insert(command);
    }

    std::vector<std::string> pressedActions;
    for (const Action& action : actions) {
      const auto binding = mapping.find(action.usage);
      if (binding == mapping.end())
        continue;

      const bool pressed = held.find(binding->second) != held.end();
      const bool wasPressed =
          std::find(previousCommands.begin(), previousCommands.end(),
                    binding->second) != previousCommands.end();
      if (pressed && !wasPressed)
        pressedActions.push_back(action.name);
    }

    std::string line = std::to_string(frame);
    if (pressedActions.empty()) {
      line += " -";
    } else {
      for (const std::string& actionName : pressedActions)
        line += ' ' + actionName;
    }
    std::cout << line << '\n';
    result.frameLines.push_back(line);
    previousCommands.assign(held.begin(), held.end());
  }

  return result;
}

int main() {
  int actionCount = 0;
  std::cin >> actionCount;
  std::vector<Action> actions(static_cast<std::size_t>(actionCount));
  for (Action& action : actions)
    std::cin >> action.name >> action.usage;

  const TableResult first = runTable(1, actions);
  const TableResult second = runTable(2, actions);
  std::cout << "IDENTIQUES "
            << (first.frameLines == second.frameLines ? "OUI" : "NON") << '\n';
  return 0;
}
