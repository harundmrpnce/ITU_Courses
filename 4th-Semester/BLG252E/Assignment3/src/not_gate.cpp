#include "not_gate.h"
#include "pin.h"

NOTGate::NOTGate(const std::string& id) : Gate(id, 1) {}  

void NOTGate::evaluate() { output->setSignal(!inputs[0]->getSignal()); }