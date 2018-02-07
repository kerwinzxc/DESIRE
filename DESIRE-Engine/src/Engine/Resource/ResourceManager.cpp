#include "Engine/stdafx.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Resource/Mesh.h"
#include "Engine/Resource/Shader.h"
#include "Engine/Resource/Texture.h"
#include "Engine/Core/fs/FileSystem.h"
#include "Engine/Core/fs/IReadFile.h"
#include "Engine/Render/Render.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const String& filename)
{
	const HashedString filenameHash = HashedString::CreateFromDynamicString(filename.c_str(), filename.Length());
	std::weak_ptr<Mesh> *meshPtr = loadedMeshes.Find(filenameHash);
	if(meshPtr != nullptr && !meshPtr->expired())
	{
		return meshPtr->lock();
	}

	std::shared_ptr<Mesh> mesh = LoadMesh(filename);

	if(meshPtr != nullptr)
	{
		*meshPtr = mesh;
	}
	else
	{
		loadedMeshes.Insert(filenameHash, mesh);
	}

	return mesh;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const String& filename, const char *defines)
{
	ASSERT(defines != nullptr);

	const String shaderNameWithDefines = filename + "|" + String(defines, strlen(defines));
	const HashedString filenameHash = HashedString::CreateFromDynamicString(shaderNameWithDefines.c_str(), shaderNameWithDefines.Length());
	std::weak_ptr<Shader> *shaderPtr = loadedShaders.Find(filenameHash);
	if(shaderPtr != nullptr && !shaderPtr->expired())
	{
		return shaderPtr->lock();
	}

	std::shared_ptr<Shader> shader = LoadShader(filename);

	if(shaderPtr != nullptr)
	{
		*shaderPtr = shader;
	}
	else
	{
		loadedShaders.Insert(filenameHash, shader);
	}

	return shader;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const String& filename)
{
	const HashedString filenameHash = HashedString::CreateFromDynamicString(filename.c_str(), filename.Length());
	std::weak_ptr<Texture> *texturePtr = loadedTextures.Find(filenameHash);
	if(texturePtr != nullptr && !texturePtr->expired())
	{
		return texturePtr->lock();
	}

	std::shared_ptr<Texture> texture = LoadTexture(filename);

	if(texturePtr != nullptr)
	{
		*texturePtr = texture;
	}
	else
	{
		loadedTextures.Insert(filenameHash, texture);
	}

	return texture;
}

std::shared_ptr<Mesh> ResourceManager::LoadMesh(const String& filename)
{
	ReadFilePtr file = FileSystem::Get()->Open(filename);
	if(file)
	{
		for(MeshLoaderFunc_t loaderFunc : meshLoaders)
		{
			Mesh *mesh = loaderFunc(file);
			if(mesh != nullptr)
			{
				return std::shared_ptr<Mesh>(mesh);
			}

			file->Seek(0, IReadFile::ESeekOrigin::BEGIN);
		}
	}

	LOG_ERROR("Failed to load mesh from: %s", filename.c_str());
	return nullptr;
}

std::shared_ptr<Shader> ResourceManager::LoadShader(const String& filename)
{
	const String filenameWithPath = Render::Get()->GetShaderFilenameWithPath(filename.c_str());

	ReadFilePtr file = FileSystem::Get()->Open(filenameWithPath);
	if(file)
	{
		for(ShaderLoaderFunc_t loaderFunc : shaderLoaders)
		{
			Shader *shader = loaderFunc(file);
			if(shader != nullptr)
			{
				return std::shared_ptr<Shader>(shader);
			}

			file->Seek(0, IReadFile::ESeekOrigin::BEGIN);
		}
	}

	LOG_ERROR("Failed to load texture from: %s", filenameWithPath.c_str());
	return nullptr;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const String& filename)
{
	ReadFilePtr file = FileSystem::Get()->Open(filename);
	if(file)
	{
		for(TextureLoaderFunc_t loaderFunc : textureLoaders)
		{
			Texture *texture = loaderFunc(file);
			if(texture != nullptr)
			{
				return std::shared_ptr<Texture>(texture);
			}

			file->Seek(0, IReadFile::ESeekOrigin::BEGIN);
		}
	}

	LOG_ERROR("Failed to load texture from: %s", filename.c_str());
	return nullptr;
}
