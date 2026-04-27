cmake_minimum_required(VERSION 3.19)
project(WS6 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
# --- ADD THIS LINE ---
find_package(VTK REQUIRED) 

qt_standard_project_setup()

# --- ADD THIS LINE ---
include_directories(${VTK_INCLUDE_DIRS})

qt_add_executable(WS6
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ModelPart.cpp
    ModelPart.h
    ModelPartList.cpp
    ModelPartList.h
    icons.qrc
)

target_link_libraries(WS6
    PRIVATE
        Qt::Core
        Qt::Widgets
        # --- ADD THIS LINE ---
        ${VTK_LIBRARIES}
)