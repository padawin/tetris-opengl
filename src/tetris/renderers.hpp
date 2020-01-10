#ifndef __RENDERERS__
#define __RENDERERS__

#include "opengl/ObjectRenderer.hpp"

void renderer_init2DSideRenderer(ObjectRenderer *renderer, int height);
void renderer_init2DPieceRenderer(ObjectRenderer *renderer);
void renderer_init3DSideRenderer(ObjectRenderer *renderer, int height);
void renderer_init3DPieceRenderer(ObjectRenderer *renderer);

#endif
