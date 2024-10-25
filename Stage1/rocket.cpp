#include "rocket.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include <random>

Rocket::Rocket(std::string name) : GameObject(name) {}

float getRandomFloatRocket(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void Rocket::update(float dt) {
    //update logic for the rocket (for instance movement)
    m_pos_y += dt / 1000.0f * 4.0f;  //move from right to left linearly [it was 2,0f]

}

void Rocket::init() {
    //initialize Jet (for instance set initial position, load texture)

    m_pos_x = getRandomFloatRocket(0.0f, GameState::getInstance()->getCanvasWidth());  
    m_pos_y = 0.0f; //1/8th from the top

    //m_width *= 3.5f;

    m_brush_rocket.fill_opacity = 1.0f;
    m_brush_rocket.outline_opacity = 0.0f;


    m_brush_rocket.texture = GameState::getInstance()->getFullAssetPath("Rocket.png");

}

void Rocket::draw() {
    
    graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, m_brush_rocket); //draws the image of the rocket 
}

