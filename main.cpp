#include <iostream>
#include <fstream>
#include <sstream>
#include "Process.h"
#include "Scheduler.h"
#include "CPU.h"
#include "TLB.h"
#include "TwoLevelPageTable.h"

int main() {
    Scheduler sched(SchedulingPolicy::MLFQ, 4);
    CPU cpu;

    TLB tlb(4);
    TwoLevelPageTable pt(16);

    std::ifstream infile("trace/random_trace.txt");
    if (!infile.is_open()) {
        std::cerr << "Cannot open trace file\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int pid, threadId;
        unsigned int addr;
        char type;
        if (!(iss >> pid >> threadId >> std::hex >> addr >> type)) continue;

        sched.addProcessIfNotExists(pid);
        auto &p = sched.getProcess(pid);
        p.memoryAccesses.push_back({threadId, addr});
        p.addThread(threadId, 1);
    }

    // Simulation loop
    bool workLeft = true;
    while (workLeft) {
        workLeft = false;
        for (auto &[pid, proc] : sched.getAllProcesses()) {
            for (auto &[tid, _] : proc.threadPriorities) {
                if (!proc.hasMoreAccesses()) continue;
                workLeft = true;
                cpu.execute(proc, tid, tlb, pt);
                sched.adjustPriority(pid, tid);
            }
        }
    }

    cpu.printStats();
    tlb.printStats();
    pt.printStats();

    return 0;
}
