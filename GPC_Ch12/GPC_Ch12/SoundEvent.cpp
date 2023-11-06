//
//  SoundEvent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#include "SoundEvent.hpp"
#include "AudioSystem.hpp"
#include <fmod_studio.hpp>

SoundEvent::SoundEvent(class AudioSystem* system, unsigned id)
    : mSystem(system)
    , mID(id)
{}

SoundEvent::SoundEvent()
    : mSystem(nullptr)
    , mID(0)
{}

bool SoundEvent::IsValid()
{
    return (mSystem && mSystem->GetEventInstance(mID) != nullptr);
}

void SoundEvent::Restart()
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        event->start();
    }
}

void SoundEvent::Stop(bool allowFadeOut /* true */)
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
        FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;
        event->stop(mode);
    }
}

// setter
void SoundEvent::SetPaused(bool pause)
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        event->setPaused(pause);
    }
}

void SoundEvent::SetVolume(float value)
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        event->setVolume(value);
    }
}


void SoundEvent::SetPitch(float value)
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        event->setPitch(value);
    }
}

void SoundEvent::SetParameter(const std::string &name, float value)
{
    auto event = mSystem ? mSystem->getEventInstance(mID) : nullptr;
    if (event)
    {
        event->setParameterValue(name.c_str(), value);
    }
}

// getter
bool SoundEvent::GetPaused() const
{
    bool retVal = false;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getPaused(&retVal);
    }
    
    return retVal;
}

float SoundEvent::GetVolume() const
{
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getVolume(&retVal);
    }
    return retVal;
}

float SoundEvent::GetPitch() const
{
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getPitch(&retVal);
    }
    return retVal;
}

float SoundEvent::GetParameter(const std::string& name)
{
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getParameterValue(name.c_str(), &retVal);
    }
    return retVal;
}

bool SoundEvent::Is3D() const
{
    bool retVal = false;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        // get the event description
        FMOD::Studio::EventDescription* ed = nullptr;
        event->getDescription(&ed);
        if (ed)
        {
            ed->is3D(&retVal);
        }
    }
    return retVal;
}

namespace {
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

void SoundEvent::Set3DAttributes(const Matrix4& worldTrans)
{
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        FMOD_3D_ATTRIBUTES attr;
        // set pos, forward, up
        attr.position = VecToFMOD(worldTrans.GetTralslation); // カメラ位置
        attr.forward = VecToFMOD(worldTrans.GetXAxis()); // 前方
        attr.up = VecToFMOD(worldTrans.GetZAxis());
        
        // set velocity
        attr.velocity = {0.f, 0.f, 0.f};
        event->set3DAttributes(&attr);
    }
}
