#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <GRAPH/GraphLine.hpp>

#define _FONT "C:\\font\\Golos_Text\\GolosText-Variable.ttf"
#define _IDEFAULT 8
#define _axislen 0.85
#define _COLOR(a) sf::Color(240, 240, 240, a)
#define _taglen 5.5f

extern sf::Font deFont;

/**
 * @brief  The graph Library. @attention use this library, ensure that your code has a global
 *        Variable defined as thus @code sf::Font deFont @endcode
 *
 */
namespace graph
{
     typedef sf::VertexArray Lines;

     enum Axis
     {
          X = 1,
          Y = 2,
          ALL = (X | Y)
     };

     typedef struct TagMark
     {
          float value;
          sf::Text label;
          sf::Vector2f position;
          sf::VertexArray mark;
     } Tag;

     typedef struct GraphScale
     {
          /*how many units to one cm on the x axis*/
          float xAxis;
          /*how many units to one cm on the y axis*/
          float yAxis;
          GraphScale(float x = 2.f, float y = 2.f) : xAxis(x), yAxis(y) {}
     } Scale;

     /// @brief A graph sheet entity
     class GraphSheet : public sf::Drawable,
                        public sf::Transformable
     {

     protected:
          /*the length of the y axis*/
          float yAxisLen;
          /*length of the x axis*/
          float xAxisLen;

     private:
          /*This represents the size of the graph*/
          sf::Vector2f graphSize;

          /*The x and y axis lines*/
          sf::VertexArray lines;

          /*Scale of the graphsheet created. This changes when change scale is called*/
          Scale graphScale;
          /*Represents the coordinates of the origin of the graph. This is used as a layer of
          abstraction to be used*/
          const sf::Vector2f pointOrigin;

          /*An array that holds plotted lines*/
          std::vector<gline::GraphLine *> plottedLines;
          /*holds the list of tag values and their labels. Useful for plotting the points*/
          std::vector<Tag> x_tags;

          /*contains all the y tags*/
          std::vector<Tag> y_tags;

          /*The X mesh*/
          std::vector<Lines> meshX;

          /*The y mesh*/
          std::vector<Lines> meshY;

          /*Number of X intervals*/
          unsigned int numXInterval;

          /*Number of y intervals*/
          unsigned int numYInterval;

     public:
          sf::Vector2u windowSize;

          /*The table of values to plot*/
          gline::Table table;
          sf::Color graphColor;
          sf::Font font;

          /**
           * @brief This routine inputs an x value and a y value into the table
           *
           * @param xvalue the value to input into the table
           * @param yval the value to input into the y table
           * @return true if table is valid
           * @return false if table is invalid
           */
          bool inputTable(float xvalue, float yval);
          // void createTable();

          void clearGraph();
          void removeLabel();
          void addLabel();
          void removeMesh();

          /**
           * @brief Change the scale of the graph
           *
           * @param axis the axis to change its scale
           * @param newScale the new scale to use on that axis
           */
          void changeScale(float newScale = 10.f, Axis axis = X);

          inline const sf::Vector2f &getSize() { return graphSize; }

          /**
           * @brief Return a copy of the graph pointOrigins.
           *
           * @return sf::Vector2f a copy of the pointOrigin member
           */
          inline sf::Vector2f graphOrigin() const { return pointOrigin; };

          /**
           * @brief This method generates a GraphLine object that can be drawn into the window.
           *        If the table is not valid, or entries are not found or not in range,
           *        the function returns a nullptr, thus always check the value of address returned
           *@param  color the color of the plots
           * @return gline::GraphLine* the address to the GraphLine object allocated in heap
           */
          gline::GraphLine *generatePlot(const sf::Color &col = _color0(150));

          /**
           * @brief Construct a new Graph Sheet object
           *
           * @param dimensions the size of the window
           * @param scale the x and y scales used
           * @param tableCap the initial capacity of the table
           */
          GraphSheet(const sf::Vector2u &dimensions, const GraphScale &scale,
                     const sf::Color &axisColor = _COLOR(150),
                     const sf::Font & = deFont,
                     unsigned int tableCap = 15);

          /**
           * @brief Creates a mesh on the specified axis
           *
           * @param num the number of lines per interval
           * @param col the colour to give the mesh lines
           * @param axis the axis to create the mesh on
           */
          void mesh(unsigned int num, const sf::Color &col, Axis axis = X);

     private:
          /**
           * @brief Giving an x value and corresponding y value, find the real coordinates
           *        to plot on window.@attention attention text Always check that the vector
           *        returned is not (0, 0) as this indicates that the value of either x or y
           *        or both were not found in the range of the graph.
           *
           * @param xvalue value of x in table
           * @param yvalue value of y in table
           * @return sf::Vector2f
           */
          sf::Vector2f getCoords(float xvalue, float yvalue);

          /**
           * @brief Check if the value is in the range of the graph. This important in making
           *        decisions that will involve rescaling the graph on any axis.
           *        @attention  returns true for the argument Axis::ALL if the value is both
           *        in the range of the y axis and the x axis.
           *
           * @param value the value to be checked
           * @param axis the axis to for which the value is checked against
           * @return true if the value is in range
           * @return false if the value is out of range
           */
          bool inRange(float value, Axis axis = X);
          /**
           * @brief Elongates the tag mark to create a well defined bound of the interval
           *
           * @param col the color of the bounding line
           */
          void boundInterval(const sf::Color &col = sf::Color(12, 12, 12, 100));
          /**
           * @brief utility to create mesh like grid in the graphsheet
           *
           * @param num This the number of line meshes in one cm of the graph
           * @param col the color of the mesh;
           */
          void createXMesh(unsigned int num = 5, const sf::Color &col = sf::Color(10, 10, 10, 50));
          void createYMesh(unsigned int num = 5, const sf::Color &col = sf::Color(10, 10, 10, 50));
          /**
           * @brief Create a Tags object and appends it to the tags array of this graphsheet.
           *        Given the number of intervals from origin to use, it calculates the
           *        correponding positions of the tags and creates them.
           *
           * @param interval the scale to use. i.e (2,,4,6) or (10,20,30) etc
           * @param numIntervals the number of intervals you wish to have from the origin
           * @param col the color of the intervals
           */
          unsigned int createYtags(float interval, unsigned int numIntervals,
                                   const sf::Color &col = sf::Color(10, 10, 10, 120));

          /**
           * @brief Create a Xtags object. Create tags for the x-axis line.
           *
           * @param numIntervals
           * @param interval the scale or interval you to use
           * @param col the color of the tag mark
           */
          unsigned int createXtags(float interval, unsigned int numIntervals,
                                   const sf::Color &col = sf::Color(10, 10, 10, 120));

          /**
           * @brief Find the lower boundary tag such that value is between the lower boundary
           *        and the upper boundary of that interval. @attention always check that -1
           *        is not returned as it indicates that the value is not in the boundaries
           *        of the graph.
           *
           * @param value
           * @return the index of the tag in the x_tag array
           */
          int findTagX(float value);

          int findTagY(float value);

          virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
     };
}; // graph classes

     // #include <Util.hpp>

#endif