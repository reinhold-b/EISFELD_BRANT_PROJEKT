#include <string>
#include <functional>

#include "Frame.hpp"

auto Frame::getStart() const
{
    return start;
}

std::string Frame::getImgPath() const
{
    return m_imgPath;
}

std::vector<Label> Frame::getLabels() const
{
    return m_labels;
}

void Frame::show()
{
    return;
}

void Frame::handleHit(double reactionTime)
{
    return;
}

/**
 * @brief Prüft, ob der Punkt eines Klicks innerhalb der richtigen BoundingBox war. 
 * 
 * @param p 
 * @return true 
 * @return false 
 */
bool Frame::checkForHit(cv::Point p)
{
    std::vector<Label> currLabels = m_labels;
    for (const auto &i : currLabels)
    {
        std::cout << i.m_type << "  --  " << i.m_frame << "  --  " << std::endl;
        std::cout << i.m_bbox.x << " || " << i.m_bbox.y << " - " << i.m_bbox.width << " || " << i.m_bbox.height << std::endl;
        if (i.m_bbox.contains(p) && i.m_type != "DontCare")
        {

            return true;
        }
    }
    return false;
}

/**
 * @brief Errechnet aus der im Frame gespeicherten Startzeit die Differenz, die als
 * Reaktionszeit angenommen wird. 
 * 
 * @return double 
 */
double Frame::calcReactionTime()
{
    // Get current timestamp
    auto now = std::chrono::steady_clock::now();

    double elapsed_time_ms = std::chrono::steady_clock::duration(now - start).count();

    std::cout << elapsed_time_ms / 1000000 << "ms" << std::endl;

    // 3 sek zurueckgeben wenn timeout
    return elapsed_time_ms != 0 ? elapsed_time_ms / 1000000 : 3000;
}

void Frame::drawBox(cv::Mat image, cv::Rect b, int thickness, cv::Scalar color)
{
    rectangle(image, b,
              color,
              thickness, cv::LINE_8);
}

/**
 * @brief Wartet, solange die Funktion condition true ergibt.
 * Wird die Wartezti ueberschritten, wird callback ausgefuehrt.
 *
 * @param timems
 * @param condition
 * @param callback
 */
void Frame::waitForInput(double timems, std::function<bool(void)> condition, std::function<void(void)> callback)
{
    auto begin = std::chrono::high_resolution_clock::now();
    while (condition())
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);

        cv::waitKey(10);
        if (elapsed.count() >= timems)
        {
            callback();
            break;
        }
    }
}
