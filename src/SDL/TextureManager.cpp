#include <iostream>
#include "../../include/SDL/TextureManager.h"

#include <SDL.h>
TextureManager::TextureManager() : textures_(), resourcedirectories_()
{
}

TextureManager::~TextureManager()
{
	textures_.clear();
	resourcedirectories_.clear();
}

Texture* TextureManager::GetTexture( const std::string& filename )
{
	// Check, whether the texture already exists

	for( std::map<std::string, std::unique_ptr<Texture>>::iterator it = textures_.begin(); it != textures_.end(); ++it)
	{
		if( filename == it->first )
			return it->second.get();
	}

	// Search project's main directory
	if( !(textures_[filename] = std::unique_ptr<Texture>(new Texture(filename,renderer_))) )
        textures_.erase(filename);
    else
    {
        std::cout << "Loaded new Texture: " << filename << std::endl;
        return textures_[filename].get();
    }



	// If the texture has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); ++it )
	{
			// Search project's main directory
        if( !(textures_[filename] = std::unique_ptr<Texture>(new Texture((*it) + filename,renderer_))) )
            textures_.erase(filename);
        else
            return textures_[filename].get();
	}

	std::cout << "GAME_ERROR: texture was not found. It is filled with an empty texture.\n";
	textures_[filename] = std::unique_ptr<Texture>(new Texture());

	return textures_[filename].get();
}

#ifdef FOO
void TextureManager::DeleteTexture( const Texture& texture )
{
	for( std::map<std::string, std::unique_ptr<Texture>>::const_iterator it = textures_.begin(); it != textures_.end(); ++it)
	{
		if( &texture == &it->second )
		{
			textures_.erase( it );
            return;
		}
	}
}
#endif
void TextureManager::DeleteTexture( const std::string& filename )
{
	std::map<std::string, std::unique_ptr<Texture>>::const_iterator it = textures_.find( filename );
	if( it != textures_.end() )
		textures_.erase( it );
}

void TextureManager::AddResourceDirectory( const std::string& directory )
{
	// Check whether the path already exists
	for( std::vector<std::string>::const_iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); ++it )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			return;
	}

	// insert the directory
	resourcedirectories_.push_back( directory );
}

void TextureManager::RemoveResourceDirectory( const std::string& directory )
{
	for( std::vector<std::string>::iterator it = resourcedirectories_.begin(); it != resourcedirectories_.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = resourcedirectories_.erase( it );
		else
			++it;
	}
}

