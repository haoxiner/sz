#include "Scene.h"
#include <fstream>
Scene::Scene():currentModelIndex(0)
{}

void Scene::LoadConfig(const char * filepath)
{
	std::ifstream file(filepath);
	std::string line;
	while (std::getline(file,line))
	{
		filepathList.push_back(line);
	}
	Load(filepathList[0].c_str());
}

void Scene::Load(const char * filepath)
{
	boxMax = Point(-5000000, -5000000, -5000000);
	boxMin = Point(5000000, 5000000, 5000000);
	std::vector<tinyobj::material_t> mtls;
	std::string err;
	shapes.clear();
	tinyobj::LoadObj(shapes, mtls, err, filepath);
	int faceCount = 0;
	for (auto shape : shapes)
	{
		for (auto idx : shape.mesh.indices)
		{
			++faceCount;
			auto v = idx * 3;
			float x = shape.mesh.positions[v];
			++v;
			float y = shape.mesh.positions[v];
			++v;
			float z = shape.mesh.positions[v];
			if (boxMax.x < x)
			{
				boxMax.x = x;
			}
			if (boxMax.y < y)
			{
				boxMax.y = y;
			}
			if (boxMax.z < z)
			{
				boxMax.z = z;
			}

			if (boxMin.x > x)
			{
				boxMin.x = x;
			}
			if (boxMin.y > y)
			{
				boxMin.y = y;
			}
			if (boxMin.z > z)
			{
				boxMin.z = z;
			}
		}
	}
	center.x = (boxMax.x + boxMin.x) / 2;
	center.y = (boxMax.y + boxMin.y) / 2;
	center.z = (boxMax.z + boxMin.z) / 2;

	colorTable.resize(faceCount / 3);
	srand(0);
	for (auto iter = colorTable.begin();iter != colorTable.end();++iter)
	{
		int r = static_cast<int>(static_cast<float>(rand()) / RAND_MAX * 225 + 30);
		int g = static_cast<int>(static_cast<float>(rand()) / RAND_MAX * 225 + 30);
		int b = static_cast<int>(static_cast<float>(rand()) / RAND_MAX * 225 + 30);
		*iter = (r << 16 | g << 8 | b);
	}
}

void Scene::switchNext()
{
	++currentModelIndex;
	currentModelIndex = (currentModelIndex%filepathList.size());
	Load(filepathList[currentModelIndex].c_str());
}

