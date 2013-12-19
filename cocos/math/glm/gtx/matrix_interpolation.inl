///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-03-05
// Updated : 2011-03-05
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_interpolation.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER void axisAngle
	(
		detail::tmat4x4<T> const & mat,
		detail::tvec3<T> & axis,
		T & angle
	)
	{
		T epsilon = (T)0.01;
		T epsilon2 = (T)0.1;

		if ((fabs(mat[1][0] - mat[0][1]) < epsilon) && (fabs(mat[2][0] - mat[0][2]) < epsilon) && (fabs(mat[2][1] - mat[1][2]) < epsilon)) {
			if ((fabs(mat[1][0] + mat[0][1]) < epsilon2) && (fabs(mat[2][0] + mat[0][2]) < epsilon2) && (fabs(mat[2][1] + mat[1][2]) < epsilon2) && (fabs(mat[0][0] + mat[1][1] + mat[2][2] - (T)3.0) < epsilon2)) {
				angle = (T)0.0;
				axis.x = (T)1.0;
				axis.y = (T)0.0;
				axis.z = (T)0.0;
				return;
			}
			angle = T(3.1415926535897932384626433832795);
			T xx = (mat[0][0] + (T)1.0) / (T)2.0;
			T yy = (mat[1][1] + (T)1.0) / (T)2.0;
			T zz = (mat[2][2] + (T)1.0) / (T)2.0;
			T xy = (mat[1][0] + mat[0][1]) / (T)4.0;
			T xz = (mat[2][0] + mat[0][2]) / (T)4.0;
			T yz = (mat[2][1] + mat[1][2]) / (T)4.0;
			if ((xx > yy) && (xx > zz)) {
				if (xx < epsilon) {
					axis.x = (T)0.0;
					axis.y = (T)0.7071;
					axis.z = (T)0.7071;
				} else {
					axis.x = sqrt(xx);
					axis.y = xy / axis.x;
					axis.z = xz / axis.x;
				}
			} else if (yy > zz) {
				if (yy < epsilon) {
					axis.x = (T)0.7071;
					axis.y = (T)0.0;
					axis.z = (T)0.7071;
				} else {
					axis.y = sqrt(yy);
					axis.x = xy / axis.y;
					axis.z = yz / axis.y;
				}
			} else {
				if (zz < epsilon) {
					axis.x = (T)0.7071;
					axis.y = (T)0.7071;
					axis.z = (T)0.0;
				} else {
					axis.z = sqrt(zz);
					axis.x = xz / axis.z;
					axis.y = yz / axis.z;
				}
			}
			return;
		}
		T s = sqrt((mat[2][1] - mat[1][2]) * (mat[2][1] - mat[1][2]) + (mat[2][0] - mat[0][2]) * (mat[2][0] - mat[0][2]) + (mat[1][0] - mat[0][1]) * (mat[1][0] - mat[0][1]));
		if (glm::abs(s) < T(0.001))
			s = (T)1.0;
		angle = acos((mat[0][0] + mat[1][1] + mat[2][2] - (T)1.0) / (T)2.0);
		axis.x = (mat[1][2] - mat[2][1]) / s;
		axis.y = (mat[2][0] - mat[0][2]) / s;
		axis.z = (mat[0][1] - mat[1][0]) / s;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> axisAngleMatrix
	(
		detail::tvec3<T> const & axis,
		T const angle
	)
	{
		T c = cos(angle);
		T s = sin(angle);
		T t = T(1) - c;
		detail::tvec3<T> n = normalize(axis);

		return detail::tmat4x4<T>(
			t * n.x * n.x + c,          t * n.x * n.y + n.z * s,    t * n.x * n.z - n.y * s,    T(0),
			t * n.x * n.y - n.z * s,    t * n.y * n.y + c,          t * n.y * n.z + n.x * s,    T(0),
			t * n.x * n.z + n.y * s,    t * n.y * n.z - n.x * s,    t * n.z * n.z + c,          T(0),
			T(0),                        T(0),                        T(0),                     T(1)
		);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> extractMatrixRotation(
		detail::tmat4x4<T> const & mat)
	{
		return detail::tmat4x4<T>(
			mat[0][0], mat[0][1], mat[0][2], 0.0,
			mat[1][0], mat[1][1], mat[1][2], 0.0,
			mat[2][0], mat[2][1], mat[2][2], 0.0,
			0.0,       0.0,       0.0,       1.0
		);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> interpolate
	(
		detail::tmat4x4<T> const & m1,
		detail::tmat4x4<T> const & m2,
		T const delta
	)
	{
		detail::tmat4x4<T> m1rot = extractMatrixRotation(m1);
		detail::tmat4x4<T> dltRotation = m2 * transpose(m1rot);
		detail::tvec3<T> dltAxis;
		T dltAngle;
		axisAngle(dltRotation, dltAxis, dltAngle);
		detail::tmat4x4<T> out = axisAngleMatrix(dltAxis, dltAngle * delta) * m1rot;
		out[3][0] = m1[3][0] + delta * (m2[3][0] - m1[3][0]);
		out[3][1] = m1[3][1] + delta * (m2[3][1] - m1[3][1]);
		out[3][2] = m1[3][2] + delta * (m2[3][2] - m1[3][2]);
		return out;
	}
}//namespace glm
