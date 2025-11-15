#pragma once
#include <vector>
#include <map>
#include <utility>

class Process {
public:
    int pid;
    int priority;
    int cpuBurstRemaining;
    std::vector<std::pair<int, unsigned int>> memoryAccesses; // (thread_id, address)
    size_t accessIndex;
    std::map<int, int> threadPriorities;

    Process(int pid_, int priority_);

    bool hasMoreAccesses() const;
    std::pair<int, unsigned int> nextAccess();
    void tick(int threadId);
    void addThread(int threadId, int threadPriority);
};
