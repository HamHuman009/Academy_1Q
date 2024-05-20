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
        Size
    };

    enum class eSoundList
    {
        Void,
        BGM,
        BGM2,
        BGM3,
        Button,
        Water,
        /*s_title,
        s_intro,
        s_talk,
        s_ingame,
        s_ending,
        s_button,
        s_dialogue,
        s_talkbubble,
        s_scooperDown,
        s_scooperUp,
        s_fishMove,
        s_fishCaught,
        s_bossCaught,
        s_sceneTrans,
        s_angerStart,
        s_angerTerm,
        s_bubble,
        s_finalscoreShownup,
        s_dadVoice,
        s_kidVoice,*/
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

        void SetVolume(float volume);

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