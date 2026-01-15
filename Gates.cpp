#include "Gates.h"

Port* Node::getPort(bool isInput, int index) {
    if (isInput) {
        return &this->inputs[index];
    }
    return &this->outputs[index];
}

void Node::setState(bool isInput, int index, bool state) {
    if (isInput) {
        this->inputs[index].state = state;
    }
    this->outputs[index].state = state;
}

void Node::addInput(int num) {
    Port p;
    p.parent = this;
    for (int i = 0; i < num; i++) {
        this->inputs.push_back(p);
    }
}

void Node::addOutput(int num) {
    Port p;
    p.parent = this;
    for (int i = 0; i < num; i++) {
        this->outputs.push_back(p);
    }
}

// Gate types
NandGate::NandGate() {
    addInput(2);
    addOutput(1);
}

bool NandGate::compute() {
    bool initial = getPort(false, 0)->state;
    if (!(getPort(true, 0)->state & getPort(true, 1)->state)) {
        setState(false, true);
    } 
    else {
        setState(false, false);
    }
    return initial != getPort(false)->state;
}


InOut::InOut(bool isInput) {
    this->isInput = isInput;
    addInput(1);
    addOutput(1);
}

bool InOut::compute() {
    setState(false, getPort(true)->state);
    return isDirty;
}


// other
void Wire::transfer() {
    this->to->state = this->from->state; // transfer the signal
}