#include "BoundingBox.hpp"

BoundingBox::BoundingBox(float up, float left, float bot, float right){
    m_upperLeftCorner.x = left;
    m_upperLeftCorner.y = up;
    m_bottomRightCorner.x = right;
    m_bottomRightCorner.y = bot;
}

bool BoundingBox::isInsideOfBox(Point p){
    return p.x >= m_upperLeftCorner.x &&
           p.y >= m_upperLeftCorner.y &&
           p.x <= m_bottomRightCorner.x &&
           p.y <= m_bottomRightCorner.y;
}