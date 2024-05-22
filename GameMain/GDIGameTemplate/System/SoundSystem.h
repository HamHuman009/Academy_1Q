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
        BGM,
        Effect,
        Voice,
        Size
    };

    enum class eSoundList
    {
        Void,
        Main_Theme, //���
        Intro_Theme, //���
        Talk_Theme, //���
        Ingame_Theme, //���
        Ending_Theme, //���
        Button_Use, //���
        Talk_Output, //���常 ������ ��.
        Comic_Talk, //����
        Scooper_Down, //���
        Scooper_Up, //���
        Fish_Move, //���� �ȳ���
        Fish_Catch, //���
        Boss_Fish_Catch, //���
        Move_Scene_Theme, //���� �̻��
        Anger_Sound_Start, //�־�� ��
        Anger_Sound_End, //�־�� ��
        Fish_breathing1, //���
        Fish_breathing2, //���
        Fish_breathing3, //���
        Final_Score_Sound, //���� �ȳ���
        Stage_End_Counting, //���� �ȳ���
        Scooper_Broken, //���� �ȳ���
        Size
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