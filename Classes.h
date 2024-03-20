#pragma once

#include <cstdint>
#include <corecrt_math.h>
#include <intrin.h>
#include <string>
#include <Windows.h>
#include <d3d9types.h>

#define M_PI 3.14159265359
#define UCONST_PI 3.1415926
#define RadianToURotation 180.0f / M_PI

#ifndef D3DMATRIX_DEFINED
typedef struct _D3DMATRIX {
	union {
		struct {
			double        _11, _12, _13, _14;
			double        _21, _22, _23, _24;
			double        _31, _32, _33, _34;
			double        _41, _42, _43, _44;

		};
		double m[4][4];
	};
} D3DMATRIX;
#define D3DMATRIX_DEFINED
#endif

typedef struct D3DXMATRIX : public D3DMATRIX
{
public:
	D3DXMATRIX() {};
	D3DXMATRIX(CONST double*);
	D3DXMATRIX(CONST D3DMATRIX&);
	D3DXMATRIX(CONST WORD*);
	D3DXMATRIX(double _11, double _12, double _13, double _14,
		double _21, double _22, double _23, double _24,
		double _31, double _32, double _33, double _34,
		double _41, double _42, double _43, double _44);


	// access grants
	double& operator () (UINT Row, UINT Col);
	double  operator () (UINT Row, UINT Col) const;

	// casting operators
	operator double* ();
	operator CONST double* () const;

	// assignment operators
	D3DXMATRIX& operator *= (CONST D3DXMATRIX&);
	D3DXMATRIX& operator += (CONST D3DXMATRIX&);
	D3DXMATRIX& operator -= (CONST D3DXMATRIX&);
	D3DXMATRIX& operator *= (double);
	D3DXMATRIX& operator /= (double);

	// unary operators
	D3DXMATRIX operator + () const;
	D3DXMATRIX operator - () const;

	// binary operators
	D3DXMATRIX operator * (CONST D3DXMATRIX&) const;
	D3DXMATRIX operator + (CONST D3DXMATRIX&) const;
	D3DXMATRIX operator - (CONST D3DXMATRIX&) const;
	D3DXMATRIX operator * (double) const;
	D3DXMATRIX operator / (double) const;

	friend D3DXMATRIX operator * (double, CONST D3DXMATRIX&);

	BOOL operator == (CONST D3DXMATRIX&) const;
	BOOL operator != (CONST D3DXMATRIX&) const;

} D3DXMATRIX, * LPD3DXMATRIX;

struct Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}
	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	~Vector3() {}

	double x;
	double y;
	double z;

	inline double Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double Distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double ADistance(Vector3 src, Vector3 dst)
	{
		Vector3 diff = Subtract(src, dst);
		return Magnitude(diff);
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator==(Vector3 v)
	{
		return Vector3(x == v.x, y == v.y, z == v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline double Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	inline Vector3 Subtract(Vector3 src, Vector3 dst)
	{
		Vector3 diff;
		diff.x = src.x - dst.x;
		diff.y = src.y - dst.y;
		diff.z = src.z - dst.z;
		return diff;
	}
	double Magnitude(Vector3 vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
};

struct FRotator
{
public:
	double Pitch = 0.f;
	double Yaw = 0.f;
	double Roll = 0.f;

	D3DMATRIX GetAxes()
	{
		auto tempMatrix = Matrix();
		return tempMatrix;
	}

	D3DMATRIX Matrix(Vector3 origin = Vector3(0, 0, 0))
	{
		double radPitch = (Pitch * double(UCONST_PI) / 180.f);
		double radYaw = (Yaw * double(UCONST_PI) / 180.f);
		double radRoll = (Roll * double(UCONST_PI) / 180.f);
		double SP = sinf(radPitch);
		double CP = cosf(radPitch);
		double SY = sinf(radYaw);
		double CY = cosf(radYaw);
		double SR = sinf(radRoll);
		double CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}
};

D3DMATRIX ToMatrix(FRotator Rotation, Vector3 origin);

Vector3 WorldToScreen(Vector3 world_location, Vector3 position, FRotator rotation, float fov);

struct FQuat
{
	double x;
	double y;
	double z;
	double w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[0x8];
	Vector3 scale;
	char pad1[0x8];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rot.x + rot.x;
		double y2 = rot.y + rot.y;
		double z2 = rot.z + rot.z;

		double xx2 = rot.x * x2;
		double yy2 = rot.y * y2;
		double zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		double yz2 = rot.y * z2;
		double wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		double xy2 = rot.x * y2;
		double wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		double xz2 = rot.x * z2;
		double wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

struct FMinimalViewInfo
{
	Vector3 Location;
	FRotator Rotation;
	float FOV;
};

struct FCameraCacheEntry
{
public:
	char pad_0x0[0x10];
	FMinimalViewInfo POV;
};