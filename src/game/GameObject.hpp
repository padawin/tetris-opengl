#ifndef __OBJECT__
#define __OBJECT__

#include <memory>
#include "GameObjectRenderer.hpp"
#include "Camera.hpp"

class GameObject {
	protected:
	std::shared_ptr<GameObjectRenderer> m_renderer = 0;
	float m_iX = 0.0f;
	float m_iY = 0.0f;
	float m_iZ = 0.0f;
	float m_iAngleX = 0.0f;
	float m_iAngleY = 0.0f;
	float m_iAngleZ = 0.0f;
	float m_iScaleX = 1.0f;
	float m_iScaleY = 1.0f;
	float m_iScaleZ = 1.0f;

	public:
	virtual ~GameObject() {}
	virtual void init() {};
	virtual void setPos(float x, float y, float z);
	virtual float getX() const;
	virtual float getY() const;
	virtual float getZ() const;
	virtual void update();
	virtual void render(std::shared_ptr<Camera> camera);
};

#endif
