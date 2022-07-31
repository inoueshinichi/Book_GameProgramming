//
//  Random.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#ifndef Random_hpp
#define Random_hpp

#include <random>

#include "Math.hpp"

class Random
{
public:
    static void Init();
    
    /* 種を生成 */
    static void Seed(unsigned int seed);
    
    // 0.0 ~ 1.0 を取得
    static float GetFloat();
    
    static float GetFloatRange(float min, float max);
    static int GetIntRange(int min, int max);
    
    static Vector2 GetVector(const Vector2& min, const Vector2& max);
    //static Vector3 GetVector(const Vector3& min, const Vector3& max);
    
private:
    static std::mt19937 sGenerator;
};

#endif /* Random_hpp */
