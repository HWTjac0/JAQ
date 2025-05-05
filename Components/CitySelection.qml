import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    anchors.fill: parent
    anchors.margins: 2
    spacing: 3
    Text {
        Layout.leftMargin: 15
        text: "Wybór miasta"
        font.bold: true
        font.pixelSize: 12
        color: "#636b72"
    }
    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "#fcfcfc"
        radius: 15
        border.width: 2
        border.color: "#dddddd"
        GridLayout {
            anchors.fill: parent
            anchors.margins: 7
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            columns: 3
            rows: 2
            rowSpacing: 2
            columnSpacing: 2
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label {
                    id: voivodeshipLabel
                    text: "Województwo"
                }
                ComboBox {
                    anchors.top: voivodeshipLabel.bottom
                    anchors.margins: 3
                    model: cityHandler.voivodeshipModel
                    onActivated: cityHandler.getCities().filterVoivodeship = currentText
                    Component.onCompleted: {
                        cityHandler.getCities().filterVoivodeship = currentText
                    }
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    id: cityLabel
                    text: "Miasto"
                }
                ComboBox {
                    id: cityCombo
                    anchors.top: cityLabel.bottom
                    anchors.margins: 3
                    model: cityHandler.getCities()
                    textRole: "cityName"
                    Connections {
                        target: cityHandler.getCities()
                        function onFilterVoivodeshipChanged() {
                            cityCombo.currentIndex = 0
                        }
                    }

                }
            }
            Item {
                Layout.rowSpan: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                ColumnLayout {
                    anchors.fill: parent
                    Label {
                        text: "Wybierz najbliższą stacje na podstawie twojej lokalizacji"
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                    Row {
                        spacing: 5
                        Label {
                            text: "Status:"
                        }
                        Text {
                            id: userLocationSearchStatus
                            text: "<po wyszukaniu>"
                            font {
                                bold: true
                            }
                        }
                    }
                    Button {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Znajdź"
                        onClicked: {
                            userLocationSearchStatus.text = "Szukanie..."
                            cityHandler.getUserLocation()
                        }
                    }
                }
                Connections {
                    target: cityHandler
                    function onUserLocationChanged(latitude, longitude) {
                        userLocationSearchStatus.text = `Znaleziono`
                        userLocationSearchStatus.color = "green"
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label {
                    id: citySearchLabel
                    text: "Wyszukaj miasto"
                }
                TextField {
                    anchors.top: citySearchLabel.bottom
                    anchors.margins: 3
                    padding: 7
                    placeholderText: "Wyszukaj dla województwa"
                    background: Rectangle {
                        implicitWidth: 200
                        color: "#fafafa"
                        radius: 5
                        border {
                            width: 1
                            color: "#cccccc"
                        }
                    }
                    onTextChanged: cityHandler.getCities().filterString = text
                    Connections {
                        target: cityHandler.getCities()
                        function onFilterStringChanged() {
                            cityCombo.currentIndex = 0
                        }
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Button {
                    anchors.fill: parent
                    text: "Sprawdź"
                    onClicked: cityHandler.citySelected(cityCombo.currentIndex)
                }
            }
        }
    }
}