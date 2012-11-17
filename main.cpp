#include "CImg.h"
//#include "grid.h"
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include <cstdlib>

#include "Blob.h"
#include "Point.h"
#include "Square.h"

using namespace std;
using namespace cimg_library;

const CImg<float> sobelX(3, 3, 1, 1, -1, 0, 1, -2, 0, 2, -1, 0, 1);
const CImg<float> sobelY = sobelX.get_transpose();
const CImg<float> sobelXInv(3, 3, 1, 1, 1, 0, -1, 2, 0, -2, 1, 0, -1);
const CImg<float> sobelYInv = sobelXInv.get_transpose();

vector<Blob> getBlobs(Image* image);

const int SQUARE_SIZE = 4;

int main()
{
    Image mainImage("image4.png");
    uint width = mainImage.width();
    uint height = mainImage.height();
    Image grayImage = mainImage.get_channel(0);
    Image blurredImage = grayImage.blur(0);
    Image convolvedImageX = blurredImage.get_convolve(sobelX);
    Image convolvedImageY = blurredImage.get_convolve(sobelY);
    Image convolvedImageXInv = blurredImage.get_convolve(sobelXInv);
    Image convolvedImageYInv = blurredImage.get_convolve(sobelYInv);
    Image convolvedImage = Image(mainImage);
    cimg_forXY(convolvedImage, x, y)
    {
        convolvedImage(x, y) = sqrt(pow(convolvedImageX(x, y), 2) + pow(convolvedImageXInv(x, y), 2) + pow(convolvedImageY(x, y), 2) + pow(convolvedImageYInv(x, y), 2));
    }

    vector<Blob> blobs = getBlobs(&convolvedImage);
    Image blobImage = Image(width, height, 1, 3);
    for(int i=0; i<blobs.size(); i++)
    {
        blobs.at(i).draw(&blobImage);
    }

    CImgDisplay mainDisplay(mainImage, "MAIN IMAGE");
    CImgDisplay convolvedDisplay(convolvedImage, "CONVOLVED IMAGE");
    CImgDisplay blobDisplay(blobImage, "BLOB IMAGE");

    while(!mainDisplay.is_closed())
    {

    }
}

vector<Blob> getBlobs(Image* image)
{
    map<Point, bool> markedPoints = map<Point, bool>();
    vector<Point> markedPointsV = vector<Point>();
    map<Point, bool>::iterator it;

    cimg_forXY(*image, x, y)
    {
        if((*image)(x, y) < 10)
        {
            it = markedPoints.begin();
            markedPoints.insert(it, pair<Point, bool>(Point(x, y), true));
            markedPointsV.push_back(Point(x, y));
        }
        else
        {
            markedPoints.insert(it, pair<Point, bool>(Point(x, y), false));
        }
    }

    vector<Blob> blobs = vector<Blob>();

    while(markedPointsV.size() > 0)
    {
        Blob blob = Blob();

        vector<Point> frontier = vector<Point>();

        frontier.push_back(markedPointsV.at(0));

        vector<Point> blobPoints = vector<Point>();

        while(frontier.size() > 0)
        {
            Point point = frontier.at(0);
            int x = point.x;
            int y = point.y;

            if(markedPoints[Point(x-1, y)])
            {
                frontier.push_back(Point(point.x-1, point.y));
            }
            if(markedPoints[Point(x+1, y)])
            {
                frontier.push_back(Point(point.x+1, point.y));
            }
            if(markedPoints[Point(x, y-1)])
            {
                frontier.push_back(Point(point.x, point.y-1));
            }
            if(markedPoints[Point(x, y+1)])
            {
                frontier.push_back(Point(point.x, point.y+1));
            }

            frontier.erase(frontier.begin());
            blobPoints.push_back(point);
            vector<Point>::iterator mit = find(markedPointsV.begin(), markedPointsV.end(), point);
            if(mit != markedPointsV.end())
            {
                markedPointsV.erase(mit);
            }
            markedPoints[point] = false;
        }

        blob.points = blobPoints;
        blobs.push_back(blob);
    }
    return blobs;
}
