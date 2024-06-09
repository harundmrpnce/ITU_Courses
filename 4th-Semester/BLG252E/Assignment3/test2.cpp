#include "../include/circuit.h"
#include "../include/pin.h"
#include "../include/and_gate.h"
#include "../include/or_gate.h"
#include "../include/not_gate.h"

#include <iostream>

int main() {
    Circuit circuit;

    // Create input pins as components
    Pin * A = new Pin{"A"};
    Pin * B = new Pin{"B"};

    A->setSignal(false);
    B->setSignal(false);

    ANDGate * and1 = new ANDGate{"AND1"};
    ORGate  * or1  = new ORGate{"OR1"};
    ORGate  * or2  = new ORGate{"OR2"};

    // Add components in the proper sequence
    circuit.addComponent(A);
    circuit.addComponent(B);
    circuit.addComponent(and1);
    circuit.addComponent(or1);
    circuit.addComponent(or2);

    // Create and add wires respecting the order of dependency
    circuit.addWire(new Wire{A, and1->getInputPin(0)});
    circuit.addWire(new Wire{B, and1->getInputPin(1)});
    circuit.addWire(new Wire{A, or1->getInputPin(0)});
    circuit.addWire(new Wire{B, or1->getInputPin(1)});
    circuit.addWire(new Wire{and1->getOutputPin(), or2->getInputPin(0)});
    circuit.addWire(new Wire{or1->getOutputPin(), or2->getInputPin(1)});

    // Run the simulation
    // Simulate all possible combinations of inputs
    for (int i = 0; i < 4; ++i) {
        // Set inputs based on the bits of i
        A->setSignal(i & 1);
        B->setSignal(i & 2);

        // Simulate the circuit
        circuit.simulate();

        // Print out the result for this combination
        std::cout << "Inputs: A=" << (i & 1) << ", B=" << ((i & 2) >> 1) << 
        " | Output: " << or2->getOutputPin()->getSignal() << std::endl;
    }

    return 0;
}