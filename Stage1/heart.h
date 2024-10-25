#pragma once
#include<vector>
#include<sgg/graphics.h>

class HealthBar {
private:
	int m_health;
	int m_maxHealth;
    int m_x;  //X position of the health bar
    int m_y;  //Y position of the health bar
    int m_barWidth;  //width of each health bar segment
    int m_barHeight;  //height of the health bar segments

public:
    HealthBar(int maxHealth, int x, int y, int barWidth, int barHeight);
    void draw();
    void update(int newHealth);
};