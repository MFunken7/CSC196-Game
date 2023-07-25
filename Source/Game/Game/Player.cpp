#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include"Renderer/ModelManager.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "SpaceGame.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_Renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_Renderer.GetHeight());

	if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f , transform, kiko::g_manager.Get("ship.txt"));
		weapon->m_tag = "PlayerBullet";
		m_scene->Add(std::move(weapon));
		kiko::g_AudioSystem.PlayOneShot("laser");
	}

}
void Player::OnCollission(Actor* other)
{
	if (other->m_tag == "EnemeyBullet") {
		m_health -= 10;
		if (m_health <= 0) {
			m_game->SetLives(m_game->GetLives() - 1);
			m_destroyed = true;
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
		}
	}
}
//if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
//	kiko::g_AudioSystem.PlayOneShot("laser");
//}