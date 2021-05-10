#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <QHash>

namespace ksaper {

constexpr int MAX_ROWS = 30;
constexpr int MAX_COLUMNS = 50;

enum Field {
    EMPTY = 0,
    MINE = 1
};

enum Neighbours {
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8
};

enum Mark {
    HIDDEN = 0,
    VISIBLE = 1,
    BOMB = 2,
    QUESTION = 3
};

enum Level {
    EASY = 0,
    ADVANCED = 1,
    EXPERT = 2,
    CUSTOM = 3
};

struct Dimension {
    int rows;
    
    int columns;
};

struct Size {
    Dimension dimension;
    
    int mines;
};

struct Square {
    Field field;
    
    Neighbours neighbours;
    
    Mark mark;
};

const QHash<Level, Size> LevelToSize {
    {Level::EASY, {{8, 8}, 10}},
    {Level::ADVANCED, {{16, 16}, 40}},
    {Level::EXPERT, {{16, 30}, 99}}
};

}

#endif // DEFINITIONS_HPP
