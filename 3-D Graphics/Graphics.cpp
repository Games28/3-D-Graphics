#include "Graphics.h"

void draw_line(olc::PixelGameEngine* pge,int x0, int y0, int x1, int y1, olc::Pixel color)
{
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int side_length = abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= side_length; i++)
	{
		pge->Draw(round(current_x), round(current_y),color);

		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_rect(olc::PixelGameEngine* pge, int x, int y, int width, int height, olc::Pixel color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int current_x = x + i;
			int current_y = y + j;
			pge->Draw(current_x, current_y, color);
		}
	}
}

void draw_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, olc::Pixel color)
{
	draw_line(pge, x0, y0, x1, y1, color);
	draw_line(pge, x1, y1, x2, y2, color);
	draw_line(pge, x2, y2, x0, y0, color);
}
