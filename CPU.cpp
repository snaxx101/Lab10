#include "CPU.h"
#include <iostream>

CPU::CPU() : cyclesExecuted(0), contextSwitches(0), threadSwitches(0), lastPid(-1), lastTid(-1) {}

void CPU::execute(Process& p, int threadId, TLB& tlb, TwoLevelPageTable& pt) {
    auto [tid, addr] = p.nextAccess();
    cyclesExecuted++;

    if (lastPid != -1 && lastPid != p.pid) contextSwitches++;
    if (lastTid != -1 && lastTid != threadId && lastPid == p.pid) threadSwitches++;

    lastPid = p.pid;
    lastTid = threadId;

    int pageNum = addr / 16; // example page size
    int frameNum;

    if (!tlb.lookup(p.pid, pageNum, frameNum)) {
        if (!pt.isInMemory(p.pid, pageNum)) {
            frameNum = pageNum;
            pt.loadPage(p.pid, pageNum, frameNum);
        } else {
            frameNum = pt.getFrame(p.pid, pageNum);
        }
        tlb.insert(p.pid, pageNum, frameNum);
    }
}

void CPU::printStats() const {
    std::cout << "CPU cycles executed: " << cyclesExecuted << "\n";
    std::cout << "Context switches: " << contextSwitches << "\n";
    std::cout << "Thread switches: " << threadSwitches << "\n";
}
