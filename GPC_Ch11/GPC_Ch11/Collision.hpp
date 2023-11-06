//
//  Collision.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/20.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "Math.hpp"
#include <vector>

// 線分
struct LineSegment
{
    LineSegment(const Vector3& start, const Vector3& end);
    
    // Get point along segment where 0<=t<=1
    Vector3 PointOnSegment(float f) const;
    
    // Get minimum distance squared between point and line segment.
    float MinDistSq(const Vector3& point) const;
    
    // Get MinDistSq between two line segment
    static float MinDistSq(const LineSegment& s1, const LineSegment& s2);
    
    Vector3 mStart;
    Vector3 mEnd;
};

// 平面
struct Plane
{
    Plane(const Vector3& normal, float d);
    
    // Constructor plane from three points
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    
    // Get the signed distance between the point and the plane
    float SignedDist(const Vector3& point) const;
    
    Vector3 mNormal;
    float mD;
};

// 球
struct Sphere
{
    Sphere(const Vector3& center, float radius);
    
    bool Contains(const Vector3& point) const;
    
    Vector3 mCenter;
    float mRadius;
};

// 軸平行型境界ボックス
struct AABB
{
    AABB(const Vector3& min, const Vector3& max);
    
    // Update min and max accounting for this point
    // (used when loading a model)
    void UpdateMinMax(const Vector3& point);
    
    // Rotated by a quaternion
    void Rotate(const Quaternion& q);
    
    bool Contains(const Vector3& point) const;
    
    float MinDistSq(const Vector3& point) const;
    
    Vector3 mMin;
    Vector3 mMax;
};

// 方向あり境界ボックス
struct OBB
{
    Vector3 mCenter;
    Quaternion mRotation;
    Vector3 mExtents;
};

// カプセル
struct Capsule
{
    Capsule(const Vector3& start, const Vector3& end, float radius);
    
    // Get point along segment where 0<=t<=1
    Vector3 PointOnSegment(float t) const;
    
    bool Contains(const Vector3& point) const;
    
    LineSegment mSegment;
    float mRadius;
};


// 凸ポリゴン
struct ConvexPolygon
{
    bool Contains(const Vector2& point) const;
    
    // Vertices have a clockwise ordering
    std::vector<Vector2> mVertices;
};


// 交差判定
bool Intersect(const Sphere& a, const Sphere& b);
bool Intersect(const AABB& a, const AABB& b);
bool Intersect(const Capsule& a, const Capsule& b);
bool Intersect(const Sphere& s, const AABB& box);

bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm);


bool SweapSphere(const Sphere& P0, const Sphere& P1,
                 const Sphere& Q0, const Sphere& Q1,
                 float& t);



#endif /* Collision_hpp */
