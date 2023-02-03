//
//  AudioSystem.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef AudioSystem_hpp
#define AudioSystem_hpp

#include <unordered_map>
#include <string>
#include "SoundEvent.hpp"
#include "Math.hpp"

// Forward declarations to avoid including FMOD header
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
    }
}

class AudioSystem
{
public:
    AudioSystem(class Game* game);
    ~AudioSystem();
    
    bool Initialize();
    void Shutdown();
    
    // Load/unload banks
    void LoadBank(const std::string& name);
}

#endif /* AudioSystem_hpp */
