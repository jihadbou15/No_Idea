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

	void SetJumpState(bool newJS);
	void SetRunState(Direction newRS);
	void SetAttackState(bool newAS);

	void CheckJumpFrame();
	void CheckRunFrame();
	void CheckAttackFrame();


private:
	static Texture *m_pTex;
	static int m_InstanceCounter;

	int m_aFrameCounter{};
	int m_rFrameCounter{};
	Point2f m_Pos;
	Rectf m_Frame;

	float m_JumpVelocity{ 1.0f };
	float m_Speed{ 100.0f };

	const float m_TexPartSizeH{ 23.75f };
	const float m_TexPartSizeW{ 24.66f };
	int m_RunFrameNr{};
	int m_JumpFrameNr{};
	int m_AttackFrameNr{};


	bool m_JumpState{};
	bool m_AttackState{};
	bool m_Flipped{};

	Direction m_RunState{};
};
