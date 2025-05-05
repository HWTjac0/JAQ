cmake_minimum_required(VERSION 3.16)

project(airQuality VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Charts Widgets Location Positioning Test)

qt_standard_project_setup(REQUIRES 6.8)

# --- Main Application ---
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
        Models/StationCoordinateModel.cpp
        Models/StationCoordinateModel.h
        core/PathManager.cpp
        core/PathManager.h
        core/NetworkChecker.cpp
        core/NetworkChecker.h
        core/NetworkWorker.cpp
        core/NetworkWorker.h
)

qt_add_qml_module(appairQuality
        URI airQuality
        VERSION 1.0
        QML_FILES
        Main.qml
        Components/SearchCity.qml
        Components/AppUtils.qml
        Components/TopBar.qml
        Components/AsideBar.qml
        Components/MainSection.qml
        Components/StationSelectList.qml
        Components/SensorSelectList.qml
        Components/CitySelection.qml
        Components/CityInfo.qml
        Components/StationInfo.qml
        Components/SensorInfo.qml
        Components/DividerHorizontal.qml
        Components/SensorDataTable.qml
        Components/SensorDataTableView.qml
        Components/SensorDataChart.qml
        Components/MapView.qml
        Components/DatePicker.qml
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

set_target_properties(appairQuality PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appairQuality
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(appairQuality
        PRIVATE Qt6::Quick Qt6::Charts Qt6::Widgets Qt6::Location Qt6::Positioning Qt6::Gui Qt6::Test
)

include(GNUInstallDirs)
install(TARGETS appairQuality
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# --- Testing Setup ---
if(BUILD_TESTING)
    enable_testing()

    add_executable(jaq_test
            Tests/test.cpp

            core/AppContext.cpp
            Handlers/SensorDataHandler.cpp
            Models/SensorDataModel.cpp
            core/GeoLocator.cpp
            Models/StationCoordinateModel.cpp
            core/PathManager.cpp
            core/NetworkChecker.cpp
            core/NetworkWorker.cpp
            core/apiclient.cpp
            Handlers/cityhandler.cpp
            core/Database/database.cpp
            Entities/city.cpp
            Entities/station.cpp
            Models/cityindexmodel.cpp
            Models/citysortproxymodel.cpp
            Models/stationmodel.cpp
            Handlers/stationhandler.cpp
            Entities/sensor.cpp
            core/Database/databasereader.cpp
            core/Database/databasewriter.cpp
            Models/sensormodel.cpp
            Handlers/sensorhandler.cpp
    )
    target_link_libraries(jaq_test
            PRIVATE Qt6::Quick Qt6::Charts Qt6::Widgets Qt6::Location Qt6::Positioning Qt6::Gui Qt6::Test
    )
    target_include_directories(jaq_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME JaQUnitTests COMMAND jaq_test)

endif()
