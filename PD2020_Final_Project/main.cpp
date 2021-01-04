
#include "Game.hpp"

// 如何使用路徑 resourcePath() + "test.png"
// 使用教學
// Game.hpp 可以修改
// 路徑要先設定好 去Resourcepath內把return 改乘自己的絕對路徑


// ini有兩個 key的話是 把固定的 存成數值 然後 丟到keybind中自訂 LEFT 要是什麼鍵 再去re他

int main()
{
    
    
    Game game;
    
    game.run(); // 設立最小fps為60
    
    
    return EXIT_SUCCESS;

//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window"); // 製作一個視窗
//    // 製作材質
//    sf::Texture texture;
//    if (!texture.loadFromFile(imagespath() + "test.png"))
//        return EXIT_FAILURE;
//
//    sf::Sprite sprite(texture);
//
//    sprite.setPosition(sf::Vector2f(400.f, 260.f));
//    sprite.setScale(sf::Vector2f(3.2f, 3.2f));
//    sprite.rotate(15.f);
//
//    // 刷新操作區

}
