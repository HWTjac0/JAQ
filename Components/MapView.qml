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
            center: QtPositioning.coordinate(59.91, 10.75) // Oslo
            zoomLevel: 14
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: root.width
                    height: root.height
                    radius: root.radius
                }
            }
        }
        Connections {
            target: cityHandler
            function onCityCoordinatesChanged(latitude, longitude) {
                console.log(latitude, longitude)
                map.center = QtPositioning.coordinate(latitude, longitude)
            }
        }
    }
}