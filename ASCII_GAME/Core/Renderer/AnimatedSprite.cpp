#include "AnimatedSprite.h"
#include "../Utils.h"

AnimatedSprite::AnimatedSprite()
:m_bInitialised(false)
,m_CurrentAnimationFrame(0)
,m_NumAnimationFrames(0)
,m_AnimationFrames(NULL)
{

}

AnimatedSprite::~AnimatedSprite()
{
	SAFE_DELETE_ARY(m_AnimationFrames);
}

void AnimatedSprite::Initialise(int* pixels, Vector3& size)
{
	m_NumAnimationFrames = size.z;
	m_AnimationFrames = new Sprite[m_NumAnimationFrames];
	for (int frameNum= 0; frameNum < m_NumAnimationFrames; frameNum++)
	{
		m_AnimationFrames[frameNum].Initialise(pixels + (frameNum*(size.x*size.y)), Vector2(size.x, size.y));
	}

	m_bInitialised = true;
}

void AnimatedSprite::Initialise(CHAR_INFO* pixels, Vector3& size)
{
	m_NumAnimationFrames = size.z;
	m_AnimationFrames = new Sprite[m_NumAnimationFrames];
	for (int frameNum = 0; frameNum < m_NumAnimationFrames; frameNum++)
	{
		m_AnimationFrames[frameNum].Initialise(pixels + (frameNum*(size.x*size.y)), Vector2(size.x, size.y));
	}

	m_bInitialised = true;
}

void AnimatedSprite::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	if(m_CurrentAnimationFrame >= 0 && m_CurrentAnimationFrame < m_NumAnimationFrames)
		m_AnimationFrames[m_CurrentAnimationFrame].Render(pRenderer);
}

void AnimatedSprite::SetPosition(int x, int y)
{ 
	m_Position.x = x;
	m_Position.y = y;

	for (int i = 0; i < m_NumAnimationFrames; i++)
	{
		m_AnimationFrames[i].SetPosition(x, y);
	}
}

void AnimatedSprite::SetPosition(Vector2& position)
{
	m_Position = position;

	for (int i = 0; i < m_NumAnimationFrames; i++)
	{
		m_AnimationFrames[i].SetPosition(position);
	}
}

Vector2 AnimatedSprite::GetPosition()
{
	return m_Position;
}

Vector2 AnimatedSprite::GetSize()
{ 
	if (m_CurrentAnimationFrame >= 0 && m_CurrentAnimationFrame < m_NumAnimationFrames)
		return m_AnimationFrames[m_CurrentAnimationFrame].GetSize();

	return Vector2(0, 0);
}

bool AnimatedSprite::Collides(Sprite& otherSprite)
{
	if (m_CurrentAnimationFrame >= 0 && m_CurrentAnimationFrame < m_NumAnimationFrames)
		return m_AnimationFrames[m_CurrentAnimationFrame].Collides(otherSprite);

	return false;
}

Sprite& AnimatedSprite::GetCurrentSprite()
{
	return m_AnimationFrames[m_CurrentAnimationFrame];
}
