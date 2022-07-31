//
//  AudioComponent.hpp
//  GPC_Ch07
//
//  Created by Inoue Shinichi on 2022/07/27.
//

#ifndef AudioComponent_hpp
#define AudioComponent_hpp

#include "Component.hpp"
#include "SoundEvent.hpp"
#include <vector>
#include <string>

class AudioComponent : public Component
{
public:
    AudioComponent(class Actor* owner, int updateOrder = 200);
    ~AudioComponent();
    
    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;
    
    SoundEvent PlayEvent(const std::string& name);
    void StopAllEvents();
private:
    std::vector<SoundEvent> mEvents2D;
    std::vector<SoundEvent> mEvents3D;
};

#endif /* AudioComponent_hpp */
