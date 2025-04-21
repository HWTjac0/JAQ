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
        SOURCES core/apiclient.h core/apiclient.cpp
        SOURCES City/cityhandler.h City/cityhandler.cpp
        SOURCES core/database.h core/database.cpp
        SOURCES City/city.h City/city.cpp
        SOURCES Station/station.h Station/station.cpp
        SOURCES City/cityindexmodel.h City/cityindexmodel.cpp
        QML_FILES Components/SearchCity.qml
        SOURCES City/citysortproxymodel.h City/citysortproxymodel.cpp
        SOURCES Station/stationmodel.h Station/stationmodel.cpp
        SOURCES Station/stationhandler.h Station/stationhandler.cpp
        SOURCES Sensor/sensor.h Sensor/sensor.cpp
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
add_subdirectory(Tests)
