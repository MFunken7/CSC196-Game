#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"

void Player::Update(float dt)
{
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
		Weapon* weapon = new Weapon{ 400, transform, m_model };
		m_scene->Add(weapon);
		kiko::g_AudioSystem.PlayOneShot("laser");
	}
}
//if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
//	kiko::g_AudioSystem.PlayOneShot("laser");
//}