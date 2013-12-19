///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2007-08-14
// Licence : This source is under MIT License
// File    : glm/gtx/euler_angles.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleX
	(
		valType const & angleX
	)
	{
		valType cosX = glm::cos(angleX);
		valType sinX = glm::sin(angleX);
	
		return detail::tmat4x4<valType>(
			valType(1), valType(0), valType(0), valType(0),
			valType(0), cosX,		sinX,		valType(0),
			valType(0),-sinX,		cosX,		valType(0),
			valType(0), valType(0), valType(0), valType(1));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleY
	(
		valType const & angleY
	)
	{
		valType cosY = glm::cos(angleY);
		valType sinY = glm::sin(angleY);

		return detail::tmat4x4<valType>(
			cosY,		valType(0),-sinY,		valType(0),
			valType(0),	valType(1),	valType(0), valType(0),
			sinY,		valType(0),	cosY,		valType(0),
			valType(0),	valType(0),	valType(0), valType(1));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleZ
	(
		valType const & angleZ
	)
	{
		valType cosZ = glm::cos(angleZ); 
		valType sinZ = glm::sin(angleZ);

		return detail::tmat4x4<valType>(
			cosZ,		sinZ,		valType(0), valType(0),
			-sinZ,		cosZ,		valType(0), valType(0),
			valType(0),	valType(0),	valType(1), valType(0),
			valType(0),	valType(0),	valType(0), valType(1));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleXY
	(
		valType const & angleX, 
		valType const & angleY
	)
	{
		valType cosX = glm::cos(angleX);
		valType sinX = glm::sin(angleX);
		valType cosY = glm::cos(angleY);
		valType sinY = glm::sin(angleY);

		return detail::tmat4x4<valType>(
			cosY,		-sinX * sinY,	cosX * sinY,	valType(0),
			valType(0), cosX,			sinX,			valType(0),
			-sinY ,		-sinX * cosY,	cosX * cosY,	valType(0),
			valType(0), valType(0),     valType(0),		valType(1));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleYX
	(
		valType const & angleY, 
		valType const & angleX
	)
	{
		valType cosX = glm::cos(angleX); 
		valType sinX = glm::sin(angleX); 
		valType cosY = glm::cos(angleY); 
		valType sinY = glm::sin(angleY);

		return detail::tmat4x4<valType>(
			cosY,			valType(0),		sinY,			valType(0),
			-sinX * sinY,	cosX,			sinX * cosY,	valType(0),
			-cosX * sinY,	-sinX,			cosX * cosY,	valType(0),
			valType(0),		valType(0),		valType(0),		valType(1));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleXZ
	(
		valType const & angleX, 
		valType const & angleZ
	)
	{
		return eulerAngleX(angleX) * eulerAngleZ(angleZ);
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleZX
	(
		valType const & angleZ, 
		valType const & angleX
	)
	{
		return eulerAngleZ(angleZ) * eulerAngleX(angleX);
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> eulerAngleYXZ
	(
		valType const & yaw, 
		valType const & pitch, 
		valType const & roll
	)
	{
		valType tmp_ch = glm::cos(yaw);
		valType tmp_sh = glm::sin(yaw);
		valType tmp_cp = glm::cos(pitch);
		valType tmp_sp = glm::sin(pitch);
		valType tmp_cb = glm::cos(roll);
		valType tmp_sb = glm::sin(roll);

		detail::tmat4x4<valType> Result;
		Result[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		Result[0][1] = tmp_sb * tmp_cp;
		Result[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		Result[0][3] = valType(0);
		Result[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		Result[1][1] = tmp_cb * tmp_cp;
		Result[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		Result[1][3] = valType(0);
		Result[2][0] = tmp_sh * tmp_cp;
		Result[2][1] = -tmp_sp;
		Result[2][2] = tmp_ch * tmp_cp;
		Result[2][3] = valType(0);
		Result[3][0] = valType(0);
		Result[3][1] = valType(0);
		Result[3][2] = valType(0);
		Result[3][3] = valType(1);
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> yawPitchRoll
	(
		valType const & yaw, 
		valType const & pitch, 
		valType const & roll
	)
	{
		valType tmp_ch = glm::cos(yaw);
		valType tmp_sh = glm::sin(yaw);
		valType tmp_cp = glm::cos(pitch);
		valType tmp_sp = glm::sin(pitch);
		valType tmp_cb = glm::cos(roll);
		valType tmp_sb = glm::sin(roll);

		detail::tmat4x4<valType> Result;
		Result[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		Result[0][1] = tmp_sb * tmp_cp;
		Result[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		Result[0][3] = valType(0);
		Result[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		Result[1][1] = tmp_cb * tmp_cp;
		Result[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		Result[1][3] = valType(0);
		Result[2][0] = tmp_sh * tmp_cp;
		Result[2][1] = -tmp_sp;
		Result[2][2] = tmp_ch * tmp_cp;
		Result[2][3] = valType(0);
		Result[3][0] = valType(0);
		Result[3][1] = valType(0);
		Result[3][2] = valType(0);
		Result[3][3] = valType(1);
		return Result;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tmat2x2<valType> orientate2
	(
		valType const & angle
	)
	{
		valType c = glm::cos(angle);
		valType s = glm::sin(angle);

		detail::tmat2x2<valType> Result;
		Result[0][0] = c;
		Result[0][1] = s;
		Result[1][0] = -s;
		Result[1][1] = c;
		return Result;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tmat3x3<valType> orientate3
	(
		valType const & angle
	)
	{
		valType c = glm::cos(angle);
		valType s = glm::sin(angle);

		detail::tmat3x3<valType> Result;
		Result[0][0] = c;
		Result[0][1] = s;
		Result[0][2] = 0.0f;
		Result[1][0] = -s;
		Result[1][1] = c;
		Result[1][2] = 0.0f;
		Result[2][0] = 0.0f;
		Result[2][1] = 0.0f;
		Result[2][2] = 1.0f;
		return Result;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tmat3x3<valType> orientate3
	(
		detail::tvec3<valType> const & angles
	)
	{
		return detail::tmat3x3<valType>(yawPitchRoll(angles.x, angles.y, angles.z));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> orientate4
	(
		detail::tvec3<valType> const & angles
	)
	{
		return yawPitchRoll(angles.z, angles.x, angles.y);
	}
}//namespace glm
