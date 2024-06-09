#include "gate.h"
#include "pin.h" 

Gate::Gate(const std::string& id, int numberOfInputs) : Component(id) {
    for (int i = 0; i < numberOfInputs; i++) {
        inputs.push_back(new Pin(id + std::to_string(i)));
    }
    output = new Pin(id + "_out");
}

Pin* Gate::getOutputPin() { return output; }

Pin* Gate::getInputPin(int i) { return inputs[i]; }

//IMPLEMENT DESTRUCTOR