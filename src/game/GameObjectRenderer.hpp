#ifndef __GAME_OBJECT_RENDERER__
#define __GAME_OBJECT_RENDERER__

class GameObjectRenderer {
	public:
	virtual ~GameObjectRenderer() {}
	virtual void render() = 0;

	virtual void setScale(float x, float y, float z) = 0;
	virtual void setRotation(float x, float y, float z) = 0;
	virtual void setPosition(float x, float y, float z) = 0;
};

#endif
