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
        Main_Theme,
        Intro_Theme,
        Talk_Theme,
        Ingame_Theme,
        Ending_Theme,
        Button_Use,
        Talk_Output,
        Comic_Talk,
        Scooper_Down,
        Scooper_Up,
        Fish_Move,
        Fish_Catch,
        Boss_Fish_Catch,
        Move_Scene_Theme,
        Anger_Sound_Start,
        Anger_Sound_End,
        Fish_breathing1,
        Fish_breathing2,
        Fish_breathing3,
        Final_Score_Sound,
        Stage_End_Counting,
        Scooper_Broken,
        Size
    };
    class SoundManager;  // 클래스 전방 선언
    extern SoundManager* soundManager;  // extern을 사용하여 외부에서 접근 가능하도록 선언

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

        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}