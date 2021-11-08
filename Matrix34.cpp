#include "Matrix34.h"

// Constructors
Matrix34::Matrix34()
{
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = 0;
	}
}

Matrix34::Matrix34(float value[12])
{
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = value[i];
	}
}

Matrix34::Matrix34(float _l1[4], float _l2[4], float _l3[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->l1[i] = _l1[i];
		this->l2[i] = _l2[i];
		this->l3[i] = _l3[i];
	}
}

Matrix34::Matrix34(const Matrix34& matrix34)
{
	float* otherValue = matrix34.Get();
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = otherValue[i];
	}
}

//Getter / Setter
float* Matrix34::Get() const
{
	float valuesCopy[12];
	for (int i = 0; i < 12; i++)
	{
		valuesCopy[i] = this->values[i];
	}

	return valuesCopy;
}

void Matrix34::Set(float value[12])
{
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = value[i];
	}
}

//Operators
Matrix34& Matrix34::operator=(const Matrix34& other)
{
	float* otherValue = other.Get();
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = otherValue[i];
	}
	return *this;
}

Matrix34 Matrix34::operator*(const Matrix34& other) const
{
	float result[12];
	float* otherValue = other.Get();
	result[0] = values[0] * otherValue[0] + values[1] * otherValue[4] + values[2] * otherValue[8];
	result[1] = values[0] * otherValue[1] + values[1] * otherValue[5] + values[2] * otherValue[9];
	result[2] = values[0] * otherValue[2] + values[1] * otherValue[6] + values[2] * otherValue[10];
	result[3] = values[0] * otherValue[3] + values[1] * otherValue[7] + values[2] * otherValue[11] + values[3];
	result[4] = values[4] * otherValue[0] + values[5] * otherValue[4] + values[6] * otherValue[8];
	result[5] = values[4] * otherValue[1] + values[5] * otherValue[5] + values[6] * otherValue[9];
	result[6] = values[4] * otherValue[2] + values[5] * otherValue[6] + values[6] * otherValue[10];
	result[7] = values[4] * otherValue[3] + values[5] * otherValue[7] + values[6] * otherValue[11] + values[7];
	result[8] = values[8] * otherValue[0] + values[9] * otherValue[4] + values[10] * otherValue[8];
	result[9] = values[8] * otherValue[1] + values[9] * otherValue[5] + values[10] * otherValue[9];
	result[10] = values[8] * otherValue[2] + values[9] * otherValue[6] + values[10] * otherValue[10];
	result[11] = values[8] * otherValue[3] + values[9] * otherValue[7] + values[10] * otherValue[11] + values[11];
	Matrix34 resultMatrix = Matrix34(result);
	return resultMatrix;
}

//Vector3 Matrix34::operator*(const Vector3& vector) const
//{
//
//}

// << operator
std::ostream& operator<< (std::ostream& os, const Matrix34& matrix34)
{
	float* values = matrix34.Get();
	os << "{" << values[0] << ", " << values[1] << ", " << values[2] << ", " << values[3] << std::endl
		<< " " << values[4] << ", " << values[5] << ", " << values[6] << ", " << values[7] << std::endl
		<< " " << values[8] << ", " << values[9] << ", " << values[10] << ", " << values[11] << std::endl
		<< " " << "0" << ", " << "0" << ", " << "0" << ", " << "1" << "}" << std::endl;
	return os;
} 