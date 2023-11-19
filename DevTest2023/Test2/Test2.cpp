#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>  
#include <numeric>   
#include <cmath>  
#include <iomanip>

// V3 ////////////
// - Create a struct "V3" to store a 3D point (float)
// - Add to the structure a function to return the V3 length. Make sure this function can be called even if V3 is const.
struct V3
{
	float x;
	float y;
	float z;
    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
};

// - Create "+" and "-" operators for V3
V3 operator+(const V3& a, const V3& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

V3 operator-(const V3& a, const V3& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}



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

int main()
{
	//Caminhos
	const std::string path = "/home/luisfernando/Área de Trabalho/Teste/DevTest2023/Test2/Data1.txt3";
	const std::string path2 = "/home/luisfernando/Área de Trabalho/Teste/DevTest2023/Test2/Data2.txt3";
	//Pontos
	std::vector<V3> d1, d2, dataDif;
	//Pontos para comprimento
	std::vector<float> len;

	// - Read the files at the project dir "Data1.txt3" and "Data2.txt3". Store it to a vector named "d1" and "d2". Print the paths, number of points found.
	printf("Test 2\n");
	printf("--- Read data ---\n"); /////////////////////////////////
	//Lê os dois arquivos
	readData(path, d1);
	readData(path2, d2);
	
	//Imprime o número de pontos
	std::cout << "Data1.txt3: " << d1.size() << " number of points\n";
	std::cout << "Data2.txt3: " << d2.size() << " number of points\n";

	// - Print the bbox for d1 and d2
	printf("\n--- Bounding box ---\n");
	V3 minD1, maxD1, minD2, maxD2;
	
	BoundingBox(d1, minD1, maxD1);
	BoundingBox(d2, minD2, maxD2);

	std::cout << "Bounding box para d1: Min(" << minD1.x << ", " << minD1.y << ", " << minD1.z << ") Max("
			<< maxD1.x << ", " << maxD1.y << ", " << maxD1.z << ")\n";

	std::cout << "Bounding box para d2: Min(" << minD2.x << ", " << minD2.y << ", " << minD2.z << ") Max("
			<< maxD2.x << ", " << maxD2.y << ", " << maxD2.z << ")\n";


	// - Find if a point "V3 p1 = { 1.0f, -5.5f, 3.0f }" is inside d1 and d2. Print the result.
	printf("\n--- p1 is inside ---\n"); /////////////////////////////////
	V3 p1 = {1.0f, -5.5f, 3.0f};
	bool insideD1 = isInside(p1, minD1, maxD1);
	bool insideD2 = isInside(p1, minD2, maxD2);

	std::cout << "Is p1 inside d1? " << (insideD1 ? "Yes" : "No") << "\n";
	std::cout << "Is p1 inside d2? " << (insideD2 ? "Yes" : "No") << "\n";

	// - Print a line for each point id and value (3 decimals precision).
	//Calc a diff entre os 4 pontos e depois converte para len
	Subtract(d1, d2, dataDif);
	len = ConvertPoint2len(dataDif);
	printf("\n--- Points distances ---\n"); /////////////////////////////////
	
	float minLength = len[0];
	size_t minId = 0;

	for (size_t i = 0; i < len.size(); ++i)
	{
		//Id e value
		std::cout << "Point " << i << ": Length = " << len[i] << "\n";

		if (len[i] < minLength)
		{
			minLength = len[i];
			minId = i;
		}
	}

	// - Print the min length and id
	std::cout << "Min Length: " << minLength << " at Point " << minId << "\n";

	return 0;
}

if (!(iss >> point.x >> point.y >> point.z)) // Updated to read z-coordinate as well
{
	badDataFound = true; continue;
}