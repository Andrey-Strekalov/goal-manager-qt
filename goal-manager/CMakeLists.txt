cmake_minimum_required(VERSION 3.19)
project(goal-manager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(goal-manager
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/windows/mainwindow.cpp
    src/windows/mainwindow.h
    src/ui/mainwindow.ui
    resources/resources.qrc
    src/core/step.h
    src/core/step.cpp
    src/core/goal.h
    src/core/goalvalidator.h
    src/core/goalvalidator.cpp
    src/core/goalcalculator.h
    src/core/goalcalculator.cpp
)

set_property(TARGET goal-manager PROPERTY AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/src/ui")

target_link_libraries(goal-manager
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS goal-manager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET goal-manager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
