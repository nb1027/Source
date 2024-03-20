#include "Classes.h"

Vector3 WorldToScreen(Vector3 world_location, Vector3 position, FRotator rotation, float fov)
{
	Vector3 screen_location = Vector3(0, 0, 0);

	D3DMATRIX tempMatrix = ToMatrix(rotation, world_location);

	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = world_location - position;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float FovAngle = fov;
	double ScreenCenterX = 1920 / 2.0f;
	double ScreenCenterY = 1080 / 2.0f;

	screen_location.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (double)M_PI / 360.f)) / vTransformed.z;
	screen_location.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (double)M_PI / 360.f)) / vTransformed.z;
	screen_location.z = 0;

	return screen_location;
}

D3DMATRIX ToMatrix(FRotator Rotation, Vector3 origin)
{
	double Pitch = (Rotation.Pitch * double(UCONST_PI) / 180.f);
	double Yaw = (Rotation.Yaw * double(UCONST_PI) / 180.f);
	double Roll = (Rotation.Roll * double(UCONST_PI) / 180.f);

	double SP = sinf(Pitch);
	double CP = cosf(Pitch);
	double SY = sinf(Yaw);
	double CY = cosf(Yaw);
	double SR = sinf(Roll);
	double CR = cosf(Roll);

	D3DMATRIX Matrix;
	Matrix._11 = CP * CY;
	Matrix._12 = CP * SY;
	Matrix._13 = SP;
	Matrix._14 = 0.f;

	Matrix._21 = SR * SP * CY - CR * SY;
	Matrix._22 = SR * SP * SY + CR * CY;
	Matrix._23 = -SR * CP;
	Matrix._24 = 0.f;

	Matrix._31 = -(CR * SP * CY + SR * SY);
	Matrix._32 = CY * SR - CR * SP * SY;
	Matrix._33 = CR * CP;
	Matrix._34 = 0.f;

	Matrix._41 = origin.x;
	Matrix._42 = origin.y;
	Matrix._43 = origin.z;
	Matrix._44 = 1.f;

	return Matrix;
}