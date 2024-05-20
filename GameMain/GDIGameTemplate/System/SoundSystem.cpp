#include "SoundSystem.h"


namespace mySound
{
    SoundManager* SoundManager::mInstance = nullptr;
    SoundManager* soundManager = SoundManager::GetInstance();  // ÃÊ±âÈ­  

    SoundManager* SoundManager::GetInstance()
    {
        if (mInstance == nullptr)
            mInstance = new SoundManager();
        return mInstance;
    }

    void SoundManager::DestroyInstance()
    {
        delete mInstance;
        //mInstance = nullptr;
    }

    void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const char* music)
    {
        System_Create(&mSystem);
        mSystem->init(2, FMOD_INIT_NORMAL, 0);

        if (loopcheck)
            mSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &mSoundList[(int)(soundlist)]);
        else
            mSystem->createSound(music, FMOD_LOOP_OFF, 0, &mSoundList[(int)(soundlist)]);
    }

    void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel)
    {   
        int k = (int)(channel);
        mChannel[k]->stop();
        mSystem->playSound(mSoundList[(int)(soundlist)], nullptr, false, &mChannel[k]);
        mChannel[k]->setVolume(mVolume);
    }

    void SoundManager::StopMusic(eSoundChannel channel)
    {
        mChannel[(int)(channel)]->stop();
    }

    void SoundManager::SetVolume(float volume)
    {
        mVolume = volume;
        for (unsigned int i = 0; i < (int)(eSoundChannel::Size); ++i)
            mChannel[i]->setVolume(mVolume);
    }

    void SoundManager::RelaseSounds()
    {
        for (int i = 0; i < (int)eSoundList::Size; i++) {
            if (mSoundList[i] != nullptr) {
                mSoundList[i]->release();
            }
        }
    }

    bool SoundManager::isChannelPlaying(eSoundChannel channel) {
        bool isPlaying = false;
        mChannel[(int)channel]->isPlaying(&isPlaying);
        return isPlaying;
    }

    SoundManager::SoundManager(): mSystem(), mChannel{}, mSoundList{}, mVolume(0.5f)
    {
    }

    SoundManager::~SoundManager()
    {
        mSystem->release();
        mSystem->close();
        DestroyInstance();
    }
};