#include "Jet.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include <random>

Jet::Jet(std::string name) : GameObject(name) {}

float getRandomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void Jet::update(float dt) {
    //update logic for the Jet (e.g., movement)
    m_pos_x -= dt / 1000.0f * 4.0f;  //move from right to left linearly [it was 2,0f]

}

void Jet::init() {
    //initialize Jet (for instance set initial position, load texture)

    m_pos_x = GameState::getInstance()->getCanvasWidth() * 10.0f / 8.0f;  //1/8th from the left
    m_pos_y = getRandomFloat(0.0f, GameState::getInstance()->getCanvasHeight());

    m_width *= 3.5f;
    
    m_brush_jet.fill_opacity = 1.0f;
    m_brush_jet.outline_opacity = 0.0f;
    
    
    m_brush_jet.texture = GameState::getInstance()->getFullAssetPath("Jet.png");
    
}

void Jet::draw() {
    //draw the Jet
    //delay(2 * 10);
    graphics::drawRect(m_pos_x, m_pos_y, 3.5f, 2.5f, m_brush_jet);  //example dimensions, adjust as needed
}

