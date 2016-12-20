#pragma once
class Player
{
public:
	Player();
	Player(float x, float y);

	~Player();
	void Draw();
	void Update(float elapsedSec, bool jumpState, float Camera);
	void Move(bool leftState, bool rightState, bool borderRight);

	Point2f GivePlayerPos();

private:
	Point2f m_Pos;
	float m_JumpVelocity{5.0f};
	float m_Speed{ 10.0f };
};

