//các hàm, lớp dùng trong menu, một số dùng cả trong game
#pragma once
#include "Texture.h"

int readBest(); //đọc điểm kỉ lục từ tệp nhị phân

class CLOUD : public Texture
{
    private:
        bool appeared = false;
        int OX = 0, OY = SCREEN_HEIGHT;

    public:
        int CLOUD_HEIGHT = SCREEN_HEIGHT / 2;

        void loadCloud(SDL_Renderer* renderer);
        void render(SDL_Renderer *renderer);
        void freeCloud();
        bool appear();
        bool exit();
};

class MOON
{   private:
        int& SCREEN_WIDTH = TMoon.SCREEN_WIDTH;
        int& SCREEN_HEIGHT = TMoon.SCREEN_HEIGHT;
        Texture TMoon; //mặt trăng
        Texture TName; //Tên game
        Texture TCre; //tên tác giả (Credit)
        Texture TBest; //Best score

        bool appeared = false;

    public:
        int MOON_HEIGHT = (SCREEN_WIDTH + SCREEN_HEIGHT) / 8;
        int& MOON_WIDTH = MOON_HEIGHT;
        int OX = SCREEN_WIDTH * 8 / 9 - MOON_WIDTH;
        int OY = 0 - MOON_HEIGHT;

        void loadMoon(SDL_Renderer* renderer);
        void render(SDL_Renderer *renderer);
        void free();
        bool appear();
        bool exit();
};


