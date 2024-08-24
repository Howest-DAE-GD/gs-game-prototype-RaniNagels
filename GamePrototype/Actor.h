#pragma once
#include "Texture.h"

class Actor
{
public:
	Actor(const Point2f& pos);
	virtual void Draw() const;
	virtual void Update(float elapsedSec) = 0;

	static void SetBoundaries(const Rectf& boundaries);
	static void SetDoubleTexture(Texture* const texture_pointer);

	void SetDoubleState(bool is_double);

protected:
	static Rectf m_Boundaries;
	static Texture* m_pTexture;

	float m_Size;
	int m_Speed;
	int m_Health;
	Point2f m_Position;

	Color4f m_FillColor;
	Color4f m_EdgeColor;

	bool m_IsDouble;
};

