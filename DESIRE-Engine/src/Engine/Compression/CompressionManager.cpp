#include "Engine/stdafx.h"
#include "Engine/Compression/CompressionManager.h"

CompressionManager::CompressionManager()
{

}

CompressionManager::~CompressionManager()
{

}

std::unique_ptr<Compression> CompressionManager::CreateCompression(HashedString name) const
{
	Compression *compression = nullptr;

	const CompressionFactoryFunc_t *factoryFunc = compressionFactories.Find(name);
	if(factoryFunc != nullptr)
	{
		compression = (*factoryFunc)();
	}

	return std::unique_ptr<Compression>(compression);
}