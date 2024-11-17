//
// Created by nico on 11/16/24.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

class Rectangle {
public:
    float x;
    float y;
    int rotation;
    std::vector<int> x_points;
    std::vector<int> y_points;

    Rectangle(float x, float y);

    static float computeCorners(float center, float x);

    std::vector<int> calculateXPoints() const;

    std::vector<int> calculateYPoints() const;

    const std::vector<int> &getXPoints() const;
    const std::vector<int> &getYPoints() const;

    static bool isCollision(const Rectangle&, const Rectangle&);

    [[nodiscard]] const float& getX() const;
    [[nodiscard]] const float& getY() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;
    [[nodiscard]] const int& getRotation() const;

    void moveRectangle(float delta_x, float delta_y, float multiplier);
};

#endif //RECTANGLE_HPP
