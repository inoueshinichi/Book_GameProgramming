//
//  Collision.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/05/29.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "Math.hpp"
#include <vector>

/* 線分 */
struct LineSegment
{
    LineSegment(const Vector3& start, const Vector3& end);
    
    // 線分のパラメータ表現(0<=t<=1)による線分上の点を取得
    Vector3 PointOnSegment(float t) const;
    
    // 点と線分の符号付き最小距離の二乗を返す
    float MinDistSq(const Vector3& point) const;
    
    // 2つの線分の間の符号付き最小距離の二乗を返す
    static float MinDistSq(const LineSegment& s1, const LineSegment& s2);
    
    Vector3 mStart;
    Vector3 mEnd;
};


/* 平面 */
struct Plane
{
    Plane(const Vector3& normal, float d);
    
    // 3点から平面を作成するコンストラクタ
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    
    // 点と平面の間の符号付き最小距離を返す
    float SignedDist(const Vector3& point) const;
    
    Vector3 mNormal;
    float mD;
};


/* 球 */
struct Sphere
{
    Sphere(const Vector3& center, float radius);
    
    bool Contains(const Vector3& point) const;
    
    Vector3 mCenter;
    float mRadius;
};


/* Axis Aligned Bounding Box */
struct AABB
{
    AABB(const Vector3& min, const Vector3& max);
    
    // 指定した点(3D)を用いてAABBを更新する(モデルを読み込む際に使用する)
    void UpdateMinMax(const Vector3& point);
    
    // クォータニオンで回転
    void Rotate(const Quaternion& q);
    
    bool Contatins(const Vector3& point) const;
    
    float MinDistSq(const Vector3& point) const;
    
    Vector3 mMin;
    Vector3 mMax;
};


/* Oriented Bounding Box */
struct OBB
{
    Vector3 mCenter;
    Quaternion mRotation;
    Vector3 mExtents;
};


/* カプセル */
struct Capsule
{
    Capsule(const Vector3& start, const Vector3& end, float radius);
    
    // 線分のパラメータ表現(0<=t<=1)による線分上の点を取得
    Vector3 PointOnSegment(float t) const;
    
    bool Contatins(const Vector3& point) const;
    
    LineSegment mSegment; /* 線分は1本だけでOK */
    float mRadius;
};


/* 凸ポリゴン */
struct ConvexPolygon
{
    bool Contains(const Vector2& point) const;
    // Vertices have a clockwise ordering
    std::vector<Vector2> mVertices;
};


// Intersection functions
bool Intersect(const Sphere& a, const Sphere& b);
bool Intersect(const AABB& a, const AABB& b);
bool Intersect(const Capsule& a, const Capsule& b);
bool Intersect(const Sphere& s, const AABB& box);

bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
bool Intersect(const LineSegment& l, const AABB& b, float& outT,
    Vector3& outNorm);

// 時間方向の衝突検知
bool SweptSphere(const Sphere& P0, const Sphere& P1,
    const Sphere& Q0, const Sphere& Q1, float& t);

/* OBB拡張 */
//bool Intersect(const OBB& a, const OBB& b);
//bool Intersect(const Sphere& s, const OBB& box);
//bool Intersect(const LineSegment& l, const OBB& b, float& outT, Vector3& outNorm);



#endif /* Collision_hpp */
