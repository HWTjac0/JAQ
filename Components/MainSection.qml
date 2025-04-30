import QtQuick
import QtQuick.Layouts

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.leftMargin: 20
    Layout.topMargin: 17
    topLeftRadius: 50
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 5
        Item {
            Layout.fillWidth: true
            Text {
                id: mainCityName
                text: "Miasto: <wybierz z listy>"
                font {
                    pixelSize: 30
                    bold: true
                }
            }
            Text {
                id: mainCityVoivodeship
                anchors.top: mainCityName.bottom
                anchors.margins: 5
                text: "Województwo: <po wybraniu miasta>"
                font {
                    pixelSize: 20
                }
            }
            Text {
                id: mainCityCounty
                anchors.top: mainCityVoivodeship.bottom
                anchors.margins: 5
                text: "Powiat: <po wybraniu miasta>"
                font {
                    pixelSize: 20
                }
            }
            Text {
                id: mainCityCommune
                anchors.top: mainCityCounty.bottom
                anchors.margins: 5
                text: "Gmina: <po wybraniu miasta>"
                font {
                    pixelSize: 20
                }
            }
        }
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width * 0.8
            height: 2
            color: "#dfdfdf"
        }
        Item {
            Text {
                id: mainStationAddress
                text: "Adres stacji: <wybierz stacje z listy>"
                font {
                    pixelSize: 17
                    bold: true
                }
            }
            Text {
                anchors.top: mainStationAddress.bottom
                id: mainStationId
                text: "ID stacji: <po wybraniu stacji>"
                font.pixelSize: 15
            }
            Text {
                anchors.top: mainStationId.bottom
                id: mainStationAQI
                text: "Ogólny stan powietrza: <po wybraniu stacji>"
                font.pixelSize: 15
            }
        }
        Connections {
            target: cityHandler
            function onCityChanged() {
                mainCityName.text           = `Miasto: ${cityHandler.currentCity.name}`
                mainCityVoivodeship.text    = `Województwo: ${cityHandler.currentCity.voivodeship}`
                mainCityCounty.text         = `Powiat: ${cityHandler.currentCity.county}`
                mainCityCommune.text        = `Gmina: ${cityHandler.currentCity.commune}`

                mainStationAddress.text     = "Adres stacji: <wybierz stacje z listy>"
                mainStationId.text     = "ID stacji: <po wybraniu stacji>"
                mainStationAQI.text     = "Ogólny stan powietrza: <po wybraniu stacji>"
            }
        }
        Connections {
            target: stationHandler
            function onStationChanged() {
                mainStationAddress.text = `Adres stacji: ${stationHandler.currentStationAddress}`
                mainStationId.text = `ID stacji: ${stationHandler.currentStationId}`
                mainStationAQI.text = "Ogólny stan powietrza: Ładowanie..."
            }
            function  onStationAQIAcquired(aqiStatus) {
                try {
                    if (!mainStationAQI) {
                        console.error("mainStationAQI is null!")
                        return
                    }
                    mainStationAQI.text = `Ogólny stan powietrza: ${aqiStatus}`
                } catch(e) {
                    console.error("Error updating AQI:", e)
                }
            }
        }
    }
}