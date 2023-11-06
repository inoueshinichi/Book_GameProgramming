//
//  AudioSystem.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#ifndef AudioSystem_hpp
#define AudioSystem_hpp

#include <unordered_map>
#include <string>
#include "SoundEvent.hpp"
#include "Math.hpp"

// Forward declarations to avoid including FMOD header
namespace FMOD {
class System;
namespace Studio {
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
    
    // load/unload banks
    void LoadBank(const std::string& name);
    void UnloadBank(const std::string& name);
    void UnloadAllBanks();
    
    SoundEvent PlayEvent(const std::stirng& name);
    
    void Update(float deltaTime);
    
    // For positional audio
    void SetListener(const Matrix4& viewMatrix);
    
    // control buses
    float GetBusVolume(const std::string& name) const;
    bool GetBusPaused(const std::string& name) const;
    void SetBusVolume(const std::string& name, float volume);
    void SetBusPased(const std::string& name, bool pause);
    
protected:
    friend class SoundEvent;
    FMOD::Studio::EventInstance * GetEventInstance(unsigned id);
    
private:
    // tracks the next ID to use for event instances
    static unsigned sNextID;
    
    class Game* mGame;
    // Map of loaded banks
    std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
    // Map of event name to EventDescription
    std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
    // Map of event id to EventInstance
    std::unordered_map<unsigned, FMOD::Studio::EventInstance*> mEventInstances;
    // Map of buses
    std::unordered_map<unsigned, FMOD::Studio::Bus*> mBuses;
    // FMOD studio system
    FMOD::Studio::System * mSystem;
    // FMOD Load-level-system (in case needed)
    FMOD::System* mLowLevelSystem;
};

#endif /* AudioSystem_hpp */
