#ifndef GTFM_H
#define GTFM_H

#include "./Math/Vec.h"
#include "./Math/Mat2.h"
#include "Ray.h"

//Direction Flag Values
constexpr bool FWDTFORM = true;
constexpr bool BCKTFORM = false;

class GTform //Geometric Transformations//
{
public:
	//Constructors
	GTform();
	~GTform();
	GTform(const Mat2<double>& fwd, const Mat2<double>& bck);

	//Set Transform Components
	void SetTransform(const Vec<double>& translation, const Vec<double>& rotation, const Vec<double>& scale);

	//Get Transform Matrices
	Mat2<double> GetForward();
	Mat2<double> GetBackward();

	//Apply Tranforms
	Ray Apply(const Ray& inputRay, bool dirFlag);
	Vec<double> Apply(const Vec<double>& inputVec, bool dirFlag);

	//Overload Operators
	friend GTform operator* (const GTform& lhs, const GTform& rhs);
	GTform operator= (const GTform& rhs);

	//Debug Print
	void PrintMatrix(bool dirFlag);
	static void PrintVector(const Vec<double>& vec);

private:
	void Print(const Mat2<double>& mat);

private:
	Mat2<double> m_fwdtfm{ 4, 4 };
	Mat2<double> m_bcktfm{ 4, 4 };
};

#endif // !GTFM_H
