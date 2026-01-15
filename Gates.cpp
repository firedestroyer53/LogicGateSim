#include "Gates.h"

class NandGate : public Node {
    public:
        NandGate() {
            Port p;
            p.parent = this;
            this->inputs.push_back(p);
            this->inputs.push_back(p);
            this->outputs.push_back(p);
        }
        bool compute() {
            bool initial = outputs[0].state;
            if (!(inputs[0].state & inputs[1].state)) {
                outputs[0].state = true;
                
            } 
            else {
                outputs[0].state = false;
            }
            return initial != outputs[0].state;
        }
};

class InOut : public Node {
    public:
        bool isInput;
        bool isDirty;

        InOut(bool isInput) {
            this->isInput = isInput;
            Port p;
            p.parent = this;
            this->inputs.push_back(p);
            this->outputs.push_back(p);
        }
        bool compute() {
            this->outputs[0] = this->inputs[0];
            return isDirty;
        }
};

void Wire::transfer() {
    this->to->state = this->from->state; // transfer the signal
}