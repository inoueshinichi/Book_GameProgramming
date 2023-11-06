//
//  AudioComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "AudioComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "AudioComponent.hpp"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder)
{}

AudioComponent::~AudioComponent()
{
    StopAllEvent();
}

void AudioComponent::Update(float deltaTime)
{
    Component::Udpate(deltaTime);
    
    // Remove invalid 2D events
    auto iter = mEvent2D.begin();
    while (iter != mEvent2D.end())
    {
        if (!iter->IsVisible())
        {
            iter = mEvent2D.erase(iter);
        }
        else {
            ++iter;
        }
    }
    
    // remove invalid 3d Events
    iter = mEvent3D.begin();
    while ( iter != mEvent3D.end())
    {
        if (!iter->IsVisible())
        {
            iter = mEvent3D.erase(iter);
        } else {
            ++iter;
        }
    }
}

void AudioComponent::OnUpdateWorldTransform()
{
    // Update 3D event's world transform
    Matrix4 world = mOwner->GetWorldTransform();
    for (auto& event : mEvent3D)
    {
        if (event.IsVisible())
        {
            event.Set3DAttributes(world);
        }
    }
}

SoundEvent AudioComponent::PlayEvent(const std::string &name)
{
    SoundEvnet e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
    
    // Is this 2D or 3D ?
    if (e.Is3D())
    {
        mEvents3D.emplace_back(e);
        // Set initial 3D attributes
        e.Set3DAttriutes(mOwner->GetWorldTransoform());
    }
    else {
        mEvent2D.emplace_back(e);
    }
    return e;
}

void AudioComponent::StopAllEvent()
{
    // Stop all sounds
    for (auto& e: mEvent2D)
    {
        e.Stop();
    }
    for (auto& e : mEvent3D)
    {
        e.Stop();
    }
    
    // Clear events
    mEvent2D.clear();
    mEvent3D.clear();
}
