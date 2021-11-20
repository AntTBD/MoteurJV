#include "Matrix34.h"

// Constructors
Matrix34::Matrix34()
{
	this->values = std::vector<float>(12);
}

Matrix34::Matrix34(std::vector<float> value)
{
	this->values = std::vector<float>(12);
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

	int j = 0;
	for (int i = 0; i < 12; i++)
	{
		if (i != 3 && i != 7 && i != 11)
		{
			this->values[i] = matrix33.Get(j);
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
	return this->values;
}

float Matrix34::Get(int index) const
{
	return this->values[index];
}

Matrix33 Matrix34::GetMatrix33() const
{
	std::vector<float> valuesCopy(9);
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

// return transform matrix to be used with opengl (with transpose)
std::vector<float> Matrix34::GetMatrix44ForGL() const {

	std::vector<float> matrix44(16);
	matrix44[0] = values[0];
	matrix44[1] = values[4];
	matrix44[2] = values[8];
	matrix44[3] = 0.f;
	matrix44[4] = values[1];
	matrix44[5] = values[5];
	matrix44[6] = values[9];
	matrix44[7] = 0.f;
	matrix44[8] = values[2];
	matrix44[9] = values[6];
	matrix44[10] = values[10];
	matrix44[11] = 0.f;
	matrix44[12] = values[3];
	matrix44[13] = values[7];
	matrix44[14] = values[11];
	matrix44[15] = 1.f;

	return matrix44;
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
	std::vector<float> result(other.Get().size());
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
	Vector3 result = Vector3(
			values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ() + values[3],
			values[4] * vector.GetX() + values[5] * vector.GetY() + values[6] * vector.GetZ() + values[7],
			values[8] * vector.GetX() + values[9] * vector.GetY() + values[10] * vector.GetZ() + values[11]
			);

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

std::vector<float> Matrix34::operator[](int index) const
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

std::string Matrix34::toString() const {
    std::stringstream stream;
    stream << *this;
    return stream.str();
}
// << operator
std::ostream& operator<< (std::ostream& os, const Matrix34& matrix34)
{
	os << "{" << matrix34[0][0] << ", " << matrix34[0][1] << ", " << matrix34[0][2] << ", " << matrix34[0][3] << std::endl
		<< " " << matrix34[1][0] << ", " << matrix34[1][1] << ", " << matrix34[1][2] << ", " << matrix34[1][3] << std::endl
		<< " " << matrix34[2][0] << ", " << matrix34[2][1] << ", " << matrix34[2][2] << ", " << matrix34[2][3] << std::endl
		<< " " << "0" << ", " << "0" << ", " << "0" << ", " << "1" << "}" << std::endl;
	return os;
}

// product with a value
Matrix34 operator*(const Matrix34& mat, const float value)
{
	std::vector<float> result;
	for (int i = 0; i < 12; i++)
	{
		result[i] = mat.Get(i) * value;
	}
	return  { result };
}

Matrix34 operator*(const float value, const Matrix34& mat)
{
	return mat * value;
}

Matrix34 Matrix34::Inverse() const
{
	Matrix33 matrix33inv = this->GetMatrix33().Inverse();
	Vector3 vec3 = -1.f * matrix33inv * this->GetVector();

	return { matrix33inv, vec3 };
}

void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3& p)
{
	Matrix33 matrix33Quaternion;
	matrix33Quaternion.SetOrientation(q);

	*this = Matrix34(matrix33Quaternion, p);
}

Vector3 Matrix34::TransformPosition(const Vector3& vector) const
{
	return *this * vector;
}

Vector3 Matrix34::TransformInversePosition(const Vector3& vector) const
{
	Vector3 tmp = vector;
	tmp.SetX(tmp.GetX() - values[3]);
	tmp.SetY(tmp.GetY() - values[7]);
	tmp.SetZ(tmp.GetZ() - values[11]);
	return {
		tmp.GetX() * values[0] + tmp.GetY() * values[4] + tmp.GetZ() * values[8],
		tmp.GetX() * values[1] + tmp.GetY() * values[5] + tmp.GetZ() * values[9],
		tmp.GetX() * values[2] + tmp.GetY() * values[6] + tmp.GetZ() * values[10]
	};
}

Vector3 Matrix34::TransformDirection(const Vector3& vector) const
{
	Vector3 result(
			values[0] * vector.GetX() + values[1] * vector.GetY() + values[2] * vector.GetZ(),
			values[4] * vector.GetX() + values[5] * vector.GetY() + values[6] * vector.GetZ(),
			values[8] * vector.GetX() + values[9] * vector.GetY() + values[10] * vector.GetZ()
			);

	return result;
}

Vector3 Matrix34::TransformInverseDirection(const Vector3& vector) const
{
	Vector3 result(
			values[0] * vector.GetX() + values[4] * vector.GetY() + values[8] * vector.GetZ(),
			values[1] * vector.GetX() + values[5] * vector.GetY() + values[9] * vector.GetZ(),
			values[2] * vector.GetX() + values[6] * vector.GetY() + values[10] * vector.GetZ()
	);

	return result;
}

