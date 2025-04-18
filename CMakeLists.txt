cmake_minimum_required(VERSION 3.16)

project(airQuality VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appairQuality
    main.cpp
)

qt_add_qml_module(appairQuality
    URI airQuality
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES app.h app.cpp
        SOURCES apiclient.h apiclient.cpp
        SOURCES cityhandler.h cityhandler.cpp
        SOURCES database.h database.cpp
        SOURCES city.h city.cpp
        SOURCES station.h station.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appairQuality PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appairQuality
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appairQuality
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appairQuality
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
