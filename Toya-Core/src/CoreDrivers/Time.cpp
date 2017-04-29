#include "Time.hpp"


namespace Toya {
	namespace CoreDrivers
	{

		double Time::deltaTime;
		unsigned int Time::m_FPS;
		float Time::m_FpsTime = 0;
		float Time::m_CurrentTime;
		float Time::m_StartTime;
		double Time::FrameTime;
		double Time::CurrentTime()
		{
			return glfwGetTime();
		}

		void Time::UpdateTime(double pTime)
		{
			deltaTime = pTime;
			++m_FPS;
			if(Elapsed() - m_FpsTime > 1.0f)
			{
				m_FpsTime += 1.0f;
				FrameTime = 1000.0f / static_cast<double>(m_FPS);
				fprintf(stdout, "FPS %d\n", m_FPS);
				m_FPS = 0;
			}
		}
		float Time::Elapsed()
		{
			return CurrentTime() - m_StartTime;
		}
		Time::Time()
		{
			deltaTime = 0;
			m_StartTime = CurrentTime();
		}
		Time::~Time()
		{
			
		}
	}
}
