/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//= INCLUDES ==========
#include "FileSystem.h"
#include "dirent.h"
#include <locale>
//=====================

//= NAMESPACES =====
using namespace std;

//==================

bool FileSystem::FileExists(const string& path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

string FileSystem::GetFileNameFromPath(string path)
{
	int lastindex = path.find_last_of("\\/");
	return path.substr(lastindex + 1, path.length());
}

string FileSystem::GetFileNameNoExtensionFromPath(string path)
{
	path = GetFileNameFromPath(path);

	int lastindex = path.find_last_of(".");
	string rawPath = path.substr(0, lastindex);

	return rawPath;
}

string FileSystem::GetPathWithoutFileName(string path)
{
	int lastindex = path.find_last_of("\\/");
	return path.substr(0, lastindex + 1);
}

string FileSystem::GetExtensionFromPath(string path)
{
	size_t lastindex = path.find_last_of(".");
	if (string::npos != lastindex)
		return path.substr(lastindex, path.length());

	// returns extension with dot
	return path;
}

string FileSystem::GetRelativePathFromAbsolutePath(string absolutePath)
{
	// NOTE: This function assumes that the path resolves somewhere 
	// inside the folder "Assets" (The default engine folder)

	// D:\Projects\Directus3D\Build\Assets\Models\cube\tex.jpg --> Assets\Models\cube\tex.jpg

	// Remove everything before the folder "Assets", making the path relative to the engine
	size_t position = absolutePath.find("Assets");
	string relativePath = absolutePath.substr(position);

	return relativePath;
}

vector<string> FileSystem::GetFoldersInDirectory(string directory)
{
	vector<string> folderPaths;

	DIR* dir = opendir(directory.c_str());
	struct dirent* entry = readdir(dir);
	while (entry != nullptr)
	{
		if (entry->d_type == DT_DIR)
			folderPaths.push_back(entry->d_name);

		entry = readdir(dir);
	}
	closedir(dir);

	return folderPaths;
}

vector<string> FileSystem::GetFilesInDirectory(string directory)
{
	DIR* dir;
	struct dirent* ent;
	vector<string> filePaths;

	if ((dir = opendir(directory.c_str())) == nullptr)
		return filePaths;

	while ((ent = readdir(dir)) != nullptr)
		filePaths.push_back(directory + "\\" + ent->d_name);

	closedir(dir);

	return filePaths;
}

vector<string> FileSystem::GetSupportedFilesInDirectory(string directory)
{
	vector<string> filesInDirectory = GetFilesInDirectory(directory);

	vector<string> imagesInDirectory = GetImagesFromPaths(filesInDirectory); // get all the images
	vector<string> scriptsInDirectory = GetScriptsFromPaths(filesInDirectory); // get all the scripts
	vector<string> modelsInDirectory = GetModelsFromPaths(filesInDirectory); // get all the models
	vector<string> supportedFiles;

	// get supported images
	for (int i = 0; i < imagesInDirectory.size(); i++)
		supportedFiles.push_back(imagesInDirectory[i]);

	// get supported scripts
	for (int i = 0; i < scriptsInDirectory.size(); i++)
		supportedFiles.push_back(scriptsInDirectory[i]);

	// get supported models
	for (int i = 0; i < modelsInDirectory.size(); i++)
		supportedFiles.push_back(modelsInDirectory[i]);

	return supportedFiles;
}

vector<string> FileSystem::GetImagesFromPaths(vector<string> paths)
{
	vector<string> images;
	for (int i = 0; i < paths.size(); i++)
	{
		string filePath = paths[i];

		if (IsSupportedImage(filePath))
			images.push_back(filePath);
	}

	return images;
}

vector<string> FileSystem::GetScriptsFromPaths(vector<string> paths)
{
	vector<string> scripts;
	for (int i = 0; i < paths.size(); i++)
	{
		string filePath = paths[i];

		if (IsSupportedScript(filePath))
			scripts.push_back(filePath);
	}

	return scripts;
}

vector<string> FileSystem::GetModelsFromPaths(vector<string> paths)
{
	vector<string> images;
	for (int i = 0; i < paths.size(); i++)
	{
		string filePath = paths[i];

		if (IsSupportedModel(filePath))
			images.push_back(filePath);
	}

	return images;
}

bool FileSystem::IsSupportedImage(string path)
{
	string fileExt = GetExtensionFromPath(path);
	vector<string> supportedExt;
	supportedExt.push_back(".jpg");
	supportedExt.push_back(".png");
	supportedExt.push_back(".bmp");
	supportedExt.push_back(".tga");
	supportedExt.push_back(".dds");
	supportedExt.push_back(".exr");
	supportedExt.push_back(".raw");
	supportedExt.push_back(".gif");
	supportedExt.push_back(".hdr");
	supportedExt.push_back(".ico");
	supportedExt.push_back(".iff");
	supportedExt.push_back(".jng");
	supportedExt.push_back(".jpeg");
	supportedExt.push_back(".koala");
	supportedExt.push_back(".kodak");
	supportedExt.push_back(".mng");
	supportedExt.push_back(".pcx");
	supportedExt.push_back(".pbm");
	supportedExt.push_back(".pgm");
	supportedExt.push_back(".ppm");
	supportedExt.push_back(".pfm");
	supportedExt.push_back(".pict");
	supportedExt.push_back(".psd");
	supportedExt.push_back(".raw");
	supportedExt.push_back(".sgi");
	supportedExt.push_back(".targa");
	supportedExt.push_back(".tiff");
	supportedExt.push_back(".wbmp");
	supportedExt.push_back(".webp");
	supportedExt.push_back(".xbm");
	supportedExt.push_back(".xpm");

	for (int i = 0; i < supportedExt.size(); i++)
	{
		if (fileExt == supportedExt[i] || fileExt == ConvertToUppercase(supportedExt[i]))
			return true;
	}

	return false;
}

bool FileSystem::IsSupportedScript(string path)
{
	string fileExt = GetExtensionFromPath(path);
	vector<string> supportedExt;
	supportedExt.push_back(".as");

	for (int i = 0; i < supportedExt.size(); i++)
	{
		if (fileExt == supportedExt[i] || fileExt == ConvertToUppercase(supportedExt[i]))
			return true;
	}

	return false;
}

bool FileSystem::IsSupportedScene(string path)
{
	string fileExt = GetExtensionFromPath(path);
	vector<string> supportedExt;
	supportedExt.push_back(".dss");

	for (int i = 0; i < supportedExt.size(); i++)
	{
		if (fileExt == supportedExt[i] || fileExt == ConvertToUppercase(supportedExt[i]))
			return true;
	}

	return false;
}

bool FileSystem::IsSupportedModel(string path)
{
	string fileExt = GetExtensionFromPath(path);
	vector<string> supportedExt;
	supportedExt.push_back(".3ds");
	supportedExt.push_back(".obj");
	supportedExt.push_back(".fbx");
	supportedExt.push_back(".blend");
	supportedExt.push_back(".dae");
	supportedExt.push_back(".lwo");
	supportedExt.push_back(".c4d");
	supportedExt.push_back(".ase");
	supportedExt.push_back(".dxf");
	supportedExt.push_back(".hmp");
	supportedExt.push_back(".md2");
	supportedExt.push_back(".md3");
	supportedExt.push_back(".md5");
	supportedExt.push_back(".mdc");
	supportedExt.push_back(".mdl");
	supportedExt.push_back(".nff");
	supportedExt.push_back(".ply");
	supportedExt.push_back(".stl");
	supportedExt.push_back(".x");
	supportedExt.push_back(".smd");
	supportedExt.push_back(".lxo");
	supportedExt.push_back(".lws");
	supportedExt.push_back(".ter");
	supportedExt.push_back(".ac3d");
	supportedExt.push_back(".ms3d");
	supportedExt.push_back(".cob");
	supportedExt.push_back(".q3bsp");
	supportedExt.push_back(".xgl");
	supportedExt.push_back(".csm");
	supportedExt.push_back(".bvh");
	supportedExt.push_back(".b3d");
	supportedExt.push_back(".ndo");

	for (int i = 0; i < supportedExt.size(); i++)
	{
		if (fileExt == supportedExt[i] || fileExt == ConvertToUppercase(supportedExt[i]))
			return true;
	}

	return false;
}

bool FileSystem::IsSupportedShader(string path)
{
	string fileExt = GetExtensionFromPath(path);
	vector<string> supportedExt;
	supportedExt.push_back(".hlsl");

	for (int i = 0; i < supportedExt.size(); i++)
	{
		if (fileExt == supportedExt[i] || fileExt == ConvertToUppercase(supportedExt[i]))
			return true;
	}

	return false;
}

string FileSystem::ConvertToUppercase(string lower)
{
	locale loc;
	string upper;
	for (string::size_type i = 0; i < lower.length(); ++i)
		upper += std::toupper(lower[i], loc);

	return upper;
}