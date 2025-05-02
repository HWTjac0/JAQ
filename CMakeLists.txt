cmake_minimum_required(VERSION 3.16)

project(airQuality VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Charts Widgets Location Positioning)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appairQuality
    main.cpp
        core/AppContext.cpp
        core/AppContext.h
        Handlers/SensorDataHandler.cpp
        Handlers/SensorDataHandler.h
        Models/SensorDataModel.cpp
        Models/SensorDataModel.h
        core/GeoLocator.cpp
        core/GeoLocator.h
)

qt_add_qml_module(appairQuality
    URI airQuality
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES Components/SearchCity.qml
        QML_FILES Components/TopBar.qml
        QML_FILES Components/AsideBar.qml
        QML_FILES Components/MainSection.qml
        QML_FILES Components/StationSelectList.qml
        QML_FILES Components/SensorSelectList.qml
        QML_FILES Components/CitySelection.qml
        QML_FILES Components/CityInfo.qml
        QML_FILES Components/StationInfo.qml
        QML_FILES Components/SensorInfo.qml
        QML_FILES Components/DividerHorizontal.qml
        QML_FILES Components/SensorDataTable.qml
        QML_FILES Components/SensorDataTableView.qml
        QML_FILES Components/SensorDataChart.qml
        QML_FILES Components/MapView.qml
        SOURCES app.h app.cpp
        SOURCES core/apiclient.h core/apiclient.cpp
        SOURCES Handlers/cityhandler.h Handlers/cityhandler.cpp
        SOURCES core/Database/database.h core/Database/database.cpp
        SOURCES Entities/city.h Entities/city.cpp
        SOURCES Entities/station.h Entities/station.cpp
        SOURCES Models/cityindexmodel.h Models/cityindexmodel.cpp
        SOURCES Models/citysortproxymodel.h Models/citysortproxymodel.cpp
        SOURCES Models/stationmodel.h Models/stationmodel.cpp
        SOURCES Handlers/stationhandler.h Handlers/stationhandler.cpp
        SOURCES Entities/sensor.h Entities/sensor.cpp
        SOURCES core/Database/databasereader.h core/Database/databasereader.cpp
        SOURCES core/Database/databasewriter.h core/Database/databasewriter.cpp
        SOURCES Models/sensormodel.h Models/sensormodel.cpp
        SOURCES Handlers/sensorhandler.h Handlers/sensorhandler.cpp
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
    PRIVATE Qt6::Quick Qt6::Charts Qt6::Widgets Qt6::Location Qt6::Positioning
)

include(GNUInstallDirs)
install(TARGETS appairQuality
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_subdirectory(Tests)
