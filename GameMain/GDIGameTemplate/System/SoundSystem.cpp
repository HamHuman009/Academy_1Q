#include "SoundSystem.h"

namespace mySound
{

	SoundManager* SoundManager::mInstance = nullptr;
	//SoundManager* soundManger = SoundManager::GetInstance();		// �ʱ�ȭ

	SoundManager* SoundManager::GetInstance()
	{
		/*if (mInstance == nullptr)
		{
			mInstance = new SoundManager();
			
		}*/
		return mInstance;
	}

	void SoundManager::DestroyInstance()
	{	
		if (mInstance != nullptr) {
			delete mInstance;
		}
		
		//mInstance = nullptr;
	}

	void SoundManager::Init()
	{
		mInstance = new SoundManager();
	}

	void SoundManager::LoadSounds(SoundList list, bool loopCheck, const char* music)
	{
		System_Create(&mSystem);
		mSystem->init(3, FMOD_INIT_NORMAL, 0);			// �ִ� 3�� ä�� ���ÿ� ��� ����

		if (loopCheck == true)
		{
			mSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(list)]);
		}
		else
		{
			mSystem->createSound(music, FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(list)]);
		}
	}

	void SoundManager::PlaySounds(SoundList list, SoundChannel channel)
	{
		//std::cout << "Attempting to play sound with list: " << static_cast<int>(list) << std::endl;
		//std::cout << "Attempting to play sound with channel: " << static_cast<int>(channel) << std::endl;
		mChannel[static_cast<int>(channel)]->stop();
		// static_cast<int>(list)���� �̻��ϹǷ� �ٸ� ����� �����.
		mSystem->playSound(mSoundList[static_cast<int>(list)], NULL, 0, &mChannel[static_cast<int>(channel)]);
		mChannel[static_cast<int>(channel)]->setVolume(mVolume);
	}

	void SoundManager::StopSounds(SoundChannel channel)
	{
		mChannel[static_cast<int>(channel)]->stop();
	}

	void SoundManager::SetVolume(float volume)
	{
		mVolume = volume;
		for (unsigned int i = 0; i < static_cast<unsigned int>(SoundChannel::Size); i++)
		{
			mChannel[i]->setVolume(mVolume);
		}
	}

	void SoundManager::RelaseSounds()
	{	
		for (int i = 0; i < (int)SoundList::Size; i++) {
			mSoundList[i]->release();
		}
		mSystem->release();
		mSystem->close();
	}

	bool SoundManager::isChannelPlaying(SoundChannel channel) {
		bool isPlaying = false;
		mChannel[(UINT)channel]->isPlaying(&isPlaying);
		return isPlaying;
	}

	SoundManager::SoundManager() :mSystem(), mChannel{}, mSoundList{}, mVolume(0.5f)
	{
	}

	SoundManager::~SoundManager()
	{
	}



}

