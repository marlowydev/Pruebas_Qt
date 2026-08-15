cmake_minimum_required(VERSION 3.16)

project(CalculadoraAguaEspumas VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(CalculadoraAguaEspumas
    main.cpp
    mainwindow.cpp mainwindow.h
    menupage.cpp menupage.h
    fosapage.cpp fosapage.h
    tanquepage.cpp tanquepage.h
)

target_link_libraries(CalculadoraAguaEspumas PRIVATE Qt6::Widgets)

set_target_properties(CalculadoraAguaEspumas PROPERTIES
    WIN32_EXECUTABLE TRUE
)
