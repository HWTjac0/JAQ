import QtLocation
import QtPositioning
import Qt5Compat.GraphicalEffects
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    Layout.fillHeight: true
    Layout.fillWidth: true
    radius: 10
    color: "transparent"
    clip: true
    border {
        width: 1
        color: "#aaaaaa"
    }
    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }
    Item {
        anchors.fill: parent
        anchors.margins: 1
        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(59.91, 10.75)
            zoomLevel: 12
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: root.width
                    height: root.height
                    radius: root.radius
                }
            }
            MapItemView {
                id: stationMarkersView
                model: cityHandler.stationMarkers
                delegate: MapQuickItem {
                    coordinate: stationCoordinate
                    sourceItem: Rectangle {
                        id: marker
                        width: 15
                        height: 15
                        radius: 10
                        color: "red"
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor

                            onClicked: {
                                stationHandler.stationSelected(model.stationId)
                            }

                            onPressed: {
                                marker.scale = 0.9;
                            }

                            onReleased: {
                                marker.scale = 1.0;
                            }

                            onEntered: {
                                marker.border.width = 3;
                            }

                            onExited: {
                                marker.border.width = 2;
                            }
                        }
                    }
                }
            }
        }
        Connections {
            target: cityHandler
            function onCityCoordinatesChanged(latitude, longitude) {
                map.center = QtPositioning.coordinate(latitude, longitude)
                stationMarkersView.model = cityHandler.stationMarkers
            }
        }
    }
}