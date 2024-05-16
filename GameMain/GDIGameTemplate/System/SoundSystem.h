#pragma once

#include "../WinMain.h"
#include "../inc/fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
#include "TimeSystem.h"

using namespace std;
using namespace FMOD;

namespace mySound
{
	enum class SoundChannel
	{
		/* 예시 */
		BGM,
		Effect,
		Size
	};

	enum class SoundList
	{
		/* 추가 */
		Void,
		Drum,
		Size,
		Singing
	};

	struct LCS
	{
		SoundList List;
		SoundChannel Channel;
		int Sec;
	};

	class SoundManager;
	extern SoundManager* soundManager;

	class SoundManager final
	{
	public:
		static SoundManager* GetInstance();

		static void DestroyInstance();

		void LoadSounds(SoundList list, bool loopCheck, const char* music);

		void PlaySounds(SoundList list, SoundChannel channel);

		void StopSounds(SoundChannel channel);

		void SetVolume(float volume);

		void StopInSecs(LCS LCS);

		void RelaseSounds();

	private:
		SoundManager();

		~SoundManager();
	private:
		static SoundManager* mInstance;
		LCS m_LCS;
		FMOD::System* mSystem;
		FMOD::Channel* mChannel[static_cast<int>(SoundChannel::Size)];
		FMOD::Sound* mSoundList[static_cast<int>(SoundList::Size)];
		float mVolume;

	};
}

