//
//  AudioSystem.cpp
//  GPC_Ch07
//
//  Created by Inoue Shinichi on 2022/07/25.
//

#include "AudioSystem.hpp"
#include <SDL2/SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

#include "Game.hpp" // ASSET_DIR

unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
    : mGame(game)
    , mSystem(nullptr)
    , mLowLevelSystem(nullptr)
{
    
}

AudioSystem::~AudioSystem()
{
    
}


bool AudioSystem::Initialize()
{
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR, // エラーだけログを取る
        FMOD_DEBUG_MODE_TTY     // stdoutに出力
    );
    
    // FMOD Studioシステムのインスタンス生成
    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&mSystem);
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to create FMOD system：%s",
                FMOD_ErrorString(result));
        return false;
    }
    
    // FMODシステムの初期化
    result = mSystem->initialize(
        512, // 最大同時発音数
        FMOD_STUDIO_INIT_NORMAL, // デフォルトの設定
        FMOD_INIT_NORMAL, // デフォルトの設定
        nullptr // 通常はnullptr
    );
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to initialize FMOD system：%s",
                FMOD_ErrorString(result));
        return false;
    }
    
    mSystem->getLowLevelSystem(&mLowLevelSystem); // ポインタ取得
    
    // マスターバンクをロードする(stringsが先)
    LoadBank(ASSET_DIR "Assets/Master Bank.strings.bank");
    LoadBank(ASSET_DIR "Assets/Master Bank.bank");
    
    return true;
}

void AudioSystem::Shutdown()
{
    UnloadAllBanks();
    
    if (mSystem)
    {
        mSystem->release();
    }
}

void AudioSystem::Update(float deltaTime)
{
    // ストップしたイベントインスタンスを探す
    std::vector<unsigned int> done;
    for (auto& iter : mEventInstances)
    {
        FMOD::Studio::EventInstance* e = iter.second;
        // イベントの状態を取得
        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
        {
            // イベントを解放してidを終了リストに追加
            e->release();
            done.emplace_back(iter.first);
        }
    }
    
    // 終了したイベントインスタンスを連想配列から削除
    for (auto id : done)
    {
        mEventInstances.erase(id);
    }
    
    // FMOD更新
    mSystem->update();
}

void AudioSystem::LoadBank(const std::string& name)
{
    // 多重読み込みの防止
    if (mBanks.find(name) != mBanks.end())
    {
        return;
    }
    
    // バンクをロード
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(
            name.c_str(), // ファイル名または空白
            FMOD_STUDIO_LOAD_BANK_NORMAL, // 通常の読み込み
            &bank // バンクへのポインタを保存
    );
    
    const int maxPathLength = 512;
    if (result == FMOD_OK)
    {
        // バンクを連想配列に追加
        mBanks.emplace(name, bank);
        // ストリーミング以外のサンプルデータをすべてロード
        bank->loadSampleData();
        // このバンクにあるイベントの数を取得
        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if (numEvents > 0)
        {
            // バンクにあるイベント記述子のリストを取得
            std::vector<FMOD::Studio::EventDescription*> events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            
            char eventName[maxPathLength];
            for (int i = 0; i < numEvents; i++)
            {
                FMOD::Studio::EventDescription* e = events[i];
                // このイベントのパスを取得して(例：event:/Explosion2D)
                e->getPath(eventName, maxPathLength, nullptr);
                // イベント連想配列に追加
                mEvents.emplace(eventName, e);
            }
        }
        
        // バンクからバスの数を取得
        int numBuses = 0;
        bank->getBusCount(&numBuses);
        if (numBuses > 0)
        {
            // バスのリストを取得
            std::vector<FMOD::Studio::Bus*> buses(numBuses);
            bank->getBusList(buses.data(), numBuses, &numBuses);
            char busName[512];
            for (int i = 0; i < numBuses; i++)
            {
                FMOD::Studio::Bus* bus = buses[i];
                
                // バスのパスを取得 (bus:/SFX)
                bus->getPath(busName, 512, nullptr);
                // バスの連想配列に追加
                mBuses.emplace(busName, bus);
            }
        }
        
    }
}

void AudioSystem::UnloadBank(const std::string& name)
{
    // ロードしていなければ、無視する
    auto iter = mBanks.find(name);
    if (iter == mBanks.end())
    {
        return;
    }
    
    const int maxPathLength = 512;
    
    // その１: このバンクからすべてのイベントを削除する
    FMOD::Studio::Bank* bank = iter->second;
    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0)
    {
        std::vector<FMOD::Studio::EventDescription*> events(numEvents);
        bank->getEventList(events.data(), numEvents, &numEvents);
        
        
        char eventName[maxPathLength];
        for (int i = 0; i < numEvents; i++)
        {
            FMOD::Studio::EventDescription* e = events[i];
            e->getPath(eventName, maxPathLength, nullptr);
            
            // イベントを削除
            auto eventi = mEvents.find(eventName);
            if (eventi != mEvents.end())
            {
                mEvents.erase(eventi);
            }
        }
    }
    
    // その２: このバンクからバスを削除する
    int numBuses = 0;
    bank->getBusCount(&numBuses);
    if (numBuses > 0)
    {
        // バスリストを取得
        std::vector<FMOD::Studio::Bus*> buses(numBuses);
        bank->getBusList(buses.data(), numBuses, &numBuses);
        char busName[maxPathLength];
        for (int i = 0; i < numBuses; i++)
        {
            FMOD::Studio::Bus* bus = buses[i];
            bus->getPath(busName, maxPathLength, nullptr);
            
            // バスを削除
            auto busi = mBuses.find(busName);
            if (busi != mBuses.end())
            {
                mBuses.erase(busi);
            }
        }
    }
    
    // バンクとサンプルデータを削除
    bank->unloadSampleData();
    bank->unload();
    
    // 連想配列からバンクを削除
    mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
    for (auto& iter : mBanks)
    {
        // Unload the sample daeta, then the bank itsself
        iter.second->unloadSampleData();
        iter.second->unload();
    }
    mBanks.clear();
    // No banks means no events
    mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
    // イベントID
    unsigned int retID = 0;
    
    // イベントの存在を確認
    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        // イベントのインスタンスを作成
        FMOD::Studio::EventInstance* event = nullptr;
        iter->second->createInstance(&event);
        if (event)
        {
            // イベントインスタンスの開始
            event->start();
            
            // 次のIDを取得し、連想配列に追加
            sNextID++;
            retID = sNextID;
            
//            // release呼び出しで、イベントインスタンスは
//            // 停止時に破棄されることになる
//            // (ループしないイベントは自動的に停止する)
//            event->release();
            
            mEventInstances.emplace(retID, event);
        }
    }
    
    return SoundEvent(this, retID);
}

namespace
{
    FMOD_VECTOR VecToFMOD(const Vector3& in)
    {
        // Convert from our coordinates (+x forward, +y right, +z up)
        // to FMOD (+z forward, +x right, +y up)
        FMOD_VECTOR v;
        v.x = in.y;
        v.y = in.z;
        v.z = in.x;
        return v;
    }
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
    // Invert the view matrix to get the correct vectors
    Matrix4 invView = viewMatrix;
    invView.Invert();
    FMOD_3D_ATTRIBUTES listener;
    // Set position, forward, up
    listener.position = VecToFMOD(invView.GetTranslation());
    // In the inverted view, third row is forward(Z axis)
    listener.forward = VecToFMOD(invView.GetZAxis());
    // In the inverted view, second row is up(Y axis)
    listener.up = VecToFMOD(invView.GetYAxis());
    // Set velocity to zero (fix if using Doppler effect)
    listener.velocity = {0.0f, 0.0f, 0.0f};
    // Send to FMOD
    mSystem->setListenerAttributes(0, &listener);
}

float AudioSystem::GetBusVolume(const std::string& name) const
{
    float retVal = 0.0f;
    const auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->getVolume(&retVal);
    }
    return retVal;
}

bool AudioSystem::GetBusPaused(const std::string& name) const
{
    bool retVal = false;
    const auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->getPaused(&retVal);
    }
    return retVal;
}

void AudioSystem::SetBusVolume(const std::string& name, float volume)
{
    auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->setVolume(volume);
    }
}

void AudioSystem::SetBusPaused(const std::string& name, bool pause)
{
    auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->setPaused(pause);
    }
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
    FMOD::Studio::EventInstance* event = nullptr;
    auto iter = mEventInstances.find(id);
    if (iter != mEventInstances.end())
    {
        event = iter->second;
    }
    return event;
}
