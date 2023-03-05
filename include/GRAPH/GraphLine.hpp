#ifndef GRAPHLINE_HPP
#define GRAPHLINE_HPP

#include <SFML/Graphics.hpp>

#define _color0(a) sf::Color(247, 247, 247, a)
#define _sdiv 7

namespace gline
{

     typedef struct GraphTable
     {
          std::vector<float> x;
          std::vector<float> y;
          GraphTable(unsigned int tableCap = 10) : x(tableCap), y(tableCap) {}
          // initialize table with space for 10

          // check if table is valid
          inline bool isEmpty() { return (x.empty() || y.empty()); }
          inline bool valid() { return (x.size() == y.size()); }
          inline void clear()
          {
               x.clear();
               y.clear();
          }
     } Table;

     class GraphLine : public sf::Drawable, sf::Transformable
     {
     public:
          GraphLine();
          /**
           * @brief Construct a new Graph Line object with a given vertex array.
           *
           * @param arg
           */
          GraphLine(const sf::VertexArray &arg, const sf::Color &col = _color0(150));

          /**
           * @brief Construct a new Graph Line object with random vertices. Use only if you want
           *        to test
           *
           * @param empty
           */
          GraphLine(bool empty);

          /**
           * @brief makes use of subdivision surface algorithms to smoothen the curves
           *        of a graph plot.
           *
           *@param times number of times to smoothen the line. The higher the times, the
                         the smoother the curve
           */
          void smoothen(unsigned int times = 1);

          /**
           * @brief Changes the color of the plotted line.
           *
           * @param col the color to change to
           */
          void changeColor(const sf::Color &col);

     private:
          /**
           * @brief Utility to subdivide the vertices of the line thus making the line consist
           *        of (2 x vertexCount) - 1.
           *
           * @param numOfTimes the number of times the vertex array should be subdivided
           */
          void subDivide(unsigned int numOfTimes = 1);

          /**
           * @brief Curve the vertices of the line. Thus creating the sense of a smoothly
           *        curved line.
           */
          void curve();

          /**
           * @brief Computes the average of two vectors or three vectors
           *
           * @param v0 first vector
           * @param v1 second vector
           * @return sf::Vector2f
           */
          sf::Vector2f average(const sf::Vector2f &v0, const sf::Vector2f &v1);
          sf::Vector2f average(const sf::Vector2f &v0, const sf::Vector2f &v1, const sf::Vector2f &v2);
          virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

          /*number of subdivisions available. To be used so that system doesnt run out memory*/
          unsigned int numDivisions;

     protected:
          /*An array of vertices of the line to be drawn on the graph plane*/
          sf::VertexArray plots;
          sf::Color color;
     };
     typedef GraphLine GLine;

}; // gline

#endif