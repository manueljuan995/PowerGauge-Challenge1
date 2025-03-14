cmake_minimum_required(VERSION 3.16)

project(Challenge1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appChallenge1
    main.cpp
    backend/backend.h backend/backend.cpp
    backend/datasource.h backend/datasource.cpp
    res.qrc
)

qt_add_qml_module(appChallenge1
    URI Challenge1
    VERSION 1.0
    QML_FILES
    SOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appChallenge1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appChallenge1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appChallenge1 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appChallenge1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
