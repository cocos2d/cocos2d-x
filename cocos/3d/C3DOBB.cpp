#include "Base.h"
#include "C3DOBB.h"
#include "C3DQuaternion.h"
#include "cocos2d.h"

namespace cocos2d
{
#define ROTATE(a,i,j,k,l) g=a.m[i + 4 * j]; h=a.m[k + 4 * l]; a.m[i + 4 * j]=(float)(g-s*(h+g*tau)); a.m[k + 4 * l]=(float)(h+s*(g-h*tau));

static Matrix _convarianceMatrix(const Vector3* aVertPos, int nVertCount)
{
	int i;
	Matrix Cov;

	double S1[3];
	double S2[3][3];

	S1[0] = S1[1] = S1[2] = 0.0;
	S2[0][0] = S2[1][0] = S2[2][0] = 0.0;
	S2[0][1] = S2[1][1] = S2[2][1] = 0.0;
	S2[0][2] = S2[1][2] = S2[2][2] = 0.0;

	// get center of mass
	for(i=0; i<nVertCount; i++)
	{
		S1[0] += aVertPos[i].x;
		S1[1] += aVertPos[i].y;
		S1[2] += aVertPos[i].z;

		S2[0][0] += aVertPos[i].x * aVertPos[i].x;
		S2[1][1] += aVertPos[i].y * aVertPos[i].y;
		S2[2][2] += aVertPos[i].z * aVertPos[i].z;
		S2[0][1] += aVertPos[i].x * aVertPos[i].y;
		S2[0][2] += aVertPos[i].x * aVertPos[i].z;
		S2[1][2] += aVertPos[i].y * aVertPos[i].z;
	}

	float n = (float)nVertCount;
	// now get covariances
	Cov.m[0] = (float)(S2[0][0] - S1[0]*S1[0] / n) / n;
	Cov.m[5] = (float)(S2[1][1] - S1[1]*S1[1] / n) / n;
	Cov.m[10] = (float)(S2[2][2] - S1[2]*S1[2] / n) / n;
	Cov.m[4] = (float)(S2[0][1] - S1[0]*S1[1] / n) / n;
	Cov.m[9] = (float)(S2[1][2] - S1[1]*S1[2] / n) / n;
	Cov.m[8] = (float)(S2[0][2] - S1[0]*S1[2] / n) / n;
	Cov.m[1] = Cov.m[4];
	Cov.m[2] = Cov.m[8];
	Cov.m[6] = Cov.m[9];

	return Cov;
}

static float& _getElement( Vector3& point, int index)
{
	if (index == 0)
		return point.x;
	if (index == 1)
		return point.y;
	if (index == 2)
		return point.z;

	CC_ASSERT(0);
	return point.x;
}

static void _eigenVectors(Matrix* vout, Vector3* dout, Matrix a)
{
	int n = 3;
	int j,iq,ip,i;
	double tresh,theta,tau,t,sm,s,h,g,c;
	int nrot;
	Vector3 b;
	Vector3 z;
	Matrix v;
	Vector3 d;

	v = Matrix::identity();
	for(ip=0; ip<n; ip++)
	{
		_getElement(b, ip) = a.m[ip + 4 * ip];
		_getElement(d, ip) = a.m[ip + 4 * ip];
		_getElement(z, ip) = 0.0;
	}

	nrot = 0;

	for(i=0; i<50; i++)
	{
		sm=0.0;
		for(ip=0; ip<n; ip++) for(iq=ip+1;iq<n;iq++) sm+=fabs(a.m[ip + 4 * iq]);
		if( sm == 0.0 )
		{
			v.transpose();
			*vout = v;
			*dout = d;
			return;
		}

		if (i < 3) tresh = 0.2 * sm / (n*n);
		else tresh=0.0;

		for(ip=0; ip<n; ip++)
		{
			for(iq=ip+1; iq<n; iq++)
			{
				g = 100.0*fabs(a.m[ip + iq * 4]);

				float dmip = _getElement(d, ip);
				float dmiq = _getElement(d, iq);
				if( i>3 && fabs(dmip)+g==fabs(dmip) && fabs(dmiq)+g==fabs(dmiq) )
					a.m[ip + 4 * iq]=0.0;
				else if (fabs(a.m[ip + 4 * iq])>tresh)
				{
					h = dmiq-dmip;
					if (fabs(h)+g == fabs(h))
						t=(a.m[ip + 4 * iq])/h;
					else
					{
						theta=0.5*h/(a.m[ip + 4 * iq]);
						t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a.m[ip + 4 * iq];
					_getElement(z, ip) -= (float)h;
					_getElement(z, iq) += (float)h;
					_getElement(d, ip) -= (float)h;
					_getElement(d, iq) += (float)h;
					a.m[ip + 4 * iq]=0.0;
					for(j=0;j<ip;j++) { ROTATE(a,j,ip,j,iq); }
					for(j=ip+1;j<iq;j++) { ROTATE(a,ip,j,j,iq); }
					for(j=iq+1;j<n;j++) { ROTATE(a,ip,j,iq,j); }
					for(j=0;j<n;j++) { ROTATE(v,j,ip,j,iq); }
					nrot++;
				}
			}
		}
		for(ip=0;ip<n;ip++)
		{
			_getElement(b, ip) += _getElement(z, ip);
			_getElement(d, ip) = _getElement(b, ip); // d.m[ip] = b.m[ip];
			_getElement(z, ip) = 0.0f; //z.m[ip] = 0.0;
		}
	}

	v.transpose();
	*vout = v;
	*dout = d;
	return;
}

//	return an OBB extracing from the vertices;
static Matrix _GetOBBOrientation(const Vector3* aVertPos, int nVertCount)
{
	Matrix Cov;

	if (nVertCount <= 0)
		return Matrix::identity();

	Cov = _convarianceMatrix(aVertPos, nVertCount);

	// now get eigenvectors
	Matrix Evecs;
	Vector3 Evals;
	_eigenVectors(&Evecs, &Evals, Cov);

	Evecs.transpose();

	return Evecs;
}

////////
C3DOBB::C3DOBB()
{
	clear();
}
C3DOBB::C3DOBB(const C3DOBB& obb)
{
}

// is point in this obb
bool C3DOBB::isPointIn(const Vector3& point) const
{
	Vector3 vd = point - center;

	float d = vd.dot(xAxis);
	if (d > extents.x || d < -extents.x)
		return false;

	d = vd.dot(yAxis);
	if (d > extents.y || d < -extents.y)
		return false;

	d = vd.dot(zAxis);
	if (d > extents.z || d < -extents.z)
		return false;

	return true;
}

// clear obb
void C3DOBB::clear()
{
	memset(this, 0, sizeof(C3DOBB));
}

// build obb from oriented bounding box
void C3DOBB::build(const C3DAABB& aabb)
{
	center = (aabb._min + aabb._max);
	center.scale(0.5f);
	xAxis = Vector3(1.0f, 0.0f, 0.0f);
	yAxis = Vector3(0.0f, 1.0f, 0.0f);
	zAxis = Vector3(0.0f, 0.0f, 1.0f);

	extents = aabb._max - aabb._min;
	extents.scale(0.5f);

	completeExtAxis();
}

// build obb from points
void C3DOBB::build(const Vector3* verts, int nVerts)
{
	clear();

	if (nVerts <= 0)
		return;

	Matrix matTransform = _GetOBBOrientation(verts, nVerts);

	//	For matTransform is orthogonal, so the inverse matrix is just rotate it;
	matTransform.transpose();

	Vector3 vecMax = matTransform * Vector3(verts[0].x, verts[0].y, verts[0].z);

	Vector3 vecMin = vecMax;

	for (int i=1; i < nVerts; i++)
	{
		Vector3 vect = matTransform * Vector3(verts[i].x, verts[i].y, verts[i].z);

		vecMax.x = vecMax.x > vect.x ? vecMax.x : vect.x;
		vecMax.y = vecMax.y > vect.y ? vecMax.y : vect.y;
		vecMax.z = vecMax.z > vect.z ? vecMax.z : vect.z;

		vecMin.x = vecMin.x < vect.x ? vecMin.x : vect.x;
		vecMin.y = vecMin.y < vect.y ? vecMin.y : vect.y;
		vecMin.z = vecMin.z < vect.z ? vecMin.z : vect.z;
	}

	matTransform.transpose();

	xAxis = Vector3(matTransform.m[0], matTransform.m[1], matTransform.m[2]);
	yAxis = Vector3(matTransform.m[4], matTransform.m[5], matTransform.m[6]);
	zAxis = Vector3(matTransform.m[8], matTransform.m[9], matTransform.m[10]);

	center	= 0.5f * (vecMax + vecMin);
	center *= matTransform;

	xAxis.normalize();
	yAxis.normalize();
	zAxis.normalize();

	extents = 0.5f * (vecMax - vecMin);

	completeExtAxis();
}

// face to the obb's -z direction
// verts[0] : front left bottom corner
// verts[1] : front right bottom corner
// verts[2] : front right top corner
// verts[3] : front left top corner
// verts[4] : back left bottom corner
// verts[5] : back right bottom corner
// verts[6] : back right top corner
// verts[7] : back left top corner
void C3DOBB::getVertices(Vector3* verts) const
{
	verts[0] = center - extX  - extY + extZ; //front left bottom;

	verts[1] = center + extX - extY + extZ; //front right bottom;

	verts[2] = center + extX + extY + extZ; //front right top corner;

	verts[3] = center - extX + extY + extZ;  //front left top corner;

	verts[4] = center - extX - extY - extZ; //back left bottom corner;

	verts[5] = center + extX - extY - extZ; //back right bottom corner

	verts[6] = center + extX + extY - extZ; //back right top corner

	verts[7] = center - extX + extY - extZ; //back left top corner;
}

void C3DOBB::transform(const Matrix& mat)
{
	Vector4 newcenter = mat * Vector4(center.x, center.y, center.z, 1.0f);// center;
	center.x = newcenter.x;
	center.y = newcenter.y;
	center.z = newcenter.z;

	xAxis = mat * xAxis;
	yAxis = mat * yAxis;
	zAxis = mat * zAxis;

	xAxis.normalize();
	yAxis.normalize();
	zAxis.normalize();

	Vector3 scale, trans;
	Quaternion quat;
	mat.decompose(&scale, &quat, &trans);

	extents.x *= scale.x;
	extents.y *= scale.y;
	extents.z *= scale.z;

	completeExtAxis();
}
}
