//các hàm khởi tạo, tắt SDL; thay đổi, lưu kích thước cửa sổ
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

const int DEFAULT_WIDTH = 1100;
const int DEFAULT_HEIGHT = DEFAULT_WIDTH / 1.7;
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

bool init();
bool UpDateSized(SDL_Event& e); //kiểm tra và thay đổi kích cỡ cửa sổ
void UpDateScreenSize(); //lưu kích cỡ cửa sổ vào tệp
void quit();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Mix_Music *Music = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        window = SDL_CreateWindow("W O L F L Y", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                UpDateScreenSize();
                SDL_SetWindowMinimumSize(window, 400, 400 / 1.7);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool UpDateSized(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) { //ấn escape để quay trở lại kích cỡ mặc định
        SDL_SetWindowSize(window, DEFAULT_WIDTH, DEFAULT_HEIGHT);
        UpDateScreenSize();
        return true;
    }
    if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
        UpDateScreenSize();
        return true;
    }
    return false;
}

void UpDateScreenSize() {
    int w = SCREEN_WIDTH, h = SCREEN_HEIGHT;
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT); //lấy kích cỡ
    //đảm bảo tỉ lệ cửa sổ
    if(w != SCREEN_WIDTH || h != SCREEN_HEIGHT) {
        if (SCREEN_WIDTH != w) {
            SCREEN_HEIGHT = SCREEN_WIDTH / 1.7;
        } else {
            SCREEN_WIDTH = SCREEN_HEIGHT * 1.7;
        }
        SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); //giữ cửa sổ ở trung tâm
        //lưu kích thước
        SDL_RWops *file = SDL_RWFromFile("media/Text/Size.bin", "w+b");
        if (file)
        {
            SDL_RWwrite(file, &SCREEN_WIDTH, sizeof(int), 1);
            SDL_RWwrite(file, &SCREEN_HEIGHT, sizeof(int), 1);
            SDL_RWclose(file);
        }
        else
        {
            printf("Failed to save screen size!\n");
        }
    }
}

void quit()
{
    Music = NULL;
    renderer = NULL;
    window = NULL;
    Mix_FreeMusic(Music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SCREEN_WIDTH = 0;
    SCREEN_HEIGHT = 0;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

