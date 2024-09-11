#include "Bitmap.h"

Bitmap::Bitmap() : m_hBitmap(NULL), m_iWidth(0),m_iHeight(0)
{

}

Bitmap::Bitmap(SDL_Renderer* renderer, const char* szFilename, SDL_Color* scTransColor)
 : m_hBitmap(NULL), m_iWidth(0),m_iHeight(0)
{
   SDL_Surface* surface = IMG_Load(szFilename);
   if(!surface)
   {
    std::cout << "Error Laoding " << szFilename << SDL_GetError() << std::endl;
   }
   this->m_iWidth = surface->w;
   this->m_iHeight = surface->h;

   if(scTransColor!=nullptr)
   {
    int retcode = SDL_SetColorKey(surface, SDL_TRUE, 
                         SDL_MapRGB(surface->format, scTransColor->r,
                          scTransColor->g, scTransColor->b));
    if(retcode<0)
    std::cout << SDL_GetError() << std::endl;                      
   }

   this->m_hBitmap = SDL_CreateTextureFromSurface(renderer, surface);
   if(scTransColor!=nullptr && scTransColor->a<0xFF)
   {
    SDL_SetTextureAlphaMod(this->m_hBitmap, scTransColor->a);
   }
   SDL_FreeSurface(surface);
}

Bitmap::~Bitmap()
{
    Free();
}

void Bitmap::Free()
{
  if(m_hBitmap!=nullptr)
  {
    SDL_DestroyTexture(m_hBitmap);
    m_hBitmap = NULL;
  }
}

void Bitmap::Draw(SDL_Renderer* renderer, int x, int y)
{
   if(m_hBitmap!=nullptr)
   {
    SDL_Rect rect = {x, y, GetWidth(), GetHeight()};
    SDL_RenderCopy(renderer, this->m_hBitmap, NULL, &rect);
   }
}