#pragma once
class Texture;


class Player
{
public:
	Player();
	Player(float x, float y);

	~Player();
	void Draw();
	void Update(float elapsedSec, bool jumpState);

private:
	static Texture *m_pTex;
	static int m_InstanceCounter;

	const float m_TexPartSize{ 25.0f };

	Point2f m_Pos;
	float m_JumpVelocity{5.0f};
	float m_Speed{ 10.0f };
	int m_FrameNr{};
	Rectf m_Frame;
};

