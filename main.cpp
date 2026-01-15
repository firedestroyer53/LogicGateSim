#define SDL_MAIN_HANDLED

#include <iostream>
#include "Solver.h"


int main() {
    auto s = std::make_unique<Solver>();

    auto i1 = std::make_unique<InOut>(true);
    auto i2 = std::make_unique<InOut>(true);
    auto nand = std::make_unique<NandGate>();
    auto output = std::make_unique<InOut>(false);

    s->addWire(&i1->outputs[0], &nand->inputs[0]);
    s->addWire(&i2->outputs[0], &nand->inputs[1]);
    s->addWire(&nand->outputs[0], &output->inputs[0]);

    s->addNode(std::move(i1));
    s->addNode(std::move(i2));
    s->addNode(std::move(nand));
    s->addNode(std::move(output));
    
    std::vector<Node*> inputs = s->getInputs();
    std::vector<Node*> outputs = s->getOutputs();

    inputs[0]->inputs[0].state = true;
    inputs[1]->inputs[0].state = true;

    s->pubSolve();



    std::cout << outputs[0]->outputs[0].state << std::endl;

    return 0;
}