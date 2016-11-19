#pragma once

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "Texture.h"

namespace SAS_System {
	class TextureManager
	{
	public:
		TextureManager(SDL_Renderer* renderer);
		~TextureManager();

	public:
		//void DeleteTexture( const Texture& Texture ); TODO I dont know if ill need to remove by texture since it is not being exposed
		void DeleteTexture(const std::string& filename);

		void AddResourceDirectory(const std::string& directory);
		void RemoveResourceDirectory(const std::string& directory);

		Texture* GetTexture(const std::string& filename);
		int CreateTargetTexture(int width, int height);
		int CreateTargetTexture(int width, int height, Uint32 format, int access);
		Texture* GetTargetTexture(int id);

	private:
		//TextureManager( const TextureManager& );
		//TextureManager& operator =( const TextureManager& );

		std::map< std::string, std::unique_ptr<Texture> > textures_;
		// Separate data structure for managing empty target textures
		std::vector<std::unique_ptr<Texture>> targettextures_;

		std::vector< std::string > resourcedirectories_;
		SDL_Renderer* renderer_;
	};

}