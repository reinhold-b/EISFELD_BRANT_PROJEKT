#ifndef BOUNDINGBOX_HPP_INCLUDED
#define BOUNDINGBOX_HPP_INCLUDED


class BoundingBox
{
    private:
    struct Point
    {
        float x;
        float y;
    };

    Point m_upperLeftCorner;
    Point m_bottomRightCorner;
    
    bool isInsideOfBox(Point p);
    

    public:
    BoundingBox(float up, float left, float bot, float right);

    ~BoundingBox();
};


#endif //BOUNDINGBOC_HPP_INCLUDED