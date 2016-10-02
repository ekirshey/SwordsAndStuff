#include <iostream>
#include "TextureManager.h"

#include <SDL.h>

namespace SAS_System {
	TextureManager::TextureManager(SDL_Renderer* renderer) : textures_(), resourcedirectories_(), renderer_(renderer)
	{
	}

	TextureManager::~TextureManager()
	{
		textures_.clear();
		resourcedirectories_.clear();
	}

	Texture* TextureManager::GetTexture(const std::string& filename)
	{
		// Check, whether the texture already exists
		for (std::map<std::string, std::unique_ptr<Texture>>::iterator it = textures_.begin(); it != textures_.end(); ++it)
		{
			if (filename == it->first)
				return it->second.get();
		}

		// Search project's main directory
		if (!(textures_[filename] = std::make_unique<Texture>(filename, renderer_)))
			textures_.erase(filename);
		else
		{
			std::cout << "Loaded new Texture: " << filename << std::endl;
			return textures_[filename].get();
		}

		// If the texture has still not been found, search all registered directories
		for (std::vector< std::string >::iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); ++it)
		{
			// Search project's main directory
			if (!(textures_[filename] = std::make_unique<Texture>((*it) + filename, renderer_)))
				textures_.erase(filename);
			else
				return textures_[filename].get();
		}

		std::cout << "GAME_ERROR: texture was not found. It is filled with an empty texture.\n";
		textures_[filename] = std::make_unique<Texture>();

		return textures_[filename].get();
	}

	int TextureManager::CreateTargetTexture(int width, int height) {
		targettextures_.push_back(std::make_unique<Texture>(width, height, renderer_));
		return targettextures_.size() - 1;
	}

	// Not sure if stream textures should be in a different structure
	// If there is a filename with the same internal stream texture name, it will cause issues
	Texture* TextureManager::GetTargetTexture(int id) {
		// Check, whether the texture already exists
		int size = targettextures_.size();
		if ((id >= 0) && (id < size)) {
			return targettextures_[id].get();
		}
		else {
			std::cout << "GAME_ERROR: Couldn't build Target Texture. It is filled with an empty texture.\n";
			return nullptr;
		}
	}

	void TextureManager::DeleteTexture(const std::string& filename)
	{
		std::map<std::string, std::unique_ptr<Texture>>::const_iterator it = textures_.find(filename);
		if (it != textures_.end())
			textures_.erase(it);
	}

	void TextureManager::AddResourceDirectory(const std::string& directory)
	{
		// Check whether the path already exists
		for (std::vector<std::string>::const_iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); ++it)
		{
			// The path exists. So it isn't necessary to add id once more.
			if (directory == (*it))
				return;
		}

		// insert the directory
		resourcedirectories_.push_back(directory);
	}

	void TextureManager::RemoveResourceDirectory(const std::string& directory)
	{
		for (std::vector<std::string>::iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); )
		{
			// The path exists. So it isn't necessary to add id once more.
			if (directory == (*it))
				it = resourcedirectories_.erase(it);
			else
				++it;
		}
	}
}
