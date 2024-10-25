#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>

class Health : public GameObject{
    graphics::Brush m_brush_health;

    float m_pos_x; //initial position x
    float m_pos_y; //initial position y
    float initial_velocity_x; //initial velocity x
    float initial_velocity_y; //initial velocity y
    
    float m_width = 1.0f;
    float m_height = 1.0f;
public:
    Health(std::string name);
    void reset();

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getX() {
        return m_pos_x;
    }
    float getY() {
        return m_pos_y;
    }
    float getWidth() {
        return m_width;
    }
    float getHeight() {
        return m_height;
    }
};