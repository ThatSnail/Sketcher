#ifndef SQUARE_H
#define SQUARE_H

#include "types.h"

class Square
{
    public:
        Square(int x, int y, int w, int h);
        virtual ~Square();

        int x;
        int y;
        int w;
        int h;

        void draw(Image* img);

    protected:
    private:
};

#endif // SQUARE_H
