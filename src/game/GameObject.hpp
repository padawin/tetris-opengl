#ifndef __OBJECT__
#define __OBJECT__

#include <memory>
#include "GameObjectRenderer.hpp"

class GameObject {
	protected:
	std::shared_ptr<GameObjectRenderer> m_renderer = 0;
	float m_iX = 0.0f;
	float m_iY = 0.0f;

	public:
	virtual ~GameObject() {}
	virtual void init() {};
	virtual void setPos(float x, float y);
	virtual float getX() const;
	virtual float getY() const;
	virtual void render();
};

#endif
