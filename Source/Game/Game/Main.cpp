#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Core/Time.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemey.h"
#include "Renderer/Text.h"

#include <chrono>
#include <vector>
#include <thread>


using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{pos},
		m_vel{vel}
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x > width) {
			m_pos.x = 0;
		}
		if (m_pos.y > height) {
			m_pos.y = 0;
		}
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};


int main(int argc, char* argv[])
{

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");



	kiko::g_Renderer.Initialize();
	kiko::g_Renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_InputSystem.Initialize();

	kiko::g_AudioSystem.Initialize();
	kiko::g_AudioSystem.AddAudio("laser", "laser-gun.wav");

	// create font / text objects
	std::shared_ptr<kiko::Font> font = std::make_shared<kiko::Font>("BlackHanSans-Regular.ttf", 24);
	std::unique_ptr<kiko::Text> text = std::make_unique<kiko::Text>(font);
	text->Create(kiko::g_Renderer, "NEUMONT", kiko::Color{1, 1, 1, 1});


	//std::vector<kiko::vec2> points{{-10, 5}, { 10,5 }, { 0,-5 }, { -10, 5 }};


	

	kiko::vec2 v{5, 5};
	v.Nomalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(kiko::g_Renderer.GetWidth()), kiko::random(kiko::g_Renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(100, 40), 0.0f);

		stars.push_back(Star(pos,vel));
	}

	kiko::Scene scene;
	unique_ptr<Player> player = make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
	player->m_tag = "Player";
	scene.Add(move(player));

	std::vector<Enemey> enemies;
	for (int i = 0; i < 5; i++) {
		unique_ptr<Enemey> enemey = make_unique<Enemey>(10.0f, kiko::Pi, kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3 }, kiko::g_manager.Get("ship.txt"));
		enemey->m_tag = "Enemey";
		scene.Add(move(enemey));
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update engine
		kiko::g_time.Tick();
		kiko::g_InputSystem.Update();
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		//update
		kiko::g_AudioSystem.Update();
		scene.Update(kiko::g_time.GetDeltaTime());


		//if (kiko::g_InputSystem.GetMouseButtonDown(0))
		//{
		//	cout << "Left Mouse Button down." << endl;
		//}if (kiko::g_InputSystem.GetMouseButtonDown(1))
		//{
		//	cout << "Middle Mouse Button down." << endl;
		//}
		//if (kiko::g_InputSystem.GetMouseButtonDown(2))
		//{
		//	cout << "Right Mouse Button down." << endl;
		//}

		//cout << kiko::g_InputSystem.GetMousePosition().x << ", " << kiko::g_InputSystem.GetMousePosition().y << endl;

	
		

		/*kiko::vec2 direction;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
		transform.position += direction * speed * kiko::g_time.GetDeltaTime();*/


		//draw game
		kiko::g_Renderer.SetColor(0, 0, 0, 0);
		kiko::g_Renderer.BeginFrame();
		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for(auto& star : stars){
			star.Update(kiko::g_Renderer.GetWidth(), kiko::g_Renderer.GetHeight());

			
			kiko::g_Renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_Renderer);
		}


		kiko::g_Renderer.SetColor(255, 255, 255, 255);
		scene.Draw(kiko::g_Renderer);

		text->Draw(kiko::g_Renderer, 400, 300);

		kiko::g_Renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	scene.RemoveAll();

	return 0;
}