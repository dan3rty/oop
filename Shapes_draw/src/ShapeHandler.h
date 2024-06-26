#pragma once

#include "CPoint.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCanvas.h"
#include "SFML/Graphics.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class ShapeHandler
{
public:
    ShapeHandler(std::istream& input, std::ostream& output);

    void ProcessShapes();

private:
    static constexpr int PRINT_PRECISION = 2;

    using IShapePtr = std::unique_ptr<IShape>;
    using ShapeVector = std::vector<IShapePtr>;

    enum class CommandType
    {
        IDLE,
        LINE,
        CIRCLE,
        RECTANGLE,
        TRIANGLE,
    };

    struct Command
    {
        CommandType type;
        std::string arguments;
    };

    using CommandHandler = std::function<IShapePtr(const std::string& arguments)>;

    const std::map<std::string, CommandType> COMMAND_KEYWORDS = {
            { "line", CommandType::LINE },
            { "circle", CommandType::CIRCLE },
            { "rectangle", CommandType::RECTANGLE },
            { "triangle", CommandType::TRIANGLE },
    };

    ShapeVector ReadShapes();
    Command ReadCommand();
    CommandType ParseCommandType(const std::string& command);
    static CommandHandler GetHandlerForCommand(CommandType type);

    static IShapePtr CreateLine(const std::string& arguments);
    static IShapePtr CreateCircle(const std::string& arguments);
    static IShapePtr CreateRectangle(const std::string& arguments);
    static IShapePtr CreateTriangle(const std::string& arguments);

    static CPoint ReadPoint(std::istream& input);
    static uint32_t ReadColor(std::istream& input);
    static double ReadValue(std::istream& input);

    void PrintShapeWithLargestArea(const ShapeVector& shapes);
    void PrintShapeWithSmallestPerimeter(const ShapeVector& shapes);

    void PrintShapeInfo(const std::unique_ptr<IShape>& shape);

    static void Draw(const ShapeVector& shapes);

    std::istream& m_input;
    std::ostream& m_output;
};