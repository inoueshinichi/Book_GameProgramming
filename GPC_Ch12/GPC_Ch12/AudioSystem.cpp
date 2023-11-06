//
//  AudioSystem.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#include "AudioSystem.hpp"
#include <SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>
#include "Game.hpp" // ASSETS_DIR

unsigned AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
    : mGame(game)
    , mSystem(nullptr)
    , mLowLevelSystem(nullptr)
{}

AudioSystem::~AudioSystem()
{}

bool AudioSystem::Initialize()
{
    // Initialize debug logging
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR, // Log only errors
        FMOD_DEBUG_MODE_TTY // Output to stdout
    );
    
    // Create FMOD studio system object
    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&mSystem);
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }
    
    // Initialize FMOD studio system
    result = mSystem->initialize(
                                 512, // Max number of concurrent sounds
                                 FMOD_STUDIO_INIT_NORMAL, // Use default settings
                                 FMOD_INIT_NORMAL, // Use default settings
                                 nullptr // Usually null
                                 );
    
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }
    
    // Save the low-level system pointer
    mSystem->getLowLevelSystem(&mLowLevelSystem);
    
    // Load the master banks (strings first)
    LoadBank(ASSETS_DIR "Assets/Master Bank.strings.bank");
    LoadBank(ASSETS_DIR "Assets/Master Bank.bank");
    
    return true;
}

void AudioSystem::Shutdown()
{
    // Unload all banks
    UnloadAllBanks();
    // Shutdown FMOD system
    if (mSystem)
    {
        mSystem->release();
    }
}

void AudioSystem::LoadBank(const std::string &name)
{
    // Prevent double-loading
    if (mBanks.find(name) != mBanks.end())
    {
        return;
    }
    
    // try to load
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(
                                name.c_str(),
                                FMOD_STUDIO_LOAD_BANK_NORMAL, // Normal loading
                                &bank // Save pointer to bank
                                               );
    
    const int maxPathLength = 512;
    if (result == FMOD_OK)
    {
        // Add bank to map
        mBanks.emplace_back(name, bank);
        // load all non-streaming sampple data
        bank->loadSampleData();
        // Get the number of events in this bank
        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if (numEvents > 0)
        {
            // Get list of event descriptions in this bank
            std::vector<FMOD::Studio::EventDescription*> events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            char eventName[maxPathLength];
            for (int i = 0; i < numEvents; i++)
            {
                FMOD::Studio::EventDescription* e = events[i];
                // Get the path of this event (e.g. event:/Explosion2D)
                e->getPath(eventName, maxPathLength, nullptr);
                // add to event map
                mEvents.emplace(eventName, e);
            }
        }
        
        // get the number of buses in this bank
        int numBuses = 0;
        bank->getBusCount(&numBuses);
        if (numBuses > 0)
        {
            // get list of buses in this bank
            std::vector<FMOD::Studio::Bus*> buses(numBuses);
            bank->getBusList(buses.data(), numBuses, &numBuses);
            char busName[512];
            for (int i = 0; i < numBuses; i++)
            {
                FMOD::Studio::Bus* bus = buses[i];
                // get the path of this bus(e.g. bus:/SFX)
                bus->getPath(busName, 512, nullptr);
                // add to buses map
                mBuses.emplace(busName, bus);
            }
        }
    }
}

void AudioSystem::UnloadBank(const std::string& name)
{
    // Ignore if not loaded
    auto iter = mBanks.find(name);
    if (iter == mBanks.end())
    {
        return;
    }
    
    // first we need to remove all events from this bank
    FMOD::Studio::Bank* bank = iter->second;
    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0)
    {
        // get event descriptions for this bank
        std::vector<FMOD::Studio::EventDescription*> events(numEvents);
        // get list of events
        bank->getEventList(events.data(), numEvents, &numEvents);
        char eventName[512];
        for (int i = 0; i < numEvents; i++)
        {
            FMOD::Studio::EventDescription* e = events[i];
            // get the path of this event
            e->getPath(eventName, 512, nullptr);
            // remove this event
            auto eventi = mEvents.find(eventName);
            if (eventi != mEvents.end())
            {
                mEvents.erase(eventi);
            }
        }
    }
    
    // get the number of buses in this bank
    int numBuses = 0;
    bank->getBusCount(&numBuses);
    if (numBuses > 0)
    {
        // get list of buses in this bank
        std::vector<FMOD::Studio::Bus*> buses(numBuses);
        bank->getBusList(buses.data(), numBuses, &numBuses);
        char busName[512];
        for (int i = 0; i < numBuses; i++)
        {
            FMOD::Studio::Bus* bus = buses[i];
            // get the path of this bus(e.g. bus:/SFX)
            bus->getPath(busName, 512, nullptr);
            
            //remove this bus
            auto busi = mBuses.find(busName);
            if (busi != mBuses.end())
            {
                mBuses.erase(busi);
            }
        }
    }
    
    // unload sample daeta and bank
    bank->unloadSampleData();
    bank->unload();
    
    // remove from banks map
    mBanks.erase(iter);
}


void AudioSystem::UnloadAllBanks()
{
    for (auto & iter : mBanks)
    {
        // Unload the sample data, then the bank itself
        iter.second->unloadSampleData();
        iter.second->unload();
    }
    mBanks.clear();
    // No banks mean no events
    mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
    unsigned retID = 0;
    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        // Create instance of event
        FMOD::Studio::EventInstance* event = nullptr;
        iter->second->createInstance(&event);
        if (event)
        {
            // Start the event instance
            event->start();
            // get the nex id, and add to map
            sNextID++;
            retID = sNextID;
            mEventInstances.emplace(retID, event);
        }
    }
    return SoundEvent(this, retID);
}

void AudioSystem::Update(float deltaTime)
{
    // find any stopped event instances
    std::vector<unsigned> done;
    for (auto& iter : mEventInstances)
    {
        FMOD::Studio::EventInstance* e = iter.second;
        
        // get the state of this event
        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
        {
            // release the event and add id to done
            e->release();
            done.emplace_back(iter.first);
        }
    }
    
    // remove done event insetances from map
    for (auto id : done)
    {
        mEventInstances.erase(id);
    }
    
    // Update FMOD
    mSystem->update();
}

namespace {
FMOD_VECTOR VecToFMOD(const Vector3& in)
{
    // convert from our coordinates(+x forward, +y right, +z up)
    // to FMOD(+z forward, +x right, +y up)
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
    invView.Invert(); // カメラ座標系に写像する行列
    
    FMOD_3D_ATTRIBUTES listener;
    // set positon, forward, up
    listener.position = VecToFMOD(inView.GetTranslation);
    // In the inverted view, third row is forward (行優先表現)
    listener.forward = VecToFMOD(invView.GetZAxis());
    // In the inverted view, second row is up
    listener.up = VecToFMOD(invView.GetYAxis());
    // Set velocity to zero (fix if using Doppler effect)
    listener.velocity = {0.0f, 0.0f, 0.0f};
    // Send to FMOD
    mSystem->setListenerAttributes(0, &listener);
}

float AudioSystem::GetBusVolume(const std::string& name) const
{
    float retVal = 0.f;
    const auto iter = mBuses.find(name);
    if (iter = mBuses.end())
    {
        iter->second->getVolume(&retVal);
    }
    return retVal;
}

void AudioSystem::SetBusVolume(const std::string &name, float volume)
{
    auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->setVolume(volume);
    }
}

void AudioSystem::SetBusPased(const std::string &name, bool pause)
{
    auto iter = mBuses.find(name);
    if (iter != mBuses.end())
    {
        iter->second->setPaused(pause);
    }
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned id)
{
    FMOD::Studio::EventInstance* event = nullptr;
    auto iter = mEventInstances.find(id);
    if (iter != mEventInstances.end())
    {
        event = iter->second;
    }
    return event;
}

