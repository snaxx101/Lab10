#include "Scheduler.h"

Scheduler::Scheduler(SchedulingPolicy policy_, int tlbSize) : policy(policy_) {}

void Scheduler::addProcessIfNotExists(int pid) {
    if (processes.find(pid) == processes.end()) {
        processes.emplace(pid, Process(pid, 1));
    }
}

Process& Scheduler::getProcess(int pid) {
    return processes.at(pid);
}

// Fixes:
std::map<int, Process>& Scheduler::getAllProcesses() {
    return processes;
}

void Scheduler::adjustPriority(int pid, int threadId) {
    // stub: implement MLFQ demotion/promotion later
}
