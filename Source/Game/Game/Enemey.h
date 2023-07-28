#pragma once
#include "Framework/Actor.h"


class Enemey : public kiko::Actor
{
public:
	Enemey(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTime = 3.0f;
		m_fireTimer = m_fireTime;
	}

	void Update(float dt) override;
	void OnCollission(Actor* other) override;

	bool GetFaceingPlayer() const { return m_faceingPlayer; }
	void SetFaceingPlayer(bool faceingPlayer) { m_faceingPlayer = faceingPlayer; }
private:
	float m_speed = 0;
	float m_turnRate = 0;

	bool m_faceingPlayer = false;

	float m_fireTime = 0;
	float m_fireTimer = 0;

	int m_health = 50;
};