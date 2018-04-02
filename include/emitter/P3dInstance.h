#pragma once

#include <boost/noncopyable.hpp>

#include <array>

struct p3d_emitter;

namespace et
{

class P3dTemplate;
class P3dRenderParams;

class P3dInstance : boost::noncopyable
{
public:
	P3dInstance(const P3dTemplate& cfg);
	~P3dInstance();

	bool Update();
	void Draw(const P3dRenderParams& rp, bool alone) const;

	void Start();
	void Stop();

	void Pause();
	void Resume();

	void Clear();

	bool IsLocal() const { return m_local; }
	
	void SetPos(float x, float y);

private:
	p3d_emitter* m_et;

	float m_mat[6];

	bool m_local;

	bool m_active;

}; // P3dInstance

}