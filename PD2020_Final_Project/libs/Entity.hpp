#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <string>


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>




//#include <glad/glad.h>
//#include <SFML/OpenGL.hpp>

#include "ResourcePath.hpp"




class Entity{
private:
    
    
protected:
    sf::RectangleShape shape;
    float movementSpeed;
public:
    
    Entity();
    ~Entity();
    
    // functions
    virtual void move(const float dt, const float x, const float y);
    
    
    virtual void update(const float& dt);
    
    virtual void render(sf::RenderTarget* target);
    
    
};


Entity::Entity(){
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
    this->shape.setFillColor(sf::Color::White);
    this->movementSpeed = 100.f;
}

Entity::~Entity(){
    
}

// x, y 表示方向
void Entity::move(const float dt, const float dir_x, const float dir_y){
    this->shape.move(dir_x * this->movementSpeed *dt, dir_y * this->movementSpeed * dt);
    
}


void Entity::update(const float & dt){

}

void Entity::render(sf::RenderTarget* target){
    target->draw(this->shape);
    
}
