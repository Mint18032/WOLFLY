#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "functions.h"
#include "menu.h"
#include "preGame.h"

int pauseGame(int scrollingOffset);
int loseScreen(int scrollingOffset, int score, int result);
void startGame(int& result);

int main(int argc, char *args[])
{
    if (!init()) //khởi tạo SDL
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        SDL_Event e;
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }
        BgTexture.renderTexture(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        int result = 0;
        BUTTON Quit;
        MOON moon;
        CLOUD cloud;
        openMenu(cloud, moon, Quit);

        while (SDL_WaitEvent(&e) != 0)
        {
            if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) || result == 1 || Play.clickButton(e)) //thao tác bắt đầu game
            {
                soundEffect(soundControl(Sound, BMusic) + "c");
                result = 1;
                closeMenu(cloud, moon, Quit);
                Guide();
                while (result == 1) {
                    startGame(result);
                }
            }
            if (result == -1) {
                result = 0;
                openMenu(cloud, moon, Quit);
            }
            if (BMusic.clickButton(e)) {
                soundEffect(soundControl(Sound, BMusic) + "c");
                if (BMusic.situation == "mmuted") {
                    BMusic.loadButonTexture("munmuted", renderer);
                    if(Sound.situation == "unmuted") {
                        Mix_PlayMusic(Music, -1);
                    }
                } else {
                    soundEffect("m");
                    BMusic.loadButonTexture("mmuted", renderer);
                }
                renderMenu(cloud, moon, Quit);
            }
            if (Sound.clickButton(e)) {
                soundEffect(soundControl(Sound, BMusic) + "c");
                if (Sound.situation == "muted") {
                    Sound.loadButonTexture("unmuted", renderer);
                    if(BMusic.situation == "munmuted") {
                        Mix_PlayMusic(Music, -1);
                    }
                } else {
                    soundEffect("b");
                    Sound.loadButonTexture("muted", renderer);
                }
                renderMenu(cloud, moon, Quit);
            }
            if (UpDateSized(e)) {
                renderMenu(cloud, moon, Quit);
            }
            if (e.type == SDL_QUIT || Quit.clickButton(e))
            {
                soundEffect(soundControl(Sound, BMusic) + "c");
                closeMenu(cloud, moon, Quit);
                close();
                return 0;
            }
        }
    }

    close();
    return 0;
}

int pauseGame(int scrollingOffset)
{
    Mix_PauseMusic();
    SDL_Event v;

    BUTTON pause;
    BUTTON replay;
    BUTTON menu;

    pause.loadButonTexture("Paused", renderer);
    Play.loadButonTexture("Continue", renderer);
    replay.loadButonTexture("replay", renderer);
    menu.loadButonTexture("Menu", renderer);

	while (true)
	{
	    SDL_RenderClear(renderer);

	    scrollBackground(renderer, BgTexture, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT);

        pause.renderAsIcon(0, 0, renderer);
        TextTexture.loadFromRenderedText(TTF_OpenFont("media/Text/debrosee.ttf", SCREEN_WIDTH / 10), "P A U S E D", {255, 255, 255}, renderer);
        TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2 , (SCREEN_HEIGHT) / 2 - TextTexture.getHeight());
        Play.renderWithString(SCREEN_WIDTH / 2 - Play.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);
        replay.renderWithString(SCREEN_WIDTH * 3 / 4 - replay.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);
        menu.renderWithString(SCREEN_WIDTH / 4 - menu.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);

        SDL_RenderPresent(renderer);

		if (SDL_WaitEvent(&v) != 0)
		{
		    UpDateSized(v);
            string act = soundControl(Sound, BMusic) + "c";
			if (replay.clickButton(v))
            {
                soundEffect(act);
                closePauseScreen(pause, replay, menu, Play, renderer);
                return 1; //replay
            }
            else if (v.type == SDL_QUIT || menu.clickButton(v))
            {
                soundEffect(act);
                closePauseScreen(pause, replay, menu, Play, renderer);
                return -1; //back to menu
            }
            else if (v.type == SDL_KEYDOWN || Play.clickButton(v) || pause.clickButton(v))
            {
                soundEffect(act);
                closePauseScreen(pause, replay, menu, Play, renderer);
                return 0; //continue
            }
		}
	}
}

int loseScreen(int scrollingOffset, int score, int result)
{
    Mix_PauseMusic();
    SDL_Event v;

    SDL_RenderClear(renderer);
    scrollBackground(renderer, BgTexture, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT);

    BUTTON pause;
    BUTTON replay;
    BUTTON menu;

    pause.loadButonTexture("Paused", renderer);
    pause.renderAsIcon(0, 0, renderer);

    std::string text = "Your score: " + std::to_string(score);
    if (result == 2)
    {
        text = "New high score: " + std::to_string(score);
    }
    TextTexture.loadFromRenderedText(TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 20), text, {255, 255, 255}, renderer);
    TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2, (SCREEN_HEIGHT) / 2 - TextTexture.getHeight());

    replay.loadButonTexture("replay", renderer);
    menu.loadButonTexture("Menu", renderer);
    replay.renderWithString(SCREEN_WIDTH * 2 / 3 - replay.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);
    menu.renderWithString(SCREEN_WIDTH / 3 - menu.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);

    SDL_RenderPresent(renderer);

    while (true)
    {
        SDL_RenderClear(renderer);
        scrollBackground(renderer, BgTexture, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT);
        pause.renderAsIcon(0, 0, renderer);

        TextTexture.loadFromRenderedText(TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 21), text, {255, 255, 255}, renderer);
        TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2, (SCREEN_HEIGHT) / 2 - TextTexture.getHeight());
        replay.renderWithString(SCREEN_WIDTH * 2 / 3 - replay.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);
        menu.renderWithString(SCREEN_WIDTH / 3 - menu.r, (SCREEN_HEIGHT + TextTexture.getHeight()) / 2, renderer);

        SDL_RenderPresent(renderer);

        if (SDL_WaitEvent(&v) != 0)
		{
            UpDateSized(v);
			if (replay.clickButton(v))
            {
                soundEffect(soundControl(Sound, BMusic) + "c");
                closePauseScreen(pause, replay, menu, Play, renderer);
                return 1; //replay
            }
            else if (v.type == SDL_QUIT || menu.clickButton(v))
            {
                soundEffect(soundControl(Sound, BMusic) + "c");
                closePauseScreen(pause, replay, menu, Play, renderer);
                return -1; //back to menu
            }
		}
    }
}

void startGame(int &result)
{
    SDL_RenderClear(renderer);
    if (Sound.situation == "unmuted" && BMusic.situation == "munmuted") {
        Mix_PlayMusic(Music, -1);
    }

    SDL_Event e;

    int score = 0, best = readBest();
    int scrollingOffset = 0;
    string CurrentColor = "d";
    bool quit = false;
    bool die = false;

    SDL_Color textColor = {255, 255, 255};
    scrollBackground(renderer, BgTexture, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT);

    HEAD wolf(renderer);
    Star star[4] = {Star(renderer), Star(renderer), Star(renderer), Star(renderer)};
    Sheep sheep[3];

    //các ngôi sao xuất hiện dần, nhiều nhất 4 ngôi
    star[0].locate(-620);
    star[1].locate(-1240);
    star[2].locate(-5000);
    star[3].locate(-7040);
    for(int i = 0; i < 3; ++i) {
        sheep[i].locate(renderer);
    }

    while (!quit)
    {
        std::string act; //kiem soat am thanh
        while (SDL_PollEvent(&e) != 0)
        {
            UpDateSized(e);
            if (e.type == SDL_QUIT)
            {
                result = -1;
                quit = true;
            }
            else if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) || Play.clickButton(e) || e.type == SDL_MOUSEBUTTONDOWN)
            {
                soundEffect(soundControl(Sound, BMusic) + "c");
                result = pauseGame(scrollingOffset);
                if (die == false && result == 0)
                {
                    if (Sound.situation == "unmuted" && BMusic.situation == "munmuted") {
                        Mix_PlayMusic(Music, -1);
                    }
                    Play.renderAsIcon(0, 0, renderer);
                } else if (result == -1 || result == 1)
                {
                        quit = true;
                }
            }
            wolf.handleEvent(e);
        }

        SDL_RenderClear(renderer);
        scrollBackground(renderer, BgTexture, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (!wolf.checkMove(star[0]) && !wolf.checkMove(star[1]) && !wolf.checkMove(star[2]) && !wolf.checkMove(star[3]))
        {
            for (int i = 0; i < 3; i++) {
                sheep[i].move(act, renderer);
            }
            for (int i = 0; i < 4; i++) {
                star[i].move(act);
            }
            if (!die)
            {
                wolf.move();
                wolf.loadFromFile(renderer, "media/Characters/Wolf/" + CurrentColor + ".png");
                if (wolf.checkEat(sheep[0], renderer, CurrentColor) || wolf.checkEat(sheep[1], renderer, CurrentColor) || wolf.checkEat(sheep[2], renderer, CurrentColor))
                {
                    wolf.loadFromFile(renderer, "media/Characters/EatingWolf/" + CurrentColor + ".png");
                    act += 'e';
                    ++score;
                    if (score > best)
                    {
                        best = score;
                    }
                }
            }
        }
        else //xay ra va cham
        {
            if (!die)
            {
                act = 'o';
            }
            die = true;
            wolf.loadFromFile(renderer, "media/Characters/DeadWolf/" + CurrentColor + ".png");
            wolf.fall(quit); //roi xuong day thi het game
            result = -2;
            if (quit && best > readBest())
            {
                result = 2;
                SDL_RWops *file = SDL_RWFromFile("media/Text/score.bin", "w+b");
                SDL_RWwrite(file, &best, sizeof(int), 1);
                SDL_RWclose(file);
            }
        }

        if(quit && (result == -2 || result == 2)) {
            result = loseScreen(scrollingOffset, score, result);
        } else
        {
            soundEffect(soundControl(Sound, BMusic) + act);
            for (int i = 0; i < 3; i++) {
                sheep[i].render(renderer);
            }
            wolf.render(renderer);
            for (int i = 0; i < 4; i++) {
                star[i].render(renderer);
            }
            Play.renderAsIcon(0, 0, renderer);

            std::string text = "Score: " + std::to_string(score) + "  Best: " + std::to_string(best);
            TextTexture.loadFromRenderedText(TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 55), text, textColor, renderer);
            TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth() - 10), (TextTexture.getHeight()) / 2);

            if(die) {
                TextTexture.loadFromRenderedText(TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 15), "G A M E  O V E R !", textColor, renderer);
                TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2, (SCREEN_HEIGHT) / 2 - TextTexture.getHeight());
            }
        }

        SDL_RenderPresent(renderer);
    }
	wolf.free();
	for(int i = 0; i < 4; ++i) {
        star[i].free();
        if(i != 3) {
            sheep[i].free();
        }
	}
}
