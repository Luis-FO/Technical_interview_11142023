#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>  
#include <numeric>   
#include <cmath>  
#include <iomanip>
#include "PointCloud.h"
// V3 ////////////
// - Create a struct "V3" to store a 3D point (float)
// - Add to the structure a function to return the V3 length. Make sure this function can be called even if V3 is const.

// // - Create "+" and "-" operators for V3
// V3 operator+(const V3& a, const V3& b)
// {
//     return {a.x + b.x, a.y + b.y, a.z + b.z};
// }

// V3 operator-(const V3& a, const V3& b)
// {
//     return {a.x - b.x, a.y - b.y, a.z - b.z};
// }



// - Create a function to read from a text file and fill a vector of V3, each line is a V3 and values are separated by " ".
void readData(const std::string& filename, std::vector<V3>& data)
{
	//Abre o arquivo
    std::ifstream file(filename);
    if (file.is_open())
    {
        V3 point;
		//https://stackoverflow.com/questions/7443787/using-c-ifstream-extraction-operator-to-read-formatted-data-from-a-file
        while (file >> point.x >> point.y >> point.z)
        {
            data.push_back(point);
        }
        file.close();
    }
}

// - Create a function to find the Min values of two V3, and other to find the Max values.
V3 minV3(const V3& a, const V3& b)
{
	//Quem é o min, o atual min ou o ponto corrente
    return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}

// - Create a function to find the Min values of two V3, and other to find the Max values.
V3 maxV3(const V3& a, const V3& b)
{
	//Quem é o max, o atual max ou o ponto corrente
    return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

//Create a function to evaluate the bounding box (bbox) of a vector<V3>. The function above may be handy.
void BoundingBox(const std::vector<V3>& data, V3& minPoint, V3& maxPoint)
{
    if (!data.empty())
    {
		//toma como ref o primeiro item
        minPoint = maxPoint = data[0];
		//Varre o vetor data
        for (const auto& point : data)
        {
            minPoint = minV3(minPoint, point);
            maxPoint = maxV3(maxPoint, point);
        }
    }
}

// - Create a function to check if a point p is inside a bbox
bool isInside(const V3& point, const V3& minBox, const V3& maxBox)
{	//Se as coordenadas estiverem dentro do intervalo entre min e max então está dentro
    return point.x >= minBox.x && point.x <= maxBox.x &&
           point.y >= minBox.y && point.y <= maxBox.y &&
           point.z >= minBox.z && point.z <= maxBox.z;
}

// - Create a function to Subtract two V3. Call it to perform d2-d1 and store it at "dataDif".
void Subtract(std::vector<V3>& d1, std::vector<V3>& d2, std::vector<V3>& dif){
	for (size_t i = 0; i < std::min(d1.size(), d2.size()); ++i)
	{
		dif.push_back(d2[i] - d1[i]);
	}
}

// - Create a function to convert a vector of points in a vector of lengths
std::vector<float> ConvertPoint2len(std::vector<V3> points){
	std::vector<float> lengths;
	for (const auto& point : points)
	{
		lengths.push_back(point.length());
	}
	return lengths;
}