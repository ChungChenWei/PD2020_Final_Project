
#include "GameState.hpp"


// 如何使用路徑 resourcePath() + "test.png"

class Game{
private:
    sf::RenderWindow* window; // 處理視窗指標
    sf::Event event; // 處理事件
    sf::Texture texture;
    sf::Sprite sprite;
    
    sf::Clock dtClock; // 時鐘
    float dt; // 微小的時間
    
    std::stack<State*> states; // 遊戲狀態如：開場畫面
    
    std::map<std::string, int> supportedKeys;
    
    void initWindow(); // 初始化視窗
    void initKeys(); // 初始化鍵盤
    void initStates(); // 初始化狀態
    
public:
    Game(); // 遊戲建構子
    virtual ~Game(); // 解構子
    
    // Functions
    
    // Regular
    void endApplication();
    
    
    // Input
    void processInput(); // 使用者輸入
    
    // Update
    void update(); // 更新遊戲的物理和AI
    void updateDt();

    // Render
    void render(); // 繪製遊戲
    
    // Core
    void run(); // 開始運作

    
};
    
void Game::initWindow(){
    
    // 處理設定問題
    
    std::ifstream ifs(ConfigPath() + "setting.ini"); // "./Config/setting.ini"
    
    std::string title = "None";
    
    sf::VideoMode window_bounds(1280,720);
    
    unsigned framerate_limit = 120;
    
    bool vertical_sync_enabled = false;
    
    if (ifs.is_open()){
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    
    ifs.close();
    
    window = new sf::RenderWindow(window_bounds, title);
    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(false);
    
        
    


}

void Game::initKeys(){
    
    std::ifstream ifs(ConfigPath() + "supported_Keys.ini"); // "./Config/setting.ini"
    
    if (ifs.is_open()){
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value){
            this->supportedKeys[key] = key_value;
        }
    }
    
    ifs.close();

}

void Game::initStates(){
    // 初始化狀態
    this->states.push(new GameState(this->window, &this->supportedKeys));
}




// 初始化Game
Game::Game() {
    
    initWindow();
    initKeys();
    initStates();
    if(!texture.loadFromFile(imagespath() + "test.png")) // "./images/"
        std::cout << "Error loading file" << std::endl;
    
    
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(1.0f, 1.0f));
    
    
    
}

Game::~Game(){
    delete this->window;
    while (!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }
}

void Game::endApplication(){
    std::cout << "Ending Application\n";
}



// 處理輸入端
void Game::processInput() {


    // 刷新操作區
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;

//                case sf::Event::KeyPressed:
//                    window.close();
//                    // ...
//                    break;
                
            case sf::Event::MouseMoved:
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                
                break;

            default:
                break;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sprite.move(-10, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sprite.move(10, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        sprite.move(0, -10);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        sprite.move(0, 10);
}

void Game::updateDt(){
    dt = dtClock.restart().asSeconds();
}


void Game::update(){
    
    processInput();
    
    // 如果狀態不是空 進入以下
    if (!states.empty()){
        states.top()->update(this->dt); // states最上面那層的Game更新
        
        if (this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top(); // 跳出當前的狀態，回到上一步
            this->states.pop();
        }
    }
    else{
        this->endApplication();
        this->window->close();
    }
    
    
}
// 繪製遊戲
void Game::render() {
    
    window->clear();
    
    if (!states.empty()){
        states.top()->render();
    }
    
    

    window->draw(sprite);

    window->display();
}

// 跑動程式的
void Game::run() {
    
    
    while (window->isOpen()){
        updateDt();
        update();
        render();
        
    }

}
