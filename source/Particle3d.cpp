#include "emitter/Particle3d.h"
#include "emitter/P3dRenderParams.h"

#include <guard/check.h>
#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>
#include <painting2/FastBlendMode.h>
#include <node0/CompAsset.h>
#include <node2/RenderSystem.h>
#include <ps_3d.h>

namespace
{

void blend_begin_func(int blend)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	switch (blend)
	{
	case pt2::FBM_NULL:
		rc.SetBlend(2, 6);      // BLEND_GL_ONE, BLEND_GL_ONE_MINUS_SRC_ALPHA
		rc.SetBlendEquation(0); // BLEND_FUNC_ADD
		break;
	case pt2::FBM_ADD:
		rc.SetBlend(2, 2);      // BLEND_GL_ONE, BLEND_GL_ONE
		rc.SetBlendEquation(0); // BLEND_FUNC_ADD
		break;
	case pt2::FBM_SUBTRACT:
		rc.SetBlend(2, 6);      // BLEND_GL_ONE, BLEND_GL_ONE_MINUS_SRC_ALPHA
		rc.SetBlendEquation(1); // BLEND_FUNC_SUBTRACT
		break;
	}
}

void blend_end_func()
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	rc.SetBlend(2, 6);		// BLEND_GL_ONE, BLEND_GL_ONE_MINUS_SRC_ALPHA
	rc.SetBlendEquation(0);	// BLEND_FUNC_ADD
}

void render_func(void* spr, void* sym, float* mat, float x, float y, float angle, float scale, 
	             struct ps_color* mul_col, struct ps_color* add_col, int fast_blend, const void* ud, float time)
{
	GD_ASSERT(ud, "null ud");
	const et::P3dRenderParams* rp = (static_cast<const et::P3dRenderParams*>(ud));

	n2::RenderParams rp_child;

	pt2::RenderColorCommon col;
	memcpy(&col.mul, mul_col, sizeof(col.mul));
	memcpy(&col.add, add_col, sizeof(col.add));
	rp_child.SetColor(rp->col * col);

	if (rp->local) 
	{
		// local mode, use node's mat
		rp_child.SetMatrix(rp->mat);
	} 
	else 
	{
		sm::Matrix2D _mat;
		memcpy(_mat.x, mat, sizeof(_mat.x));
		rp_child.SetMatrix(_mat);
	}

	if (spr) 
	{
		//Sprite* s2_spr = static_cast<Sprite*>(spr);
		//DrawNode::Draw(s2_spr, *rp_child);
	} 
	else if (sym) 
	{
		auto casset = static_cast<n0::CompAsset*>(sym);
		n2::RenderSystem::Draw(*casset, sm::vec2(x, y), angle, 
			sm::vec2(scale, scale), sm::vec2(0, 0), rp_child);
//		s2_sym->Update(UpdateParams(), time);
	}
}

static void
update_func(void* spr, float x, float y)
{
	//if (!spr) {
	//	return;
	//}

	//Sprite* s2_spr = static_cast<Sprite*>(spr);
	//UpdateParams up;
	//S2_MAT mat;
	//mat.Translate(x, y);
	//up.SetPrevMat(mat);
	//s2_spr->Update(up);
}

static void 
add_func(p3d_particle* p, void* ud)
{
//  	ParticleSystem* ps = (ParticleSystem*)ud;
//  	const sm::vec2& pos = ps->GetPosition();
//  	p->init_pos.x = pos.x;
//  	p->init_pos.y = pos.y;

	//////////////////////////////////////////////////////////////////////////

	//if (!p->ud) {
	//	Symbol* sym = static_cast<Symbol*>(p->cfg.sym->ud);
	//	switch (sym->Type())
	//	{
	//	case SYM_TRAIL:
	//		{
	//			TrailSprite* s2_spr = new TrailSprite(sym);
	//			s2_spr->SetInP3d();
	//			p->ud = static_cast<Sprite*>(s2_spr);
	//		}
	//		break;
	//	case SYM_PARTICLE3D:
	//		{
	//			Sprite* s2_p3d = new Particle3dSprite(sym);
	//			p->ud = s2_p3d;
	//		}
	//		break;
	//	}
	//}
}

static void 
remove_func(p3d_particle* p, void* ud)
{
// 	ParticleSystem* ps = (ParticleSystem*)ud;
// 	if (ps) {
// 		ps->RemoveFromInvertRecord(p);
// 	}

	//////////////////////////////////////////////////////////////////////////

	//if (p->ud) {
	//	Sprite* spr = static_cast<Sprite*>(p->ud);
	//	spr->RemoveReference();
	//	p->ud = NULL;
	//}
}

}

namespace et
{

void Particle3d::Init()
{
	p3d_init();
	p3d_regist_cb(blend_begin_func, blend_end_func, 
		render_func, update_func, add_func, remove_func);
}

}