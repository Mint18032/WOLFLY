#include "menu.h"

void MOON::loadMoon(SDL_Renderer* renderer)
{
    std::string best = "Best score: " + std::to_string(readBest());
    TMoon.loadFromFile(renderer, "media/Background/Moon.png");
    TName.loadFromRenderedText(TTF_OpenFont("media/Text/Debrosee.ttf", (SCREEN_WIDTH + SCREEN_HEIGHT) / 15), "W O L F L Y", {255, 255, 255}, renderer);
    TCre.loadFromRenderedText(TTF_OpenFont("media/Text/Debrosee.ttf", (SCREEN_WIDTH + SCREEN_HEIGHT) / 119), "b y  N g o c  M i n h", {255, 255, 255}, renderer);
    TBest.loadFromRenderedText(TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 55), best, {255, 255, 255}, renderer);
}

void MOON::render(SDL_Renderer *renderer)
{
    TMoon.getScreenSize();
    MOON_HEIGHT = (SCREEN_WIDTH + SCREEN_HEIGHT) / 8;
    OX = SCREEN_WIDTH * 8 / 9 - MOON_WIDTH;
    if (appeared) {
        OY = SCREEN_HEIGHT / 10;
    }
    loadMoon(renderer);
    TMoon.renderTexture(renderer, OX, OY, MOON_WIDTH, MOON_HEIGHT);
    TName.render(renderer, OX - TName.getWidth() + MOON_WIDTH / 2, OY);
    TCre.render(renderer, OX - TCre.getWidth() + MOON_WIDTH / 3, OY + MOON_HEIGHT / 2);
    TBest.render(renderer, (SCREEN_WIDTH - TBest.getWidth() - 10), (TBest.getHeight()) / 2);
}

void MOON::free()
{
    appeared = false;
    TMoon.free();
    TName.free();
    TCre.free();
    TBest.free();
}

bool MOON::appear()
{
    if (OY >= SCREEN_HEIGHT / 10) {
        appeared = true;
    } else {
        appeared = false;
        OY += SCREEN_HEIGHT / 60;
    }
    return appeared;
}

bool MOON::exit()
{
    appeared = false;
    if (OY <= 0 - MOON_HEIGHT) {
        return true;
    } else {
        OY -= SCREEN_HEIGHT / 60;
        return false;
    }
}

void CLOUD::loadCloud(SDL_Renderer* renderer)
{
    loadFromFile(renderer, "media/Background/Cloud.png");
}

void CLOUD::render(SDL_Renderer *renderer)
{
    getScreenSize();
    CLOUD_HEIGHT = SCREEN_HEIGHT / 2 + 10;
    if (!appeared) {
        renderTexture(renderer, OX, OY, SCREEN_WIDTH, CLOUD_HEIGHT);
    } else {
        renderTexture(renderer, OX, SCREEN_HEIGHT / 2 + 5, SCREEN_WIDTH, CLOUD_HEIGHT);
    }
}

void CLOUD::freeCloud()
{
    appeared = false;
    free();
}

bool CLOUD::appear()
{
    if (OY <= SCREEN_HEIGHT / 2 + 5) {
        appeared = true;
    } else {
        OY -= SCREEN_HEIGHT / 60;
        appeared = false;
    }
    return appeared;
}

bool CLOUD::exit()
{
    appeared = false;
    if (OY >= SCREEN_HEIGHT) {
        return true;
    } else {
        OY += SCREEN_HEIGHT / 60;
        return false;
    }
}

int readBest()
{
    int best = 0;
    SDL_RWops *file = SDL_RWFromFile("media/Text/score.bin", "r+b"); //nếu tệp không tồn tại thì sẽ được tạo và kỉ lục tính là 0
    if (file)
    {
        SDL_RWread(file, &best, sizeof(int), 1);
        SDL_RWclose(file);
    }
    return best;
}
