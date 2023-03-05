
#include <Util.hpp>
#include <cmath>

sf::Vector2f util::midPoint(const sf::Vector2f &v0, const sf::Vector2f &v1)
{
     sf::Vector2f mid;
     float y, x;
     if (v1.x > v0.x)
     {
          x = (v1.x - v0.x) / 2;
          y = (v1.y - v0.y) / 2;
          mid.x = v0.x + x;
          mid.y = v0.y + y;
     }
     else
     {
          x = (v0.x - v1.x) / 2;
          y = (v0.y - v1.y) / 2;
          mid.x = v1.x + x;
          mid.y = v1.y + y;
     }
     return mid;
}

sf::Vertex util::midPoint(const sf::Vertex &v0, const sf::Vertex &v1)
{
     sf::Vertex vert;
     vert.color = v0.color;
     vert.position.x = (v0.position.x + v1.position.x) / 2;
     vert.position.y = (v0.position.y + v1.position.y) / 2;
     return vert;
}

float util::pointAngle(sf::Vertex v0, sf::Vertex v1)
{
     float angle;
     int y, x;
     y = v1.position.y - v0.position.y;
     x = v1.position.x - v0.position.x;
     angle = std::atan((y / x)); // shift tan of opposite over adjacent
     return angle;
}
float util::pointAngle(sf::Vector2f v0, sf::Vector2f v1)
{
     float angle;
     int y, x;
     y = v1.y - v0.y;
     x = v1.x - v0.x;
     angle = std::atan((y / x)); // shift tan of opposite over adjacent
     return angle;
}

float util::lineLength(sf::Vector2f p0, sf::Vector2f p1)
{
     int y, x, len;
     y = p1.y - p0.y;
     x = p1.x - p0.x;
     len = std::sqrt(std::pow(y, 2) + std::pow(x, 2));
     return len;
}

sf::VertexArray util::horizonLine(sf::Vector2f start, float len, const sf::Color &col)
{

     sf::VertexArray temp(sf::Lines, 2);
     temp[0].position = start;
     temp[1].color = temp[0].color = col;
     temp[1].position = sf::Vector2f(start.x + len, start.y);

     /*return temp*/
     return temp;
}
sf::VertexArray util::verticalLine(sf::Vector2f start, float len, const sf::Color &col)
{
     sf::VertexArray temp(sf::Lines, 2);
     temp[0].color = temp[1].color = col;
     temp[0].position = start;
     temp[1].position = sf::Vector2f(start.x, start.y + len);
     return temp;
}

sf::Vector2f util::average(const sf::Vector2f &p0, const sf::Vector2f &p1, const sf::Vector2f &p2)
{
     sf::Vector2f avg;
     avg.x = (p0.x + p1.x + p2.x) / 3.f;
     avg.y = (p0.y + p1.y + p2.y) / 3.f;

     return avg;
}

sf::Vertex util::average(const sf::Vertex &v0, const sf::Vertex &v1, const sf::Vertex &v2)
{
     // average vertex
     sf::Vertex avg;

     avg.color = v0.color;
     avg.position.x = (v0.position.x + v1.position.x + v2.position.x) / 3.f;
     avg.position.y = (v0.position.y + v1.position.y + v2.position.y) / 3.f;

     return avg;
}