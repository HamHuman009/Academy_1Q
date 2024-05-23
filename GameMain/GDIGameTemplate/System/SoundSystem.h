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
        Effect2,
        Effect3,
        Voice,
        Size
    };

    enum class eSoundList
    {
        Void,
        Main_Theme, //사용
        Intro_Theme, //사용
        Talk_Theme, //사용
        Ingame_Theme, //사용
        Ending_Theme, //사용
        Button_Use, //사용
        Talk_Output, //미사용
        Comic_Talk, //몰루
        Scooper_Down, //사용
        Scooper_Up, //사용
        Fish_Move, //아직 안넣음
        Fish_Catch, //사용
        Boss_Fish_Catch, //사용
        Move_Scene_Theme1, //아직 미사용
        Move_Scene_Theme2, //
        Move_Scene_Theme3, //
        Anger_Sound_Start, //사용
        Anger_Sound_End, //사용
        Fish_breathing1, //사용
        Fish_breathing2, //사용
        Fish_breathing3, //사용
        Final_Score_Sound, //아직 안넣음
        Stage_End_Counting, //사용
        Scooper_Broken, //사용
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

        FMOD_RESULT result;
        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}