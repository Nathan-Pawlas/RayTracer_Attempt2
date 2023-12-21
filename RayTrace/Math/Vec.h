#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T>
class Vec
{
public:
	Vec();
	Vec(int numDims);
	Vec(std::vector<T> inputData);

	~Vec();


	int GetNumDims() const;
	T GetElement(int index) const;
	void SetElement(int index, T value);

	// Functions to perform computations on the vector.
	// Return the length of the vector.
	T norm();

	// Return a normalized copy of the vector.
	Vec<T> Normalized();

	// Normalize the vector in place.
	void Normalize();

	// Overloaded operators.
	Vec<T> operator+ (const Vec<T>& rhs) const;
	Vec<T> operator- (const Vec<T>& rhs) const;
	Vec<T> operator* (const T& rhs) const;

	// Friend functions.
	template <class U> friend Vec<U> operator* (const U& lhs, const Vec<U>& rhs);

	// Static functions.
	static T dot(const Vec<T>& a, const Vec<T>& b);
	static Vec<T> cross(const Vec<T>& a, const Vec<T>& b);

private:
	std::vector<T> m_vectorData;
	int m_nDims;

};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vec<T>::Vec()
{
	m_nDims = 0;
	m_vectorData = std::vector<T>();
}

template <class T>
Vec<T>::Vec(int numDims)
{
	m_nDims = numDims;
	m_vectorData = std::vector<T>(numDims, static_cast<T>(0.0));
}

template <class T>
Vec<T>::Vec(std::vector<T> inputData)
{
	m_nDims = inputData.size();
	m_vectorData = inputData;
}

template <class T>
Vec<T>::~Vec()
{

}

/* **************************************************************************************************
FUNCTIONS TO RETURN PARAMETERS
/* *************************************************************************************************/
template <class T>
int Vec<T>::GetNumDims() const
{
	return m_nDims;
}

/* **************************************************************************************************
FUNCTIONS TO HANDLE ELEMENTS OF THE VECTOR
/* *************************************************************************************************/
template <class T>
T Vec<T>::GetElement(int index) const
{
	return m_vectorData[index];
}

template <class T>
void Vec<T>::SetElement(int index, T value)
{
	m_vectorData[index] = value;
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector,known as the 'norm'.
template <class T>
T Vec<T>::norm()
{
	T cumulativeSum = static_cast<T>(0.0);
	for (int i = 0; i < m_nDims; ++i)
		cumulativeSum += (m_vectorData.at(i) * m_vectorData.at(i));

	return sqrt(cumulativeSum);
}

// Return a normalized copy of the vector.
template <class T>
Vec<T> Vec<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();

	// Compute the normalized version of the vector.
	Vec<T> result(m_vectorData);
	return result * (static_cast<T>(1.0) / vecNorm);
}

// Normalize the vector in place.
template <class T>
void Vec<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();

	// Compute the elements of the normalized version of the vector.
	for (int i = 0; i < m_nDims; ++i)
	{
		T temp = m_vectorData.at(i) * (static_cast<T>(1.0) / vecNorm);
		m_vectorData.at(i) = temp;
	}
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vec<T> Vec<T>::operator+ (const Vec<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (m_nDims != rhs.m_nDims)
		throw std::invalid_argument("Vector dimensions do not match.");

	Vec<T> resultData(m_nDims);
	for (int i = 0; i < m_nDims; ++i)
		resultData.SetElement(i, (m_vectorData.at(i) + rhs.m_vectorData.at(i)));

	return resultData;
}

template <class T>
Vec<T> Vec<T>::operator- (const Vec<T>& rhs) const
{
	// Check that the number of dimensions match.
	if (m_nDims != rhs.m_nDims)
		throw std::invalid_argument("Vector dimensions do not match.");

	Vec<T> resultData(m_nDims);
	for (int i = 0; i < m_nDims; ++i)
		resultData.SetElement(i, (m_vectorData.at(i) - rhs.m_vectorData.at(i)));

	return resultData;
}

template <class T>
Vec<T> Vec<T>::operator* (const T& rhs) const
{
	Vec<T> resultData(m_nDims);
	for (int i = 0; i < m_nDims; ++i)
		resultData.SetElement(i, (m_vectorData.at(i) * rhs));

	return resultData;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vec<T> operator* (const T& lhs, const Vec<T>& rhs)
{
	std::vector<T> resultData(rhs.m_nDims);
	for (int i = 0; i < rhs.m_nDims; ++i)
		resultData.at(i) = (lhs * rhs.m_vectorData.at(i));

	Vec<T> result(resultData);
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vec<T>::dot(const Vec<T>& a, const Vec<T>& b)
{
	// Check that the number of dimensions match.
	if (a.m_nDims != b.m_nDims)
		throw std::invalid_argument("Vector dimensions must match for the dot-product to be computed.");

	// Compute the dot product.
	T cumulativeSum = static_cast<T>(0.0);
	for (int i = 0; i < a.m_nDims; ++i)
		cumulativeSum += a.m_vectorData.at(i) * b.m_vectorData.at(i);

	return cumulativeSum;
}

template <class T>
Vec<T> Vec<T>::cross(const Vec<T>& a, const Vec<T>& b)
{
	// Check that the number of dimensions match.
	if (a.m_nDims != b.m_nDims)
		throw std::invalid_argument("Vector dimensions must match for the cross-product to be computed.");

	// Check that the number of dimensions is 3.
	/* Although the cross-product is also defined for 7 dimensions, we are
		not going to consider that case at this time. */
	if (a.m_nDims != 3)
		throw std::invalid_argument("The cross-product can only be computed for three-dimensional vectors.");

	// Compute the cross product.
	std::vector<T> resultData;
	resultData.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
	resultData.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
	resultData.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) - (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

	Vec<T> result(resultData);
	return result;
}
#endif // !VECTOR_H

