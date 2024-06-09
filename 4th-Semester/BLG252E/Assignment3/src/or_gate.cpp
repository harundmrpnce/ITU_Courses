#include "or_gate.h"
#include "pin.h"

ORGate::ORGate(const std::string& id) : Gate(id, 2) {}  // MAYBE IT HAS MORE THAN 2 INPUTS

void ORGate::evaluate() {
    bool result = false;
    for (auto input : inputs) {
        result = result || input->getSignal();
    }
    output->setSignal(result);
}

