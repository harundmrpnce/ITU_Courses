#include "wire.h"

Wire::Wire(Pin* src, Pin* dest) : source(src), destination(dest) {}

void Wire::propagateSignal() { destination->setSignal(source->getSignal()); }