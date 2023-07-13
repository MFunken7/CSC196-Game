#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Core/Time.h"
#include "Actor.h"
#include "Player.h"
#include "Enemey.h"
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
	
	constexpr float a = kiko::DegreesToRadians(180.f);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");



	kiko::g_Renderer.Initialize();
	kiko::g_Renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_InputSystem.Initialize();

	//std::vector<kiko::vec2> points{{-10, 5}, { 10,5 }, { 0,-5 }, { -10, 5 }};
	kiko::Model model;

	model.Load("ship.txt");

	kiko::vec2 v{5, 5};
	v.Nomalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(kiko::g_Renderer.GetWidth()), kiko::random(kiko::g_Renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(100, 40), 0.0f);

		stars.push_back(Star(pos,vel));
	}

	kiko::Transform transform{ {400,300}, 0, 3 };

	float speed = 50;
	float turnRate = kiko::DegreesToRadians(180.0f);

	Player player{200, kiko::Pi, { {400, 300}, 0, 6 }, model };

	std::vector<Enemey> enemies;
	for (int i = 0; i < 10; i++) {
		Enemey enemey{ 20, kiko::Pi, { {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3}, model};
		enemies.push_back(enemey);
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
		player.Update(kiko::g_time.GetDeltaTime());
		for(auto& enemey : enemies) enemey.Update(kiko::g_time.GetDeltaTime());



		if (kiko::g_InputSystem.GetMouseButtonDown(0))
		{
			cout << "Left Mouse Button down." << endl;
		}if (kiko::g_InputSystem.GetMouseButtonDown(1))
		{
			cout << "Middle Mouse Button down." << endl;
		}
		if (kiko::g_InputSystem.GetMouseButtonDown(2))
		{
			cout << "Right Mouse Button down." << endl;
		}

		cout << kiko::g_InputSystem.GetMousePosition().x << ", " << kiko::g_InputSystem.GetMousePosition().y << endl;

		

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
		
		player.Draw(kiko::g_Renderer);
		for (auto& enemey : enemies) enemey.Draw(kiko::g_Renderer);

		kiko::g_Renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}