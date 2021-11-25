#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>

class RendererShaders
{
public:
	RendererShaders();
	~RendererShaders();
	void LoadShaders();
	std::string GetVertexShader(std::string name);
	std::string GetFragmentShader(std::string name);
	std::string GetGeometryShader(std::string name);
private:
	std::map<std::string, std::string> VertexShaders;
	std::map<std::string, std::string> FragmentShaders;
	std::map<std::string, std::string> GeometryShaders;
};

RendererShaders::RendererShaders()
{
}

RendererShaders::~RendererShaders()
{
}

void RendererShaders::LoadShaders()// loads shaders from default shader folder
{
	namespace fs = std::filesystem;
	std::string path("shaders");
	for (const auto& p : fs::directory_iterator(path))
	{
		if (p.path().extension() == (".vrt"))
		{
			std::string data;
			std::ifstream file (p.path());
			data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			VertexShaders.insert(std::make_pair(p.path().stem().string(), data));
		}
		if (p.path().extension() == (".frg"))
		{
			std::string data;
			std::ifstream file(p.path());
			data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			FragmentShaders.insert(std::make_pair(p.path().stem().string(), data));
		}
		if (p.path().extension() == (".gmr"))
		{
			std::string data;
			std::ifstream file(p.path());
			data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			GeometryShaders.insert(std::make_pair(p.path().stem().string(), data));

		}
		else
		{
			std::cout << "Warning: No shader file found in shaders directory" << std::endl;
		}

	}

}


std::string RendererShaders::GetVertexShader(std::string name)
{
	std::string VertexShader = VertexShaders[name];
	return VertexShader;
}

std::string RendererShaders::GetFragmentShader(std::string name)
{
	std::string FragmentShader = FragmentShaders[name];
	return FragmentShader;
}

std::string RendererShaders::GetGeometryShader(std::string name)
{
	std::string GeometryShader = GeometryShaders[name];
	return GeometryShader;
}
