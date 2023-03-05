#include <GraphLine.hpp>

#define _xtart 2.5

gline::GraphLine::GraphLine() : plots(sf::LineStrip, 10),
                                numDivisions(_sdiv), color(_color0(150)) {}

gline::GraphLine::GraphLine(const sf::VertexArray &arg, const sf::Color &col)
    : plots(arg), numDivisions(_sdiv), color(col)
{
     for (int i = 0; i < plots.getVertexCount(); i++)
          plots[i].color = color;
}

gline::GraphLine::GraphLine(bool empty) : plots(sf::LineStrip, 10),
                                          numDivisions(_sdiv),
                                          color(_color0(150))
{
     if (!empty)
     {
          sf::Vertex vert(sf::Vector2f(_xtart + (1 * 25), std::rand() % 100));
          plots[0] = vert;
          plots[0].color = _color0(150);
          _color0(150);

          for (int i = 1; i < plots.getVertexCount(); i++)
          {
               plots[i] = sf::Vertex(sf::Vector2f(_xtart + ((i + 1) * 25),
                                                  (std::rand() % 10) * i));
               plots[i].color = color;
          }
     }
};

void gline::GraphLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
     states.transform *= getTransform();
     states.texture = NULL;

     target.draw(plots);
}

sf::Vector2f gline::GraphLine::average(const sf::Vector2f &v0, const sf::Vector2f &v1)
{
     sf::Vector2f avg;
     avg.x = (v0.x + v1.x) / 2.f; // average of the x coordinates
     avg.y = (v0.y + v1.y) / 2.f;
     // sf::Vector2f avg = sf::Vector2f(x, y);
     return avg; // return the copy of the average
}
sf::Vector2f gline::GraphLine::average(const sf::Vector2f &v0, const sf::Vector2f &v1,
                                       const sf::Vector2f &v2)
{
     float x, y;
     x = (v0.x + v1.x + v2.x) / 3;
     y = (v0.y + v1.y + v2.y) / 3;
     return sf::Vector2f(x, y); // return vector
}

void gline::GraphLine::smoothen(unsigned int numTimes)
{
     subDivide(numTimes);
     curve();
}

void gline::GraphLine::curve()
{
     sf::Vector2f tem_pos;
     for (int i = 0; i < plots.getVertexCount() - 2; i++)
     {
          tem_pos = average(plots[i].position, plots[i + 1].position, plots[i + 2].position);
          plots[i + 1].position = average(average(plots[i + 1].position, tem_pos),
                                          plots[i + 1].position);
     }
}

void gline::GraphLine::subDivide(unsigned int numTimes)
{

     for (int j = 0; j < numTimes; j++)
     {
          if (numDivisions <= 0)
               break; // if available divisions has been exhausted

          sf::VertexArray temp(sf::LinesStrip, (plots.getVertexCount() * 2) - 1);
          sf::Vector2f pos;
          temp[0].position = plots[0].position;

          // create a subdivided array of the original plots array
          for (int i = 0; i < plots.getVertexCount() - 1; i++)
          {
               pos = average(plots[i].position, plots[i + 1].position);

               temp[(2 * i) + 1].position.x = pos.x;
               temp[(2 * i) + 1].position.y = pos.y;
               temp[(2 * i) + 1].color = color;

               temp[(2 * i) + 2].position.x = plots[i + 1].position.x;
               temp[(2 * i) + 2].position.y = plots[i + 1].position.y;
               temp[(2 * i) + 2].color = sf::Color(color.r, color.g,
                                                   color.b, (std::rand() % 255));
          }
          plots.resize(temp.getVertexCount());
          plots = temp;
          numDivisions--;
     }
}

void gline::GraphLine::changeColor(const sf::Color &col)
{
     color = col;
     for (int i = 0; i < plots.getVertexCount(); i++)
          plots[i].color = col;
}