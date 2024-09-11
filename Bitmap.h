#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Bitmap
{
    protected:
    SDL_Texture* m_hBitmap;
    int m_iWidth, m_iHeight;
    void Free();

    public:
    Bitmap();
    Bitmap(SDL_Renderer* renderer, const char* szFilename, SDL_Color* scTransColor = nullptr);
    ~Bitmap();

    void Draw(SDL_Renderer* renderer, int x, int y);
    int GetWidth(){return m_iWidth;};
    int GetHeight(){return m_iHeight;};
};


