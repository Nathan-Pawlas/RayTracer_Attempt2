#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Vec.h"
#include "Ray.h"

class Camera {
public:
	Camera();

	void SetPosition(const Vec<double>& newPos);
	void SetLookAt(const Vec<double>& newLookAt);
	void SetUp(const Vec<double>& upVector);
	void SetLength(double newLength);
	void SetHorizontalSize(double newSize);
	void SetAspect(double newAspect);

	Vec<double> GetPos();
	Vec<double> GetLookAt();
	Vec<double> GetUp();
	Vec<double> GetU();
	Vec<double> GetV();
	Vec<double> GetScreenCenter();
	double		GetLength();
	double		GetHorizontalSize();
	double		GetAspect();

	Ray GenerateRay(float proScreenX, float proScreenY);

	void UpdateCameraGeometry();

private:
	Vec<double> m_CamPos	{3};
	Vec<double> m_CamLookAt {3};
	Vec<double> m_CamUp		{3};
	double m_CamLength;
	double m_CamHorzSize;
	double m_CamAspect;

	Vec<double> m_AlignmentVector		{3};
	Vec<double> m_ProjectionScreenU		{3};
	Vec<double> m_ProjectionScreenV		{3};
	Vec<double> m_ProjectionScreenCenter{3};


};

#endif // !CAMERA_H
