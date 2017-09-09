#include "GraphSVG.h"

#include <string>
#include <regex>
#include <sstream>

using namespace std;

std::string GraphSVG::bodyTag = R"svg(<svg height="{w}" width="{h}">{content}</svg>)svg";
std::string GraphSVG::circleTag = R"svg(<circle cx="{x}" cy="{y}" r="{r}" stroke="black" stroke-width="1"/>)svg";
std::string GraphSVG::lineTag = R"svg(<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}"/>)svg";
std::string GraphSVG::textTag = R"svg(<text x="{x}" y="{y}" fill="red">{text}</text>)svg";

string GraphSVG::subs(string templ, map<string, string> feedDict)
{
    string result = templ;
    for (auto pr : feedDict) {
        result = regex_replace(result, regex("{"+pr.first+"}"), pr.second);
    }
    return result;
}

void GraphSVG::addNode(string name, int x, int y)
{
    coordMap[name] = {x, y};

    width = max(x, width);
    height = max(y, height);

    body << subs(circleTag, {
        {"x", to_string(x)}, 
        {"y", to_string(y)}});
    body << subs(textTag, {
        {"x", to_string(x)}, 
        {"y", to_string(y)}, 
        {"text", name}});
}

void GraphSVG::addEdge(string from, string to)
{
    Coord p1, p2;
    auto it = coordMap.find(from);
    if (it == coordMap.end()) {
        // TODO: handle error
    }
    p1 = it->second;

    it = coordMap.find(to);
    if (it == coordMap.end()) {
        // TODO: handle error
    }
    p2 = it->second;

    body << subs(lineTag, {
        {"x1", to_string(p1.x)},
        {"y1", to_string(p1.y)},
        {"x2", to_string(p2.x)},
        {"y2", to_string(p2.y)}});
}

string GraphSVG::getContent() const
{
    stringstream ss;
    ss << subs(bodyTag, {
        {"w", to_string(width)},
        {"h", to_string(height)},
        {"content", body.str()}});
    return ss.str();
}
