#pragma once
#include <iostream>
#include <vector>
#include "./inc/fmod.hpp"
#include <conio.h>
#include <vector>
#pragma comment (lib, "fmod_vc.lib")

using namespace std;
using namespace FMOD;

namespace mySound
{
	enum class SoundChannel
	{
		/* ���� */
		BGM,
		Effect,
		Size
	};

	enum class SoundList
	{
		/* �߰� */
		Drum,
		Size,
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
	private:
		SoundManager();

		~SoundManager();
	private:
		static SoundManager* mInstance;

		FMOD::System* mSystem;
		FMOD::Channel* mChannel[static_cast<int>(SoundChannel::Size)];
		FMOD::Sound* mSoundList[static_cast<int>(SoundList::Size)];
		float mVolume;

	};
}

