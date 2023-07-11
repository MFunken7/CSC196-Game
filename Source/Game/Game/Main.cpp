#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include <chrono>
#include <vector>

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
		m_pos += m_vel;
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
	kiko::seedRandom((unsigned int)time(nullptr));



	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	std::vector<kiko::vec2> points{{-10, 5}, { 10,5 }, { 0,-5 }, { -10, 5 }};
	kiko::Model model(points);

	kiko::vec2 v{5, 5};
	v.Nomalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos,vel));
	}

	bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		if (inputSystem.GetMouseButtonDown(0))
		{
			cout << "Left Mouse Button down." << endl;
		}if (inputSystem.GetMouseButtonDown(1))
		{
			cout << "Middle Mouse Button down." << endl;
		}
		if (inputSystem.GetMouseButtonDown(2))
		{
			cout << "Right Mouse Button down." << endl;
		}

		cout << inputSystem.GetMousePosition().x << ", " << inputSystem.GetMousePosition().y << endl;


		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for(auto& star : stars){
			star.Update(renderer.GetWidth(), renderer.GetHeight());

			
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(renderer);
		}
		
		model.Draw(renderer, {400,300}, 4);

		renderer.EndFrame();
	}

	return 0;
}