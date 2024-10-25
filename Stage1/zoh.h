#pragma once
#include"gameobject.h"
#include<sgg/graphics.h>
#include"player.h"


class Zoh : public GameObject {
    graphics::Brush m_brush_zoh;
    graphics::Brush m_brush_zohx3;
    graphics::Brush m_brush_zohx2;
    graphics::Brush m_brush_zohx1;
    graphics::Brush m_brush_zohx0;

    float m_pos_x; //initial position x
    float m_pos_y; //initial position y
    Player& m_player;

public:
    Zoh(std::string name, Player* player);
    
    void update(float dt) override;
    void init() override;
    void draw() override;
    
    
    float getX() {
        return m_pos_x;
    }
    float getY() {
        return m_pos_y;
    }
};