#include "ImageLoader.h"

#include "picoPNG.h"
#include "IOManager.h"
#include "ErrorManager.h"

namespace Solengine
{
	GLTexture ImageLoader::LoadPNG(std::string filePath)
	{
		GLTexture texture = {}; 
		std::vector<unsigned char> bufferedPNG = IOManager::ReadFileToBuffer(filePath);
		std::vector<unsigned char> decodedPNG;
		unsigned long width, height;


		//Using picoPNG
		int errorCode = decodePNG(decodedPNG, width, height, &(bufferedPNG[0]), bufferedPNG.size());
		if (errorCode != 0)
		{
			ErrorManager::FatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.textureID));

		glBindTexture(GL_TEXTURE_2D, texture.textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(decodedPNG[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}