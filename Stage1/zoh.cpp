#include "zoh.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "player.h"


Zoh::Zoh(std::string name, Player* player) : GameObject(name), m_player(*player) {}

void Zoh::update(float dt) {
    //update logic for the Zoh (for instance movement)
    

}

void Zoh::init() {
    //initialize Zoh (for instance set initial position, load texture)

    m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;  //set the initial X position
    m_pos_y = GameState::getInstance()->getCanvasHeight() - 14.75f;


    m_brush_zoh.fill_opacity = 1.0f;
    m_brush_zoh.outline_opacity = 0.0f;
    m_brush_zoh.texture = GameState::getInstance()->getFullAssetPath("Heart.png");

    
    //initializes the number 3 inside the heart
    m_brush_zohx3.fill_opacity = 1.0f;
    m_brush_zohx3.outline_opacity = 0.0f;
    m_brush_zohx3.texture = GameState::getInstance()->getFullAssetPath("3.png");
    
    //initializes the number 2 inside the heart
    m_brush_zohx2.fill_opacity = 1.0f;
    m_brush_zohx2.outline_opacity = 0.0f;
    m_brush_zohx2.texture = GameState::getInstance()->getFullAssetPath("2.png");
    
    //initializes the number 1 inside the heart
    m_brush_zohx1.fill_opacity = 1.0f;
    m_brush_zohx1.outline_opacity = 0.0f;
    m_brush_zohx1.texture = GameState::getInstance()->getFullAssetPath("1.png");
    
    
    
}

void Zoh::draw() {
    
    graphics::drawRect(m_pos_x, m_pos_y, 1.35f, 1.35f, m_brush_zoh);
    
    //each of the following does the drawing of one of the numbers inside the heart
    
    if (m_player.getHealth() == 1) {
        graphics::drawRect(m_pos_x - 0.1f, m_pos_y, 0.4f, 0.7f, m_brush_zohx1);
    }
    if (m_player.getHealth() == 2) {
        graphics::drawRect(m_pos_x, m_pos_y, 0.8f, 0.8f, m_brush_zohx2);
    }
    if (m_player.getHealth() == 3) {
        graphics::drawRect(m_pos_x, m_pos_y, 0.9f, 0.9f, m_brush_zohx3);
    }
    
}