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
    
    SDL_Rect bounds;
    std::vector<Port> inputs;
    std::vector<Port> outputs;
};


class Wire {
public:
    Port* from;
    Port* to;

    void transfer();

    void render(SDL_Renderer* renderer);
};