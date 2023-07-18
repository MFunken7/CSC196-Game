#pragma once
#include <list>
#include "Actor.h"

namespace kiko {

	class Renderer;
	

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& Renderer);

		void Add(Actor* actor);
		void Remove(Actor* actor);
		void RemoveAll();

		friend class Scene;
	private:
		std::list<Actor*> m_actors;
	};
}