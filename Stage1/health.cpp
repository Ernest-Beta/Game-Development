#include "health.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include <random>
Health::Health(std::string name) : GameObject(name) {}

float getRandomFloat2(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}


void Health::update(float dt) {
    //update logic for the Health (for instance movement)
    m_pos_x -= dt / 1000.0f * 2.0f;  //move from right to left linearly

}

void Health::init() {
    //initialize Health (for instance set initial position, load texture)

    m_pos_x = GameState::getInstance()->getCanvasWidth() * 10.0f / 8.0f;  //1/8th from the left
    m_pos_y = getRandomFloat2(0.0f, GameState::getInstance()->getCanvasHeight());

    
    m_brush_health.fill_opacity = 1.0f;
    m_brush_health.outline_opacity = 0.0f;
    m_brush_health.texture = GameState::getInstance()->getFullAssetPath("Heart.png");
    
}

void Health::draw() {
    //draw the Health
    //delay(2 * 10);
    graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, m_brush_health);  
}