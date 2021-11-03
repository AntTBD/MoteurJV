#include "Matrix33.h"

// Constructor
Matrix33::Matrix33()
{
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = 0;
	}
}

Matrix33::Matrix33(float value[9])
{
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = value[i];
	}
}

Matrix33::Matrix33(float _l1[3], float _l2[3], float _l3[3])
{
	for (int i = 0; i < 3; i++)
	{
		this->l1[i] = _l1[i];
		this->l2[i] = _l2[i];
		this->l3[i] = _l3[i];
	}
}

Matrix33::Matrix33(const Matrix33& matrix33)
{
	float* otherValue = matrix33.Get();
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = otherValue[i];
	}
}

// Getter / Setter
float* Matrix33::Get() const
{
	float valuesCopy[9];
	for (int i = 0; i < 9; i++)
	{
		valuesCopy[i] = this->values[i];
	}

	return valuesCopy;
}

void Matrix33::Set(float value[9])
{
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = value[i];
	}
}

// operators
Matrix33& Matrix33::operator=(const Matrix33& other)
{
	float* otherValue = other.Get();
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = otherValue[i];
	}
	return *this;
}

Matrix33 Matrix33::operator*(const Matrix33& other) const
{
	float result[9];
	float* otherValue = other.Get();
	result[0] = values[0] * otherValue[0] + values[1] * otherValue[3] + values[2] * otherValue[6];
	result[1] = values[0] * otherValue[1] + values[1] * otherValue[4] + values[2] * otherValue[7];
	result[2] = values[0] * otherValue[2] + values[1] * otherValue[5] + values[2] * otherValue[8];
	result[3] = values[3] * otherValue[0] + values[4] * otherValue[3] + values[5] * otherValue[6];
	result[4] = values[3] * otherValue[1] + values[4] * otherValue[4] + values[5] * otherValue[7];
	result[5] = values[3] * otherValue[2] + values[4] * otherValue[5] + values[5] * otherValue[8];
	result[6] = values[6] * otherValue[0] + values[7] * otherValue[3] + values[8] * otherValue[6];
	result[7] = values[6] * otherValue[1] + values[7] * otherValue[4] + values[8] * otherValue[7];
	result[8] = values[6] * otherValue[2] + values[7] * otherValue[5] + values[8] * otherValue[8];
	Matrix33 resultMatrix = Matrix33(result);
	return resultMatrix;
}

Vector3 Matrix33::operator*(const Vector3& vector) const
{
	Vector3 result = Vector3(values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ(),
							values[3] * vector.GetX() + values[4] * vector.GetY() + values[5] * vector.GetZ(),
							values[6] * vector.GetX() + values[7] * vector.GetY() + values[8] * vector.GetZ());

	return result;
}

float* Matrix33::operator[](int index)
{
	if (index == 0)
	{
		return l1;
	}
	else if (index == 1)
	{
		return l2;
	}
	else if (index == 2)
	{
		return l3;
	}
}

// << operator
std::ostream& operator<< (std::ostream& os, const Matrix33& matrix33)
{
	float* values =  matrix33.Get();
	os << "{" << values[0] << ", " << values[1] << ", " << values[2] << std::endl
		<< " " << values[3] << ", " << values[4] << ", " << values[5] << std::endl
		<< " " << values[6] << ", " << values[7] << ", " << values[8] << "}" << std::endl;
	return os;
}

// product with a value
Matrix33 operator*(const Matrix33& mat, const float value)
{
	float result[9];
	float* matValue = mat.Get();
	for (int i = 0; i < 9; i++)
	{
		result[i] = matValue[i] * value;
	}
	Matrix33 resultM = Matrix33(result);
	return resultM;
}

Matrix33 operator*(const float value, const Matrix33& mat)
{
	return mat * value;
}

Matrix33 Matrix33::Transpose()
{
	float matrixTValues[9];
	matrixTValues[0] = values[0];
	matrixTValues[1] = values[3];
	matrixTValues[2] = values[6];
	matrixTValues[3] = values[1];
	matrixTValues[4] = values[4];
	matrixTValues[5] = values[7];
	matrixTValues[6] = values[2];
	matrixTValues[7] = values[5];
	matrixTValues[8] = values[8];
	
	Matrix33 matrixT = Matrix33(matrixTValues);

	return matrixT;
}

Matrix33 Matrix33::Inverse()
{
	float detM = values[0] * values[4] * values[8]
				+ values[3] * values[7] * values[2]
				+ values[6] * values[1] * values[5]
				- values[0] * values[7] * values[5]
				- values[6] * values[4] * values[2]
				- values[3] * values[1] * values[8];
	float intermediateValue[9];
	intermediateValue[0] = values[4] * values[8] - values[5] * values[7];
	intermediateValue[1] = values[2] * values[7] - values[1] * values[8];
	intermediateValue[2] = values[1] * values[5] - values[2] * values[4];
	intermediateValue[3] = values[5] * values[6] - values[3] * values[8];
	intermediateValue[4] = values[0] * values[8] - values[2] * values[6];
	intermediateValue[5] = values[2] * values[3] - values[0] * values[5];
	intermediateValue[6] = values[3] * values[7] - values[4] * values[6];
	intermediateValue[7] = values[1] * values[6] - values[0] * values[7];
	intermediateValue[8] = values[0] * values[4] - values[1] * values[3];
	
	Matrix33 intermediateMatrix = Matrix33(intermediateValue);

	Matrix33 invMatrix;
	invMatrix = 1 / detM * intermediateMatrix;

	return invMatrix;
}

void Matrix33::SetOrientation(const Quaternion& q)
{
	values[0] = 1 - (2*pow(q.GetJ(), 2) + 2*pow(q.GetK(), 2));
	values[1] = 2 * q.GetI() * q.GetJ() + 2 * q.GetK() * q.GetW();
	values[2] = 2 * q.GetI() * q.GetK() - 2 * q.GetJ() * q.GetW();
	values[3] = 2 * q.GetI() * q.GetJ() - 2 * q.GetK() * q.GetW();
	values[4] = 1 - (2 * pow(q.GetI(), 2) + 2 * pow(q.GetK(), 2));
	values[5] = 2 * q.GetJ() * q.GetK() + 2 * q.GetI() * q.GetW();
	values[6] = 2 * q.GetI() * q.GetK() + 2 * q.GetJ() * q.GetW();
	values[7] = 2 * q.GetJ() * q.GetK() - 2 * q.GetI() * q.GetW();
	values[8] = 1 - (2 * pow(q.GetI(), 2) + 2 * pow(q.GetJ(), 2));
}