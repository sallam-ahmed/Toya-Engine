#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>

namespace Toya{
	namespace CoreDrivers
{
	
	class Time
	{
		static float m_StartTime;
		static float m_CurrentTime;
		static float m_Elapsed;
		static float m_FpsTime;
		static unsigned int m_FPS;
	public:
		static double deltaTime;
		static double CurrentTime();
		static void UpdateTime(double pTime);
		static float Elapsed();
		static double FrameTime;
		Time();
		~Time();
	};


} }
