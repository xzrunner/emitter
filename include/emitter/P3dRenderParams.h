#pragma once

#include <SM_Matrix2D.h>
#include <painting2/RenderColorCommon.h>

namespace et
{

class P3dRenderParams
{
public:
	sm::Matrix2D mat;

	pt2::RenderColorCommon col;

	bool local;

public:
	P3dRenderParams() : local(true) {}

}; // P3dRenderParams

}