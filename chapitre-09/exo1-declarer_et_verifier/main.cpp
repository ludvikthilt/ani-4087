#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Action {
  std::string name;
  std::string type;
  int usage;
};

int usageNumber(const std::string& usage) {
  const std::vector<std::string> usages = {
      "SELECT",       "GRAB",         "MENU",          "MOVE",
      "AIM_POSE",     "GRIP_POSE",    "HAPTIC",        "SELECT_LEFT",
      "GRAB_LEFT",    "AIM_POSE_LEFT","GRIP_POSE_LEFT","HAPTIC_LEFT",
      "MOVE_RIGHT"};
  for (std::size_t i = 0; i < usages.size(); ++i) {
    if (usages[i] == usage)
      return static_cast<int>(i);
  }
  return 0;
}

int main() {
  int operationCount = 0;
  std::cin >> operationCount;

  std::vector<Action> actions;
  std::unordered_set<std::string> names;
  int duplicateNames = 0;
  int attachedCount = 0;
  bool attached = false;

  for (int i = 0; i < operationCount; ++i) {
    std::string operation;
    std::cin >> operation;

    if (operation == "cree") {
      Action action;
      std::string usage;
      std::cin >> action.name >> action.type >> usage;
      action.usage = usageNumber(usage);
      actions.push_back(action);
      if (!names.insert(action.name).second)
        ++duplicateNames;
      std::cout << "ACTION " << actions.size() << ' ' << action.name << ' '
                << action.type << ' ' << action.usage << '\n';
    } else if (operation == "attache") {
      if (attached) {
        std::cout << "ATTACHE REFUSE\n";
      } else {
        attached = true;
        attachedCount = static_cast<int>(actions.size());
        std::cout << "ATTACHE " << attachedCount << '\n';
      }
    } else if (operation == "lit") {
      unsigned long long handle = 0;
      std::cin >> handle;
      if (handle == 0 || handle > actions.size()) {
        std::cout << "LIT " << handle << " INVALIDE\n";
      } else if (!attached || handle > static_cast<unsigned long long>(attachedCount)) {
        std::cout << "LIT " << handle << " INCONNUE\n";
      } else {
        std::cout << "LIT " << handle << ' '
                  << actions[static_cast<std::size_t>(handle - 1)].name << '\n';
      }
    }
  }

  std::cout << "ACTIONS " << actions.size() << '\n';
  std::cout << "ATTACHEES " << attachedCount << '\n';
  std::cout << "NOMS EN DOUBLE " << duplicateNames << '\n';
  return 0;
}
