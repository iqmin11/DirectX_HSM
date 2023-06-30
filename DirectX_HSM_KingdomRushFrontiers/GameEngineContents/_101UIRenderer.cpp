#include "PrecompileHeader.h"
#include "_101UIRenderer.h"

_101UIRenderer::_101UIRenderer()
{

}

_101UIRenderer::~_101UIRenderer()
{

}

void _101UIRenderer::Start()
{
	PushCameraRender(101);
	SpriteRenderInit();
}
