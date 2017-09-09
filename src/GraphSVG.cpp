#include "GraphSVG.h"

#include <string>
#include <regex>
#include <sstream>

using namespace std;

string GraphSVG::bodyTag = R"svg(<svg xmlns="http://www.w3.org/2000/svg"
width="{w}" height="{h}" viewBox="{min-x} {min-y} {w} {h}"
style="background-color:#F5F5F5;">{content}</svg>)svg";

string GraphSVG::circleTag = R"svg(<circle cx="{x}" cy="{y}" r="{r}"
fill="{color}" opacity="0.9"/>)svg";

string GraphSVG::lineTag = R"svg(<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}"
stroke="black" stroke-width="1"/>)svg";

string GraphSVG::textTag = R"svg(<text x="{x}" y="{y}" fill="black" 
text-anchor="middle" alignment-baseline="central" 
font-family="Helvetica">{text}</text>)svg";

string GraphSVG::subs(string templ, map<string, string> feedDict)
{
    // a mini template engine
    string result = templ;
    for (auto pr : feedDict) {
        result = regex_replace(result, regex("\\{"+pr.first+"\\}"), pr.second);
    }
    return result;
}

void GraphSVG::addNode(string name, int x, int y, int r, string color)
{
    coordMap[name] = {x, y};

    minX = min(x - r, minX);
    minY = min(y - r, minY);
    maxX = max(x + r, maxX);
    maxY = max(y + r, maxY);

    nodes << subs(circleTag, {
        {"x", to_string(x)},
        {"y", to_string(y)},
        {"r", to_string(r)},
        {"color", color}});
    nodes << subs(textTag, {
        {"x", to_string(x)}, 
        {"y", to_string(y)}, 
        {"text", name}});
}

void GraphSVG::addEdge(string from, string to)
{
    Coord p1, p2;
    auto it = coordMap.find(from);
    if (it == coordMap.end()) {
        throw SVGDrawError("node '" + from + "' hasn't been defined");
    }
    p1 = it->second;

    it = coordMap.find(to);
    if (it == coordMap.end()) {
        throw SVGDrawError("node '" + to + "' hasn't been defined");
    }
    p2 = it->second;

    edges << subs(lineTag, {
        {"x1", to_string(p1.x)},
        {"y1", to_string(p1.y)},
        {"x2", to_string(p2.x)},
        {"y2", to_string(p2.y)}});
}

string GraphSVG::getContent(int border) const
{
    stringstream ss;
    int w = maxX - minX;
    int h = maxY - minY;
    ss << subs(bodyTag, {
        {"w", to_string(w + 2 * border)},
        {"h", to_string(h + 2 * border)},
        {"min-x", to_string(minX - border)},
        {"max-x", to_string(maxX + border)},
        {"min-y", to_string(minY - border)},
        {"max-y", to_string(maxY + border)},
        {"content", edges.str() + nodes.str()}});
    return ss.str();
}
