cmake_minimum_required(VERSION 3.19)
project(Homework LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Homework
    WIN32 MACOSX_BUNDLE
    main.cpp
    Mywindow.cpp
    Mywindow.h
    mainwindow.h mainwindow.cpp mainwindow.ui
)

target_link_libraries(Homework
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Homework
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Homework
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
