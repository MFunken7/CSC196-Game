#include "SpaceGame.h"
#include "Player.h"
#include "Enemey.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<kiko::Font>("BlackHanSans-Regular.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_Renderer, "SCORE 0000", kiko::Color{1, 1, 1, 1});

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_Renderer, "SPACE", kiko::Color{1, 1, 1, 1});
	//load audio
	kiko::g_AudioSystem.AddAudio("laser", "laser-gun.wav");

	m_scene = std::make_unique<kiko::Scene>();
	
	/*std::vector<Enemey> enemies;
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<Enemey> enemey = std::make_unique<Enemey>(10.0f, kiko::Pi, kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3 }, kiko::g_manager.Get("ship.txt"));
		enemey->m_tag = "Enemey";
		m_scene->Add(move(enemey));
	}*/

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(move(player));

	}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			std::unique_ptr<Enemey> enemey = std::make_unique<Enemey>(10.0f, kiko::Pi, kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3 }, kiko::g_manager.Get("ship.txt"));
			enemey->m_tag = "Enemey";
			enemey->m_game = this;
			m_scene->Add(move(enemey));
		}
		break;
	case SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;

		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_Renderer, "SCORE " + std::to_string(m_score), {1,1,1,1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_titleText->Draw(renderer, 350, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
}
