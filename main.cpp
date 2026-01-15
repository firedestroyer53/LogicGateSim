#define SDL_MAIN_HANDLED

#include <iostream>
#include "Solver.h"

#define input_port true
#define output_port false

int main() {
    auto s = std::make_unique<Solver>();

    auto i1 = std::make_unique<InOut>(true);
    auto i2 = std::make_unique<InOut>(true);
    auto nand = std::make_unique<NandGate>();
    auto output = std::make_unique<InOut>(false);

    s->addWire(i1->getPort(output_port, 0), nand->getPort(input_port, 0));
    s->addWire(i2->getPort(output_port, 0), nand->getPort(input_port, 1));
    s->addWire(nand->getPort(output_port, 0), output->getPort(input_port, 0));

    s->addNode(std::move(i1));
    s->addNode(std::move(i2));
    s->addNode(std::move(nand));
    s->addNode(std::move(output));
    
    std::vector<Node*> inputs = s->getInputs();
    std::vector<Node*> outputs = s->getOutputs();

    inputs[0]->setState(input_port, 0, true);
    inputs[1]->setState(input_port, 1, true);

    s->pubSolve();

    std::cout << outputs[0]->getPort(output_port)->state << std::endl;

    return 0;
}