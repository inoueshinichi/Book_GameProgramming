//
//  SplineCamera.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/03/07.
//

#ifndef SplineCamera_hpp
#define SplineCamera_hpp

#include "CameraComponent.hpp"

#include <vector>

struct Spline
{
    /* Catmul-Romスプライン */
    // スプラインのための制御点
    // N個の点を通る曲線にはN+2個の制御点が必要.
    std::vector<Vector3> mControlPoints;
    
    // startIdx=P1の区間で
    // tの値に基づいて位置を計算する
    Vector3 Compute(size_t startIdx, float t) const;
    
    size_t GetNumPoints() const { return mControlPoints.size(); }
    
};

class SplineCamera : public CameraComponent
{
public:
    SplineCamera(class Actor* owner);
    ~SplineCamera() {}
    
    void Restart();
    
    void SetSpeed(float speed) { mSpeed = speed; }
    void SetSpline(const Spline& spline) { mPath = spline; }
    void SetPaused(bool pause) { mPaused = pause; }
    
    void Update(float deltaTime) override;
    
private:
    // カメラが追従するスプライン経路
    Spline mPath;
    //　現在の制御点のインデックスとtの値
    size_t mIndex;
    float mT;
    // スピード = tの増分 / 秒
    float mSpeed;
    // カメラを経路に沿って動かすか
    bool mPaused;
};

#endif /* SplineCamera_hpp */
