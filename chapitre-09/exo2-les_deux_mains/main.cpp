#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Action {
  std::string name;
  std::string usage;
  std::string hand;
  std::string command;
};

Action makeAction(const std::string& name, const std::string& usage) {
  Action action{name, usage, "DROITE", "AUCUNE"};
  if (usage == "MENU" || usage == "MOVE" || usage == "SELECT_LEFT" ||
      usage == "GRAB_LEFT" || usage == "AIM_POSE_LEFT" ||
      usage == "GRIP_POSE_LEFT" || usage == "HAPTIC_LEFT") {
    action.hand = "GAUCHE";
  }

  if (usage == "SELECT")
    action.command = "SOURIS_G";
  else if (usage == "GRAB")
    action.command = "SOURIS_D";
  else if (usage == "MENU")
    action.command = "TAB";
  else if (usage == "MOVE")
    action.command = "FLECHES";
  else if (usage == "SELECT_LEFT")
    action.command = "SOURIS_M";
  else if (usage == "GRAB_LEFT")
    action.command = "MAJ_G";
  else if (usage == "MOVE_RIGHT")
    action.command = "IJKL";
  return action;
}

int main() {
  int actionCount = 0;
  int frameCount = 0;
  std::cin >> actionCount >> frameCount;

  std::vector<Action> actions;
  int rightCount = 0;
  int leftCount = 0;
  for (int i = 0; i < actionCount; ++i) {
    std::string name;
    std::string usage;
    std::cin >> name >> usage;
    actions.push_back(makeAction(name, usage));
    if (actions.back().hand == "DROITE")
      ++rightCount;
    else
      ++leftCount;
    std::cout << actions.back().name << ' ' << actions.back().hand << ' '
              << actions.back().command << '\n';
  }

  int headFrames = 0;
  std::vector<std::unordered_set<std::string>> frames;
  frames.reserve(static_cast<std::size_t>(frameCount));
  for (int frame = 0; frame < frameCount; ++frame) {
    int commandCount = 0;
    std::cin >> commandCount;
    std::unordered_set<std::string> held;
    bool movesHead = false;
    for (int i = 0; i < commandCount; ++i) {
      std::string command;
      std::cin >> command;
      held.insert(command);
      if (command == "Z" || command == "Q" || command == "S" ||
          command == "D")
        movesHead = true;
    }
    if (movesHead)
      ++headFrames;
    frames.push_back(std::move(held));
  }

  for (std::size_t frame = 0; frame < frames.size(); ++frame) {
    const auto& held = frames[frame];
    int arrowX = (held.count("F_DROITE") != 0) -
                 (held.count("F_GAUCHE") != 0);
    int arrowY = (held.count("F_HAUT") != 0) -
                 (held.count("F_BAS") != 0);
    int ijklX = (held.count("L") != 0) - (held.count("J") != 0);
    int ijklY = (held.count("I") != 0) - (held.count("K") != 0);

    std::cout << frame + 1;
    for (const Action& action : actions) {
      std::cout << ' ';
      if (action.command == "AUCUNE") {
        std::cout << '-';
      } else if (action.command == "FLECHES") {
        std::cout << arrowX << ',' << arrowY;
      } else if (action.command == "IJKL") {
        std::cout << ijklX << ',' << ijklY;
      } else {
        std::cout << (held.count(action.command) != 0 ? 1 : 0);
      }
    }
    std::cout << '\n';
  }
  std::cout << "DROITE " << rightCount << '\n';
  std::cout << "GAUCHE " << leftCount << '\n';
  std::cout << "TETE " << headFrames << '\n';
  return 0;
}
