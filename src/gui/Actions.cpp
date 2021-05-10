#include "Actions.hpp"

#include <QAction>

Actions::Actions() :
        newGame(new QAction("&New game")) {
    newGame->setShortcut(QKeySequence::New);
    newGame->setToolTip("New game");
}

Actions::~Actions() {
    delete newGame;
}
