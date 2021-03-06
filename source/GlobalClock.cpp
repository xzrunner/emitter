#include "emitter/GlobalClock.h"

namespace et
{

CU_SINGLETON_DEFINITION(GlobalClock)

GlobalClock::GlobalClock()
	: m_time(0)
{
}

void GlobalClock::Update(float dt)
{
	m_time += dt;
}

}