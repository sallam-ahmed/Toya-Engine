#include "AudioSource.hpp"
#include <cstdio>
#include <cstdlib>

namespace Toya
{
	namespace CoreDrivers
	{
		AudioSource::AudioSource(bool loop = false)
		{
			m_SoundEngine = createIrrKlangDevice();
			
			if (!m_SoundEngine)
			{
				fprintf(stdout, "Error while initializing IrrKlang.\n");
				system("pause");
			}
			Loop = loop;
		}

		AudioSource::AudioSource()
		{
			m_SoundEngine = createIrrKlangDevice();

			if (!m_SoundEngine)
			{
				fprintf(stdout, "Error while initializing IrrKlang.\n");
				system("pause");
			}
			Loop = false;
		}

		AudioSource::~AudioSource()
		{
			m_SoundEngine->drop();
		}

		void AudioSource::Play(const char* filePath) const
		{
			m_SoundEngine->play2D(filePath, Loop);
		}
		void AudioSource::PlayOnce(const char* filePath) const
		{
			if (m_SoundEngine->isCurrentlyPlaying(filePath))
				return;
			else
				m_SoundEngine->play2D(filePath);
		}
		void AudioSource::Update()
		{
			//m_SoundEngine->update();
		}
		void AudioSource::Stop() const
		{
			m_SoundEngine->stopAllSounds();
		}
	}
}
