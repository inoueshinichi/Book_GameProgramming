//
//  AudioSystem.hpp
//  GPC_Ch07
//
//  Created by Inoue Shinichi on 2022/07/25.
//

#ifndef AudioSystem_hpp
#define AudioSystem_hpp

#include <unordered_map>
#include <string.h>
#include "SoundEvent.hpp"
#include "Math.hpp"

// FMODヘッダーのインクルードを回避する前方宣言
namespace FMOD
{
    class System;
    namespace Studio
    {
        class Bank;
        class EventDescription;
        class EventInstance;
        class System;
        class Bus;
    };
};

class AudioSystem
{
public:
    AudioSystem(class Game* game);
    ~AudioSystem();
    
    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
    
    SoundEvent PlayEvent(const std::string& name);
    
    // ポジショナル・オーディオ
    void SetListener(const Matrix4& viewMatrix);
    
    // バス制御
    float GetBusVolume(const std::string& name) const;
    bool GetBusPaused(const std::string& name) const;
    void SetBusVolume(const std::string& name, float volume);
    void SetBusPaused(const std::string& name, bool pause);
    // バンク制御
    void LoadBank(const std::string& name);
    void UnloadBank(const std::string& name);
    void UnloadAllBanks();
protected:
    friend class SoundEvent;
    FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
    class Game* mGame;
    // FMOD studio システム
    FMOD::Studio::System* mSystem;
    // FMOD Low-level システム
    FMOD::System* mLowLevelSystem;
    
    // ロードされたバンクの連想配列
    std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
    // イベント名からEventDescriptionへの連想配列
    std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
    // バスの連想配列
    std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
    
    // イベントインスタンス管理のための連想配列
    std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
    
    // イベントID
    static unsigned int sNextID;
    
};

#endif /* AudioSystem_hpp */
