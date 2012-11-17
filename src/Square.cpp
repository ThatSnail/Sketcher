#include "Square.h"

Square::Square(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Square::~Square()
{
    //dtor
}

void Square::draw(Image* img)
{
    for(int dx=0; dx<w; dx++)
    {
        if(0 <= x+dx && x+dx < img->width())
        {
            if(y < img->height())
            {
                (*img)(x+dx, y) = 255;
            }
            if(y+h < img->height())
            {
                (*img)(x+dx, y+h) = 255;
            }
        }
    }
    for(int dy=0; dy<h; dy++)
    {
        if(0 <= y+dy && y+dy < img->height())
        {
            if(x < img->width() && y < img->height())
            {
                if(x < img->width())
                {
                    (*img)(x, y+dy) = 255;
                }
                if(x+w < img->width())
                {
                    (*img)(x+w, y+dy) = 255;
                }
            }
        }
    }
}
