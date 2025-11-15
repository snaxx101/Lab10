#include "Clock.h"
#include <iostream>

Clock::Clock(int frameCount) : clockHand(0) {
    frames.resize(frameCount, {-1, -1, false, false});
}

// Evict and replace using Clock with reference and modified bits
int Clock::evictAndReplace(int pid, int pageNum, bool isModified) {
    size_t n = frames.size();
    while (true) {
        FrameEntry &entry = frames[clockHand];
        if (!entry.referenced && !entry.modified) {
            // Evict this frame
            int evictedPage = entry.pageNumber;
            entry = {pid, pageNum, true, isModified};
            clockHand = (clockHand + 1) % n;
            return evictedPage;
        } else {
            // Give second chance
            entry.referenced = false;
            clockHand = (clockHand + 1) % n;
        }
    }
}

// Debug print
void Clock::printFrames() const {
    std::cout << "Frames: ";
    for (auto &f : frames) {
        std::cout << "(" << f.pid << "," << f.pageNumber 
                  << "," << f.referenced << "," << f.modified << ") ";
    }
    std::cout << "\n";
}
