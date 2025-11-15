#include "TwoLevelPageTable.h"
#include <iostream>

TwoLevelPageTable::TwoLevelPageTable(int frameCount)
    : clock(frameCount) {}

bool TwoLevelPageTable::isInMemory(int pid, int pageNum) const {
    return memoryPages.count({pid,pageNum}) > 0;
}

int TwoLevelPageTable::getFrame(int pid, int pageNum) const {
    auto it = secondLevel.find({pid,pageNum});
    if(it != secondLevel.end()) return it->second;
    return -1;
}

void TwoLevelPageTable::loadPage(int pid, int pageNum, bool isModified) {
    if(memoryPages.size() < clock.getFrameCount()){
        int frame = memoryPages.size();
        memoryPages.insert({pid,pageNum});
        secondLevel[{pid,pageNum}] = frame;
        clock.evictAndReplace(pid,pageNum,isModified); 
    } else {
        int evictedFrame = clock.evictAndReplace(pid,pageNum,isModified);
        // Remove evicted page
        for(auto it = memoryPages.begin(); it != memoryPages.end(); ++it){
            if(secondLevel[*it] == evictedFrame){
                memoryPages.erase(it);
                secondLevel.erase(*it);
                break;
            }
        }
        memoryPages.insert({pid,pageNum});
        secondLevel[{pid,pageNum}] = evictedFrame;
    }
}

void TwoLevelPageTable::printStats() const {
    std::cout << "Pages in memory: " << memoryPages.size() << "\n";
    clock.printFrames();
}
