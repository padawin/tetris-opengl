#ifndef __RECTANGLE__
#define __RECTANGLE__

#include <vector>

#include "ObjectRenderer.hpp"

class Rectangle {
	private:
	int m_iX = 0;
	int m_iY = 0;
	ObjectRenderer m_objectRenderer = ObjectRenderer();

	public:
	void init();
	void setPos(int x, int y);
	int getX() const;
	int getY() const;
	void render() const;
};

#endif
