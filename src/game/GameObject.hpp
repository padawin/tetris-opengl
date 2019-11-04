#ifndef __OBJECT__
#define __OBJECT__

#include <memory>
#include "GameObjectRenderer.hpp"

class GameObject {
	protected:
	std::shared_ptr<GameObjectRenderer> m_renderer = 0;
	int m_iX = 0;
	int m_iY = 0;

	public:
	virtual ~GameObject() {}
	virtual void init() {};
	virtual void setPos(int x, int y);
	virtual int getX() const;
	virtual int getY() const;
	virtual void render();
};

#endif
