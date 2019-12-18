#ifndef __PIECE__
#define __PIECE__

#include <vector>
#include "game/GameObject.hpp"
#include "opengl/ObjectRenderer.hpp"

class Piece : public GameObject {
	protected:
	std::shared_ptr<GameObject> m_ghost = nullptr;
	std::vector<glm::ivec2> m_vBlockCoordinates[4] = {};
	// From 0 to 3, represents the quarter of a circle
	int m_iOrientation = 0;
	glm::vec3 m_color = {0.0f, 0.0f, 0.0f};

	void _render(std::shared_ptr<Camera> camera, ObjectRenderer *renderer, glm::vec3 position);

	public:
	virtual ~Piece() {}
	std::vector<glm::ivec2> getBlocks() const;
	void rotate(int quarter);
	void render(std::shared_ptr<Camera> camera, ObjectRenderer *renderer);
	virtual void init() = 0;

	void initGhost();
	std::shared_ptr<GameObject> getGhost();
};

#endif
