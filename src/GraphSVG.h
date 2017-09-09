#ifndef _GraphSVG_h_
#define _GraphSVG_h_

#include <string>
#include <map>
#include <sstream>

class GraphSVG {
public:
    void addNode(std::string name, int x, int y);
    void addEdge(std::string from, std::string to);
    std::string getContent() const;
private:
    struct Coord { int x, y; };
    std::stringstream body;
    static std::string bodyTag;
    static std::string circleTag;
    static std::string lineTag;
    static std::string textTag;
    std::map<std::string, Coord> coordMap;
    int width = 0;
    int height = 0;
private:
    static std::string subs(std::string templ, std::map<std::string, std::string> feedDict);
};

#endif
