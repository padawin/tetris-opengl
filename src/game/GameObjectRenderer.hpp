#ifndef __GAME_OBJECT_RENDERER__
#define __GAME_OBJECT_RENDERER__

class GameObjectRenderer {
	public:
	virtual ~GameObjectRenderer() {}
	virtual void render() = 0;
};

#endif
