#pragma once

#include <vector>
#include <Windows.h>
#include "../Maths/Vector2.h"
#include "../Maths/Vector3.h"
#include "Sprite.h"

class ASCIIRenderer;

class AnimatedSprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	void Initialise(int* pixels, Vector3& size);
	void Initialise(CHAR_INFO* pixels, Vector3& size);

	void Render(ASCIIRenderer* pRenderer);

	void SetPosition(int x, int y);
	void SetPosition(Vector2& position);

	Vector2 GetPosition();
	Vector2 GetSize();

	bool Collides(Sprite& otherSprite);

	int  GetAnimationFrame() { return m_CurrentAnimationFrame;  }
	void SetAnimationFrame(int frameNum) { if (frameNum >= 0 && frameNum < m_NumAnimationFrames) { m_CurrentAnimationFrame = frameNum; } }

	Sprite& GetCurrentSprite();

private:

	Vector2 m_Position;

	Sprite* m_AnimationFrames;
	int m_NumAnimationFrames;
	int m_CurrentAnimationFrame;

	bool m_bInitialised;

};
