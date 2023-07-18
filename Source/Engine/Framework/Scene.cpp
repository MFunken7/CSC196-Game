#include "Scene.h"

namespace kiko
{
	void Scene::Update(float dt)
	{
		for (auto actor : m_actors) {
			actor->Update(dt);
		}
	}
	void Scene::Draw(Renderer& Renderer)
	{
		for (auto actor : m_actors) {
			actor->Draw(Renderer);
		}
	}
	void Scene::Add(Actor* actor)
	{
		actor->m_scene = this;
		m_actors.push_back(actor);
	}
	void Scene::Remove(Actor* actor)
	{
		m_actors.remove(actor);
	}
	void Scene::RemoveAll()
	{
	}
}