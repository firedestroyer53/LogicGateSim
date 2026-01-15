#include <SDL2/SDL.h>
#include <vector>

struct Port;
class Node;

struct Port {
    bool state = false;
    Node* parent = nullptr;
    SDL_Point relativePos;
};

class Node {
    public:
        virtual ~Node() = default;
        // returns true if the output changed
        virtual bool compute() = 0;
        void render(SDL_Renderer* renderer);
        Port* getPort(bool isInput, int index = 0); 
        void setState(bool isInput, int index = 0, bool state);
        void addInput(int num);
        void addOutput(int num);

        
        SDL_Rect bounds;
    private:
        std::vector<Port> inputs;
        std::vector<Port> outputs;
};

class NandGate : public Node {
    public:
        NandGate();
        bool compute();

};

class InOut : public Node {
    public:
        bool isInput;
        bool isDirty;

        InOut(bool isInput);
        bool compute();
};



class Wire {
    public:
        Port *from;
        Port *to;

        void transfer();

        void render(SDL_Renderer *renderer);
};