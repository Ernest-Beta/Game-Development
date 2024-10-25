#pragma once

#include <string>
#include <sgg/graphics.h>
#include "level.h"
#include "Jet.h"
#include "xp.h"
#include"zoh.h"
#include"health.h"
#include"Bird.h"
#include"rocket.h"
#include <vector>
#include <ctime>
#include <chrono>
#include <list>
#include"timer.h"
#include"player.h"
class GameState {
    
private:
    std::string m_asset_path = "assets\\";
    typedef enum {STATUS_START, STATUS_PLAYING, STATUS_GAMEOVER} status_t;
    float m_canvas_width = 20.0f;
    float m_canvas_height = 16.0f;
    float m_spawn_interval;
    const int MAX_JETS = 5; //maximum number of Jets
    int num_active_jets = 0; //number of active Jets
    
    status_t status = STATUS_START;
    bool musicPlaying = false;
    bool startPlaying = false;
    bool overPlaying = false;

    void updateStartScreen(float dt);
    void updatePlayingScreen(float dt);
    void updateOverScreen(float dt);
    void resetGameState();
    void drawStartScreen();
    void drawPlayingScreen();
    void drawOverScreen();
    


    static GameState* m_unique_instance;
    GameState();
    
    class Timer* timer = nullptr;
    class Player* m_player = nullptr;
    class Level* m_current_level = nullptr;
    class Zoh* m_zoh = nullptr;
    class Rocket* rocket = nullptr;
    class XP* m_xp = nullptr;
    
    std::list<Rocket*>m_dynamic_rocket;
    std::list<Jet*> m_dynamic_objects;
    std::list<Health*> m_dynamic_health;
    std::list<Xp*> m_dynamic_xp;
    std::list<Bird*>m_dynamic_bird;
    
    

    //time tracking for object spawning
    int m_last_spawn_time = 0;

    

public:
    float m_global_offset_x = 0.0f;
    float m_global_offset_y = 0.0f;
    bool m_debugging = false;
    int lastSpawnTime;
    int lastSpawnTime_health;
    int lastSpawnTime_xp;
    int lastSpawnTime_bird;
    int lastSpawnTime_rocket;

    void init();
    void draw();
    void update(float dt);

    double getElapsedTime();

    void spawnJet();
    void spawnHealth();
    void spawnXp();
    void spawnBird();
    void spawnRocket();

    void playStartMusic();
    void stopStartMusic();
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void playGameOverMusic();
    void stopGameOverMusic();

    static GameState* getInstance();

    ~GameState();

    float getCanvasWidth() { return m_canvas_width; }
    float getCanvasHeight() { return m_canvas_height; }

    std::string getAssetDir() { return m_asset_path; }
    std::string getFullAssetPath(const std::string& asset) { return m_asset_path + asset; }

    class Player* getPlayer() { return m_player; }

    int getCurrentTime();
    
    bool timeToSpawnJet();
    bool timeToSpawnHealth();
    bool timeToSpawnXp();
    bool timeToSpawnBird();
    bool timeToSpawnRocket();
    
};
