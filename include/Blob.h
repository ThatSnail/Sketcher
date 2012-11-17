#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include "Point.h"
#include "types.h"

class Blob
{
    public:
        Blob();
        virtual ~Blob();

        std::vector<Point> points;
        void draw(Image* image);
    protected:
    private:
};

#endif // BLOB_H
