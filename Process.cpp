#include "Process.h"
#include <stdexcept>

Process::Process(int pid_, int priority_)
    : pid(pid_), priority(priority_), cpuBurstRemaining(0), accessIndex(0) {}

bool Process::hasMoreAccesses() const {
    return accessIndex < memoryAccesses.size();
}

std::pair<int, unsigned int> Process::nextAccess() {
    if (!hasMoreAccesses()) throw std::runtime_error("No more accesses");
    return memoryAccesses[accessIndex++];
}

void Process::tick(int threadId) {
    if (cpuBurstRemaining > 0) cpuBurstRemaining--;
}

void Process::addThread(int threadId, int threadPriority) {
    threadPriorities[threadId] = threadPriority;
}
