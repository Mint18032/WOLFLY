#include "functions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

string soundControl(BUTTON& Sound, BUTTON& BMusic)
{
    if(Sound.situation == "muted") {
        return "b"; //mute Both
    }
    if(BMusic.situation == "mmuted") {
        return "m"; //mute Music only
    }
    return " ";
}

void soundEffect(std::string act)
{
	Mix_Chunk *sound;
	if (act == "q") //quit
    {
        Mix_PauseMusic();
        sound = NULL;
        Mix_FreeChunk(sound);
    } else {
        for (char &c : act)
        {
            sound = NULL;
            if (c == 'm' || c == 'b') //mute
            {
                if (Mix_PlayingMusic() != 0) {
                    Mix_HaltMusic();
                }
                if (c == 'b') { //both music and sound are muted
                    return;
                }
            }
            if (c == 's') //sheep
            {
                sound = Mix_LoadWAV("media/sound/bleat.mp3");
            }
            if (c == 'o') //gameover
            {
                sound = Mix_LoadWAV("media/sound/GameOver.wav");
                Mix_HaltMusic();
            }
            if (c == 'f') //star falling
            {
                sound = Mix_LoadWAV("media/Sound/star.wav");
            }
            if (c == 'e') //eating sheep
            {
                sound = Mix_LoadWAV("media/Sound/eating.wav");
            }
            if (c == 'c') //mouse clicking
            {
                sound = Mix_LoadWAV("media/Sound/click.wav");
            }
            Mix_PlayChannel(-1, sound, 0);
        }
    }
}

void scrollBackground(SDL_Renderer* renderer, Texture& BgTexture, int& scrollingOffset, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
     --scrollingOffset;
    if (scrollingOffset < -(SCREEN_WIDTH * 1.5))
    {
        scrollingOffset = 0;
    }
    BgTexture.renderTexture(renderer, scrollingOffset, 0, SCREEN_WIDTH * 1.5, SCREEN_HEIGHT);
    BgTexture.renderTexture(renderer, scrollingOffset + SCREEN_WIDTH * 1.5, 0, SCREEN_WIDTH * 1.5, SCREEN_HEIGHT);
}

void closePauseScreen(BUTTON& pause, BUTTON& replay, BUTTON& menu, BUTTON& Play, SDL_Renderer* renderer)
{
    Play.loadButonTexture("Play", renderer);
    pause.free();
    replay.free();
    menu.free();
}

