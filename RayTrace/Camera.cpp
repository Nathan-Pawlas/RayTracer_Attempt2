#include "Camera.h"
#include "Ray.h"
#include "Math/Vec.h"

Camera::Camera()
{
	m_CamPos = Vec<double>{ std::vector<double>{0.0, -10.0, 0.0} };
	m_CamLookAt = Vec<double>{ std::vector<double>{0.0, 0.0, 0.0} };
	m_CamUp = Vec<double>{ std::vector<double>{0.0, 0.0, 1.0} };
	m_CamLength = 1.0;
	m_CamHorzSize = 1.0;
	m_CamAspect = 1.0;
}

void Camera::SetPosition(const Vec<double>& newPos)
{
	m_CamPos = newPos;
}

void Camera::SetLookAt(const Vec<double>& newLookAt)
{
	m_CamLookAt = newLookAt;
}

void Camera::SetUp(const Vec<double>& upVector)
{
	m_CamUp = upVector;
}

void Camera::SetLength(double newLength)
{
	m_CamLength = newLength;
}

void Camera::SetHorizontalSize(double newSize)
{
	m_CamHorzSize = newSize;
}

void Camera::SetAspect(double newAspect)
{
	m_CamAspect = newAspect;
}

Vec<double> Camera::GetPos()
{
	return m_CamPos;
}

Vec<double> Camera::GetLookAt()
{
	return m_CamLookAt;
}

Vec<double> Camera::GetUp()
{
	return m_CamUp;
}

Vec<double> Camera::GetU()
{
	return m_ProjectionScreenU;
}

Vec<double> Camera::GetV()
{
	return m_ProjectionScreenV;
}

Vec<double> Camera::GetScreenCenter()
{
	return m_ProjectionScreenCenter;
}

double Camera::GetLength()
{
	return m_CamLength;
}

double Camera::GetHorizontalSize()
{
	return m_CamHorzSize;
}

double Camera::GetAspect()
{
	return m_CamAspect;
}

Ray Camera::GenerateRay(float proScreenX, float proScreenY)
{
	//Screen Space -> World Space
	Vec<double> worldCoordinate = (m_ProjectionScreenCenter + (m_ProjectionScreenU * proScreenX)) + (m_ProjectionScreenV * proScreenY);

	//Generate Ray from CamPos and World Coordinate
	return Ray(m_CamPos, worldCoordinate);
}

void Camera::UpdateCameraGeometry()
{
	//Get Vector From CamPos to LookAt
	m_AlignmentVector = m_CamLookAt - m_CamPos;
	m_AlignmentVector.Normalize();

	//Get U and V vecs
	m_ProjectionScreenU = Vec<double>::cross(m_AlignmentVector, m_CamUp);
	m_ProjectionScreenU.Normalize();
	m_ProjectionScreenV = Vec<double>::cross(m_ProjectionScreenU, m_AlignmentVector);
	m_ProjectionScreenV.Normalize();

	//Get Projection Center
	m_ProjectionScreenCenter = m_CamPos + (m_CamLength * m_AlignmentVector);

	//Modify U and V based on Aspect Ratio
	m_ProjectionScreenU = m_ProjectionScreenU * m_CamHorzSize;
	m_ProjectionScreenV = m_ProjectionScreenU * (m_CamHorzSize / m_CamAspect);
}


