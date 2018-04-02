#include "emitter/P3dTemplate.h"

#include <guard/check.h>
#include <ps_3d.h>
#include <sm_const.h>

#include <string.h>

namespace et
{

P3dTemplate::P3dTemplate(int max_sym_count)
	: m_sym_cap(max_sym_count)
{
	int sz = SIZEOF_P3D_EMITTER_CFG + SIZEOF_P3D_SYMBOL * max_sym_count;
	m_cfg = (p3d_emitter_cfg*) operator new(sz);
	memset(m_cfg, 0, sz);
	m_cfg->syms = (p3d_symbol*)(m_cfg + 1);
}

P3dTemplate::~P3dTemplate()
{
	delete m_cfg;
}

p3d_symbol* P3dTemplate::AddSymbol(const n0::CompAssetPtr& casset)
{
	if (!casset) {
		return nullptr;
	}
	GD_ASSERT(m_cfg->sym_count < m_sym_cap - 1, "full");

	p3d_symbol& sym = m_cfg->syms[m_cfg->sym_count++];
	memset(&sym, 0, SIZEOF_P3D_SYMBOL);

	sym.scale_start = sym.scale_end = 1;

	sym.mul_col_begin.r = sym.mul_col_begin.g = sym.mul_col_begin.b = sym.mul_col_begin.a = 255;
	sym.mul_col_end.r = sym.mul_col_end.g = sym.mul_col_end.b = sym.mul_col_end.a = 255;
	sym.add_col_begin.r = sym.add_col_begin.g = sym.add_col_begin.b = sym.add_col_begin.a = 0;
	sym.add_col_end.r = sym.add_col_end.g = sym.add_col_end.b = sym.add_col_end.a = 0;

	m_cached.push_back(casset);

	sym.ud = casset.get();

	return &sym;
}

void P3dTemplate::RemoveAllSymbols()
{
	m_cfg->sym_count = 0;
	m_cached.clear();
}

void P3dTemplate::SetHori(int min, int max)
{
	m_cfg->hori     = (min + max) * 0.5f * SM_DEG_TO_RAD;
	m_cfg->hori_var = (max - min) * 0.5f * SM_DEG_TO_RAD;
}

void P3dTemplate::SetVert(int min, int max)
{
	m_cfg->vert     = (min + max) * 0.5f * SM_DEG_TO_RAD;
	m_cfg->vert_var = (max - min) * 0.5f * SM_DEG_TO_RAD;
}

void P3dTemplate::SetGround(int ground)
{
	m_cfg->ground = ground;
}

}