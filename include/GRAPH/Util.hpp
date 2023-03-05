#ifndef UTIL_HPP
#define UTIL_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace util
{
     /**Check if coordinates is a zero (0 ,0) coordinates*/
     inline bool checkCords(sf::Vector2f cd) { return ((cd.x == 0) && (cd.y == 0)); }
     /**
      * @brief Calculate the midpoint between two points
      *
      * @param v0
      * @param v1
      * @return sf::Vector2f
      */
     sf::Vector2f midPoint(const sf::Vector2f &v0, const sf::Vector2f &v1);

     /**
      * @brief Averages two vertices
      *
      * @param v0 first vertex
      * @param v1 second vertex
      * @return sf::Vertex
      */
     sf::Vertex midPoint(const sf::Vertex &v0, const sf::Vertex &v1);

     /**
      * @brief This function computes the angle between two points or vertexes
      *
      */
     float pointAngle(sf::Vertex vertex0, sf::Vertex vertex1);

     float pointAngle(sf::Vector2f p0, sf::Vector2f p1);

     /**
      * @brief utility function to compute the average of two point positions
      *
      * @param arg0 first position
      * @param arg1 second position
      * @return sf::Vector2f the positions
      */
     sf::Vector2f average(const sf::Vector2f &arg0, const sf::Vector2f &arg1, const sf::Vector2f &arg2);

     /**
      * @brief Subdivision utility average function. This function averages three vertices
      *
      * @param arg0
      * @param arg1
      * @param arg2
      * @return sf::Vertex
      */
     sf::Vertex average(const sf::Vertex &arg0, const sf::Vertex &arg1, const sf::Vertex &arg2);

     float lineLength(sf::Vector2f arg0, sf::Vector2f arg1);

     /**
      * @brief Utility function to create a horizontal line
      *
      * @param startPos the point to start
      * @param len the length of choice
      * @param cr the color
      * @return sf::VertexArray a vertex array containing two points that would draw the line
      *             of choice.
      */
     sf::VertexArray horizonLine(sf::Vector2f startPos, float len,
                                 const sf::Color &cr = sf::Color::White);

     /**
      * @brief Just drawing horizontal lines, this function takes in the same arguments
      *
      * @param startPos the start point
      * @param len the lenght of choice
      * @param cr the color of the line
      * @return sf::VertexArray
      */
     sf::VertexArray verticalLine(sf::Vector2f startPos, float len,
                                  const sf::Color &cr = sf::Color::White);

} // utility functions

#endif