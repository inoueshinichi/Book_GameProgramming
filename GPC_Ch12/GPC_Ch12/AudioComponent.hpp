//
//  AudioComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
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
    void StopAllEvent();
    
private:
    std::vector<SoundEvnet> mEvent2D;
    std::vector<SoundEvent> mEvent3D;
};

#endif /* AudioComponent_hpp */
