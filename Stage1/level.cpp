#include"level.h"
#include"gamestate.h"
#include"player.h"
#include<chrono>
#include<iomanip>
#include<sstream>

//The level should decide if the Player will be shown or not.


void Level::update(float dt)
{
	//Used for creating the moving forward effect by creating a sliding towards left background slider.
	for (int i = 0; i < 6; ++i) {
		m_background_positions[i] += m_background_speed * dt;

		//when a background moves off screen, reset its position to the right of the last background
		if (m_background_positions[i] < -m_state->getCanvasWidth()) {
			int rightmostIndex = (i == 0) ? 3 : i - 1; //find the rightmost background's index
			m_background_positions[i] = m_background_positions[rightmostIndex] + m_state->getCanvasWidth();
		}
	}
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);
	GameObject::update(dt);
}

void Level::init()
{
	for (int i = 0; i < 6; ++i) {
		m_brush_backgrounds[i].outline_opacity = 0.0f;
		m_brush_backgrounds[i].texture = m_state->getFullAssetPath("Winter" + std::to_string(i) + ".png");
	}
	
	

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();
}

void Level::draw()
{
	float windowWidth = m_state->getCanvasWidth();
	float windowHeight = m_state->getCanvasHeight();

	graphics::Brush br;
	
	//draw background
	for (int i = 0; i < 6; ++i) {
		graphics::drawRect(m_background_positions[i] + windowWidth / 2, windowHeight / 2,
			windowWidth+0.1, windowHeight+1.5, m_brush_backgrounds[i]);
	}

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->draw();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->draw();
	
}

Level::Level(const std::string& name)
{
	for (int i = 0; i < 6; ++i) {
		m_background_positions[i] = i * m_state->getCanvasWidth();
	}
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;
}