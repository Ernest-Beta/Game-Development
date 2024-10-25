#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "Jet.h"
#include "health.h"
#include "xp.h"
#include"zoh.h"
#include"Bird.h"
#include"rocket.h"
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include "util.h"
#include "timer.h"
#include<iomanip>
#include<sstream>

GameState::GameState() {}
//used for the timer
std::chrono::steady_clock::time_point gameStartTime;

void GameState::init()
{

    status = STATUS_START;
    
    timer = new Timer();
    

    m_current_level = new Level();//creates Level object
    m_current_level->init();//init method is called on the object

    m_player = new Player("Goku");//creates Player object
    m_player->init();//init method is called on the object

    m_zoh = new Zoh("Zoh", m_player); //creates Zoh object
    m_zoh->init();//init method is called on the object


    // Load initial assets
    graphics::preloadBitmaps(getAssetDir());
    int jetSpawnDelay = 1200;      //delay the first jet spawn by 1.2 seconds
    int xpSpawnDelay = 1900;      //delay the first XP spawn by 1.9 seconds after the Jet
    int healthSpawnDelay = 5000;  //delay the first health spawn by 5 seconds after the XP
    int birdSpawnDelay = 1200;  //delay the first bird spawn by 1.2 seconds
    int rocketSpawnDelay = 5000;  

    lastSpawnTime = getCurrentTime() + jetSpawnDelay;           // Jet
    lastSpawnTime_xp = getCurrentTime() + xpSpawnDelay;         // XP
    lastSpawnTime_health = getCurrentTime() + healthSpawnDelay;
    lastSpawnTime_bird = getCurrentTime() + birdSpawnDelay;
    lastSpawnTime_rocket = getCurrentTime() + rocketSpawnDelay;


}

//checks the status of the game and draws screen accordingly 
void GameState::draw()

{
    if (status == STATUS_START) {
        drawStartScreen();
    }
    if (status == STATUS_PLAYING) {
        drawPlayingScreen();
    }
    if (status == STATUS_GAMEOVER) {
        drawOverScreen();
    }

}
//updates what the screen shows considering the status of the game 
void GameState::update(float dt)
{
    if (status == STATUS_START) {
        updateStartScreen(dt);

    }
    if (status == STATUS_PLAYING) {
        updatePlayingScreen(dt);
        
    }
    if (status == STATUS_GAMEOVER) {
        updateOverScreen(dt);
    }
}
//////////////////////==================================================================//////////////////////////////////////////
bool GameState::timeToSpawnJet()
{
    const int baseDelayInterval = 5000; //5 second in milliseconds

    double elapsedtime = getElapsedTime();
    double multiplier = 1.0;

    if (elapsedtime > 60) { //start changing frequency after 60 seconds
        //calculate how many 20-second intervals have passed since the 60-second mark
        int intervals = static_cast<int>((elapsedtime - 60) / 20);

        //start from 1.2 and increase by 0.2 for each interval,till 2.6
        multiplier = 1.2 + intervals * 0.2;
        if (multiplier > 2.6) {
            multiplier = 2.6;
        }
    }

    //adjust the delay interval based on the multiplier
    int delayInterval = static_cast<int>(baseDelayInterval / multiplier);

    int currentTime = getCurrentTime();
    
    if (currentTime - lastSpawnTime >= delayInterval) {
        lastSpawnTime = currentTime;
        int lastSpawnTime = 0;
        return true;
    }
    int lastSpawnTime = 0;
    return false;
}
bool GameState::timeToSpawnRocket()
{
    const int baseDelayInterval_rocket = 5000; //5 second in milliseconds

    double elapsedtime = getElapsedTime();
    double multiplier = 1.0;

    if (elapsedtime > 70) { //start changing frequency after 70 seconds
        //calculate how many 20-second intervals have passed since the 60-second mark
        int intervals = static_cast<int>((elapsedtime - 60) / 20);

        //start from 1.2 and increase by 0.2 for each interval,till 2.6
        multiplier = 1.2 + intervals * 0.2;
        if (multiplier > 2.6) {
            multiplier = 2.6;
        }
    }

    //adjust the delay interval based on the multiplier
    int delayInterval = static_cast<int>(baseDelayInterval_rocket / multiplier);

    if (elapsedtime >= 70){
        int currentTime_rocket = getCurrentTime();
        if (currentTime_rocket - lastSpawnTime_rocket >= delayInterval) {
            lastSpawnTime_rocket = currentTime_rocket;
            int lastSpawnTime_rocket = 0;
            return true;
        }
    }
    int lastSpawnTime_rocket = 0;
    return false;
}
bool GameState::timeToSpawnHealth()
{
    const int delayInterval_health = 20000; //20 second in milliseconds

    int currentTime_health = getCurrentTime();
    if (currentTime_health - lastSpawnTime_health >= delayInterval_health) {
        lastSpawnTime_health = currentTime_health;
        int lastSpawnTime_health = 0;
        return true;
    }
    int lastSpawnTime_health = 0;
    return false;
}
bool GameState::timeToSpawnXp() {
    const int basedelayInterval_xp = 6000; //6 second in milliseconds
    double elapsedtime = getElapsedTime();
    double multiplier = 1.0;

    if (elapsedtime > 40) { //start changing frequency after 40 seconds
        //calculate how many 20-second intervals have passed since the 60-second mark
        int intervals = static_cast<int>((elapsedtime - 60) / 20);

        //start from 1.2 and increase by 0.2 for each interval,till 2.6
        multiplier = 1.2 + intervals * 0.2;
        if (multiplier > 2.6) {
            multiplier = 2.6;
        }
    }

    //adjust the delay interval based on the multiplier
    int delayInterval_xp = static_cast<int>(basedelayInterval_xp / multiplier);

    int currentTime_xp = getCurrentTime();
    if (currentTime_xp - lastSpawnTime_xp >= delayInterval_xp) {
        lastSpawnTime_xp = currentTime_xp;
        int lastSpawnTime_xp = 0;
        return true;
    }
    int lastSpawnTime_xp = 0;
    return false;
}
bool GameState::timeToSpawnBird() {
    const int basedelayInterval_bird = 5000; //5 second in milliseconds
    double elapsedtime = getElapsedTime();
    
    double multiplier = 1.0;

    if (elapsedtime > 60) { //start changing frequency after 60 seconds
        //calculate how many 20-second intervals have passed since the 60-second mark
        int intervals = static_cast<int>((elapsedtime - 60) / 20);

        //start from 1.2 and increase by 0.2 for each interval,till 2.6
        multiplier = 1.2 + intervals * 0.2;
        if (multiplier > 2.6) {
            multiplier = 2.6;
        }
    }

    //adjust the delay interval based on the multiplier
    int delayInterval_bird = static_cast<int>(basedelayInterval_bird / multiplier);

    int currentTime_bird = getCurrentTime();
    if (currentTime_bird - lastSpawnTime_bird >= delayInterval_bird) {
        lastSpawnTime_bird = currentTime_bird;
        int lastSpawnTime_bird = 0;
        return true;
    }
    int lastSpawnTime_bird = 0;
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void GameState::spawnJet()
{
    Jet* jet = new Jet("Jet");
    jet->init();
    m_dynamic_objects.push_back(jet);
}
void GameState::spawnRocket()
{
    Rocket* rocket = new Rocket("Rocket");
    rocket->init();
    m_dynamic_rocket.push_back(rocket);
}
void GameState::spawnHealth()
{
    Health* health = new Health("Health");
    health->init();
    m_dynamic_health.push_back(health);
}
void GameState::spawnXp() {
    Xp* xp = new Xp("XP");
    xp->init();
    m_dynamic_xp.push_back(xp);
}
void GameState::spawnBird() {
    Bird* bird = new Bird("Bird");
    bird->init();
    m_dynamic_bird.push_back(bird);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void GameState::playBackgroundMusic() {
    //plays the backround music and notes that music has started playing 
    if (!musicPlaying) {
        graphics::playMusic(GameState::getInstance()->getFullAssetPath("Lsound.mp3"), 1.0f, true, 0);
        musicPlaying = true;
    }
}
//stops the music
void GameState::stopBackgroundMusic() {
    graphics::stopMusic();
    musicPlaying = false;

}
//while game is being played, music is also playing in the backround 
void GameState::playGameOverMusic() {
    if (!musicPlaying) {
        graphics::playMusic(GameState::getInstance()->getFullAssetPath("GameOver.mp3"), 1.0f, true, 0);
        musicPlaying = true;
    }
}
//stops the music
void GameState::stopGameOverMusic() {
    graphics::stopMusic();
    musicPlaying = false;
}
//plays the starting screen music and notes that music has started playing 
void GameState::playStartMusic() {
    if (!musicPlaying) {
        graphics::playMusic(GameState::getInstance()->getFullAssetPath("Start.mp3"), 1.0f, true, 0);
        musicPlaying = true;
    }
}
//stops the music
void GameState::stopStartMusic() {
    graphics::stopMusic();
    musicPlaying = false;
}
//this method returns the currect time in milliseconds that the game has been running for 
int GameState::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
//ensures that only one instance of the GameState class exists while the game is running 
GameState* GameState::getInstance() {
    if (m_unique_instance == nullptr)
        m_unique_instance = new GameState();

    return m_unique_instance;
}

GameState* GameState::m_unique_instance = nullptr;
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void GameState::updatePlayingScreen(float dt) {
    int playerHealth = m_player->getHealth();
    //if player doesnt have any health then game over 
    if (playerHealth == 0) {
        status = STATUS_GAMEOVER;
        stopBackgroundMusic();
        playGameOverMusic();
        return;
    }
    
    if (dt > 500) // Adjust as needed
        return;

    if (!m_current_level)
        return;

    m_current_level->update(dt);

    //check if its time to spawn a new Jet
    if (timeToSpawnJet()) {
        spawnJet();
    }
    //check if its time to spawn a new Rocket
    if (timeToSpawnRocket()) {
        spawnRocket();
    }
    //check if its time to spawn a new Health
    if (timeToSpawnHealth()) {
        spawnHealth();
    }
    //check if its time to spawn a new Xp
    if (timeToSpawnXp()) {
        spawnXp();
    }
    //check if its time to spawn a new Bird
    if (timeToSpawnBird()) {
        spawnBird();
    }

    //update all active Jet objects and remove objects that move beyond the screen boundaries
    for (auto it = m_dynamic_rocket.begin(); it != m_dynamic_rocket.end(); ) {
        Rocket* obj = *it;
        if (obj->isActive()) {
            obj->update(dt);
            //check if the object is outside the screen boundaries
            if (obj->getY() > m_canvas_height+5.0f) {
                delete obj; //delete the object
                it = m_dynamic_rocket.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            //check for collision with the player
            if (m_player->hitsRocket(*obj)) {
                delete obj; //delete the rocket object
                it = m_dynamic_rocket.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            ++it; //move to the next object
        }
        else {
            delete obj; //delete the inactive object
            it = m_dynamic_rocket.erase(it); //remove it from the list
        }
    }
    for (auto it = m_dynamic_objects.begin(); it != m_dynamic_objects.end(); ) {
        Jet* obj = *it;
        if (obj->isActive()) {
            obj->update(dt);
            //check if the object is outside the screen boundaries
            if (obj->getX() < 0 || obj->getX() > m_canvas_width + 5.0f || obj->getY() < 0 || obj->getY() > m_canvas_height + 5.0f) {
                delete obj; //delete the object
                it = m_dynamic_objects.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            //check for collision with the player
            if (m_player->hitsJet(*obj)) {
                delete obj; //delete the jet object
                it = m_dynamic_objects.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            ++it; //move to the next object
        }
        else {
            delete obj; //delete the inactive object
            it = m_dynamic_objects.erase(it); //remove it from the list
        }
    }
    for (auto it = m_dynamic_bird.begin(); it != m_dynamic_bird.end(); ) {
        Bird* obj = *it;
        if (obj->isActive()) {
            obj->update(dt);
            //check if the object is outside the screen boundaries
            if (obj->getX() < 0 || obj->getX() > m_canvas_width + 5.0f || obj->getY() < 0 || obj->getY() > m_canvas_height + 5.0f) {
                delete obj; //delete the object
                it = m_dynamic_bird.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            //check for collision with the player
            if (m_player->hitsBird(*obj)) {
                delete obj; //delete the birds object
                it = m_dynamic_bird.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            ++it; //move to the next object
        }
        else {
            delete obj; //delete the inactive object
            it = m_dynamic_bird.erase(it); //remove it from the list
        }
    }
    for (auto it = m_dynamic_health.begin(); it != m_dynamic_health.end(); ) {
        Health* obj = *it;
        if (obj->isActive()) {
            obj->update(dt);
            //check if the object is outside the screen boundaries
            if (obj->getX() < 0 || obj->getX() > m_canvas_width + 5.0f || obj->getY() < 0 || obj->getY() > m_canvas_height + 5.0f) {
                delete obj; //delete the object
                it = m_dynamic_health.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            //check for collision with the player
            if (m_player->hitsHealth(*obj)) {
                delete obj; //delete the Health object
                it = m_dynamic_health.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            ++it; //move to the next object
        }
        else {
            delete obj; //delete the inactive object
            it = m_dynamic_health.erase(it); //remove it from the list
        }
    }
    for (auto it = m_dynamic_xp.begin(); it != m_dynamic_xp.end(); ) {
        Xp* obj = *it;
        if (obj->isActive()) {
            obj->update(dt);
            //check if the object is outside the screen boundaries
            if (obj->getX() < 0 || obj->getX() > m_canvas_width + 5.0f || obj->getY() < 0 || obj->getY() > m_canvas_height + 5.0f) {
                delete obj; //delete the object
                it = m_dynamic_xp.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            //check for collision with the player
            if (m_player->hitsXp(*obj)) {
                delete obj; //delete the Xp object
                it = m_dynamic_xp.erase(it); //remove it from the list
                continue; //skip the rest of the loop iteration
            }
            ++it; //move to the next object
        }
        else {
            delete obj; //delete the inactive object
            it = m_dynamic_xp.erase(it); //remove it from the list
        }
    }



}
void GameState::updateStartScreen(float dt) {
    playStartMusic();
    if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
        status = STATUS_PLAYING;
        stopStartMusic();
        playBackgroundMusic();
        gameStartTime = std::chrono::steady_clock::now();
        timer->start();
        
    }
}
void GameState::updateOverScreen(float dt) {
    if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
        status = STATUS_PLAYING;
        stopGameOverMusic();
        playBackgroundMusic();
        gameStartTime = std::chrono::steady_clock::now();
        timer->start();
        resetGameState(); //restart the game
    }
}
void GameState::drawPlayingScreen() {
    if (!m_current_level)
        return;
    
    //set the canvas size to match the window size
    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    
    //used for timer
    
    graphics::Brush br;
    
    SETCOLOR(br.fill_color, 1, 0.4, 0);
    
    float timer_h = GameState::getInstance()->getCanvasHeight() - 14.75f;
    float timer_w = GameState::getInstance()->getCanvasWidth() / 2.0 - 4.0f;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count(); //assuming gameStartTime is a std::chrono::steady_clock::time_point representing the start time of the game

    std::stringstream ss;
    ss << "Time: " << std::setfill('0') << std::setw(2) << (elapsedTime / 60) << ":" << std::setw(2) << (elapsedTime % 60); //format elapsed time as minutes:seconds
    graphics::setFont(GameState::getInstance()->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(timer_w, timer_h, 0.5f, ss.str(), br);
    

     
    m_current_level->draw();
    m_zoh->draw();

    for (auto obj : m_dynamic_objects) {
        if (obj->isActive())
            obj->draw();
    }
    for (auto obj : m_dynamic_health) {
        if (obj->isActive())
            obj->draw();
    }
    for (auto obj : m_dynamic_xp) {
        if (obj->isActive())
            obj->draw();
    }
    for (auto obj : m_dynamic_rocket) {
        if (obj->isActive())
            obj->draw();
    }
    for (auto obj : m_dynamic_bird) {
        if (obj->isActive())
            obj->draw();
    }

}
void GameState::drawStartScreen() {
    static bool fadeIn = true;
    static float fadeSpeed = 1.0f; //adjust the speed of fading as needed
    static float opacity = 0.0f;
    //fixing a basic highscore logic
    
    
    static std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

    //calculate time elapsed since last update
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastUpdateTime);
    lastUpdateTime = currentTime;

    if (fadeIn) {
        opacity += fadeSpeed * deltaTime.count();
        if (opacity >= 1.0f) {
            opacity = 1.0f;
            fadeIn = false;
        }
    }
    else {
        opacity -= fadeSpeed * deltaTime.count();
        if (opacity <= 0.0f) {
            opacity = 0.0f;
            fadeIn = true;
        }
    }

    graphics::Brush loading;
    graphics::Brush loading1;
    SETCOLOR(loading1.fill_color, 0, 0, 0);

    float windowWidth = 1000.0f;
    float windowHeight = 800.0f;

    float w = GameState::getInstance()->getCanvasWidth()+3.0f;
    float h = GameState::getInstance()->getCanvasHeight()+3.0f;

    float text_h = GameState::getInstance()->getCanvasHeight() / 2.0f + 3.0f;
    float text_w = GameState::getInstance()->getCanvasWidth() / 2.0 - 3.5f;

    loading.outline_opacity = 0.0f;
    loading.texture = GameState::getInstance()->getFullAssetPath("Start.png");
    //set opacity for the image

    graphics::drawRect(w / 2.0f, h / 2.0f, w, h, loading);

    
    std::string print_txt = "Press ENTER to start the game";

    loading1.fill_opacity = opacity; //set opacity for the text
    graphics::setFont(GameState::getInstance()->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(text_w, text_h, 0.5f, print_txt, loading1);
}
void GameState::drawOverScreen() {
    static bool fadeIn = true;
    static float fadeSpeed = 1.0f; //adjust the speed of fading as needed
    static float opacity = 0.0f;
    static std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

    int total_xp = m_player->getHighScore();
    int xp = m_player->getXp();
    std::string print_xp = "Your High score is: " + std::to_string(total_xp);
    std::string print_thisxp = "This time you got: " + std::to_string(xp);

    //calculate time elapsed since last update
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastUpdateTime);
    lastUpdateTime = currentTime;

    if (fadeIn) {
        opacity += fadeSpeed * deltaTime.count();
        if (opacity >= 1.0f) {
            opacity = 1.0f;
            fadeIn = false;
        }
    }
    else {
        opacity -= fadeSpeed * deltaTime.count();
        if (opacity <= 0.0f) {
            opacity = 0.0f;
            fadeIn = true;
        }
    }

    graphics::Brush loading;
    graphics::Brush loading1;
    graphics::Brush drawxp;
    graphics::Brush drawthisxp;
    SETCOLOR(drawxp.fill_color, 1, 1, 0);
    SETCOLOR(drawthisxp.fill_color, 1, 1, 0);
    SETCOLOR(loading1.fill_color, 1, 0, 0);

    float windowWidth = 1000.0f;
    float windowHeight = 800.0f;

    float w = 20.0f;
    float h = 16.0f;

    float text_h = GameState::getInstance()->getCanvasHeight() / 2.0f + 5.0f;
    float text_w = GameState::getInstance()->getCanvasWidth() / 2.0 - 3.5f;

    loading.outline_opacity = 0.0f;
    loading.texture = GameState::getInstance()->getFullAssetPath("GameOver.png");
    //set opacity for the image

    graphics::drawRect(w / 2.0f, h / 2.0f, w * 1.1f, h * 1.1f, loading);
    std::string print_txt = "Press ENTER to restart the game";


    loading1.fill_opacity = opacity; // Set opacity for the text
    drawthisxp.fill_opacity = opacity;
    graphics::setFont(GameState::getInstance()->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(text_w+0.5, text_h, 0.5f, print_txt, loading1);
    
    graphics::setFont(GameState::getInstance()->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(text_w+1.49f, text_h-11.5f, 0.55f, print_xp, drawxp);
    
    graphics::setFont(GameState::getInstance()->getFullAssetPath("Sportzan.ttf"));
    graphics::drawText(text_w+1.75f, text_h -10.5f, 0.5f, print_thisxp, drawthisxp);
}

void GameState::resetGameState() {
    //eeset game state to initial conditions
    //status = STATUS_START;

    //clear all dynamic objects
    for (auto obj : m_dynamic_objects) {
        delete obj;
    }
    m_dynamic_objects.clear();

    for (auto obj : m_dynamic_health) {
        delete obj;
    }
    m_dynamic_health.clear();

    for (auto obj : m_dynamic_xp) {
        delete obj;
    }
    m_dynamic_xp.clear();

    for (auto obj : m_dynamic_bird) {
        delete obj;
    }
    m_dynamic_bird.clear();
    for (auto obj : m_dynamic_rocket) {
        delete obj;
    }
    m_dynamic_rocket.clear();

    //reset spawn times
    int jetSpawnDelay = 1200;
    int xpSpawnDelay = 1900;
    int healthSpawnDelay = 5000;
    int birdSpawnDelay = 1200;

    lastSpawnTime = getCurrentTime() + jetSpawnDelay;
    lastSpawnTime_xp = getCurrentTime() + xpSpawnDelay;
    lastSpawnTime_health = getCurrentTime() + healthSpawnDelay;
    lastSpawnTime_bird = getCurrentTime() + birdSpawnDelay;
    
    m_player->reset();
    m_player->init();
    
}
double GameState::getElapsedTime() {
    return timer->getElapsedTime();
}


GameState::~GameState()
{
    if (m_player)
        delete m_player;
    if (m_current_level)
        delete m_current_level;
    for (auto obj : m_dynamic_objects) {
        delete obj;
    }
    for (auto obj : m_dynamic_health) {
        delete obj;
    }
    for (auto obj : m_dynamic_xp) {
        delete obj;
    }
    for (auto obj : m_dynamic_rocket) {
        delete obj;
    }
    for (auto obj : m_dynamic_bird) {
        delete obj;
    }
}
