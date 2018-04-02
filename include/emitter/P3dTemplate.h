#pragma once

#include <node0/typedef.h>

#include <boost/noncopyable.hpp>

#include <vector>

struct p3d_emitter_cfg;
struct p3d_symbol;

namespace et
{

class P3dTemplate : boost::noncopyable
{
public:
	P3dTemplate(int max_sym_count);
	~P3dTemplate();

	const p3d_emitter_cfg* GetCfg() const { return m_cfg; }
	p3d_emitter_cfg* GetCfg() { return m_cfg; }

	p3d_symbol* AddSymbol(const n0::CompAssetPtr& casset);
	void RemoveAllSymbols();

	void SetHori(int min, int max);
	void SetVert(int min, int max);

	void SetGround(int ground);

private:
	int m_sym_cap;

	p3d_emitter_cfg* m_cfg;

	std::vector<n0::CompAssetPtr> m_cached;

}; // P3dTemplate

}