//
//  SoundEvent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#ifndef SoundEvent_hpp
#define SoundEvent_hpp

#include <string>
#include "Math.hpp"

class SoundEvent
{
public:
    SoundEvent();
    
    // return true if associated FMOD event still exists
    bool IsValid();
    
    // restart evetn from begining
    void Restart();
    
    // stop this evet
    void Stop(bool allowFadeOut = true);
    
    void SetPaused(bool pause);
    void SetVolume(float value);
    void SetPitch(float value);
    void SetParameter(const std::string& name, float value);
    
    bool GetPaused() const;
    float GetVolume() const;
    float GetPitch() const;
    float GetParameter(const std::string& name);
    
    bool Is3D() const;
    void Set3DAttributes(const Matrix4& worldTrans);
    
protected:
    friend class AudioSystem;
    SoundEvent(class AudioSystem* system, unsigned id);
private:
    class AudioSystem* mSystem
    unsigned mID;
};

#endif /* SoundEvent_hpp */
