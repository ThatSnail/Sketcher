#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(int x, int y);
        virtual ~Point();

        int x;
        int y;

        bool operator==(Point point);
        bool operator<(const Point& point) const;
    protected:
    private:
};

#endif // POINT_H
