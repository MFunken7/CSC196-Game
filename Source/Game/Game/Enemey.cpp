#include "Enemey.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Renderer/ModelManager.h"
#include "Player.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"


void Enemey::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() +kiko::HalfPi;
	}

	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_Renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_Renderer.GetHeight());

	m_fireTimer -= kiko::g_time.GetDeltaTime();

	if (m_fireTimer <= 0) {
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, transform, kiko::g_manager.Get("ship.txt"));
		weapon->m_tag = "EnemeyBullet";
		m_scene->Add(std::move(weapon));
		kiko::g_AudioSystem.PlayOneShot("laser");

		m_fireTimer = m_fireTime;
	}
}

void Enemey::OnCollission(Actor* other)
{
	if (other->m_tag == "PlayerBullet") {
		m_health -= 10;
		if (m_health <= 0) {
			m_destroyed = true;
		}
	}
}
