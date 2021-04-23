//class hỗ trợ việc vẽ đồ họa
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class Texture
{
	public:
		Texture();
		~Texture();

		int getWidth();
		int getHeight();
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

		bool loadFromFile(SDL_Renderer* renderer, std::string path);
		bool loadFromRenderedText(TTF_Font* Font, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);
        bool getScreenSize(); //đọc kích thước màn hình từ tệp

		//có thể nhập các giá trị để render Texture theo 2 cách, cách 2 để không phải tạo SDL_Rect ở ngoài
		void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,  SDL_RendererFlip flip = SDL_FLIP_NONE );
		void renderTexture(SDL_Renderer *ren, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void free();

	private:
		SDL_Texture* texture;
		int Width;
		int Height;
};

