//Các class cho nhân vật (đầu sói, ngôi sao rơi, cừu)
#pragma once
#include "Texture.h"

using namespace std;


class Star : public Texture
{
    public:
        int Star_WIDTH = 0;
        int& Star_HEIGHT = Star_WIDTH;
        int OX, OY; //tọa độ theo 2 phương

        Star(SDL_Renderer *renderer);
        ~Star();
        void locate(int x);
        void move(std::string &act);
        void render(SDL_Renderer *renderer);

    private:
        int VelocityY;
};

class Sheep : public Texture
{
    public:
        int Sheep_WIDTH = SCREEN_WIDTH / 15.5;
        int& Sheep_HEIGHT = Sheep_WIDTH;
        int OX, OY;
        string GetColor();

        void locate(SDL_Renderer *renderer);
        void move(std::string &act, SDL_Renderer *renderer);
        void render(SDL_Renderer *renderer);

    private:
        int VelocityX;
        void ReSize();
        string Color;
};

class HEAD : public Texture //đầu con sói
{
    public:
        HEAD(SDL_Renderer* renderer);
        ~HEAD();
        void handleEvent(SDL_Event &e); //thay đổi tọa độ khi điều khiển sói
        void move();
        void fall(bool &quit); //hiệu ứng sói rơi sau khi xảy ra va chạm với sao
        void render(SDL_Renderer *renderer);
        bool checkCollition(double a, double b, double x, double y, double r); //xác định va chạm
        bool checkMove(Star& s); //xác định va chạm với sao
        bool checkEat(Sheep& s, SDL_Renderer *renderer, string& CurrentColor); //xác định đã ăn cừu

    private:
        int HEAD_WIDTH = SCREEN_WIDTH / 9.2;
        int HEAD_HEIGHT = SCREEN_HEIGHT / 6.5;
        int HEAD_VEL = SCREEN_WIDTH / 124;
        int VelocityX, VelocityY;
        int OX, OY;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
};

