#include <iostream>
#include <string>

class Session {
public:
    bool wait() {
        if (frameOpen) {
            ++refusals;
            return false;
        }
        return true;
    }

    bool begin() {
        if (frameOpen) {
            ++refusals;
            return false;
        }
        frameOpen = true;
        ++beginnings;
        return true;
    }

    bool end() {
        if (!frameOpen) {
            ++refusals;
            return false;
        }
        frameOpen = false;
        ++ends;
        return true;
    }

    bool isOpen() const {
        return frameOpen;
    }

    int beginnings = 0;
    int ends = 0;
    int refusals = 0;

private:
    bool frameOpen = false;
};

class FrameGuard {
public:
    explicit FrameGuard(Session &session) : session_(session) {}

    FrameGuard(const FrameGuard &) = delete;
    FrameGuard &operator=(const FrameGuard &) = delete;

    ~FrameGuard() {
        if (active_) {
            session_.end();
        }
    }

    void activate() {
        active_ = true;
    }

private:
    Session &session_;
    bool active_ = false;
};

struct Result {
    int beginnings;
    int ends;
    int refusals;
    int images;
    bool frameOpen;
};

Result run(const std::string &paths, bool guarded) {
    Session session;
    int images = 0;

    for (char path : paths) {
        const bool waitAccepted = session.wait();
        const bool beginAccepted = session.begin();
        if (!waitAccepted && (path == 'N' || path == 'C')) {
            path = 'V';
        }

        if (guarded) {
            if (beginAccepted) {
                FrameGuard guard(session);
                guard.activate();
                if (path == 'N') {
                    ++images;
                } else if (path == 'C') {
                    continue;
                } else if (path == 'R') {
                    break;
                }
            } else if (path == 'R') {
                break;
            }
        } else {
            if (path == 'N' && beginAccepted) {
                ++images;
            } else if (path == 'C') {
                continue;
            } else if (path == 'R') {
                break;
            }
            session.end();
        }
    }

    return {session.beginnings, session.ends, session.refusals, images,
            session.isOpen()};
}

void printResult(const char *label, const Result &result) {
    std::cout << label << " DEBUTS " << result.beginnings << " FINS "
              << result.ends << " REFUS " << result.refusals << " IMAGES "
              << result.images << " OUVERTE "
              << (result.frameOpen ? "OUI" : "NON") << '\n';
}

int main() {
    int pathCount = 0;
    std::string paths;
    if (!(std::cin >> pathCount)) {
        return 0;
    }
    if (pathCount > 0) {
        std::cin >> paths;
    }

    const Result withoutGuard = run(paths.substr(0, static_cast<std::size_t>(pathCount)),
                                    false);
    const Result withGuard = run(paths.substr(0, static_cast<std::size_t>(pathCount)),
                                 true);
    printResult("SANS", withoutGuard);
    printResult("AVEC", withGuard);
}
