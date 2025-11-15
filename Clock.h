#pragma once
#include <vector>


struct FrameEntry {
    int pid;
    int pageNumber;
    bool referenced;
    bool modified;
};

class Clock {
private:
    std::vector<FrameEntry> frames;
    size_t clockHand;

public:
    Clock(int frameCount);
    int evictAndReplace(int pid, int pageNum, bool isModified);
    void printFrames() const;

    size_t getFrameCount() const { return frames.size(); }
};
