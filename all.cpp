#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
struct Point
{
    double x, y;
    Point(double x=0, double y=0) : x(x), y(y) {}
};
double Distance(const Point &p1, const Point &p2)
{
    return sqrt(pow(p1.x-p2.x, 2)+pow(p1.y-p2.y, 2));
}
double PathLength(const vector<int> &route, const vector<Point> &locations)
{
    double totalDistance=0.0;
    for (size_t i=0; i< route.size()-1; ++i)
    {
        totalDistance += Distance(locations[route[i]], locations[route[i+1]]);
    }
    return totalDistance + Distance(locations[route.back()], locations[route.front()]);
}
void Optimize2Opt(vector<int> &route, const vector<Point> &locations, int size)
{
    bool improved=true;
    while (improved)
    {
        improved=false;
        double currentLength=PathLength(route, locations);
        for (int i=1; i<size - 2; i++)
        {
            for (int j = i + 1; j < size - 1; j++)
            {
                reverse(route.begin() + i, route.begin() + j + 1);
                double newLength = PathLength(route, locations);
                if (newLength < currentLength)
                {
                    currentLength = newLength;
                    improved = true;
                }
                else
                {
                    reverse(route.begin() + i, route.begin() + j + 1);
                }
            }
        }
    }
}
void Optimize3Opt(vector<int> &route, const vector<Point> &locations, int size)
{
    bool improved = true;
    while (improved)
    {
        improved = false;
        double currentLength=PathLength(route, locations);
        for (int i = 1; i <size - 2; i++)
        {
            for (int j = i + 1; j < size - 1; j++)
            {
                for (int k = j + 1; k < size; k++)
                {
                    reverse(route.begin() + i, route.begin() + j + 1);
                    reverse(route.begin()+j+1, route.begin()+k+1);
                    double newLength=PathLength(route,locations);
                    if (newLength<currentLength)
                    {
                        currentLength=newLength;
                        improved=true;
                    }
                    else
                    {
                        reverse(route.begin()+i, route.begin()+j+1);
                        reverse(route.begin()+j+1, route.begin()+k+1);
                    }
                }
            }
        }
    }
}
int main()
{
    int pointCount;
    cin>>pointCount;
    vector<Point> locations(pointCount);
    for (int i=0; i<pointCount; ++i)
    {
        cin>>locations[i].x>>locations[i].y;
    }
    vector<int> route(pointCount + 1);
    for (int i=0; i<pointCount; ++i)
    {
        route[i]=i;
    }
    route[pointCount]=0;
    Optimize2Opt(route, locations, pointCount + 1);
    Optimize3Opt(route, locations, pointCount + 1);
    double finalDistance=PathLength(route, locations);
    cout<<finalDistance<< " 1" << endl;
    for (int i=0; i<pointCount + 1; ++i)
    {
        cout << route[i] << " ";
    }
    cout << endl;
    return 0;
}
