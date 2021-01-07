#include "State.hpp"

class GameState: public State{
private:
    
    Entity player;
    
    // functions
    
    void initKeybinds();
    
    
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    
    
    virtual ~GameState();
    
    // function
    void endState();
    
    void updateInput(const float & dt);
    void update(const float& dt);
    
    void render(sf::RenderTarget* target = nullptr);
    
};


void GameState::initKeybinds(){
    
    std::ifstream ifs(ConfigPath() + "gameState_keybinds.ini"); // "./Config/setting.ini"
    
    if (ifs.is_open()){
        std::string key = "";
        std::string key2 = "";
        
        while (ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    
    ifs.close();
    
    
    
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys): State(window, supportedKeys){
    this->initKeybinds();
}

GameState::~GameState(){
    
}

void GameState::endState(){
    std::cout << "Ending GameState\n";
}

void GameState::updateInput(const float & dt){
    this->checkForQuit();
    
    // update player input
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt, -1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt, 1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt, 0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt){
    this->updateInput(dt);
    this->player.update(dt);
    

}

void GameState::render(sf::RenderTarget* target){
    
    if (!target){
        target = this->window;
    }
    
    this->player.render(this->window);
    
    
}


