#pragma once
class Texture;

enum class Direction
{
	Stationary, Left, Right,
};

class Player
{
public:
	Player();
	Player(float x, float y);
	~Player();

	void Draw();
	void Update(float elapsedSec, float totalElapsedSec, float ground);
	

	bool GetJumpState();
	Direction GetRunState();
	bool GetAttackState();
	Point2f GetPos();

	void SetJumpState(bool newJS);
	void SetRunState(Direction newRS);
	void SetAttackState(bool newAS);

	void CheckJumpFrame();
	void CheckRunFrame();
	void CheckAttackFrame();

	void SetJumpVelocity(float NewJumpVel);
	void SetVelocity(float NewVel);

	float GetJumpVelocity();
	float GetVelocity();

private:
	static Texture *m_pTex;
	static int m_InstanceCounter;	
	const float m_TexPartSizeH{ 23.75f };
	const float m_TexPartSizeW{ 25.0f };
	
	int m_aFrameCounter{};
	int m_rFrameCounter{};

	Point2f m_Pos;
	Rectf m_Frame{ 0.0f,0.0f,m_TexPartSizeW,m_TexPartSizeW };

	const float m_JumpAcceleration{ 5.0f };
	const float m_Acceleration{ 100.0f };

	float m_JumpVelocity{m_JumpAcceleration};
	float m_Velocity{};

	
	int m_RunFrameNr{};
	int m_JumpFrameNr{};
	int m_AttackFrameNr{};

	bool m_JumpState{};
	bool m_AttackState{};
	bool m_Flipped{};

	Direction m_RunState{};
};
