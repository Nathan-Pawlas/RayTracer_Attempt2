#include "gtfm.h"

GTform::GTform()
{
	//Set Fwd and Bck Transforms to Identifty Mat
	m_fwdtfm.SetToIdentity();
	m_bcktfm.SetToIdentity();
}

GTform::GTform(const Mat2<double>& fwd, const Mat2<double>& bck)
{
	//Verify Inputs are 4x4
	if ((fwd.GetNumRows() != 4 || fwd.GetNumCols() != 4) || (bck.GetNumCols() != 4 || bck.GetNumRows() != 4)) 
	{
		throw std::invalid_argument("Inputs for Geometric Transform are not 4x4");
	}

	m_fwdtfm = fwd;
	m_bcktfm = bck;
}

GTform::~GTform()
{
}

void GTform::SetTransform(const Vec<double>& translation, const Vec<double>& rotation, const Vec<double>& scale)
{
	//Define Matrix for each transformation
	Mat2<double> translationMat{ 4, 4 };
	Mat2<double> rotationMatX{ 4, 4 };
	Mat2<double> rotationMatY{ 4, 4 };
	Mat2<double> rotationMatZ{ 4, 4 };
	Mat2<double> scaleMat{ 4, 4 };

	//Set Transformation Matrices to Identity
	translationMat.SetToIdentity();
	rotationMatX.SetToIdentity();
	rotationMatY.SetToIdentity();
	rotationMatZ.SetToIdentity();
	scaleMat.SetToIdentity();

	//Set Values//
	//translation
	translationMat.SetElement(0, 3, translation.GetElement(0));
	translationMat.SetElement(1, 3, translation.GetElement(1));
	translationMat.SetElement(2, 3, translation.GetElement(2));

	//rotation
	rotationMatZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatZ.SetElement(1, 1, cos(rotation.GetElement(2)));

	rotationMatY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatY.SetElement(2, 2, cos(rotation.GetElement(1)));

	rotationMatX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatX.SetElement(2, 2, cos(rotation.GetElement(0)));

	//scale
	scaleMat.SetElement(0, 0, scale.GetElement(0));
	scaleMat.SetElement(1, 1, scale.GetElement(1));
	scaleMat.SetElement(2, 2, scale.GetElement(2));

	//Combine into Fwd Transform Matrix
	m_fwdtfm = translationMat * scaleMat * rotationMatX * rotationMatY * rotationMatZ;

	//Bck Transform Matrix
	m_bcktfm = m_fwdtfm;
	m_bcktfm.Inverse();
}

Mat2<double> GTform::GetForward()
{
	return m_fwdtfm;
}

Mat2<double> GTform::GetBackward()
{
	return m_bcktfm;
}

Ray GTform::Apply(const Ray& inputRay, bool dirFlag)
{
	Ray outputRay;

	outputRay.m_point1 = this->Apply(inputRay.m_point1, dirFlag);
	outputRay.m_point2 = this->Apply(inputRay.m_point2, dirFlag);
	outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;

	return outputRay;
}

Vec<double> GTform::Apply(const Vec<double>& inputVec, bool dirFlag)
{
	//Vec3 -> Vec4 (for homogenous coords in transform)
	std::vector<double> values{ inputVec.GetElement(0), inputVec.GetElement(1), inputVec.GetElement(2), 1.0 };
	Vec<double> tempVec{ values };

	Vec<double> resultVec;

	if (dirFlag)
		resultVec = m_fwdtfm * tempVec;
	else
		resultVec = m_bcktfm * tempVec;

	//Vec4 -> Vec3 (for our vectors in 3D space)
	return Vec<double> {std::vector<double> { resultVec.GetElement(0), resultVec.GetElement(1), resultVec.GetElement(2)}};
}

GTform GTform::operator=(const GTform& rhs)
{
	if (this == &rhs)
		return *this;

	m_fwdtfm = rhs.m_fwdtfm;
	m_bcktfm = rhs.m_bcktfm;

	return *this;
}

GTform operator*(const GTform& lhs, const GTform& rhs)
{
	Mat2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

	Mat2<double> bckResult = fwdResult;
	bckResult.Inverse();

	GTform finalTransform(fwdResult, bckResult);
	return finalTransform;
}

void GTform::PrintMatrix(bool dirFlag)
{
	if (dirFlag)
		Print(m_fwdtfm);
	else
		Print(m_bcktfm);
}

void GTform::PrintVector(const Vec<double>& vec)
{
	int n = vec.GetNumDims();
	for (int i = 0; i < n; i++)
	{
		std::cout << std::fixed << std::setprecision(3) << vec.GetElement(i) << ", ";
	}
	std::cout << std::endl;
}

void GTform::Print(const Mat2<double>& mat)
{
	int nRows = mat.GetNumRows();
	int nCols = mat.GetNumCols();

	for (int r = 0; r < nRows; r++)
	{
		for (int c = 0; c < nCols; c++)
		{
			std::cout << std::fixed << std::setprecision(3) << mat.GetElement(r, c) << " ";
		}
		std::cout << std::endl;
	}
}
