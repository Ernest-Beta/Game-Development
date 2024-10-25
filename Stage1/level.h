#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include <vector> //include the vector header

class Level : public GameObject {
    graphics::Brush m_brush_backgrounds[6];
    float m_background_positions[6]; //X positions for the 4 backgrounds
    float m_background_speed = -0.0005f;
    
    float m_center_x = 5.0f;
    float m_center_y = 5.0f;
    std::vector<GameObject*> m_static_objects;  //storage for static objects
    
public:
    std::vector<GameObject*> m_dynamic_objects; //storage for dynamic objects
    bool firsttimer = false;
    void update(float dt) override;
    void init() override;
    void draw() override;
    Level(const std::string& name = "Level1");
    ~Level();
};
