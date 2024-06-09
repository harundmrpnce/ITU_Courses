#include "circuit.h"

void Circuit::addComponent(Component* comp) { components.push_back(comp); }

void Circuit::addWire(Wire* wire) { wires.push_back(wire); }

void Circuit::simulate() {
    for (Wire* wire : wires) {
        wire->propagateSignal();
        for (Component* comp : components) {
            comp->evaluate();
        }
    }
}

// IMPLEMENT DESTRUCTOR