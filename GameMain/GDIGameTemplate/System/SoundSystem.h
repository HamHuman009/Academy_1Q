#pragma once
// FMOD
#ifndef _WIN64
#include "../inc/fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "../inc/fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif

namespace mySound
{
	enum class eSoundChannel
	{
		BGM = 0,
		Effect = 1,
		Effect2 = 2,
		Effect3 = 3,
		Voice = 4,
		Size = 5
	};

	enum class eSoundList
	{
		Void = 0,
		Main_Theme = 1, //���
		Intro_Theme = 2, //���
		Talk_Theme = 3, //���
		Ingame_Theme = 4, //���
		Ending_Theme = 5, //���
		Button_Use = 6, //���
		Talk_Output = 7, //�̻��
		Comic_Talk = 8, //����
		Scooper_Down = 9, //���
		Scooper_Up = 10, //���
		Fish_Move = 11, //���� �ȳ���
		Fish_Catch = 12, //���
		Boss_Fish_Catch = 13, //���
		Move_Scene_Theme1 = 14, //���� �̻��
		Move_Scene_Theme2 = 15, //
		Move_Scene_Theme3 = 16, //
		Anger_Sound_Start = 17, //���
		Anger_Sound_End = 18, //���
		Fish_breathing1 = 19, //���
		Fish_breathing2 = 20, //���
		Fish_breathing3 = 21, //���
		Final_Score_Sound = 22, //���� �ȳ���
		Stage_End_Counting = 23, //���
		Scooper_Broken = 24, //���
		CrabDance = 25,
		Size = 26
	};
	class SoundManager;  // Ŭ���� ���� ����
	extern SoundManager* soundManager;  // extern�� ����Ͽ� �ܺο��� ���� �����ϵ��� ����

	class SoundManager final
	{
	public:
		static SoundManager* GetInstance();

		static void DestroyInstance();

		void LoadMusic(eSoundList list, bool loopcheck, const char* music);

		void PlayMusic(eSoundList list, eSoundChannel channel);

		void StopMusic(eSoundChannel channel);

		void SetVolumeAll(float volume);

		void SetVolume(float volume, int channel);

		bool isChannelPlaying(eSoundChannel channel);

		void RelaseSounds();

	private:
		SoundManager();

		~SoundManager();

		static SoundManager* mInstance;

		FMOD_RESULT result;
		FMOD::System* mSystem;
		FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
		FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
		float mVolume;
	};

}