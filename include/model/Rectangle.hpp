//
// Created by nico on 11/16/24.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

struct Point {
    float x;
    float y;

    Point(float x, float y): x(x), y(y) { }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point& operator*(const float& multiplier) {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }
};

class Rectangle {
public:
    Point center;
    float top;
    float bottom;
    float left;
    float right;
    int rotation;
    std::vector<Point> corner_points;


    Rectangle(float x, float y);

    void initialize(Point, int);

    static bool isCollision(const Rectangle&, const Rectangle&);

    [[nodiscard]] const Point& getCenter() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;
    [[nodiscard]] const int& getRotation() const;
    [[nodiscard]] const std::vector<Point>& getCornerPoints() const;

    void moveRectangle(Point delta_position, float multiplier);
};

#endif //RECTANGLE_HPP
