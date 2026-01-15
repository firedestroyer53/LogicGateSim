#define SDL_MAIN_HANDLED

#include <iostream>
#include "Solver.h"

#define type_input true
#define type_output false

int main() {
    auto s = std::make_unique<Solver>();
    
    // create 2 inputs, a nand gate, and an output
    auto i1 = std::make_unique<InOut>(type_input);
    auto i2 = std::make_unique<InOut>(type_input);
    auto nand = std::make_unique<NandGate>();
    auto o1 = std::make_unique<InOut>(type_output);

    // add a wire from the first output port of i1 to the first input port of nand
    s->addWire(i1->getPort(type_output, 0), nand->getPort(type_input, 0));
    // add a wire from the first output port of i2 to the second input port of nand
    s->addWire(i2->getPort(type_output, 0), nand->getPort(type_input, 1));
    // add a wire from the first output port of nand to the first input port of o1
    s->addWire(nand->getPort(type_output, 0), o1->getPort(type_input, 0));

    // transfer the nodes to the solver (note, the ownership of the pointers is transferred to the solver)
    s->addNode(std::move(i1));
    s->addNode(std::move(i2));
    s->addNode(std::move(nand));
    s->addNode(std::move(o1));

    std::vector<Node*> inputs = s->getInputs();
    std::vector<Node*> outputs = s->getOutputs();

    // set the state of the inputs
    inputs[0]->setState(type_input, 0, true);
    inputs[1]->setState(type_input, 1, true);

    s->pubSolve();

    // print the state of the output
    std::cout << outputs[0]->getPort(type_output)->state << std::endl;

    return 0;
}