#pragma once
#include <map>
#include <set>
#include "Clock.h"

class TwoLevelPageTable {
private:
    std::map<std::pair<int,int>, int> firstLevel;   // Not strictly used in simplified sim
    std::map<std::pair<int,int>, int> secondLevel;  // (pid,page) -> frame number
    std::set<std::pair<int,int>> memoryPages;       // Pages currently in memory
    Clock clock;                                    // Clock replacement

public:
    TwoLevelPageTable(int frameCount);

    bool isInMemory(int pid, int pageNum) const;
    int getFrame(int pid, int pageNum) const;
    void loadPage(int pid, int pageNum, bool isModified=false);
    void printStats() const;
};
