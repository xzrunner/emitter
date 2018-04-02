#include "emitter/P3dInstance.h"
#include "emitter/P3dTemplate.h"
#include "emitter/P3dRenderParams.h"
#include "emitter/GlobalClock.h"

#include <ps_3d.h>

namespace et
{

P3dInstance::P3dInstance(const P3dTemplate& cfg)
	: m_et(nullptr)
	, m_local(false)
	, m_active(false)
{
	m_et = p3d_emitter_create(cfg.GetCfg());

	memset(m_mat, 0, sizeof(m_mat));
	m_mat[0] = m_mat[3] = 1;
}

P3dInstance::~P3dInstance()
{
	p3d_emitter_release(m_et);
}

bool P3dInstance::Update()
{
	if (!m_et || !m_active) {
		return false;
	}

	float curr_time = GlobalClock::Instance()->GetTime();
	if (m_et->time == 0)
	{
		m_et->time = curr_time;
		return false;
	}

	if (m_et->time >= curr_time) {
		return false;
	}

	p3d_emitter_update(m_et, curr_time - m_et->time, m_mat);
	m_et->time = curr_time;

	return true;
}

void P3dInstance::Draw(const P3dRenderParams& rp, bool alone) const
{
	if (!m_et || !m_active) {
		return;
	}

	P3dRenderParams rp_child(rp);
	if (alone) {
		memcpy(rp_child.mat.x, m_mat, sizeof(m_mat));
	}
	rp_child.local = m_local;

	p3d_emitter_draw(m_et, &rp_child);
}

void P3dInstance::Start()
{
	m_active = true;
	m_et->time = GlobalClock::Instance()->GetTime();
	p3d_emitter_start(m_et);
}

void P3dInstance::Stop()
{
	m_active = false;
	if (m_et) {
		p3d_emitter_stop(m_et);
		p3d_emitter_clear(m_et);
	}
}

void P3dInstance::Pause()
{
	m_active = false;
	if (m_et) {
		p3d_emitter_pause(m_et);
	}
}

void P3dInstance::Resume()
{
	m_active = true;
	if (m_et) {
		p3d_emitter_resume(m_et);
	}
}

void P3dInstance::Clear()
{
	if (m_et) {
		p3d_emitter_clear(m_et);
	}
}

bool P3dInstance::IsLoop() const
{
	return m_et ? true : m_et->loop;
}

void P3dInstance::SetLoop(bool loop)
{
	if (m_et) {
		m_et->loop = loop;
	}
}

void P3dInstance::SetPos(float x, float y)
{
	m_mat[4] = x;
	m_mat[5] = y;
}

}