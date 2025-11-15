#pragma once
#include "Process.h"
#include "TLB.h"
#include "TwoLevelPageTable.h"

class CPU {
private:
    int cyclesExecuted;
    int contextSwitches;
    int threadSwitches;
    int lastPid;
    int lastTid;

public:
    CPU();
    void execute(Process& p, int threadId, TLB& tlb, TwoLevelPageTable& pt);
    void printStats() const;
};
