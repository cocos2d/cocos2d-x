/*
 Copyright 2009 Johannes Vuorinen
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 
 http://www.apache.org/licenses/LICENSE-2.0 
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef OpenGLESMath_H_
#define OpenGLESMath_H_

#define PI 3.1415926535897932384626433832795f

#include <math.h>
#include <string.h>
#include "OpenGLESUtil.h"
#include "OpenGLESConfig.h"

namespace OpenGLES {
	
	// Column-major order
	template <class T>
	class Matrix4x4 {
	public:
		Matrix4x4() {
			for (int i = 0; i < 16; i++) {
				m[i] = 0;
			}
		}
		
		Matrix4x4(const Matrix4x4<T> &other) {
			for (int i = 0; i < 16; i++) {
				m[i] = other.m[i];
			}
		}
		
		Matrix4x4(const Matrix4x4<T> *other) {
			for (int i = 0; i < 16; i++) {
				m[i] = other->m[i];
			}
		}
		
		T& operator()(int i, int j) {
			return m[i*4 + j];
		}
		
		T operator()(int i, int j) const {
			return m[i*4 + j];
		}
		
		Matrix4x4<T>& operator= (const Matrix4x4<T> &other) {
			for (int i = 0; i < 16; i++) {
				m[i] = other.m[i];
			}
			
			return *this;
		}
		
		Matrix4x4<T>& operator= (const T *other) {
			for (int i = 0; i < 16; i++) {
				m[i] = other[i];
			}
			
			return *this;
		}
		
		bool operator== (const Matrix4x4<T> &other) {
			for (int i = 0; i < 16; i++) {
				if (m[i] != other.m[i]) {
					return false;
				}
			}
			
			return true;
		}
		
		bool operator!= (const Matrix4x4<T> &other) {
			
			return !operator==(other);
		}
		
		T m[16];
	};
	
	// Column-major order
	template <class T>
	struct Matrix3x3 {
		
		Matrix3x3() {
			for (int i = 0; i < 9; i++) {
				m[i] = 0;
			}
		}
		
		Matrix3x3(const Matrix3x3<T> &other) {
			for (int i = 0; i < 9; i++) {
				m[i] = other.m[i];
			}
		}
		
		Matrix3x3<T>& operator= (const Matrix3x3<T> &other) {
			for (int i = 0; i < 9; i++) {
				m[i] = other.m[i];
			}
			
			return *this;
		}
		
		T& operator()(int i, int j) {
			return m[i*3 + j];
		}
		
		T operator()(int i, int j) const {
			return m[i*3 + j];
		}
		
		bool operator== (const Matrix3x3<T> &other) {
			for (int i = 0; i < 9; i++) {
				if (m[i] != other.m[i]) {
					return false;
				}
			}
			
			return true;
		}
		
		bool operator!= (const Matrix3x3<T> &other) {
			
			return !operator==(other);
		}
		
		T m[9];
	};
	
	template <class T>
	class Vector3 {
	public:
		Vector3() {
			v[0] = 0;
			v[1] = 0;
			v[2] = 0;
		}
		
		Vector3(T x, T y, T z) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
		}
		
		Vector3(const T *a) {
			v[0] = a[0];
			v[1] = a[1];
			v[2] = a[2];
		}
		
		Vector3(const Vector3<T> &other) {
			v[0] = other.v[0];
			v[1] = other.v[1];
			v[2] = other.v[2];
		}
		
		Vector3(const Vector3<T> *other) {
			v[0] = other->v[0];
			v[1] = other->v[1];
			v[2] = other->v[2];
		}
		
		Vector3<T>& operator=(const Vector3<T> &other) {
			v[0] = other.v[0];
			v[1] = other.v[1];
			v[2] = other.v[2];
			
			return *this;
		}
		
		bool operator== (const Vector3<T> &other) {
			for (int i = 0; i < 3; i++) {
				if (v[i] != other.v[i]) {
					return false;
				}
			}
			
			return true;
		}
		
		bool operator!= (const Vector3<T> &other) {
			
			return !operator==(other);
		}
		
		T operator[] (int i) const {
			return v[i];
		}
		
		T& operator[] (int i) {
			return v[i];
		}
		
		Vector3<T> operator-() const {
			return Vector3<T>(-v[0], -v[1], -v[2]);
		}
		
		Vector3<T> operator-(const Vector3<T> &vec) const {
			return Vector3<T>(v[0] - vec.v[0], v[1] - vec.v[1], v[2] - vec.v[2]);
		}
		
		Vector3<T> operator+(const Vector3<T> &vec) const {
			return Vector3<T>(v[0] + vec.v[0], v[1] + vec.v[1], v[2] + vec.v[2]);
		}
		
		Vector3<T> operator*(const T s) const
		{
			return Vector3<T>(v[0]*s, v[1]*s, v[2]*s);
		}
		
		T v[3];
	};
	
	template <class T>
	class Vector4 {
	public:
		Vector4() {
			v[0] = 0;
			v[1] = 0;
			v[2] = 0;
			v[3] = 0;
		}
		
		Vector4(T x, T y, T z, T w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}
		
		Vector4(const T *a) {
			v[0] = a[0];
			v[1] = a[1];
			v[2] = a[2];
			v[3] = a[3];
		}
		
		Vector4(const Vector4<T> &other) {
			v[0] = other.v[0];
			v[1] = other.v[1];
			v[2] = other.v[2];
			v[3] = other.v[3];
		}
		
		Vector4(const Vector4<T> *other) {
			v[0] = other->v[0];
			v[1] = other->v[1];
			v[2] = other->v[2];
			v[3] = other->v[3];
		}
		
		Vector4<T>& operator=(const Vector4<T> &other) {
			v[0] = other.v[0];
			v[1] = other.v[1];
			v[2] = other.v[2];
			v[3] = other.v[3];
			
			return *this;
		}
		
		bool operator== (const Vector4<T> &other) {
			for (int i = 0; i < 4; i++) {
				if (v[i] != other.v[i]) {
					return false;
				}
			}
			
			return true;
		}
		
		bool operator!= (const Vector4<T> &other) {
			
			return !operator==(other);
		}
		
		T operator[] (int i) const {
			return v[i];
		}
		
		T &operator[] (int i) {
			return v[i];
		}
		
		T v[4];
	};
	
	class OpenGLESMath {
	public:
		
		template <typename T>
		static void scale(Matrix4x4<T> *result, T sx, T sy, T sz) 
		{
			result->m[0] *= sx;
			result->m[1] *= sx;
			result->m[2] *= sx;
			result->m[3] *= sx;
			
			result->m[4] *= sy;
			result->m[5] *= sy;
			result->m[6] *= sy;
			result->m[7] *= sy;
			
			result->m[8] *= sz;
			result->m[9] *= sz;
			result->m[10] *= sz;
			result->m[11] *= sz;
		}
		
		template <typename T>
		static void translate(Matrix4x4<T> *result, T tx, T ty, T tz)
		{
			result->m[12] += (result->m[0] * tx + result->m[4] * ty + result->m[8] * tz);
			result->m[13] += (result->m[1] * tx + result->m[5] * ty + result->m[9] * tz);
			result->m[14] += (result->m[2] * tx + result->m[6] * ty + result->m[10] * tz);
			result->m[15] += (result->m[3] * tx + result->m[7] * ty + result->m[11] * tz);
		}
		
		template <typename T>
		static void rotate(Matrix4x4<T> *result, T angle, T x, T y, T z)
		{
			T sinAngle = sinf(angle * PI / 180.0f);
			T cosAngle = cosf(angle * PI / 180.0f);
			T oneMinusCos = 1.0f - cosAngle;
			T mag = sqrtf(x * x + y * y + z * z);
			
			if (mag != 0.0f && mag != 1.0f) {
				x /= mag;
				y /= mag;
				z /= mag;
			}
			
			T xx = x * x;
			T yy = y * y;
			T zz = z * z;
			T xy = x * y;
			T yz = y * z;
			T zx = z * x;
			T xs = x * sinAngle;
			T ys = y * sinAngle;
			T zs = z * sinAngle;
			
			Matrix4x4<T> rotationMatrix;
			
			rotationMatrix.m[0] = (oneMinusCos * xx) + cosAngle;
			rotationMatrix.m[1] = (oneMinusCos * xy) - zs;
			rotationMatrix.m[2] = (oneMinusCos * zx) + ys;
			rotationMatrix.m[3] = 0.0f; 
			
			rotationMatrix.m[4] = (oneMinusCos * xy) + zs;
			rotationMatrix.m[5] = (oneMinusCos * yy) + cosAngle;
			rotationMatrix.m[6] = (oneMinusCos * yz) - xs;
			rotationMatrix.m[7] = 0.0f;
			
			rotationMatrix.m[8] = (oneMinusCos * zx) - ys;
			rotationMatrix.m[9] = (oneMinusCos * yz) + xs;
			rotationMatrix.m[10] = (oneMinusCos * zz) + cosAngle;
			rotationMatrix.m[11] = 0.0f; 
			
			rotationMatrix.m[12] = 0.0f;
			rotationMatrix.m[13] = 0.0f;
			rotationMatrix.m[14] = 0.0f;
			rotationMatrix.m[15] = 1.0f;
			
			multiply( result, &rotationMatrix, result );
		}
		
		template <typename T>
		static void frustum(Matrix4x4<T> *result, T left, T right, T bottom, T top, T nearZ, T farZ)
		{
			T deltaX = right - left;
			T deltaY = top - bottom;
			T deltaZ = farZ - nearZ;
			Matrix4x4<T> frust;
			
			if ((nearZ <= 0.0f) || (farZ <= 0.0f) || (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f)) {
				OPENGLES_LOG_DEBUG_MESSAGE("Invalid frustrum");
				return;
			}
			
			frust.m[0] = 2.0f * nearZ / deltaX;
			frust.m[1] = frust.m[2] = frust.m[3] = 0.0f;
			
			frust.m[5] = 2.0f * nearZ / deltaY;
			frust.m[4] = frust.m[6] = frust.m[7] = 0.0f;
			
			frust.m[8] = (right + left) / deltaX;
			frust.m[9] = (top + bottom) / deltaY;
			frust.m[10] = -(nearZ + farZ) / deltaZ;
			frust.m[11] = -1.0f;
			
			frust.m[14] = -2.0f * nearZ * farZ / deltaZ;
			frust.m[12] = frust.m[13] = frust.m[15] = 0.0f;
			
			multiply(result, &frust, result);
		}
		
		template <typename T>
		static void perspective(Matrix4x4<T> *result, T fovy, T aspect, T nearZ, T farZ)
		{
			T frustumHeight = tanf(fovy / 360 * PI) * nearZ;
			T frustumWidth = frustumHeight * aspect;
			
			frustum( result, -frustumWidth, frustumWidth, -frustumHeight, frustumHeight, nearZ, farZ );
		}
		
		template <typename T>
		static void ortho(Matrix4x4<T> *result, T left, T right, T bottom, T top, T nearZ, T farZ)
		{
			T deltaX = right - left;
			T deltaY = top - bottom;
			T deltaZ = farZ - nearZ;
			Matrix4x4<T> ortho;
			
			if ((deltaX == 0) || (deltaY == 0) || (deltaZ == 0)) {
				OPENGLES_LOG_MESSAGE("Invalid ortho");
				return;
			}
			
			loadIdentity(&ortho);
			ortho.m[0] = 2 / deltaX;
			ortho.m[12] = -(right + left) / deltaX;
			ortho.m[5] = 2 / deltaY;
			ortho.m[13] = -(top + bottom) / deltaY;
			ortho.m[10] = -2 / deltaZ;
			ortho.m[14] = -(nearZ + farZ) / deltaZ;
			
			multiply(result, &ortho, result);
		}
		
		template <typename T>
		static void multiply(Matrix4x4<T> *result, const Matrix4x4<T> * const srcA, const Matrix4x4<T> * const srcB)
		{
			Matrix4x4<T> tmp;
			
			for (int i = 0; i < 4; i++)
			{
				int a = 4*i;
				int b = a + 1;
				int c = a + 2;
				int d = a + 3;
				
				tmp.m[a] =	srcA->m[a] * srcB->m[0] +
				srcA->m[b] * srcB->m[4] +
				srcA->m[c] * srcB->m[8] +
				srcA->m[d] * srcB->m[12];
				
				tmp.m[b] =	srcA->m[a] * srcB->m[1] + 
				srcA->m[b] * srcB->m[5] +
				srcA->m[c] * srcB->m[9] +
				srcA->m[d] * srcB->m[13];
				
				tmp.m[c] =	srcA->m[a] * srcB->m[2] + 
				srcA->m[b] * srcB->m[6] +
				srcA->m[c] * srcB->m[10] +
				srcA->m[d] * srcB->m[14];
				
				tmp.m[d] =	srcA->m[a] * srcB->m[3] + 
				srcA->m[b] * srcB->m[7] +
				srcA->m[c] * srcB->m[11] +
				srcA->m[d] * srcB->m[15];
			}
			
			memcpy(result, &tmp, sizeof(Matrix4x4<T>));
		}
		
		template <typename T>
		static void multiply(Matrix4x4<T> *result, const Matrix4x4<T> * const srcA, const T* const srcB)
		{
			Matrix4x4<T> tmp;
			
			for (int i = 0; i < 4; i++)
			{
				int a = 4*i;
				int b = a + 1;
				int c = a + 2;
				int d = a + 3;
				
				tmp.m[a] =	srcA->m[a] * srcB[0] +
				srcA->m[b] * srcB[4] +
				srcA->m[c] * srcB[8] +
				srcA->m[d] * srcB[12];
				
				tmp.m[b] =	srcA->m[a] * srcB[1] + 
				srcA->m[b] * srcB[5] +
				srcA->m[c] * srcB[9] +
				srcA->m[d] * srcB[13];
				
				tmp.m[c] =	srcA->m[a] * srcB[2] + 
				srcA->m[b] * srcB[6] +
				srcA->m[c] * srcB[10] +
				srcA->m[d] * srcB[14];
				
				tmp.m[d] =	srcA->m[a] * srcB[3] + 
				srcA->m[b] * srcB[7] +
				srcA->m[c] * srcB[11] +
				srcA->m[d] * srcB[15];
			}
			
			memcpy(result, &tmp, sizeof(Matrix4x4<T>));
		}
		
		template <typename T>
		static void multiply(Matrix3x3<T> *result, const Matrix3x3<T> * const srcA, const Matrix3x3<T> * const srcB)
		{
			Matrix3x3<T> tmp;
			
			for (int i = 0; i < 3; i++)
			{
				int a = 3*i;
				int b = a + 1;
				int c = a + 2;
				
				tmp.m[a] =	srcA->m[a] * srcB->m[0] +
				srcA->m[b] * srcB->m[3] +
				srcA->m[c] * srcB->m[6];
				
				tmp.m[b] =	srcA->m[a] * srcB->m[1] + 
				srcA->m[b] * srcB->m[4] +
				srcA->m[c] * srcB->m[7];
				
				tmp.m[c] =	srcA->m[a] * srcB->m[2] + 
				srcA->m[b] * srcB->m[5] +
				srcA->m[c] * srcB->m[8];
			}
			
			memcpy(result, &tmp, sizeof(Matrix3x3<T>));
		}
		
		template <typename T>
		static void multiply(Vector3<T> *result, const Matrix3x3<T> * const srcA, const Vector3<T> * const srcB)
		{
			Vector3<T> tmp;
			for (int i = 0; i < 3; i++)
			{
				tmp.v[i] =	srcA->m[i] * srcB->v[0] +
				srcA->m[i + 3] * srcB->v[1] +
				srcA->m[i + 6] * srcB->v[2];
			}
			memcpy(result, &tmp, sizeof(Vector3<T>));
		}
		
		template <typename T>
		static void multiply(Vector4<T> *result, const Matrix4x4<T> * const srcA, const Vector4<T> * const srcB)
		{
			Vector4<T> tmp;
			for (int i = 0; i < 4; i++)
			{
				tmp.v[i] =	srcA->m[i] * srcB->v[0] +
				srcA->m[i + 4] * srcB->v[1] +
				srcA->m[i + 8] * srcB->v[2] +
				srcA->m[i + 12] * srcB->v[3];
			}
			memcpy(result, &tmp, sizeof(Vector4<T>));
		}
		
		template <typename T>
		static void loadIdentity(Matrix3x3<T> *result)
		{
			memset(result, 0x0, sizeof(Matrix3x3<T>));
			result->m[0] = 1;
			result->m[4] = 1;
			result->m[8] = 1;
		}
		
		template <typename T>
		static void loadIdentity(Matrix4x4<T> *result)
		{
			memset(result, 0x0, sizeof(Matrix4x4<T>));
			result->m[0] = 1;
			result->m[5] = 1;
			result->m[10] = 1;
			result->m[15] = 1;
		}
		
		template <typename T>
		static void transpose(Matrix3x3<T> *result)
		{
			Matrix3x3<T> tmp;
			
			tmp.m[0] = result->m[0];
			tmp.m[1] = result->m[3];
			tmp.m[2] = result->m[6];
			tmp.m[3] = result->m[1];
			tmp.m[4] = result->m[4];
			tmp.m[5] = result->m[7];
			tmp.m[6] = result->m[2];
			tmp.m[7] = result->m[5];
			tmp.m[8] = result->m[8];
			
			memcpy(result, &tmp, sizeof(Matrix3x3<T>));
		}
		
		template <typename T>
		static void transpose(Matrix4x4<T> *result)
		{
			Matrix4x4<T> tmp;
			
			tmp.m[0] = result->m[0];
			tmp.m[1] = result->m[4];
			tmp.m[2] = result->m[8];
			tmp.m[3] = result->m[12];
			tmp.m[4] = result->m[1];
			tmp.m[5] = result->m[5];
			tmp.m[6] = result->m[9];
			tmp.m[7] = result->m[13];
			tmp.m[8] = result->m[2];
			tmp.m[9] = result->m[6];
			tmp.m[10] = result->m[10];
			tmp.m[11] = result->m[14];
			tmp.m[12] = result->m[3];
			tmp.m[13] = result->m[7];
			tmp.m[14] = result->m[11];
			tmp.m[15] = result->m[15];
			
			memcpy(result, &tmp, sizeof(Matrix4x4<T>));
		}
		
		template <typename T>
		static void adjoint(Matrix3x3<T> *result, const Matrix3x3<T> * const src)
		{
			T a1 = src->m[0];
			T a2 = src->m[3];
			T a3 = src->m[6];
			
			T b1 = src->m[1];
			T b2 = src->m[4];
			T b3 = src->m[7];
			
			T c1 = src->m[2];
			T c2 = src->m[5];
			T c3 = src->m[8];
			
			result->m[0] = (b2*c3 - b3*c2);
			result->m[3] = (a3*c2 - a2*c3);
			result->m[6] = (a2*b3 - a3*b2);
			
			result->m[1] = (b3*c1 - b1*c3);
			result->m[4] = (a1*c3 - a3*c1);
			result->m[7] = (a3*b1 - a1*b3);
			
			result->m[2] = (b1*c2 - b2*c1);
			result->m[5] = (a2*c1 - a1*c2);
			result->m[8] = (a1*b2 - a2*b1);
		}
		
		template <typename T>
		static void inverse(Matrix3x3<T> *result, const Matrix3x3<T> * const src)
		{
			T a1 = src->m[0];
			T a2 = src->m[3];
			T a3 = src->m[6];
			
			T b1 = src->m[1];
			T b2 = src->m[4];
			T b3 = src->m[7];
			
			T c1 = src->m[2];
			T c2 = src->m[5];
			T c3 = src->m[8];
			
			T det = (a1*(b2*c3 - b3*c2) + a2*(b3*c1 - b1 * c3) + a3*(b1*c2 - b2*c1));
			
			result->m[0] = (b2*c3 - b3*c2)/det;
			result->m[3] = (a3*c2 - a2*c3)/det;
			result->m[6] = (a2*b3 - a3*b2)/det;
			
			result->m[1] = (b3*c1 - b1*c3)/det;
			result->m[4] = (a1*c3 - a3*c1)/det;
			result->m[7] = (a3*b1 - a1*b3)/det;
			
			result->m[2] = (b1*c2 - b2*c1)/det;
			result->m[5] = (a2*c1 - a1*c2)/det;
			result->m[8] = (a1*b2 - a2*b1)/det;
			
		}
		
		template <typename T>
		static void inverse(Matrix4x4<T> *result, const Matrix4x4<T> * const src)
		{
			int swap;
			T t;
			T temp[4][4];
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					temp[i][j] = (*src)(i, j);
				}
			}
			
			loadIdentity(result);
			
			for (int i = 0; i < 4; i++) {
				swap = i;
				for (int j = i + 1; j < 4; j++) {
					if (fabs(temp[j][i]) > fabs(temp[i][i])) {
						swap = j;
					}
				}
				
				if (swap != i) {
					for (int k = 0; k < 4; k++) {
						t = temp[i][k];
						temp[i][k] = temp[swap][k];
						temp[swap][k] = t;
						
						t = (*result)(i, k);
						(*result)(i, k) = (*result)(swap, k);
						(*result)(swap, k) = t;
					}
				}
				if (temp[i][i] == 0) {
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Matrix is singular, cannot invert.");
					return;
				}
				t = temp[i][i];
				for (int k = 0; k < 4; k++) {
					temp[i][k] /= t;
					(*result)(i, k) /= t;
				}
				for (int j = 0; j < 4; j++) {
					if (j != i) {
						t = temp[j][i];
						for (int k = 0; k < 4; k++) {
							temp[j][k] -= temp[i][k] * t;
							(*result)(j, k) -= (*result)(i, k) * t;
						}
					}
				}
			}
		}
		
		template <typename T>
		static void copyMatrix4x4UpperLeftToMatrix3x3(Matrix3x3<T> *result, const Matrix4x4<T> * const mat)
		{
			result->m[0] = mat->m[0];
			result->m[1] = mat->m[1];
			result->m[2] = mat->m[2];
			
			result->m[3] = mat->m[4];
			result->m[4] = mat->m[5];
			result->m[5] = mat->m[6];
			
			result->m[6] = mat->m[8];
			result->m[7] = mat->m[9];
			result->m[8] = mat->m[10];
		}
		
		template <typename T>
		static bool isUnitVector(Vector4<T> *vec)
		{
			T length = sqrtf(vec->v[0]*vec->v[0] + vec->v[1]*vec->v[1] + vec->v[2]*vec->v[2] + vec->v[3]*vec->v[3]);
			float epsilon = 0.01f;
			return 1.0f - epsilon <= length && length <= 1.0f + epsilon;
		}
		
		template <typename T>
		static T clamp(T t, T minV, T maxV) 
		{
			return std::max(std::min(maxV, t), minV);
		}
	};
	
}

#endif
