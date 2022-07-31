//
//  Random.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef Random_hpp
#define Random_hpp

#include "Math.hpp"

#include <random>

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
    
private:
    static std::mt19937_64 sGenerator;
};


#endif /* Random_hpp */
