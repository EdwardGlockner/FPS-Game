// Vector3.h
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-08.

//*********************************************************************************
// Header guard
//*********************************************************************************
#ifndef __VECTOR3_H
#define __VECTOR3_H

//*********************************************************************************
// Headers
//*********************************************************************************
#include <math.h>

//*********************************************************************************
// Class
//*********************************************************************************
class Vector3 {
    public:
        //Constructors and destructors
         
        // 
        // Vector3
        // Description:
        //      Construtor.
        //      Creates the 3D vector. Zero values by default.
        // Parameters:
        //      X <float>: x value.
        //      Y <float>: y value.
        //      Z <float>: z value.
        // Returns:
        //      None (void).
        //
        Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) {
            x = X;
            y = Y;
            z = Z;
        } 

        // Public class functions
        
        // 
        // operator+
        // Description:
        //      Addition operator.
        // Parameters:
        //      vec <Vector3&>: Vector that should be added.
        // Returns:
        //      <Vector3>: Sum of the two vectors.
        //
        Vector3 operator+(const Vector3& vec) {
            return Vector3(vec.x + x, vec.y + y, vec.z + z);
        } 

        // 
        // operator+=
        // Description:
        //      Addition equals operator.
        // Parameters:
        //      vec <Vector3&>: Vector that should be added.
        // Returns:
        //      <Vector3>: Sum of the two vectors.
        //
        Vector3 operator+=(const Vector3& vec) {
            return (*this = (*this + vec));
        }
        
        // 
        // operator-
        // Description:
        //      Subtraction operator.
        // Parameters:
        //      vec <Vector3&>: Vector that should be subtracted.
        // Returns:
        //      <Vector3>: Difference of the two vectors.
        //
        Vector3 operator-(const Vector3& vec) {
            return Vector3(x - vec.x, y - vec.y, z - vec.z);
        }        
         
        // 
        // operator-=
        // Description:
        //      Subtraction equals operator.
        // Parameters:
        //      vec <Vector3&>: Vector that should be subtracted
        // Returns:
        //      <Vector3>: Difference of the two vectors.
        //
        Vector3 operator-=(const Vector3& vec) {
            return (*this = (*this - vec));
        }
         
        // 
        // operator*
        // Description:
        //      Scalar multiplication operator.
        // Parameters:
        //      num <float>: Scalar value that should be multiplied.
        // Returns:
        //      <Vector3>: The scaled vector.
        //
        Vector3 operator*(float num) {
            return (*this = (*this * num)); 
        }        
         
        // 
        // operator*=
        // Description:
        //      Scalar multiplication equals operator.
        // Parameters:
        //      num <float>: Scalar value that should be multiplied.
        // Returns:
        //      <Vector3>: The scaled vector.
        //
        Vector3 operator*=(float num) {
            return Vector3(x * num , y * num, z * num);
        }
         
        // 
        // operator/
        // Description:
        //      Scalar division operator.
        // Parameters:
        //      num <float>: Scalar value that should be divided.
        // Returns:
        //      <Vector3>: The scaled vector.
        //
        Vector3 operator/(float num) {
            return (*this = (*this / num)); 
        }        
         
        // 
        // operator/=
        // Description:
        //      Scalar division equals operator.
        // Parameters:
        //      num <float>: Scalar value that should be divided.
        // Returns:
        //      <Vector3>: The scaled vector.
        //
        Vector3 operator/=(float num) {
            return Vector3(x / num , y / num, z / num);
        }
         
        // 
        // operator-
        // Description:
        //      Inverse operator.
        // Parameters:
        //      None (void).
        // Returns:
        //      <Vector3>: The inverted vector.
        //
        Vector3 operator-(void) {
            return Vector3(-x, -y, -z);
        }
         
        // 
        // Dot
        // Description:
        //      Dot product.
        // Parameters:
        //      vec <Vector3&>: The vector that should be multiplied.
        // Returns:
        //      <float>: The dot product of the two vectors.
        //
        float Dot(Vector3& vec) {
            return (x * vec.x + y * vec.y + z * vec.z);
        }
         
        // 
        // operator*
        // Description:
        //      Cross product.
        // Parameters:
        //      vec <Vector3&>: The vector that should be multiplied.
        // Returns:
        //      <Vector3>: The cross product of the two vectors.
        //
        Vector3 operator*(const Vector3& vec) {
            return Vector3(y * vec.z - z * vec.y,
                           z * vec.x - x * vec.z,
                           x * vec.y - y * vec.x);
        }
         
        // 
        // Length
        // Description:
        //      Calculates the euclidian length of the vector.
        // Parameters:
        //      None (void).
        // Returns:
        //      <float>: Length of the vector.
        //
        float Length(void) {
            return sqrt(x * x + y * y + z * z);
        }
         
        // 
        // Normalize
        // Description:
        //      Normalizes the vector.
        // Parameters:
        //      None (void).
        // Returns:
        //      None (void).
        //
        Vector3 Normalize(void) {
            float length = Length();

            x /= length;
            y /= length;
            z /= length;

            return *this;
        }
         
        // 
        // Distance
        // Description:
        //      Calculates the distance between two vectors.
        // Parameters:
        //      vec <Vector3&>: The vector for which to calculate the distance to.
        // Returns:
        //      <flotat>: The distance to the vector.
        //
        float Distance(Vector3& vec) {
            float disX = vec.x - x;
            float disY = vec.y - y;
            float disZ = vec.z - z;

            return sqrt(disX * disX + disY * disY + disZ * disZ);
        }
         
        // 
        // operator==
        // Description:
        //      Is equal to operator.
        // Parameters:
        //      vec <Vector3&>: Vector that is checked if it's equal to or not.
        // Returns:
        //      <bool>: If the two vectors are equal or not.
        //
        bool operator==(Vector3& vec) {
            return (vec.x == x && vec.y == y && vec.z == z);
        }
         
        // 
        // operator!=
        // Description:
        //      Not equal to operator.
        // Parameters:
        //      vec <Vector3&>: Vector that is checked if it's not equal to.
        // Returns:
        //      <bool>: If the two vectors are not equal or not.
        //
        bool operator!=(Vector3& vec) {
            return !(vec == *this);
        }

        // Public class members
        float x, y, z;
};

#endif

