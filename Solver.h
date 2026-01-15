#include <vector>
#include <memory>
#include <stdexcept>

#include "Gates.h"

class Solver {
    public:
        void addNode(std::unique_ptr<Node> node);

        void addWire(Port* from, Port* to);

        void pubSolve();

        std::vector<Node*> getOutputs();

        std::vector<Node*> getInputs();

    private:
        std::vector<Wire> wires;
        std::vector<std::unique_ptr<Node>> nodes;

        void solve(const std::vector<Node*>& inputs);

        std::vector<Node*> getConnectedNodes(const Node* node);
};