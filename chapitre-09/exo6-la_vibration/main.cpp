#include <algorithm>
#include <iostream>
#include <string>

int main() {
  int callCount = 0;
  std::cin >> callCount;

  int goodCalls = 0;
  int longCalls = 0;
  int silentCalls = 0;
  long long totalDuration = 0;

  for (int call = 1; call <= callCount; ++call) {
    long long amplitudeInput = 0;
    long long durationInput = 0;
    long long frequencyInput = 0;
    std::cin >> amplitudeInput >> durationInput >> frequencyInput;

    const long long amplitude = std::clamp(amplitudeInput, 0LL, 100LL);
    const long long duration = durationInput > 0 ? durationInput : 0;
    const std::string durationLabel =
        durationInput > 0 ? std::to_string(durationInput) : "MIN";
    const std::string frequencyLabel =
        frequencyInput > 0 ? std::to_string(frequencyInput) : "DEFAUT";
    totalDuration += duration;

    std::string verdict;
    if (amplitude == 0) {
      verdict = "MUETTE";
      ++silentCalls;
    } else if (durationInput < 50) {
      verdict = "BREVE";
    } else if (durationInput <= 200) {
      verdict = "BONNE";
      ++goodCalls;
    } else {
      verdict = "LONGUE";
      ++longCalls;
    }

    std::cout << call << ' ' << amplitude << ' ' << durationLabel << ' '
              << frequencyLabel << ' ' << verdict << '\n';
  }

  std::cout << "BONNES " << goodCalls << '\n';
  std::cout << "LONGUES " << longCalls << '\n';
  std::cout << "MUETTES " << silentCalls << '\n';
  std::cout << "TEMPS " << totalDuration << '\n';
  return 0;
}
