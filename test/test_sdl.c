#include<SDL.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;

	SDL_Surface *window_surface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL init failed: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		printf("window could not be created: %s\n", SDL_GetError());
		return 1;
	}

	window_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0x7F, 0x80, 0x00));

	SDL_UpdateWindowSurface(window_surface);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
