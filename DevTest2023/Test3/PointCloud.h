#pragma once
#include <vector>
#include <cmath>
#include <iostream>

struct V3
{
	float x;
	float y;
	float z;

	float Lenght() const { return std::sqrt(x * x + y * y + z * z); }
};

class PointCloud
{
public:
	std::vector<V3> Points;


	// V3 ////////////
	// - Create a struct "V3" to store a 3D point (float)
	// - Add to the structure a function to return the V3 length. Make sure this function can be called even if V3 is const.

	// // - Create "+" and "-" operators for V3
	// V3 operator+(const V3& a, const V3& b)
	// {
	// 	return {a.x + b.x, a.y + b.y, a.z + b.z};
	// }

	// V3 operator-(const V3& a, const V3& b)
	// {
	// 	return {a.x - b.x, a.y - b.y, a.z - b.z};
	// }



	// - Create a function to read from a text file and fill a vector of V3, each line is a V3 and values are separated by " ".
	void readData(const std::string& filename, std::vector<V3>& data);

	// - Create a function to find the Min values of two V3, and other to find the Max values.
	V3 minV3(const V3& a, const V3& b);

	// - Create a function to find the Min values of two V3, and other to find the Max values.
	V3 maxV3(const V3& a, const V3& b);
	//Create a function to evaluate the bounding box (bbox) of a vector<V3>. The function above may be handy.
	void BoundingBox(const std::vector<V3>& data, V3& minPoint, V3& maxPoint);

	// - Create a function to check if a point p is inside a bbox
	bool isInside(const V3& point, const V3& minBox, const V3& maxBox);

	// - Create a function to Subtract two V3. Call it to perform d2-d1 and store it at "dataDif".
	void Subtract(std::vector<V3>& d1, std::vector<V3>& d2, std::vector<V3>& dif);

	// - Create a function to convert a vector of points in a vector of lengths
	std::vector<float> ConvertPoint2len(std::vector<V3> points);

};