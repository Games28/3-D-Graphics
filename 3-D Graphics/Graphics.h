#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "olcPixelGameEngine.h"

void draw_line(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, olc::Pixel color);
void draw_rect(olc::PixelGameEngine* pge, int x, int y, int width, int height, olc::Pixel color);
void draw_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, olc::Pixel color);

#endif // !GRAPHICS_H


