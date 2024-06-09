#include "and_gate.h"
#include "pin.h"

ANDGate::ANDGate(const std::string& id) : Gate(id, 2) {}  // MAYBE IT HAS MORE THAN 2 INPUTS

void ANDGate::evaluate() {
    bool result = true;
    for (auto input : inputs) {
        result = result && input->getSignal();
    }
    output->setSignal(result);
}