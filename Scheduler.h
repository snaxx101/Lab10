#pragma once
#include "Process.h"
#include <map>

enum class SchedulingPolicy { FCFS, RoundRobin, Priority, MLFQ };

class Scheduler {
private:
    SchedulingPolicy policy;
    std::map<int, Process> processes;

public:
    Scheduler(SchedulingPolicy policy_, int tlbSize);
    void addProcessIfNotExists(int pid);
    Process& getProcess(int pid);

    // Fix for compilation:
    std::map<int, Process>& getAllProcesses();
    void adjustPriority(int pid, int threadId); // MLFQ stub
};

