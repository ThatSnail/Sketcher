#include "Blob.h"
#include <time.h>

Blob::Blob()
{
    points = std::vector<Point>();
}

Blob::~Blob()
{
    //dtor
}

void Blob::draw(Image* image)
{
    //srand(time(NULL));
    unsigned char color[] = {rand() % 255, rand() % 255, rand() % 255};
    for(int i=0; i<points.size(); i++)
    {
        Point point = points.at(i);
        (*image)(point.x, point.y, 0) = color[0];
        (*image)(point.x, point.y, 1) = color[1];
        (*image)(point.x, point.y, 2) = color[2];
    }
}
