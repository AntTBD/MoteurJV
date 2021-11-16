#include "Matrix34.h"
#include <assert.h>

// Constructors
Matrix34::Matrix34()
{
	this->values = std::vector<float>(12);
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = 0;
	}
}

Matrix34::Matrix34(std::vector<float> value)
{
	this->values = std::vector<float>(12);
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = 0;
	}
	assert(value.size() == 12 && "Size != 12");
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = value[i];
	}
}

Matrix34::Matrix34(const Matrix34& matrix34)
{
	this->values = matrix34.Get();
}

Matrix34::Matrix34(const Matrix33& matrix33, const Vector3& vec)
{
	this->values = std::vector<float>(12);
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = 0;
	}
	std::vector<float> matrix33Value = matrix33.Get();

	int j = 0;
	for (int i = 0; i < 12; i++)
	{
		if (i != 3 && i != 7 && i != 11)
		{
			this->values[i] = matrix33Value[j];
			j++;
		}
	}
	
	this->values[3] = vec.GetX();
	this->values[7] = vec.GetY();
	this->values[11] = vec.GetZ();
}

//Getter / Setter
std::vector<float> Matrix34::Get() const
{
	std::vector<float> valuesCopy(this->values);

	return valuesCopy;
}

float Matrix34::Get(int index) const
{
	return this->values[index];
}

Matrix33 Matrix34::GetMatrix33() const
{
	std::vector<float> valuesCopy;
	int j = 0;
	for (int i = 0; i < 12; i++)
	{
		if (i != 3 && i != 7 && i != 11)
		{
			valuesCopy[j] = this->values[i];
			j++;
		}
	}

	return { valuesCopy };
}

Vector3 Matrix34::GetVector() const
{
	return { this->Get(3), this->Get(7), this->Get(11) };
}

void Matrix34::Set(std::vector<float> value)
{
	assert(value.size() == 12 && "Size != 12");
	this->values = value;
}

//Operators
Matrix34& Matrix34::operator=(const Matrix34& other)
{
	std::vector<float> otherValue = other.Get();
	for (int i = 0; i < 12; i++)
	{
		this->values[i] = otherValue[i];
	}
	return *this;
}

Matrix34 Matrix34::operator*(const Matrix34& other) const
{
	std::vector<float> result;
	std::vector<float> otherValue = other.Get();

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
	return { result };
}

Vector3 Matrix34::operator*(const Vector3& vector) const
{
	Vector3 result = Vector3(values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ() + values[3],
							values[4] * vector.GetX() + values[5] * vector.GetY() + values[6] * vector.GetZ() + values[7],
							values[8] * vector.GetX() + values[9] * vector.GetY() + values[10] * vector.GetZ() + values[11]);

	return result;
}

std::vector<float> Matrix34::operator[](int index)
{
	if (index == 0)
	{
		std::vector<float> v = { this->values[0], this->values[1], this->values[2], this->values[3] };
		return v;
	}
	else if (index == 1)
	{
		std::vector<float> v = { this->values[4], this->values[5], this->values[6], this->values[7] };
		return v;
	}
	else if (index == 2)
	{
		std::vector<float> v = { this->values[8], this->values[9], this->values[10], this->values[11] };
		return v;
	}
}

// << operator
std::ostream& operator<< (std::ostream& os, const Matrix34& matrix34)
{
	std::vector<float> values = matrix34.Get();
	os << "{" << matrix34.Get()[0] << ", " << matrix34.Get()[1] << ", " << matrix34.Get()[2] << ", " << matrix34.Get()[3] << std::endl
		<< " " << matrix34.Get()[4] << ", " << matrix34.Get()[5] << ", " << matrix34.Get()[6] << ", " << matrix34.Get()[7] << std::endl
		<< " " << matrix34.Get()[8] << ", " << matrix34.Get()[9] << ", " << matrix34.Get()[10] << ", " << matrix34.Get()[11] << std::endl
		<< " " << "0" << ", " << "0" << ", " << "0" << ", " << "1" << "}" << std::endl;
	return os;
}

// product with a value
Matrix34 operator*(const Matrix34& mat, const float value)
{
	std::vector<float> result;
	std::vector<float> matValue = mat.Get();
	for (int i = 0; i < 12; i++)
	{
		result[i] = matValue[i] * value;
	}
	return  { result };
}

Matrix34 operator*(const float value, const Matrix34& mat)
{
	return mat * value;
}

Matrix34 Matrix34::Inverse()
{
	Matrix33 matrix33inv = this->GetMatrix33().Inverse();
	Vector3 vec3 = -1*matrix33inv * this->GetVector();

	return { matrix33inv, vec3 };
}

void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3& p)
{
	Matrix33 matrix33Quaternion;
	matrix33Quaternion.SetOrientation(q);
	std::vector<float> matrix33QuaternionValues = matrix33Quaternion.Get();

	int j = 0;
	for (int i = 0; i < 12; i++)
	{
		if (i != 3 && i != 7 && i != 11)
		{
			this->values[i] = matrix33QuaternionValues[j];
			j++;
		}
	}

	this->values[3] = p.GetX();
	this->values[7] = p.GetY();
	this->values[11] = p.GetZ();
}

Vector3 Matrix34::TransformPosition(const Vector3& vector)
{
	return *this * vector;
}

Vector3 Matrix34::TransformDirection(const Vector3& vector)
{
	Vector3 result = Vector3(values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ(),
		values[4] * vector.GetX() + values[5] * vector.GetY() + values[6] * vector.GetZ(),
		values[8] * vector.GetX() + values[9] * vector.GetY() + values[10] * vector.GetZ());

	return result;
}