#pragma once
class Actor
{
public:
	Actor(const Point2f& pos, const Rectf& boundaries);
	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;
protected:
	int m_Size;
	int m_Speed;
	Point2f m_Position;

	Rectf m_Boundaries;

	Color4f m_FillColor;
	Color4f m_EdgeColor;

	Color4f ConvertColor(int r, int g, int b);
};

