//
//  Math.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#ifndef Math_hpp
#define Math_hpp

#include <cmath>
#include <memory>
#include <limits>

namespace Math
{
    const float Pi = 3.1415926535f;;
    const float TwoPi = Pi * 2.f;
    const float PiOver2 = Pi / 2.f;
    const float Infinity = std::numeric_limits<float>::infinity();
    const float NegInfinity = -std::numeric_limits<float>::infinity();
    
    inline float ToRadian(foat degrees)
    {
        return degrees * Pi / 180.f;
    }
    
    inline float ToDegrees(float radians)
    {
        return radians * 180.f / Pi;
    }
    
    inline bool NearZero(float val, float epsilon = 0.001f)
    {
        if (fabs(val) <= epsilon)
        {
            return true;
        } else {
            return false;
        }
    }
    
    template <typename T>
    T Max(const T& a, const T& b)
    {
        return (a < b ? b : a);
    }
    
    template <typename T>
    T Min(const T& a, const T& b)
    {
        return (a < b ? a : b);
    }
    
    template <typename T>
    T Clamp(const T& value, const T& lower, const T& upper)
    {
        return Min(upper, Max(lower, value));
    }
    
    inline float Abs(float value)
    {
        return fabs(value);
    }
    
    inline float Cos(float angle)
    {
        return cosf(angle);
    }
    
    inline float Sin(float angle)
    {
        return sinf(angle);
    }
    
    inline float Tan(float angle)
    {
        return tanf(angle);
    }
    
    inline float Acos(float value)
    {
        return acosf(value);
    }
    
    inline float Atan2(float y, float x)
    {
        return atan2f(y, x);
    }
    
    inline float Cot(float angle)
    {
        return 1.f / Tan(angle);
    }
    
    inline float Lerp(float a, float b, float f)
    {
        return a + f * (a - b);
    }
    
    inline float Sqrt(float value)
    {
        return sqrtf(value);
    }
    
    inline float Fmod(float numer, float denom)
    {
        return fmod(numer, denom);
    }
} // Math


// 2D Vector
class Vector2
{
public:
    float x;
    float y;
    
    Vector2()
    : x(0.f), y(0.f){}
    
    explicit Vector2(float inX, float inY)
    : x(inX), y(inY) {}
    
    void Set(float inX, float inY)
    {
        x = inX;
        y = inY;
    }
    
    // a + b
    friend Vector2 operator+(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x + b.x, a.y + b.y);
    }
    
    // a - b
    friend Vector2 operator-(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    
    // component-wise mul
    // (a.x * b.x, ...)
    friend Vector2 operator*(const Vector2& a, const Vector2& b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }
    
    // scalar mul
    friend Vector2 operator*(float scalar, const Vector2& vec)
    {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }
    
    // scalar *=
    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    // Vector +=
    Vector2& operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }
    
    // Vector -=
    Vector2& operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }
    
    // Length squared of vector
    float LengthSq() const
    {
        return (x*x + y*y);
    }
    
    // Length of vector
    float Length() const
    {
        return (Math::Sqrt(LengthSq()));
    }
    
    // Normalize this vector
    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
    }
    
    // Normalize the provided vector
    static Vector2 Normalize(const Vector2& vec)
    {
        Vector2 temp = vec;
        temp.Normalize();
        return temp;
    }
    
    // Dot product between two vectors ( a dot b )
    static float Dot(const Vector2& a, const Vector2& b)
    {
        return (a.x * b.x + a.y * b.y);
    }
    
    // Lerp from A to B by f
    static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
    {
        return Vector2(a + f * (b - a));
    }
    
    // Reflect V about (normalized) N
    static Vector2 Reflect(const Vector2& v, const Vector2& n)
    {
        return v - 2.f * Vector2::Dot(v, n) * n;
    }
    
    // Transform vector by matrix
    static Vector2 Transform(const Vector2& vec,
                             const class Matrix3& mat,
                             float w = 1.0f);
    
    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegUnitX;
    static const Vector2 NegUnitY;
};


// 3D Vector
class Vector3
{
public:
    float x;
    float y;
    float z;
    
    Vector3() : x(0.f), y(0.f), z(0.f) {}
    
    explicit Vector3(float inX, float inY, float inZ)
    : x(inX), y(inY), z(inZ) {}
    
    // cast to a const float pointer
    const float* GetAsFloatPtr() const
    {
        return reinterpret_cast<const float*>(&x);
    }
    
    // set all thee components in one line
    void Set(float inX, float inY, float inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }
    
    // a + b
    friend Vector3 operator+(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    
    // a - b
    friend Vector3 operator-(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    
    // Component-wise mul
    friend Vector3 operator*(const Vector3& left, const Vector3& right)
    {
        return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
    }
    
    // scalar mul
    friend Vector3 operator*(const Vector3& vec, float scalar)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    
    // scalar nul
    friend Vector3 operator*(float scalar, const Vector3& vec)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    
    // scalar *=
    Vector3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
    // add +=
    Vector3& operator+=(const Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }
    
    // sub -=
    Vector3& operator-=(const Vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }
    
    // Length squared of vector
    float LengthSq() const
    {
        return (x*x + y*y + z*z);
    }
    
    // Length of vector
    float Length() const
    {
        return (Math::Sqrt(LengthSq()));
    }
    
    // Normalize this vector
    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
        z /= length;
    }
    
    // Normalize the provided vector
    static Vector3 Normalize(const Vector3& vec)
    {
        Vector3 temp = vec;
        temp.Normalize();
        return temp;
    }
    
    // dot ( a dot b)
    static float Dot(const Vector3& a, const Vector3& b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }
    
    // cross ( a cross b)
    static Vector3 Cross(const Vector3& a, const Vector3& b)
    {
        Vector3 temp;
        temp.x = a.y * b.z - a.z * b.y;
        temp.y = a.z * b.x - a.x * b.z;
        temp.z = a.x * b.y - a.y * b.x;
        return temp;
    }
    
    // Lerp from A to B by f
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
    {
        return Vector3(a + f * (b - a));
    }
    
    // Reflect V about (normalized) N
    static Vector3 Reflect(const Vector3& v, const Vector3& n)
    {
        return v - 2.f * Vector3::Dot(v,n) * n;
    }
    
    static Vector3 Transform(const Vector3& vec,
                             const class Matrix4& mat,
                             float w = 1.0f);
    
    // this will transform the vector and renormalize the w compoennt
    static Vector3 TransformWithPerspDiv(const Vector3& vec,
                                         const class Matrix4& mat,
                                         float w = 1.f);
    
    // Transform a vector3 by a quaternion
    static Vector3 Transform(const Vector3& v,
                             const class Quaternion& q);
    
    static const Vector3 Zero;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 NegUnitX;
    static const Vector3 NegUnitY;
    static const Vector3 NegUnitZ;
    static const Vector3 Infinity;
    static const Vector3 NegInfinity;
};

// 3x3 matrix
class Matrix3
{
public:
    float mat[3][3];
    
    Matrix3() {
        *this = Matrix3::Identity;
    }
    
    explicit Matrix3(float inMat[3][3])
    {
        std::memcpy(mat, inMat, 9 * sizeof(float));
    }
    
    // cast to a const float pointer
    const float* GetAsFloatPtr() const
    {
        return reinterpret_cast<const float*>(&mat[0][0]);
    }
    
    // mat mul
    friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
    {
        Matrix3 retVal;
        
        // row 0
        retVal.mat[0][0] =
            left.mat[0][0] * right.mat[0][0] +
            left.mat[0][1] * right.mat[1][0] +
            left.mat[0][2] * right.mat[2][0];

        retVal.mat[0][1] =
            left.mat[0][0] * right.mat[0][1] +
            left.mat[0][1] * right.mat[1][1] +
            left.mat[0][2] * right.mat[2][1];

        retVal.mat[0][2] =
            left.mat[0][0] * right.mat[0][2] +
            left.mat[0][1] * right.mat[1][2] +
            left.mat[0][2] * right.mat[2][2];
        
        // row 1
        retVal.mat[1][0] =
            left.mat[1][0] * right.mat[0][0] +
            left.mat[1][1] * right.mat[1][0] +
            left.mat[1][2] * right.mat[2][0];

        retVal.mat[1][1] =
            left.mat[1][0] * right.mat[0][1] +
            left.mat[1][1] * right.mat[1][1] +
            left.mat[1][2] * right.mat[2][1];

        retVal.mat[1][2] =
            left.mat[1][0] * right.mat[0][2] +
            left.mat[1][1] * right.mat[1][2] +
            left.mat[1][2] * right.mat[2][2];
        
        // row 2
        retVal.mat[2][0] =
            left.mat[2][0] * right.mat[0][0] +
            left.mat[2][1] * right.mat[1][0] +
            left.mat[2][2] * right.mat[2][0];

        retVal.mat[2][1] =
            left.mat[2][0] * right.mat[0][1] +
            left.mat[2][1] * right.mat[1][1] +
            left.mat[2][2] * right.mat[2][1];

        retVal.mat[2][2] =
            left.mat[2][0] * right.mat[0][2] +
            left.mat[2][1] * right.mat[1][2] +
            left.mat[2][2] * right.mat[2][2];

        return retVal;
    }
    
    Matrix3& operator*=(const Matrix3& right)
    {
        *this = *this * right;
        return *this;
    }
    
    // create a scale mat with x and y
    static Matrix3 CreateScale(float xScale, float yScale)
    {
        float temp[3][3] =
        {
            { xScale, 0.0f, 0.0f },
            { 0.0f, yScale, 0.0f },
            { 0.0f, 0.0f, 1.0f },
        };
        return Matrix3(temp);
    }
    
    static Matrix3 CreateScale(const Vector2& scalarVector)
    {
        return CreateScale(scalarVector.x, scalarVector.y);
    }
    
    // Create a scale matrix a uniform factor
    static Matrix3 CreateScale(float scale)
    {
        return CreateScale(scale, scale);
    }
    
    // Create rotation matrix about the Z axis
    // theta is in radians
    static Matrix3 CreateRotation(float theta)
    {
        float temp[3][3] =
        {
            { Math::Cos(theta), Math::Sin(theta), 0.0f },
            { -Math::Sin(theta), Math::Cos(theta), 0.0f },
            { 0.0f, 0.0f, 1.0f },
        };
        return Matrix3(temp);
    }
    
    // Create a translation matrix (on the xy-plane)
    static Matrix3 CreateTranslation(const Vector2& trans)
    {
        float temp[3][3] =
        {
            { 1.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
            { trans.x, trans.y, 1.0f },
        };
        return Matrix3(temp);
    }
    
    static const Matrix3 Identity;
};


// 4x4 matrix
class Matrix4
{
public:
    float mat[4][4];
    
    Matrix4()
    {
        *this = Matrix4::Identity;
    }
    
    explicit Matrix4(float inMat[4][4])
    {
        std::memcpy(mat, inMat, 16 * sizeof(float));
    }
    
    const float* GetAsFloatPtr() const
    {
        return reinterpret_cast<const float*>(&mat[0][0]);
    }
    
    // mat mul
    friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
    {
        Matrix4 retVal;
        // row 0
        retVal.mat[0][0] =
            a.mat[0][0] * b.mat[0][0] +
            a.mat[0][1] * b.mat[1][0] +
            a.mat[0][2] * b.mat[2][0] +
            a.mat[0][3] * b.mat[3][0];

        retVal.mat[0][1] =
            a.mat[0][0] * b.mat[0][1] +
            a.mat[0][1] * b.mat[1][1] +
            a.mat[0][2] * b.mat[2][1] +
            a.mat[0][3] * b.mat[3][1];

        retVal.mat[0][2] =
            a.mat[0][0] * b.mat[0][2] +
            a.mat[0][1] * b.mat[1][2] +
            a.mat[0][2] * b.mat[2][2] +
            a.mat[0][3] * b.mat[3][2];
        
        retVal.mat[0][3] =
            a.mat[0][0] * b.mat[0][3] +
            a.mat[0][1] * b.mat[1][3] +
            a.mat[0][2] * b.mat[2][3] +
            a.mat[0][3] * b.mat[3][3];

        // row 1
        retVal.mat[1][0] =
            a.mat[1][0] * b.mat[0][0] +
            a.mat[1][1] * b.mat[1][0] +
            a.mat[1][2] * b.mat[2][0] +
            a.mat[1][3] * b.mat[3][0];

        retVal.mat[1][1] =
            a.mat[1][0] * b.mat[0][1] +
            a.mat[1][1] * b.mat[1][1] +
            a.mat[1][2] * b.mat[2][1] +
            a.mat[1][3] * b.mat[3][1];

        retVal.mat[1][2] =
            a.mat[1][0] * b.mat[0][2] +
            a.mat[1][1] * b.mat[1][2] +
            a.mat[1][2] * b.mat[2][2] +
            a.mat[1][3] * b.mat[3][2];

        retVal.mat[1][3] =
            a.mat[1][0] * b.mat[0][3] +
            a.mat[1][1] * b.mat[1][3] +
            a.mat[1][2] * b.mat[2][3] +
            a.mat[1][3] * b.mat[3][3];

        // row 2
        retVal.mat[2][0] =
            a.mat[2][0] * b.mat[0][0] +
            a.mat[2][1] * b.mat[1][0] +
            a.mat[2][2] * b.mat[2][0] +
            a.mat[2][3] * b.mat[3][0];

        retVal.mat[2][1] =
            a.mat[2][0] * b.mat[0][1] +
            a.mat[2][1] * b.mat[1][1] +
            a.mat[2][2] * b.mat[2][1] +
            a.mat[2][3] * b.mat[3][1];

        retVal.mat[2][2] =
            a.mat[2][0] * b.mat[0][2] +
            a.mat[2][1] * b.mat[1][2] +
            a.mat[2][2] * b.mat[2][2] +
            a.mat[2][3] * b.mat[3][2];

        retVal.mat[2][3] =
            a.mat[2][0] * b.mat[0][3] +
            a.mat[2][1] * b.mat[1][3] +
            a.mat[2][2] * b.mat[2][3] +
            a.mat[2][3] * b.mat[3][3];

        // row 3
        retVal.mat[3][0] =
            a.mat[3][0] * b.mat[0][0] +
            a.mat[3][1] * b.mat[1][0] +
            a.mat[3][2] * b.mat[2][0] +
            a.mat[3][3] * b.mat[3][0];

        retVal.mat[3][1] =
            a.mat[3][0] * b.mat[0][1] +
            a.mat[3][1] * b.mat[1][1] +
            a.mat[3][2] * b.mat[2][1] +
            a.mat[3][3] * b.mat[3][1];

        retVal.mat[3][2] =
            a.mat[3][0] * b.mat[0][2] +
            a.mat[3][1] * b.mat[1][2] +
            a.mat[3][2] * b.mat[2][2] +
            a.mat[3][3] * b.mat[3][2];

        retVal.mat[3][3] =
            a.mat[3][0] * b.mat[0][3] +
            a.mat[3][1] * b.mat[1][3] +
            a.mat[3][2] * b.mat[2][3] +
            a.mat[3][3] * b.mat[3][3];
        
        return retVal;
    }
    
    Matrix4& operator*=(const Matrix4& right)
    {
        *this = *this * right;
        return *this;
    }
    
    // Invert very slow
    void Invert();
    
    Vector3 GetTranslation() const
    {
        return Vector3(mat[3][0], mat[3][1], mat[3][2]);
    }
    
    Vector3 GetXAxis() const
    {
        return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
    }
    
    Vector3 GetYAxis() const
    {
        return Vector3::Normalize(Vector3(mat[1][0], mat1[1][1], mat[1][2]));
    }
    
    Vector3 GetZAxis() const
    {
        return Vector3::Normalize(Vector3(mat[2][0], mat1[2][1], mat[2][2]));
    }
    
    Vector3 GetScale() const
    {
        Vector3 retVal;
        retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
        retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
        retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
        return retVal;
    }
    
    static Matrix4 CreateScale(float xScale, float yScale, float zScale)
    {
        float temp[4][4] =
        {
            { xScale, 0.0f, 0.0f, 0.0f },
            { 0.0f, yScale, 0.0f, 0.0f },
            { 0.0f, 0.0f, zScale, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        return Matrix4(temp);
    }
    
    static Matrix4 CreateScale(const Vector3& scaleVector)
    {
        return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
    }
    
    static Matrix4 CreateScale(float scale)
    {
        return CreateScale(scale, scale, scale);
    }
    
    // rot x-axis
    static Matrix4 CreateRotaitonX(float theta)
    {
        float temp[4][4] =
        {
            { 1.0f, 0.0f, 0.0f , 0.0f },
            { 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
            { 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }
    
    // rot y-axis
    static Matrix4 CreateRotationY(float theta)
    {
        float temp[4][4] =
        {
            { Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }
    
    // rot z-axis
    static Matrix4 CreateRotationZ(float theta)
    {
        float temp[4][4] =
        {
            { Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
            { -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }
    
    
    // rot by quaternion
    static Matrix4 CreateFromQuaternion(const class Quaternion& q);
    
    static Matrix4 CreateTranslation(const Vector3& trans)
    {
        float temp[4][4] =
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { trans.x, trans.y, trans.z, 1.0f }
        };
        return Matrix4(temp);
    }
    
    static Matrix4 CreateLookAt(const Vector3& /*world pos of camera*/eye,
                                const Vector3& /*world point of target*/target,
                                const Vector3& /*camera up*/up)
    {
        // 左手座標系
        Vector3 zaxis = Vector3::Normalize(target - eye); // z on camera
        Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis)); // x on camera
        Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis)); // y on camera
        
        // 並進要素は, カメラの位置ベクトルをカメラの姿勢基底(xa,ya,za)への射影ベクトルの逆になる
        Vector3 trans;
        trans.x -= Vector3::Dot(xaxis, eye); // カメラ座標系X軸に射影
        trans.y -= Vector3::Dot(yaxis, eye); // カメラ座標系X軸に射影
        trans.z -= Vector3::Dot(zaxis, eye); // カメラ座標系Z軸に射影
        
        // 並進要素はカメラ姿勢行列の逆行列(=転置)になる
        float temp[4][4] =
        {/* 行優先表現 */
            { xaxis.x, yaxis.x, zaxis.x, 0.f },
            { xaxis.y, yaxis.y, zaxis.y, 0.f },
            { xaxis.z, yaxis.z, zaxis.z, 0.f },
            { trans.x, trans.y, trans.z, 1.f }
        };
        
        return Matrix4(temp);
    }
    
    /* 平行投影行列 */
    // シェーダーパイプライン内での計算に使用する
    // NDC Z: [0,1], 視線方向(target-eye)の向きがNDCのZ軸の正の向き
    // 平行投影行列 (カメラ座標系をNDC座標系に射影する)
    static Matrix4 CreateOrtho(float width, float height,
                               float near, float far)
    {
        float temp[4][4] =
        {/* 行優先表現 */
            { 2.f / width, 0.f, 0.f, 0.f },
            { 0.f, 2.f / height, 0.f, 0.f },
            { 0.f, 0.f, 1.f / (far - near), 0.f },
            { 0.f, 0.f, near / (near - far), 1.f }
        };
        return Matrix4(temp);
    }
    
    /* (垂直)視野角型の透視投影行列 */
    // シェーダーパイプライン内での計算に使用する
    // NDC Z: [0,1], 視線方向(target-eye)の向きがNDCのZ軸の正の向き?
    // 透視投影行列(FOV) (カメラ座標系をNDC座標系に射影する)
    static Matrix4 CreatePerspectiveFOV(float fovY, float width,
                                        float height, float near, float far)
    {
        float yScale = Math::Cot(fovY / 2.f); // 垂直方向を基準にする
        float xScale = yScale * height / width; // yScale * アスペクト比
        
        float temp[4][4] =
        { /* 行優先表現 */
            { xScale, 0.f, 0.f, 0.f },
            { 0.f, yScale, 0.f, 0.f },
            { 0.f, 0.f, far / (far - near), 1.f },
            { 0.f, 0.f, -near * far / (far - near), 0.f }
            // Z軸の値でPerspective Division
        };
        
        return Matrix4(temp);
    }
    
    // 2D用の平行投影行列 (2DWorld座標系をカメラ座標系に変換)
    static Matrix4 CreateSimpleViewProj(float width, float height)
    {
        float temp[4][4] =
        {
            { 2.f / width, 0.f, 0.f, 0.f },
            { 0.f, 2.f / height, 0.f, 0.f },
            { 0.f, 0.f, 1.f, 0.f }, // Z軸をZ軸に恒等射影
            { 0.f, 0.f, 1.f, 1.f } // Z軸の値をW設定 (Z軸の値でPerspective Division)
        };
        
        return Matrix4(temp);
    }
    
    
    static const Matrix4 Identity;

    
}; // class Matrix4

// Unit Quaternion
class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;
    
    Quaternion() { *this = Quaternion::Identity; }
    
    // This directly sets the quaternion components -- don't use for axis/angle
    explicit Quaternion(float inX, float inY, float inZ, float inW)
    {
        Set(inX, inY, inZ, inW);
    }
    
    // Construct the quaternion from an axis and angle
    // It is assumed that axis is already normalized,
    // and the angle is in radians
    explicit Quaternion(const Vector3& axis, float angle)
    {
        float scalar = Math::Sin(angle / 2.f);
        x = axis.x * scalar;
        y = axis.y * scalar;
        z = axis.z * scalar;
        w = Math::Cos(angle / 2.f);
    }
    
    // Directly set the internal components
    void Set(float inX, float inY, float inZ, float inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    
    // 共役クォータニオン
    void Conjugate()
    {
       x *= -1.0f;
       y *= -1.0f;
       z *= -1.0f;
    }
    
    float LengthSq() const
    {
        return (x*x + y*y + z*z + w*w);
    }
    
    float Length() const
    {
        return Math::Sqrt(LengthSq());
    }
    
    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
    
    // Normalize the provided quaternion
    static Quaternion Normalize(const Quaternion& q)
    {
        Quaternion retVal = q;
        retVal.Normalize();
        return retVal;
    }
    
    // 線形補間
    static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
    {
        Quaternion retVal;
        retVal.x = Math::Lerp(a.x, b.x, f);
        retVal.y = Math::Lerp(a.y, b.y, f);
        retVal.z = Math::Lerp(a.z, b.z, f);
        retVal.w = Math::Lerp(a.w, b.w, f);
        retVal.Normalize(); // クォータニオンが3次元回転を表現するのは、単位クォータニオンに限る
        return retVal;
    }
    
    // 内積
    static float Dot(const Quaternion& a, const Quaternion& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
    
    // 球面補間
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
    {
        float rawCosm = Quaternion::Dot(a,b); // rawCosmは正負が不明
        
        // cosomを必ず正値にする
        float cosom = -rawCosm;
        if (rawCosm >= 0.f)
        {
            cosom = rawCosm;
        }
        
        // スケールを決める
        float scale0, scale1;
        
        if (cosom < 0.9999f)
        {
            const float omega = Math::Acos(cosom);
            const float invSin = 1.f / Math::Sin(omega);
            scale0 = Math::Sin((1.f - f) * omega) * invSin;
            scale1 = Math::Sin(f * omega) * invSin;
        }
        else
        {
            // Use lineaer interpolation if the quaternions
            // are collinear (2つクォータニオンが共面関係)
            scale0 = 1.f - f;
            scale1 = f;
        }
        
        // もしrawCosmが負値の場合
        if (rawCosm < 0.f)
        {
            // scale1の符号を反転
            scale1 = -scale1;
        }
        
        // 補間Quaternionを作成
        Quaternion retVal;
        retVal.x = scale0 * a.x + scale1 * b.x;
        retVal.y = scale0 * a.y + scale1 * b.y;
        retVal.z = scale0 * a.z + scale1 * b.z;
        retVal.w = scale0 * a.w + scale1 * b.w;
        retVal.Normalize();
        return retVal;
    }
    
    // クォータニオンの連結
    // q(状態:姿勢)をp(作用:回転)で回転状態を進める
    // Rotate by q FOLLOWED BY p
    static Quaternion Concatenate(const Quaternion& q,
                                  const Quaternion& p)
    {
        Quaternion retVal;
        
        // Vector compoennt is:
        // ps * qv + qs * pv + pv x qv
        Vector3 qv(q.x,q.y,q.z);
        Vector3 pv(p.x,p.y,p.z);
        Vector3 newVec = p.w * qv + q.w * pv * Vector3::Cross(pv,qv);
        retVal.x = newVec.x;
        retVal.y = newVec.y;
        retVal.z = newVec.z;
        
        // wを決める
        // ps * qs - pv . qv
        retVal.w = p.w * q.w - Vector3::Dot(pv, qv);
        
        return retVal;
    }
    
    static const Quaternion Identity;
    
}; // class Quaternion

namespace Color
{
    static const Vector3 Black(0.0f, 0.0f, 0.0f);
    static const Vector3 White(1.0f, 1.0f, 1.0f);
    static const Vector3 Red(1.0f, 0.0f, 0.0f);
    static const Vector3 Green(0.0f, 1.0f, 0.0f);
    static const Vector3 Blue(0.0f, 0.0f, 1.0f);
    static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
    static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
    static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
    static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
    static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}

#endif /* Math_hpp */
