#if !defined(MATRIX_4_H)
#define MATRIX_4_H

#include "quaternion.h"
#include "vector3.h"

#include <memory.h>

static float m4Ident[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}};

template <typename T = float> struct Matrix4
{
    static_assert(std::is_arithmetic_v<T>, "Matrix4 can only be instantiated with arithmetic types");

    T mat[4][4];

    inline static Matrix4 identity()
    {
        return Matrix4(m4Ident);
    }

    Matrix4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = m4Ident[i][j];
            }
        }
    }

    Matrix4(T inMat[4][4])
    {
        memcpy(mat, inMat, 16 * sizeof(T));
    }

    // Cast to a const T pointer
    const T *getAsFloatPtr() const
    {
        return reinterpret_cast<const T *>(&mat[0][0]);
    }

    // Matrix multiplication (a * b)
    friend Matrix4 operator*(const Matrix4 &a, const Matrix4 &b)
    {
        Matrix4 retVal;
        // row 0
        retVal.mat[0][0] = a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0] + a.mat[0][2] * b.mat[2][0] +
                           a.mat[0][3] * b.mat[3][0];

        retVal.mat[0][1] = a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1] + a.mat[0][2] * b.mat[2][1] +
                           a.mat[0][3] * b.mat[3][1];

        retVal.mat[0][2] = a.mat[0][0] * b.mat[0][2] + a.mat[0][1] * b.mat[1][2] + a.mat[0][2] * b.mat[2][2] +
                           a.mat[0][3] * b.mat[3][2];

        retVal.mat[0][3] = a.mat[0][0] * b.mat[0][3] + a.mat[0][1] * b.mat[1][3] + a.mat[0][2] * b.mat[2][3] +
                           a.mat[0][3] * b.mat[3][3];

        // row 1
        retVal.mat[1][0] = a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0] + a.mat[1][2] * b.mat[2][0] +
                           a.mat[1][3] * b.mat[3][0];

        retVal.mat[1][1] = a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1] + a.mat[1][2] * b.mat[2][1] +
                           a.mat[1][3] * b.mat[3][1];

        retVal.mat[1][2] = a.mat[1][0] * b.mat[0][2] + a.mat[1][1] * b.mat[1][2] + a.mat[1][2] * b.mat[2][2] +
                           a.mat[1][3] * b.mat[3][2];

        retVal.mat[1][3] = a.mat[1][0] * b.mat[0][3] + a.mat[1][1] * b.mat[1][3] + a.mat[1][2] * b.mat[2][3] +
                           a.mat[1][3] * b.mat[3][3];

        // row 2
        retVal.mat[2][0] = a.mat[2][0] * b.mat[0][0] + a.mat[2][1] * b.mat[1][0] + a.mat[2][2] * b.mat[2][0] +
                           a.mat[2][3] * b.mat[3][0];

        retVal.mat[2][1] = a.mat[2][0] * b.mat[0][1] + a.mat[2][1] * b.mat[1][1] + a.mat[2][2] * b.mat[2][1] +
                           a.mat[2][3] * b.mat[3][1];

        retVal.mat[2][2] = a.mat[2][0] * b.mat[0][2] + a.mat[2][1] * b.mat[1][2] + a.mat[2][2] * b.mat[2][2] +
                           a.mat[2][3] * b.mat[3][2];

        retVal.mat[2][3] = a.mat[2][0] * b.mat[0][3] + a.mat[2][1] * b.mat[1][3] + a.mat[2][2] * b.mat[2][3] +
                           a.mat[2][3] * b.mat[3][3];

        // row 3
        retVal.mat[3][0] = a.mat[3][0] * b.mat[0][0] + a.mat[3][1] * b.mat[1][0] + a.mat[3][2] * b.mat[2][0] +
                           a.mat[3][3] * b.mat[3][0];

        retVal.mat[3][1] = a.mat[3][0] * b.mat[0][1] + a.mat[3][1] * b.mat[1][1] + a.mat[3][2] * b.mat[2][1] +
                           a.mat[3][3] * b.mat[3][1];

        retVal.mat[3][2] = a.mat[3][0] * b.mat[0][2] + a.mat[3][1] * b.mat[1][2] + a.mat[3][2] * b.mat[2][2] +
                           a.mat[3][3] * b.mat[3][2];

        retVal.mat[3][3] = a.mat[3][0] * b.mat[0][3] + a.mat[3][1] * b.mat[1][3] + a.mat[3][2] * b.mat[2][3] +
                           a.mat[3][3] * b.mat[3][3];

        return retVal;
    }

    Matrix4 &operator*=(const Matrix4 &right)
    {
        *this = *this * right;
        return *this;
    }

    Vector3<T> getTranslation() const
    {
        return Vector3<T>(mat[3][0], mat[3][1], mat[3][2]);
    }

    Vector3<T> getXAxis() const
    {
        return Vector3<T>::normalize(Vector3<T>(mat[0][0], mat[0][1], mat[0][2]));
    }

    Vector3<T> getYAxis() const
    {
        return Vector3<T>::normalize(Vector3<T>(mat[1][0], mat[1][1], mat[1][2]));
    }

    Vector3<T> getZAxis() const
    {
        return Vector3<T>::normalize(Vector3<T>(mat[2][0], mat[2][1], mat[2][2]));
    }

    Vector3<T> getScale() const
    {
        Vector3<T> retVal;
        retVal.x = Vector3<T>(mat[0][0], mat[0][1], mat[0][2]).length();
        retVal.y = Vector3<T>(mat[1][0], mat[1][1], mat[1][2]).length();
        retVal.z = Vector3<T>(mat[2][0], mat[2][1], mat[2][2]).length();
        return retVal;
    }

    static Matrix4 createScale(T xScale, T yScale, T zScale)
    {
        T temp[4][4] = {{xScale, 0.0f, 0.0f, 0.0f},
                        {0.0f, yScale, 0.0f, 0.0f},
                        {0.0f, 0.0f, zScale, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f}};
        return Matrix4(temp);
    }

    static Matrix4 createScale(const Vector3<T> &scaleVector)
    {
        return createScale(scaleVector.x, scaleVector.y, scaleVector.z);
    }

    static Matrix4 createScale(T scale)
    {
        return createScale(scale, scale, scale);
    }

    static Matrix4 createRotationX(T theta)
    {
        T temp[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, Maths::cos(theta), Maths::sin(theta), 0.0f},
            {0.0f, Maths::sin(theta), Maths::cos(theta), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Matrix4(temp);
    }

    static Matrix4 createRotationY(T theta)
    {
        T temp[4][4] = {
            {Maths::cos(theta), 0.0f, -Maths::sin(theta), 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {Maths::sin(theta), 0.0f, Maths::cos(theta), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Matrix4(temp);
    }

    static Matrix4 createRotationZ(T theta)
    {
        T temp[4][4] = {
            {Maths::cos(theta), Maths::sin(theta), 0.0f, 0.0f},
            {-Maths::sin(theta), Maths::cos(theta), 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Matrix4(temp);
    }

    static Matrix4 createTranslation(const Vector3<T> &trans)
    {
        T temp[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {trans.x, trans.y, trans.z, 1.0f}};
        return Matrix4(temp);
    }

    static Matrix4 createSimpleViewProj(T width, T height)
    {
        T temp[4][4] = {{2.0f / width, 0.0f, 0.0f, 0.0f},
                        {0.0f, 2.0f / height, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 1.0f}};
        return Matrix4(temp);
    }

    static Matrix4 createFromQuaternion(const Quaternion &q)
    {
        T mat[4][4];

        mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
        mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
        mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
        mat[0][3] = 0.0f;

        mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
        mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
        mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
        mat[1][3] = 0.0f;

        mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
        mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
        mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
        mat[2][3] = 0.0f;

        mat[3][0] = 0.0f;
        mat[3][1] = 0.0f;
        mat[3][2] = 0.0f;
        mat[3][3] = 1.0f;

        return Matrix4(mat);
    }

    static Matrix4 createLookAt(const Vector3<T> &eye, const Vector3<T> &target, const Vector3<T> &up)
    {
        Vector3<T> zaxis = Vector3<T>::normalize(target - eye);
        Vector3<T> xaxis = Vector3<T>::normalize(Vector3<T>::cross(up, zaxis));
        Vector3<T> yaxis = Vector3<T>::normalize(Vector3<T>::cross(zaxis, xaxis));
        Vector3<T> trans;
        trans.x = -Vector3<T>::dot(xaxis, eye);
        trans.y = -Vector3<T>::dot(yaxis, eye);
        trans.z = -Vector3<T>::dot(zaxis, eye);

        T temp[4][4] = {{xaxis.x, yaxis.x, zaxis.x, 0.0f},
                        {xaxis.y, yaxis.y, zaxis.y, 0.0f},
                        {xaxis.z, yaxis.z, zaxis.z, 0.0f},
                        {trans.x, trans.y, trans.z, 1.0f}};
        return Matrix4(temp);
    }

    static Matrix4 createOrtho(T width, T height, T near, T far)
    {
        T temp[4][4] = {{2.0f / width, 0.0f, 0.0f, 0.0f},
                        {0.0f, 2.0f / height, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f / (far - near), 0.0f},
                        {0.0f, 0.0f, near / (near - far), 1.0f}};
        return Matrix4(temp);
    }

    static Matrix4 createPerspectiveFOV(T fovY, T width, T height, T near, T far)
    {
        T yScale = Maths::cot(fovY / 2.0f);
        T xScale = yScale * height / width;
        T temp[4][4] = {{xScale, 0.0f, 0.0f, 0.0f},
                        {0.0f, yScale, 0.0f, 0.0f},
                        {0.0f, 0.0f, far / (far - near), 1.0f},
                        {0.0f, 0.0f, -near * far / (far - near), 0.0f}};
        return Matrix4(temp);
    }

    // Invert the matrix - super slow
    inline void invert()
    {
        T tmp[12];
        T src[16];
        T dst[16];
        T det;

        // Transpose matrix
        // row 1 to col 1
        src[0] = mat[0][0];
        src[4] = mat[0][1];
        src[8] = mat[0][2];
        src[12] = mat[0][3];

        // row 2 to col 2
        src[1] = mat[1][0];
        src[5] = mat[1][1];
        src[9] = mat[1][2];
        src[13] = mat[1][3];

        // row 3 to col 3
        src[2] = mat[2][0];
        src[6] = mat[2][1];
        src[10] = mat[2][2];
        src[14] = mat[2][3];

        // row 4 to col 4
        src[3] = mat[3][0];
        src[7] = mat[3][1];
        src[11] = mat[3][2];
        src[15] = mat[3][3];

        // Calculate cofactors
        tmp[0] = src[10] * src[15];
        tmp[1] = src[11] * src[14];
        tmp[2] = src[9] * src[15];
        tmp[3] = src[11] * src[13];
        tmp[4] = src[9] * src[14];
        tmp[5] = src[10] * src[13];
        tmp[6] = src[8] * src[15];
        tmp[7] = src[11] * src[12];
        tmp[8] = src[8] * src[14];
        tmp[9] = src[10] * src[12];
        tmp[10] = src[8] * src[13];
        tmp[11] = src[9] * src[12];

        dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
        dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
        dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
        dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
        dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
        dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
        dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
        dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
        dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
        dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
        dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
        dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
        dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
        dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
        dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
        dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

        tmp[0] = src[2] * src[7];
        tmp[1] = src[3] * src[6];
        tmp[2] = src[1] * src[7];
        tmp[3] = src[3] * src[5];
        tmp[4] = src[1] * src[6];
        tmp[5] = src[2] * src[5];
        tmp[6] = src[0] * src[7];
        tmp[7] = src[3] * src[4];
        tmp[8] = src[0] * src[6];
        tmp[9] = src[2] * src[4];
        tmp[10] = src[0] * src[5];
        tmp[11] = src[1] * src[4];

        dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
        dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
        dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
        dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
        dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
        dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
        dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
        dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
        dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
        dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
        dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
        dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
        dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
        dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
        dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
        dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

        // Calculate determinant
        det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

        // Inverse of matrix is divided by determinant
        det = 1 / det;
        for (int j = 0; j < 16; j++)
        {
            dst[j] *= det;
        }

        // Set it back
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = dst[i * 4 + j];
            }
        }
    }
};

#endif
