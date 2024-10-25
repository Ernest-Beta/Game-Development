#pragma once
#include "gameobject.h"
#include<sgg/graphics.h>
#include"Jet.h"
#include"rocket.h"
#include"xp.h"
#include"health.h"
#include "Bird.h"

class Player : public GameObject {
	graphics::Brush m_brush_player;
	std::vector<std::string>m_drako;
	int m_health;
	int m_experience;
	int highscore = 0;
	bool alreadyHitJet = false;
	bool alreadyHitHealth = false;
	bool alreadyHitXp = false;
	bool alreadyHitBird = false;
	bool alreadyHitRocket = false;
	float m_pos_x; //initial position x
	float m_pos_y; //initial position y
	float initial_velocity_x; //initial velocity x
	float initial_velocity_y;
	float m_width = 1.0f;
	float m_height = 1.0f;
	

public:
	Player() : GameObject(""), m_health(3),m_experience(0) {}
	Player(std::string name) : GameObject(name), m_health(3), m_experience(0) {}
	
	void update(float dt) override;
	void init() override;
	void draw() override;
	void reset() {
		m_health = 3;  //reset health to initial value
		m_experience = 0;  //reset experience to initial value
		alreadyHitJet = false;  //reset hit status
		alreadyHitHealth = false;
		alreadyHitXp = false;
		alreadyHitBird = false;
		alreadyHitRocket = false;
	}
	int getHealth() {
		return m_health;
	}
	void setHealth(int h) {
		this->m_health = h;
	}
	int getXp() {
		return m_experience;
	}
	void setXp(int xp) {
		this->m_experience = xp;
	}
	bool hitsJet(Jet& jet); //pass Jet by reference
	
	bool hasBeenHitJet() {
		return alreadyHitJet;
	}
	void HitGokuJet(bool hit) {
		this->alreadyHitJet = hit;
	}
	bool hitsRocket(Rocket& jet); 

	bool hasBeenHitRocket() {
		return alreadyHitRocket;
	}
	void HitGokuRocket(bool hit) {
		this->alreadyHitRocket = hit;
	}
	bool hitsHealth(Health& health); 
	
	bool hasBeenHitHealth() {
		return alreadyHitHealth;
	}
	void HitGokuHealth(bool hit) {
		this->alreadyHitHealth = hit;
	}
	bool hitsXp(Xp& xp); 
	
	bool hasBeenHitXp() {
		return alreadyHitXp;
	}
	void HitGokuXp(bool hit) {
		this->alreadyHitXp = hit;
	}
	bool hitsBird(Bird& bird); 
	
	bool hasBeenHitBird() {
		return alreadyHitBird;
	}
	void HitGokuBird(bool hit) {
		this->alreadyHitBird = hit;
	}
	int getHighScore() {
		if (m_experience > highscore) {
			highscore = m_experience;
			
		}
		return highscore;
	}
	
};
