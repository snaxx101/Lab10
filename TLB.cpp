#include "TLB.h"
#include <iostream>


TLB::TLB(int size) : currentTime(0), maxSize(size) {}


bool TLB::lookup(int pid, int pageNumber, int& frameNumber) {
currentTime++;
for (auto& e : tlbEntries) {
if (e.pid == pid && e.pageNumber == pageNumber) {
e.lastUsed = currentTime;
frameNumber = e.frameNumber;
return true;
}
}
return false;
}


void TLB::insert(int pid, int pageNumber, int frameNumber) {
currentTime++;
if (tlbEntries.size() >= maxSize) {
// LRU eviction
int lruIndex = 0;
for (int i = 1; i < tlbEntries.size(); ++i)
if (tlbEntries[i].lastUsed < tlbEntries[lruIndex].lastUsed) lruIndex = i;
tlbEntries[lruIndex] = {pid, pageNumber, frameNumber, currentTime};
} else {
tlbEntries.push_back({pid, pageNumber, frameNumber, currentTime});
}
}


void TLB::printStats() const {
std::cout << "TLB contains " << tlbEntries.size() << " entries.\n";
}