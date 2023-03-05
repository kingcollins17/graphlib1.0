#include <Graphsheet.hpp>
#include <Util.hpp>

using namespace std;

graph::GraphSheet::GraphSheet(const sf::Vector2u &dimension,
                              const graph::GraphScale &scale,
                              const sf::Color &axisCol, const sf::Font &fnt,
                              unsigned int tCap)
    : graphColor(axisCol),
      lines(sf::Lines, 4),
      windowSize(dimension),
      font(fnt),
      pointOrigin(sf::Vector2f(dimension.x / 2.f,
                               dimension.y / 2.f)),
      x_tags(std::vector<Tag>()),
      y_tags(std::vector<Tag>()),
      graphScale(scale),
      table(tCap),
      plottedLines(),
      meshX(),
      meshY()

{

     int len, offset;
     for (size_t i = 0; i < lines.getVertexCount(); i++)
     {

          if (i < 2) // if less than 2
          {
               yAxisLen = len = dimension.y * _axislen;
               offset = (dimension.y - len) / 2;

               if (i == 1)
                    lines[i].position = sf::Vector2f(dimension.x / 2, offset + len);
               else
                    lines[i].position = sf::Vector2f(dimension.x / 2, offset);
          }
          else
          {
               xAxisLen = len = dimension.x * _axislen;
               offset = (dimension.x - len) / 2;
               if (i == 3)
                    lines[i].position = sf::Vector2f(offset, dimension.y / 2);
               else
                    lines[i] = sf::Vector2f(offset + len, dimension.y / 2);
          }
          lines[i].color = graphColor;
     }

     // origin
     sf::Color tagCol = sf::Color(graphColor.r, graphColor.g,
                                  graphColor.b, graphColor.a - (50));
     numYInterval = createYtags(graphScale.yAxis, _IDEFAULT, tagCol); /*Tags y - axis*/
     numXInterval = createXtags(graphScale.xAxis, _IDEFAULT, tagCol);
     setOrigin(pointOrigin);
     graphSize = sf::Vector2f(xAxisLen, yAxisLen);
     // createXMesh();
     // createYMesh();
     // boundInterval();
}

void graph::GraphSheet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
     states.transform *= getTransform();
     states.texture = NULL;
     sf::Text txt;
     for (int i = 0; i < x_tags.size(); i++)
     {
          // draw the x axis tags
          target.draw(x_tags[i].mark);
          txt = x_tags[i].label;
          txt.setFont(font);
          target.draw(txt);

          // draw the y axis tags
          target.draw(y_tags[i].mark);
          txt = y_tags[i].label;
          txt.setFont(font);
          target.draw(txt);
     }

     target.draw(lines);
     if ((!meshX.empty()) && (!meshY.empty()))
          for (int i = 0; (i < meshX.size()) && (i < meshY.size()); i++)
          {
               target.draw(meshX[i]);
               target.draw(meshY[i]);
          }

     for (int x = 0; x < plottedLines.size(); x++)
          if (plottedLines[x] != nullptr)
               target.draw((*plottedLines[x]));
}

// createTags() definition

unsigned int graph::GraphSheet::createYtags(float interval, unsigned int numIntervals, const sf::Color &col)
{
     y_tags.clear(); // clear the original y_tags

     if (numIntervals > _IDEFAULT)
     {
          interval = (numIntervals * interval) / (_IDEFAULT);
          numIntervals = _IDEFAULT;
     }
     // to track the label marks on the y axis
     sf::Vector2f xpos = sf::Vector2f((windowSize.x - _taglen) / 2,
                                      (windowSize.y - yAxisLen) / 2);

     graph::Tag tag;

     float yintervalLen = yAxisLen / (numIntervals * 2.f);
     // printf("\nOriginal lenght of y intervals = (%.2f)\n", yintervalLen);

     int i;
     float x = (numIntervals * interval);
     char buffer[20];

     for (i = 0; i < (numIntervals * 2) + 1; i++)
     {
          // use horizontal lines for labeling y axis
          tag.value = x;
          // sprintf(buffer, "%3.1f", tag.value);
          sprintf(buffer, "%3.1f", tag.value);
          tag.position = xpos;

          tag.label.setScale(0.2f, 0.3f);
          x != 0 ? tag.label.setString(buffer) : tag.label.setString(" ");

          tag.label.setPosition(xpos.x - (float)_taglen * 2.5, xpos.y - 7.50f);
          tag.label.setFillColor(graphColor);
          // use horizontal line marks to label the y-axis
          tag.mark = (x == (numIntervals * interval) || x == -(numIntervals * interval))
                         ? (util::horizonLine(sf::Vector2f((windowSize.x - xAxisLen) / 2.f, xpos.y),
                                              xAxisLen, col))
                         : util::horizonLine(xpos, _taglen, col);

          // tag.mark = (util::horizonLine(sf::Vector2f((windowSize.x - xAxisLen) / 2.f, xpos.y),
          //                               xAxisLen, col));

          xpos.y += yintervalLen;

          y_tags.push_back(tag); // insert the tag into the vector array
          x -= interval;
     }
     return ((numIntervals * 2));
}

unsigned int graph::GraphSheet::createXtags(float interval, unsigned int numIntervals, const sf::Color &col)
{
     x_tags.clear(); // clear the original x tags
     // check if number of intervals is above 10
     if (numIntervals > _IDEFAULT)
     {
          interval = (numIntervals * interval) / _IDEFAULT;
          numIntervals = _IDEFAULT;
     }
     sf::Vector2f ypos = sf::Vector2f((windowSize.x - xAxisLen) / 2.f,
                                      (windowSize.y - _taglen) / 2.f);

     float xInterLen = xAxisLen / (numIntervals * 2); /*The lenght of one interval*/
     int i;
     float x;
     char buff[20];
     graph::Tag tag;
     x = -(numIntervals * interval);
     for (i = 0; i < (numIntervals * 2) + 1; i++)
     {
          tag.value = x;
          sprintf(buff, "%2.1f", tag.value);
          tag.position = ypos;

          x != 0 ? tag.label.setString(buff) : tag.label.setString(" ");
          tag.label.setFillColor(graphColor);
          tag.label.setScale(0.2f, 0.3f);

          tag.label.setPosition(ypos.x - 7.5f, ypos.y + (_taglen * 2)); /*position of tag*/
          tag.mark = (x == (numIntervals * interval) ||
                      x == -(numIntervals * interval))
                         ? (util::verticalLine(sf::Vector2f(ypos.x,
                                                            (windowSize.y - yAxisLen) / 2),
                                               yAxisLen, col))
                         : util::verticalLine(ypos, _taglen, col); /*Line mark*/
          // tag.mark = (util::verticalLine(sf::Vector2f(ypos.x,
          //                                             (windowSize.y - yAxisLen) / 2),
          //                                yAxisLen, col));

          x_tags.push_back(tag); // append tag to the list of tags;
          x += interval;
          ypos.x += xInterLen;
     }
     /*reason for removing the minus 1 is that number of intervals is
     different from number of tags. Number of tags is equal to number of interval + 1
     reason being that number of tags, zero 0 is included
     */
     return (numIntervals * 2);
}

//------------------------------------------------------------------
int graph::GraphSheet::findTagX(float sval)
{
     for (int i = 0; i < x_tags.size(); i++)
     {
          // if the value is in the boundary, return the index of that tag
          if ((x_tags[i].value <= sval) && (x_tags[i + 1].value > sval))
               return i;
     }
     return -1;
}

int graph::GraphSheet::findTagY(float sval)
{
     for (int i = 0; i < y_tags.size(); i++)
     {
          // if the value is in the boundary, return the index of that tag
          if ((y_tags[i].value > sval) && (y_tags[i + 1].value <= sval))
               return i;
     }
     return -1;
}

//------------------------------------------------------------------------
/*@TODO: TO BE REVISED*/
sf::Vector2f graph::GraphSheet::getCoords(float x_val, float y_val)
{
     sf::Vector2f cords;
     // NOTE: Revised approach
     if ((inRange(x_val) && inRange(y_val, Y)))
     {
          cords.x = pointOrigin.x + ((x_val / graphScale.xAxis) * (xAxisLen / numXInterval));
          cords.y = pointOrigin.y - ((y_val / graphScale.yAxis) * (yAxisLen / numYInterval));
     }
     /*return the coordinates*/
     return cords;
}

//------------------------------------------------------------------------
bool graph::GraphSheet::inputTable(float x_val, float y_val)
{
     table.x.push_back(x_val); /*insert into the x table*/
     table.y.push_back(y_val); /*insert into the y table*/
     return table.valid();
}

gline::GraphLine *graph::GraphSheet::generatePlot(const sf::Color &col)
{
     if (table.valid() && (table.isEmpty() == false))
     {
          sf::VertexArray temp(sf::LinesStrip, table.x.size());
          sf::Vector2f tpos;
          int i;
          for (i = 0; i < table.x.size(); i++)
          {
               tpos = getCoords(table.x[i], table.y[i]);
               if ((tpos.x == 0) && (tpos.y == 0))
                    break;

               // else continue in the loop
               temp[i].position = tpos;
               // temp[i].color = _color0(150);
          }
          temp.resize(i);
          gline::GraphLine *gline = new gline::GraphLine(temp, col);

          plottedLines.push_back(gline); // add it to the array of plotted lines
          return gline;
     }
     return nullptr;
}

void graph::GraphSheet::changeScale(float newScale, Axis axis)
{
     if (axis == X)
     {
          numXInterval = createXtags(newScale, _IDEFAULT);
          graphScale.xAxis = newScale;
     }
     else
     {
          numYInterval = createYtags(newScale, _IDEFAULT);
          graphScale.yAxis = newScale;
     }
}

void graph::GraphSheet::clearGraph()
{
     for (int i = 0; i < plottedLines.size(); i++)
     {
          /*Delete the GraphLine object stored at that location*/
          delete plottedLines[i];
          plottedLines[i] = nullptr;
     }
     plottedLines.clear();
}

void graph::GraphSheet::removeLabel()
{
     int i;
     for (i = 0; i < x_tags.size(); i++)
     {
          x_tags[i].label.setString(" ");
          y_tags[i].label.setString(" ");
     }
}
void graph::GraphSheet::addLabel()
{
     int i;
     char buf[20];
     if ((x_tags[0].label.getString() != " ") || (y_tags[0].label.getString() != " "))
          return;
     for (i = 0; i < x_tags.size(); i++)
     {
          if (x_tags[i].value != 0)
          {
               sprintf(buf, "%.1f", x_tags[i].value);
               x_tags[i].label.setString(buf);
          }

          if (y_tags[i].value != 0)
          {
               sprintf(buf, "%.1f", y_tags[i].value);
               y_tags[i].label.setString(buf);
          }
     }
}

void graph::GraphSheet::boundInterval(const sf::Color &col)
{

     // ypos to manage the position of the y tags and xpos for x tags
     sf::Vector2f xpos, ypos;
     xpos.y = (windowSize.y - yAxisLen) / 2.f;
     ypos.x = (windowSize.x - xAxisLen) / 2.f;

     for (int i = 0; i < x_tags.size(); i++)
     {
          xpos.x = x_tags[i].position.x;
          ypos.y = y_tags[i].position.y;

          x_tags[i].mark = util::verticalLine(xpos, yAxisLen, col);

          y_tags[i].mark = util::horizonLine(ypos, xAxisLen, col);
     }
}

void graph::GraphSheet::createXMesh(unsigned int num, const sf::Color &col)
{
     // meshX.clear();
     if (meshX.empty())
     {
          sf::Vector2f tpos;
          float unit = (graphScale.xAxis / num);
          int i, j;
          float intervLen = (xAxisLen / numXInterval); // interval lenght
          for (i = 0; i < (x_tags.size() - 1); i++)
          {
               tpos = x_tags[i].position;
               for (j = 0; j < num; j++)
               {
                    tpos.x += ((unit / graphScale.xAxis) * intervLen);
                    meshX.push_back(util::verticalLine(
                        sf::Vector2f(tpos.x, ((windowSize.y - yAxisLen) / 2.f)),
                        yAxisLen, col));
               }
          }
     }
}

// duplicate function
void graph::GraphSheet::createYMesh(unsigned int num, const sf::Color &col)
{
     // meshY.clear();
     if (meshY.empty())
     {
          sf::Vector2f ypos;
          float unit = (graphScale.yAxis / num);
          int i, j;
          float intervLen = (yAxisLen / numYInterval); // interval lenght

          for (i = 0; i < (y_tags.size() - 1); i++)
          {
               ypos = y_tags[i].position;
               for (j = 0; j < num; j++)
               {
                    ypos.y += ((unit / graphScale.yAxis) * intervLen);
                    meshY.push_back(util::horizonLine(sf::Vector2f((windowSize.x - xAxisLen) / 2, ypos.y),
                                                      xAxisLen, col));
               }
          }
     }
}

void graph::GraphSheet::mesh(unsigned int num, const sf::Color &col, graph::Axis axis)
{
     if (axis == graph::X)
          createXMesh(num, col);
     else if (axis == graph::Y)
          createYMesh(num, col);
     else if (axis == (graph::X | graph::Y))
     {
          createXMesh(num, col);
          createYMesh(num, col);
     }
     boundInterval(sf::Color(col.r, col.g, col.b, col.a + (250 - col.a)));
}

void graph::GraphSheet::removeMesh()
{
     meshX.clear();
     meshY.clear();
     createXtags(graphScale.xAxis, _IDEFAULT, graphColor);
     createYtags(graphScale.yAxis, _IDEFAULT, graphColor);
}

bool graph::GraphSheet::inRange(float value, graph::Axis axis)
{
     bool stat;
     if (axis == X)
          stat = (x_tags[0].value <= value) && (x_tags[x_tags.size() - 1].value >= value);
     else if (axis == Y)
          stat = ((y_tags[0].value >= value) && (y_tags[y_tags.size() - 1].value <= value));
     else
     {
          stat = (x_tags[0].value <= value) && (x_tags[x_tags.size() - 1].value >= value) &&
                 ((y_tags[0].value >= value) && (y_tags[y_tags.size() - 1].value <= value));
     }
     return stat;
}