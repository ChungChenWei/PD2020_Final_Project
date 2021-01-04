
#include "Entity.hpp"



class State{
private:
    
protected:
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    
    // 資源
    std::vector<sf::Texture> texture;

    // function
    
    virtual void initKeybinds() = 0;
    
public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~State();
    
    const bool& getQuit() const;
    
    virtual void checkForQuit();
    virtual void endState() = 0;
    
    
    virtual void updateInput(const float & dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    
};

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys){
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}

State::~State(){
    
}

const bool & State::getQuit() const{
    return this->quit;
}


void State::checkForQuit(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))){
        this->quit = true;
    }
}
