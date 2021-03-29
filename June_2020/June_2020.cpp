
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <chrono>
#include <numeric>
#include <vector>
#include <string>

enum class RingAngle
{
    NoRotation = 0,
    Rotated = 1,
};

struct Point
{
    double x_, y_;
    Point(double x, double y) : x_(x), y_(y) {};
    Point() : x_(0), y_(0) {};
};

struct Circle
{
    double radius_;
    Point center_;

    Circle(Point center = {}, double radius = 0) : center_(center), radius_(radius) {};

    double Area() const { return M_PI * std::pow(radius_, 2); };
    double Perimeter() const { return M_PI * 2. * radius_; };
    bool CirclesCross(const Circle& other) const
    {
        double xDist = std::pow((center_.x_ - other.center_.x_), 2);
        double yDist = std::pow((center_.y_ - other.center_.y_), 2);
        double distanceBetweenCircles = std::sqrt(xDist + yDist);
        if (distanceBetweenCircles < (radius_ + other.radius_))
            return true;
        return false;
    }
};

using Circles = std::vector<Circle>;

struct Ring
{
    double sideLength_;
    RingAngle ringStartAngle_;
    Point center_;
    Circles circles_;


    Ring(Point center, double sideLength, RingAngle ringStartAngle) :
        center_(center), sideLength_(sideLength), ringStartAngle_(ringStartAngle)
    {
        circles_ = {};
        CreateRings();
    }

    void CreateRings()
    {
        circles_.clear();
        for (int i{}; i < 6; ++i)
        {
            double radius = sideLength_ / 2.;
            double xPoint = sideLength_ * std::cos(i * M_PI / 3. + ((int)ringStartAngle_ * M_PI / 6.));
            double yPoint = sideLength_ * std::sin(i * M_PI / 3. + ((int)ringStartAngle_ * M_PI / 6.));

            circles_.emplace_back(Circle({ xPoint, yPoint }, radius));
        }
    }

    double OccupyingArea() const
    {
        return circles_[0].Area() * 6.;
    }

    bool VerifyNoRingOverlap(const Ring& other)
    {
        for (int i{}; i < circles_.size(); ++i)
        {
            for (int j{}; j < other.circles_.size(); ++j)
            {
                if (circles_[i].CirclesCross(other.circles_[j]))
                {
                    return false;
                }
            }
        }
        return true;
    }

    void reduceSideLength(double increment)
    {
        sideLength_ -= increment;
        CreateRings();
    }

    double Perimeter() const
    {
        return 2 * M_PI * sideLength_ * 1.5;
    }
};


double Solve()
{
    double CRadius = 1.5, totalArea{};
    int initialStartAngle{};
    Ring previousRing{ {}, 1, (RingAngle)initialStartAngle };
    while (true)
    {
        double areaIncrement = previousRing.OccupyingArea();
        if (areaIncrement < 0.0000001)
            break;
        totalArea += areaIncrement;
        initialStartAngle++;
        Ring ring{ {}, previousRing.sideLength_ - 0.0000001, (RingAngle)(initialStartAngle % 2) };
        while (!ring.VerifyNoRingOverlap(previousRing))
        {
            ring.reduceSideLength(0.0000001);
        }
        std::cout << "Next largest radius that doesn't overlap with previous ring: " << ring.sideLength_ << std::endl;
        previousRing = ring;
    }
    return totalArea / (M_PI * CRadius * CRadius);
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    auto solutionTuple = Solve();
    std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
    std::cout << "Computation time (seconds): " << (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000000) << std::endl;
    std::cout << "Area of containing circles / area of outer circle: " << solutionTuple << std::endl;
}

