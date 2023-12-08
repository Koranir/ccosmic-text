#include "ccosmic_text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL_blendmode.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct RenderState {
    SDL_Renderer *renderer;
} RenderState;

void rendererFunc(void *state, int32_t x, int32_t y, uint32_t w, uint32_t h, ctColor color) {
    RenderState renderState = *(RenderState *)state;
    
    SDL_SetRenderDrawColor(renderState.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderState.renderer, x, y);
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Cosmic Text Test 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

    SDL_RenderSetVSync(renderer, 1);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    ctFontSystem fontsystem = ctFontSystem_New();
    ctSwashCache swashCache = ctSwashCache_New();

    ctMetrics metrics = ctMetrics_New(36.0, 40.0);
    ctBuffer buffer = ctBuffer_New(fontsystem, metrics);

    ctBuffer_SetSize(buffer, fontsystem, 800.0, 600.0);

    ctAttrs attrs = ctAttrs_New();

    const char *text = "Hello, C! We got emojis 🐀 and ligatures! 안녕하세요!";
    ctSlice textSlice = {
        .ptr = (uint8_t *)text,
        .len = strlen(text)
    };

    ctBuffer_SetText(buffer, fontsystem, textSlice, attrs, ctShaping_ADVANCED);
    ctBuffer_ShapeUntilScroll(buffer, fontsystem);

    ctColor textColor = ctColor_Rgba(0xFF, 0xFF, 0xFF, 0xFF);

    bool exit = false;
    while (!exit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        RenderState state = {.renderer = renderer};
        ctBuffer_Draw(buffer, fontsystem, swashCache, textColor, &state, rendererFunc);

        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
