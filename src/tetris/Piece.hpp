#ifndef __PIECE__
#define __PIECE__

#include <vector>
#include "game/GameObject.hpp"

class Piece : public GameObject {
	protected:
	std::vector<glm::ivec2> m_vBlockCoordinates[4] = {};
	// From 0 to 3, represents the quarter of a circle
	int m_iOrientation = 0;
	glm::vec3 m_color = {0.0f, 0.0f, 0.0f};

	public:
	virtual ~Piece() {}
	std::vector<glm::ivec2> getBlocks() const;
	void rotate(int quarter);
	void render(std::shared_ptr<Camera> camera);
	virtual void init();
};

#endif
