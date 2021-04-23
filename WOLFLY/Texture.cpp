#include "Texture.h"

Texture::Texture()
{
    getScreenSize();
	texture = NULL;
	Width = 0;
	Height = 0;
}

Texture::~Texture()
{
    SCREEN_WIDTH = 0;
    SCREEN_HEIGHT = 0;
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			Width = loadedSurface->w;
			Height = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}
	texture = newTexture;
	return texture != NULL;
}

bool Texture::loadFromRenderedText(TTF_Font* Font, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( Font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			Width = textSurface->w;
			Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return texture != NULL;
}

void Texture::free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		Width = 0;
		Height = 0;
	}
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    getScreenSize();
	SDL_Rect rect = {x, y, Width, Height};

	if( clip != NULL )
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
}

void Texture::renderTexture(SDL_Renderer *ren, int x, int y, int w, int h, SDL_RendererFlip flip)
{
    getScreenSize();
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
    rect.w = w;
    rect.h = h;

	SDL_RenderCopyEx(ren, texture, NULL, &rect, 0.0, NULL, flip);
}

int Texture::getWidth()
{
	return Width;
}

int Texture::getHeight()
{
	return Height;
}

bool Texture::getScreenSize()
{
    int w = SCREEN_WIDTH;
    SDL_RWops *file = SDL_RWFromFile("media/Text/Size.bin", "rb");
    if (file)
    {
        SDL_RWread(file, &SCREEN_WIDTH, sizeof(int), 1);
        SDL_RWread(file, &SCREEN_HEIGHT, sizeof(int), 1);

        SDL_RWclose(file);
    }
    else
    {
        printf("Failed to read screen size!\n");
    }
    return (SCREEN_WIDTH != w); //true nếu có sự thay đổi kích thước
}

