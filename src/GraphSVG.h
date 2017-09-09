#ifndef _GraphSVG_h_
#define _GraphSVG_h_

#include <string>
#include <map>
#include <sstream>
#include <limits>

class GraphSVG {
public:
    void addNode(std::string name, int x, int y, int r = 24, std::string color = "#1A4F63");
    void addEdge(std::string from, std::string to);
    std::string getContent(int border = 30) const;
private:
    struct Coord { int x, y; };
    std::stringstream nodes;
    std::stringstream edges;
    static std::string bodyTag;
    static std::string circleTag;
    static std::string lineTag;
    static std::string textTag;
    std::map<std::string, Coord> coordMap;
    int minX = std::numeric_limits<int>::infinity();
    int minY = std::numeric_limits<int>::infinity();
    int maxX = -std::numeric_limits<int>::infinity();
    int maxY = -std::numeric_limits<int>::infinity();
private:
    static std::string subs(std::string templ, std::map<std::string, std::string> feedDict);
};

#endif
