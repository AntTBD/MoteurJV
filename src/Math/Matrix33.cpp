#include "Matrix33.h"

// Constructor
Matrix33::Matrix33()
{
	this->values = std::vector<float>(9);
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = 0;
	}
}

Matrix33::Matrix33(std::vector<float> value)
{
	this->values = std::vector<float>(9);

	assert(value.size() == 9 && "Size != 9");
	this->values = std::vector<float>(9);
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = value[i];
	}
}

Matrix33::Matrix33(const Matrix33& matrix33)
{
	this->values = matrix33.Get();

}

Matrix33::~Matrix33()
{

}

// Getter / Setter
std::vector<float> Matrix33::Get() const
{
	std::vector<float> valuesCopy(this->values);

	return valuesCopy;
}

float Matrix33::Get(int index) const
{
	return this->values[index];
}

void Matrix33::Set(std::vector<float> value)
{
	assert(value.size() == 9 && "Size != 9");
	this->values = value;
}

// operators
Matrix33& Matrix33::operator=(const Matrix33& other)
{
	std::vector<float> value = other.Get();
	for (int i = 0; i < 9; i++)
	{
		this->values[i] = value[i];
	}
	return *this;
}

Matrix33 Matrix33::operator*(const Matrix33& other) const
{
	std::vector<float> result(other.Get().size());
	std::vector<float> otherValue = other.Get();

	result[0] = values[0] * otherValue[0] + values[1] * otherValue[3] + values[2] * otherValue[6];
	result[1] = values[0] * otherValue[1] + values[1] * otherValue[4] + values[2] * otherValue[7];
	result[2] = values[0] * otherValue[2] + values[1] * otherValue[5] + values[2] * otherValue[8];
	result[3] = values[3] * otherValue[0] + values[4] * otherValue[3] + values[5] * otherValue[6];
	result[4] = values[3] * otherValue[1] + values[4] * otherValue[4] + values[5] * otherValue[7];
	result[5] = values[3] * otherValue[2] + values[4] * otherValue[5] + values[5] * otherValue[8];
	result[6] = values[6] * otherValue[0] + values[7] * otherValue[3] + values[8] * otherValue[6];
	result[7] = values[6] * otherValue[1] + values[7] * otherValue[4] + values[8] * otherValue[7];
	result[8] = values[6] * otherValue[2] + values[7] * otherValue[5] + values[8] * otherValue[8];
	return { result };
}

void Matrix33::operator*=(const Matrix33& other)
{
    *this = *this * other;
}

Vector3 Matrix33::operator*(const Vector3& vector) const
{
	Vector3 result = Vector3(values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ(),
							values[3] * vector.GetX() + values[4] * vector.GetY() + values[5] * vector.GetZ(),
							values[6] * vector.GetX() + values[7] * vector.GetY() + values[8] * vector.GetZ());

	return result;
}

std::vector<float> Matrix33::operator[](int index)
{
	if (index == 0)
	{
		std::vector<float> v = { this->values[0], this->values[1], this->values[2] };
		return v;
	}
	else if (index == 1)
	{
		std::vector<float> v = { this->values[3], this->values[4], this->values[5] };
		return v;
	}
	else if (index == 2)
	{
		std::vector<float> v = { this->values[6], this->values[7], this->values[8] };
		return v;
	}
}

std::string Matrix33::toString() const {
    std::stringstream stream;
    stream << *this;
    return stream.str();
}
// << operator
std::ostream& operator<< (std::ostream& os, const Matrix33& matrix33)
{
	std::vector<float> values =  matrix33.Get();
	os << "{" << values[0] << ", " << values[1] << ", " << values[2] << std::endl
		<< " " << values[3] << ", " << values[4] << ", " << values[5] << std::endl
		<< " " << values[6] << ", " << values[7] << ", " << values[8] << "}" << std::endl;
	return os;
}

// product with a value
Matrix33 operator*(const Matrix33& mat, const float value)
{
	std::vector<float> result(mat.Get().size());
	for (int i = 0; i < 9; i++)
	{
		result[i] = mat.Get(i) * value;
	}
	return { result };
}

Matrix33 operator*(const float value, const Matrix33& mat)
{
	return mat * value;
}

Vector3 Matrix33::TransformPosition(const Vector3& vector)
{
	return *this * vector;
}

Matrix33 Matrix33::Transpose()
{
	std::vector<float> matrixTValues(this->Get().size());
	matrixTValues[0] = values[0];
	matrixTValues[1] = values[3];
	matrixTValues[2] = values[6];
	matrixTValues[3] = values[1];
	matrixTValues[4] = values[4];
	matrixTValues[5] = values[7];
	matrixTValues[6] = values[2];
	matrixTValues[7] = values[5];
	matrixTValues[8] = values[8];

	return { matrixTValues };
}

Matrix33 Matrix33::Inverse()
{
	float detM = values[0] * values[4] * values[8]
				+ values[3] * values[7] * values[2]
				+ values[6] * values[1] * values[5]
				- values[0] * values[7] * values[5]
				- values[6] * values[4] * values[2]
				- values[3] * values[1] * values[8];
	std::vector<float> intermediateValue(this->Get().size());
	intermediateValue[0] = values[4] * values[8] - values[5] * values[7];
	intermediateValue[1] = values[2] * values[7] - values[1] * values[8];
	intermediateValue[2] = values[1] * values[5] - values[2] * values[4];
	intermediateValue[3] = values[5] * values[6] - values[3] * values[8];
	intermediateValue[4] = values[0] * values[8] - values[2] * values[6];
	intermediateValue[5] = values[2] * values[3] - values[0] * values[5];
	intermediateValue[6] = values[3] * values[7] - values[4] * values[6];
	intermediateValue[7] = values[1] * values[6] - values[0] * values[7];
	intermediateValue[8] = values[0] * values[4] - values[1] * values[3];
	
	Matrix33 intermediateMatrix(intermediateValue);

	return { 1.f / detM * intermediateMatrix };
}

void Matrix33::SetOrientation(const Quaternion& q)
{
    values[0] = 1.f - (2.f * pow(q.GetJ(), 2.f) + 2.f * pow(q.GetK(), 2.f));
    values[1] = 2.f * q.GetI() * q.GetJ() + 2.f * q.GetK() * q.GetW();
    values[2] = 2.f * q.GetI() * q.GetK() - 2.f * q.GetJ() * q.GetW();
    values[3] = 2.f * q.GetI() * q.GetJ() - 2.f * q.GetK() * q.GetW();
    values[4] = 1.f - (2.f * pow(q.GetI(), 2.f) + 2.f * pow(q.GetK(), 2.f));
    values[5] = 2.f * q.GetJ() * q.GetK() + 2.f * q.GetI() * q.GetW();
    values[6] = 2.f * q.GetI() * q.GetK() + 2.f * q.GetJ() * q.GetW();
    values[7] = 2.f * q.GetJ() * q.GetK() - 2.f * q.GetI() * q.GetW();
    values[8] = 1.f - (2.f * pow(q.GetI(), 2.f) + 2.f * pow(q.GetJ(), 2.f));
}


Matrix33 Matrix33::Transform(const Matrix34& transformMatrix) {

    // multiplication des 2 matrices en enlevant la dernière colonne
    Matrix33 transformMatrix33Original(transformMatrix.GetMatrix33());
    Matrix33 transformMatrix33 = transformMatrix33Original * this->values;

    // mutiplication par la tansposée
    Matrix33 matrixInWorld = transformMatrix33 * transformMatrix33Original.Transpose();

    return matrixInWorld;
}
