#include "SpaceGame.h"
#include "Player.h"
#include "Enemey.h"
#include "Asteroid.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<kiko::Font>("BlackHanSans-Regular.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_Renderer, "SCORE: 0000", kiko::Color{1, 1, 1, 1});

	m_livesText = std::make_unique<kiko::Text>(m_font);
	m_livesText->Create(kiko::g_Renderer, "LIVES: 0", kiko::Color{1, 1, 1, 1});

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_Renderer, "SPACE", kiko::Color{1, 1, 1, 1});

	m_gameOverText = std::make_unique<kiko::Text>(m_font);
	m_gameOverText->Create(kiko::g_Renderer, "GAME OVER", kiko::Color{1, 1, 1, 1});

	m_deadText = std::make_unique<kiko::Text>(m_font);
	m_deadText->Create(kiko::g_Renderer, "YOU ARE DEAD", kiko::Color{1, 1, 1, 1});


	//load audio
	kiko::g_AudioSystem.AddAudio("laser", "laser-gun.wav");
	kiko::g_AudioSystem.AddAudio("music", "music.wav");

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
		std::unique_ptr<Player> player = std::make_unique<Player>(10.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(move(player));

	}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;

		
		m_MultiplyerTimer -= dt;
 		if (m_MultiplyerTimer <= 0) {
			m_PointMultiplyer = 1;
		}


		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			std::unique_ptr<Enemey> enemey = std::make_unique<Enemey>(10.0f, kiko::Pi, kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 4 }, kiko::g_manager.Get("enemy.txt"));
			enemey->m_tag = "Enemey";
			enemey->m_game = this;
			m_scene->Add(move(enemey));

			std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(5.0f, kiko::randomf(6.0f,8.0f), kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 4 }, kiko::g_manager.Get("asteroid.txt"));
			asteroid->m_tag = "Asteroid";
			asteroid->m_game = this;
			m_scene->Add(move(asteroid));
		}

		


		

		break;
	case SpaceGame::eState::PlayerDeadStart:
		m_stateTimer = 450;
		if (m_lives == 0) { m_state = eState::GameOver; }
		else m_state = eState::PlayerDead;
		
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		

		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer == 0)
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_Renderer, "SCORE " + std::to_string(m_score), {1,1,1,1});
	m_livesText->Create(kiko::g_Renderer, "LIVES " + std::to_string(m_lives), {1,1,1,1});
 	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_titleText->Draw(renderer, 350, 300);
	}
	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(renderer, 350, 300);
	}
	if (m_state == eState::PlayerDead) {
		m_deadText->Draw(renderer, 300, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_livesText->Draw(renderer, 650, 40);
	kiko::g_particleSystem.Draw(renderer);
	m_scene->Draw(renderer);
}
