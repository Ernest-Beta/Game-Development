#include "xp.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include <random>
#include<chrono>
#include<thread>
Xp::Xp(std::string name) :GameObject(name)
{
}

float getRandomFloat1(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void Xp::reset()
{
}

void Xp::update(float dt)
{
    m_pos_x -= dt / 1000.0f * 2.0f;
}

void Xp::init()
{
    m_pos_x = GameState::getInstance()->getCanvasWidth() * 10.0f / 8.0f;  //1/8th from the left
    m_pos_y = getRandomFloat1(0.0f, GameState::getInstance()->getCanvasHeight());


    m_brush_xp.fill_opacity = 2.0f;
    m_brush_xp.outline_opacity = 0.0f;
    
    
    for (int i = 0; i <= 23; i++) {
        m_xp.push_back(m_state->getFullAssetPath("xp" + std::to_string(i) + ".png"));
    }

}

void Xp::draw()
{
    static int s = 0; //initialize 's' as static to persist its value between function calls
    static auto lastUpdateTime = std::chrono::steady_clock::now(); //track the time of the last update

    //calculate the elapsed time since the last update
    auto currentTime = std::chrono::steady_clock::now();
    float elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();

    //if 0.05 seconds have elapsed, switch to the next image
    if (elapsedTime >= 50.0f) {
        //increment 's' to switch to the next image
        s++;
        if (s >= m_xp.size()) {
            s = 0; //reset 's' to loop back to the first image
        }
        lastUpdateTime = currentTime; //update the last update time
    }

    //draw the current image
    m_brush_xp.texture = m_xp[s];
    graphics::drawRect(m_pos_x, m_pos_y, 1.8f, 1.4f, m_brush_xp);
}
