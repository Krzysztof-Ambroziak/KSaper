cmake_minimum_required(VERSION 3.11)

project(KSaper
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KSaper)
target_sources(KSaper
    PRIVATE src/Definitions.hpp
    PRIVATE src/KSaperApplication.cpp
    PRIVATE src/controller/Controller.cpp
    PRIVATE src/controller/Controller.hpp
    PRIVATE src/gui/Actions.cpp
    PRIVATE src/gui/Actions.hpp
    PRIVATE src/gui/MainWindow.cpp
    PRIVATE src/gui/MainWindow.hpp
    PRIVATE src/gui/MainWindow.ui
    PRIVATE src/gui/BoardWidget.cpp
    PRIVATE src/gui/BoardWidget.hpp
    PRIVATE src/model/Board.cpp
    PRIVATE src/model/Board.hpp
    PRIVATE src/model/IModel.hpp
    PRIVATE src/model/Model.cpp
    PRIVATE src/model/Model.hpp
    PRIVATE src/renderer/IRenderer.hpp
    PRIVATE src/renderer/NullRenderer.cpp
    PRIVATE src/renderer/NullRenderer.hpp
    PRIVATE src/renderer/Renderer.cpp
    PRIVATE src/renderer/Renderer.hpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Widgets
)
