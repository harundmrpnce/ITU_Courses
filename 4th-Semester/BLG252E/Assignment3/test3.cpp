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
    Pin * C = new Pin{"C"};

    // Set initial signals
    A->setSignal(false);
    B->setSignal(false);
    C->setSignal(false);

    // Create gates
    ANDGate * and1 = new ANDGate{"AND1"};
    ANDGate * and2 = new ANDGate{"AND2"};
    ANDGate * and3 = new ANDGate{"AND3"};
    ORGate  * or1  = new ORGate{"OR1"};
    ORGate  * or2  = new ORGate{"OR2"};

    // Add components in the proper sequence
    circuit.addComponent(A);
    circuit.addComponent(B);
    circuit.addComponent(C);
    circuit.addComponent(and1);
    circuit.addComponent(and2);
    circuit.addComponent(and3);
    circuit.addComponent(or1);
    circuit.addComponent(or2);

    // Create and add wires respecting the order of dependency
    circuit.addWire(new Wire{A, and1->getInputPin(0)});
    circuit.addWire(new Wire{B, and1->getInputPin(1)});
    circuit.addWire(new Wire{B, and2->getInputPin(0)});
    circuit.addWire(new Wire{C, and2->getInputPin(1)});
    circuit.addWire(new Wire{B, or1->getInputPin(0)});
    circuit.addWire(new Wire{and2->getOutputPin(), and3->getInputPin(0)});
    circuit.addWire(new Wire{or1->getOutputPin(), and3->getInputPin(1)});
    circuit.addWire(new Wire{and1->getOutputPin(), or2->getInputPin(0)});
    circuit.addWire(new Wire{and3->getOutputPin(), or2->getInputPin(1)});

    // Run the simulation
    // Simulate all possible combinations of inputs
    for (int i = 0; i < 8; ++i) {
        // Set inputs based on the bits of i
        A->setSignal(i & 1);
        B->setSignal(i & 2);
        C->setSignal(i & 4);

        // Simulate the circuit
        circuit.simulate();

        // Print out the result for this combination
        std::cout << "Inputs: A=" << (i & 1) << ", B=" << ((i & 2) >> 1) << ", C=" << ((i & 4) >> 2) << 
        " | Output: " << or2->getOutputPin()->getSignal() << std::endl;
    }

    return 0;
}
