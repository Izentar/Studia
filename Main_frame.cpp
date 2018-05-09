#ifndef MAIN_FRAME_CPP
#define MAIN_FRAME_CPP

#include "Main_frame.h"

Image::Image(const int& width, const int& height, const char& filling_edges, const char& filling_corner_ux, const char& filling_corner_uy, const char& filling_corner_dx, const char& filling_corner_dy, const char& main_filling)
{
    Board.resize(width);
    for (int i=0; i<width; i++)
    {
        Board[i].resize(height, ' ');
    }

    for
}

Image::Main_frame::Main_frame(const int& pos_x, const int& pos_y, const int& M_width, const int& M_height, const char& filling_edges, const char& filling_corner_ux, const char& filling_corner_uy, const char& filling_corner_dx, const char& filling_corner_dy, const char& main_filling)
:x(pos_x), y(pos_y), width(M_width), height(M_height) {}

Image::Main_frame::~Main_frame() {}

void Image::Main_frame::make_frame()
{
    //for (int i=; i<)
}


#endif // MAIN_FRAME_CPP
