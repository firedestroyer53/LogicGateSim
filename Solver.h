#include <vector>
#include <memory>
#include <stdexcept>

#include "Gates.cpp"

class Solver {
    public:
        void addNode(std::unique_ptr<Node> node) {
            if (!node) {
                throw std::invalid_argument("Node cannot be null.");
            }

            nodes.push_back(std::move(node));
        }

        // Usage:
        // solver.addNode(std::make_unique<NandGate>());
        void addWire(Port* from, Port* to) { // for now just trust the user of the function put two correct ports.
            Wire wire;
            wire.from = from;
            wire.to = to;
            wires.push_back(wire);
        }

        void pubSolve() {
            solve(getInputs());
        }

        std::vector<Node*> getOutputs() {
            std::vector<Node*> outputs;
            for (auto& node : nodes) {
                Node* n = node.get();
                InOut* inout = dynamic_cast<InOut*>(n);
                if (inout) {
                    if (!inout->isInput) {
                        outputs.push_back(inout);
                    }
                }
            }
            return outputs;
        }

        std::vector<Node*> getInputs() {
            std::vector<Node*> inputs;
            for (auto& node : nodes) {
                Node* n = node.get();
                InOut* inout = dynamic_cast<InOut*>(n);
                if (inout) {
                    if (inout->isInput) {
                        inputs.push_back(inout);
                    }
                }
            }
            return inputs;
        }


    private:
        std::vector<Wire> wires;
        std::vector<std::unique_ptr<Node>> nodes;

        void solve(const std::vector<Node*>& inputs) {
            for (int i = 0; i < inputs.size(); i++) {
                Node* node = inputs[i];
                InOut* inout = dynamic_cast<InOut*>(node);
                if (inout) {
                    if (!inout->isInput) { // base case (reached an output)
                        inout->compute();
                        break;
                    }
                    if (inout->isDirty) { // is an input, and did change since last seen
                        inout->compute();
                        solve(getConnectedNodes(inout));
                    }
                }
                if (node->compute()) { // output did change
                    solve(getConnectedNodes(node));
                }
            }
        }

        std::vector<Node*> getConnectedNodes(const Node* node) {
            std::vector<Node*> connectedNodes;
            for (auto wire : wires) {
                if (wire.from->parent == node) {
                    connectedNodes.push_back(wire.to->parent);
                    wire.transfer();
                }
            }
            return connectedNodes;
        }
};