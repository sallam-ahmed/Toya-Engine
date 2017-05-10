#pragma once
#include "irrKlang.h"

#include "../Components/Base/Component.hpp"

namespace Toya
{
	namespace CoreDrivers
	{
		using namespace irrklang;
		class AudioSource : public Components::Component
		{
			ISoundEngine* m_SoundEngine;
		public:
			AudioSource(bool);
			AudioSource();
			~AudioSource()override;
			
			void Play(const char* filePath) const;
			void PlayOnce(const char* filePath) const;
			void Stop() const;
			void Update();
			bool Loop;
		};
	}
}
