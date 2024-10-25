#include"player.h"
#include<sgg/graphics.h>
#include"gamestate.h"
#include "Jet.h"
#include "health.h"
#include "xp.h"
#include "Bird.h"
#include"rocket.h"
#include"util.h"
#include<chrono>
#include<thread>
#include"timer.h"

Timer timer;
void Player::update(float dt)
{
    float delta_time = dt / 1000.0f;
    const float velocity = 10.0f;

    //update player position based on input

    if (graphics::getKeyState(graphics::SCANCODE_W))
        m_pos_y -= delta_time * velocity;
    if (graphics::getKeyState(graphics::SCANCODE_S))
        m_pos_y += delta_time * velocity;
    if (m_state->getElapsedTime() >= 60.0) {
        if (graphics::getKeyState(graphics::SCANCODE_A))
            m_pos_x -= delta_time * velocity;
        if (graphics::getKeyState(graphics::SCANCODE_D))
            m_pos_x += delta_time * velocity;

        //ensure the player stays within the canvas boundaries for horizontal movement
        float canvasWidth = m_state->getCanvasWidth();
        m_pos_x = std::max(0.0f, std::min(m_pos_x, canvasWidth));
    }
    //ensure the player stays within the canvas boundaries
    float canvasHeight = m_state->getCanvasHeight();
    m_pos_y = std::max(0.0f, std::min(m_pos_y, canvasHeight));
}

void Player::init()
{
    m_pos_x = m_state->getCanvasWidth() / 8.5f;  //set the initial X position
    m_pos_y = m_state->getCanvasHeight() / 2.0f; //set the initial Y position
    
    
    

    m_state->m_global_offset_x = 0.0f; //reset global offset X
    m_state->m_global_offset_y = 0.0f; //reset global offset Y

    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
    for (int i = 0; i <= 8; i++) {
        m_drako.push_back(m_state->getFullAssetPath("Dragon" + std::to_string(i) + ".png"));
    }

}


void Player::draw()
{



    static int s = 0; //initialize 's' as static to persist its value between function calls
    static auto lastUpdateTime = std::chrono::steady_clock::now(); //track the time of the last update

    //calculate the elapsed time since the last update
    auto currentTime = std::chrono::steady_clock::now();
    float elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();

    //if 0.05 seconds have elapsed, switch to the next image
    if (elapsedTime >= 100.0f) {
        //increment 's' to switch to the next image
        s++;
        if (s >= m_drako.size()) {
            s = 0; //reset 's' to loop back to the first image
        }
        lastUpdateTime = currentTime; //update the last update time
    }

    // Draw the current image
    m_brush_player.texture = m_drako[s];
    graphics::drawRect(m_pos_x, m_pos_y, 1.75f, 1.75f, m_brush_player);
    //////////////////////////////////////////////////////////////////////////////////
    graphics::Brush brush_xp;
    graphics::Brush msg;

    
    SETCOLOR(msg.fill_color, 1, 0, 0); // RGB for the message color
    SETCOLOR(brush_xp.fill_color, 1, 0.4, 0); // RGB for the XP color

    float xp_h = m_state->getCanvasHeight() - 14.75f;
    float xp_w = m_state->getCanvasWidth() / 2.0 + 1.5f;

    std::string msgs = "Full movement ACTIVATED";
    float current_time = m_state->getElapsedTime();

    if (current_time >= 60.0 && current_time <= 70.0)
    {
        // Calculate how far we are between 60 and 70 seconds
        float time_diff = current_time - 60.0; // 0 at start, 10 at end
        float alpha;

        if (time_diff <= 5.0) // First half (fade in)
        {
            alpha = time_diff / 5.0; // Increase alpha from 0 to 1
        }
        else // Second half (fade out)
        {
            alpha = 1.0 - ((time_diff - 5.0) / 5.0); // Decrease alpha from 1 to 0
        }

        msg.fill_opacity = alpha; // Apply the calculated alpha
        graphics::drawText(m_state->getCanvasWidth() / 2.0 - 3.0f, m_state->getCanvasHeight() / 2.0f + 5.0f, 0.5f, msgs, msg);
    }
    std::string m_experience_str = std::to_string(m_experience);
    std::string print_xp = "XP: " + m_experience_str;
    graphics::setFont(m_state->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(xp_w, xp_h, 0.5f, print_xp, brush_xp);
    //////////////////////////////////////////////////////////////////////////////////


}
bool Player::hitsJet(Jet& jet) {
    bool hitter = false; //initialize the hitter flag

    if (!hasBeenHitJet()) { //check if the player has already been hit in this frame
        hitter = (fabs(m_pos_x - jet.getX()) * 2.0f < (m_width + jet.getWidth())) &&
            (fabs(m_pos_y - jet.getY()) * 2.0f < (m_height + jet.getHeight()));

        if (hitter) {
            m_health--; //decrease player's health
            graphics::playSound(m_state->getFullAssetPath("Hit.mp3"), 1.0f);
            HitGokuJet(true); //set alreadyHit flag to true to indicate the player has been hit
            
        }
    }
    else {
        //reset the alreadyHit flag if the player was hit in the previous frame
        HitGokuJet(false);
    }

    return hitter;
}

bool Player::hitsHealth(Health& health) {
    bool hitter = false; //initialize the hitter flag

    if (!hasBeenHitHealth()) { //check if the player has already been hit in this frame
        hitter = (fabs(m_pos_x - health.getX()) * 2.0f < (m_width + health.getWidth())) &&
            (fabs(m_pos_y - health.getY()) * 2.0f < (m_height + health.getHeight()));

        if (hitter && m_health<3 && m_health>0) {
            m_health++; //decrease player's health
            graphics::playSound(m_state->getFullAssetPath("Health.mp3"), 1.0f);
            HitGokuHealth(true); //set alreadyHit flag to true to indicate the player has been hit
            
        }
    }
    else {
        //reset the alreadyHit flag if the player was hit in the previous frame
        HitGokuHealth(false);
    }

    return hitter;
}
bool Player::hitsXp(Xp& xp) {
    bool hitter = false; //initialize the hitter flag

    if (!hasBeenHitXp()) { //check if the player has already been hit in this frame
        hitter = (fabs(m_pos_x - xp.getX()) * 2.0f < (m_width + xp.getWidth())) &&
            (fabs(m_pos_y - xp.getY()) * 2.0f < (m_height + xp.getHeight()));

        if (hitter) {
            m_experience=m_experience+10; // Decrease player's health
            graphics::playSound(m_state->getFullAssetPath("Xp.mp3"), 1.0f);
            HitGokuXp(true); //set alreadyHit flag to true to indicate the player has been hit
        }
    }
    else {
        //reset the alreadyHit flag if the player was hit in the previous frame
        HitGokuXp(false);
    }

    return hitter;
}
bool Player::hitsBird(Bird& bird) {
    bool hitter = false; //initialize the hitter flag

    if (!hasBeenHitBird()) { //check if the player has already been hit in this frame
        hitter = (fabs(m_pos_x - bird.getX()) * 2.0f < (m_width + bird.getWidth())) &&
            (fabs(m_pos_y - bird.getY()) * 2.0f < (m_height + bird.getHeight()));

        if (hitter) {
            m_health--; //decrease player's health
            graphics::playSound(m_state->getFullAssetPath("Quack.mp3"), 1.0f);
            HitGokuBird(true); //set alreadyHit flag to true to indicate the player has been hit
        }
    }
    else {
        //reset the alreadyHit flag if the player was hit in the previous frame
        HitGokuBird(false);
    }

    return hitter;
}
bool Player::hitsRocket(Rocket& rocket) {
    bool hitter = false; //initialize the hitter flag

    if (!hasBeenHitRocket()) { //check if the player has already been hit in this frame
        hitter = (fabs(m_pos_x - rocket.getX()) * 2.0f < (m_width + rocket.getWidth())) &&
            (fabs(m_pos_y - rocket.getY()) * 2.0f < (m_height + rocket.getHeight()));

        if (hitter) {
            m_health--; //decrease player's health
            graphics::playSound(m_state->getFullAssetPath("Bum.mp3"), 1.0f);
            HitGokuRocket(true); //set alreadyHit flag to true to indicate the player has been hit
        }
    }
    else {
        //reset the alreadyHit flag if the player was hit in the previous frame
        HitGokuRocket(false);
    }

    return hitter;
}


