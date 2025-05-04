import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    property date currentDate: new Date()
    property date maxDate: new Date()
    property date minDate: new Date(2010, 0, 1)
    property alias day: dayCombo.currentIndex
    property alias month: monthCombo.currentIndex
    property alias year: yearCombo.currentIndex

    function getSelectedDate() {
        return new Date(
            yearCombo.currentValue,
            monthCombo.currentIndex,
            dayCombo.currentValue
        )
    }

    function updateCurrentDate() {
        var newDate = getSelectedDate()
        if (newDate.getTime() !== root.currentDate.getTime()) {
            root.currentDate = newDate
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 5

        ComboBox {
            id: dayCombo
            Layout.fillWidth: true
            textRole: "display"
            valueRole: "value"

            onActivated: updateCurrentDate()
            Component.onCompleted: updateDays()
        }

        ComboBox {
            id: monthCombo
            Layout.fillWidth: true
            model: [
                { display: "Styczeń", value: 1 },
                { display: "Luty", value: 2 },
                { display: "Marzec", value: 3 },
                { display: "Kwiecień", value: 4 },
                { display: "Maj", value: 5 },
                { display: "Czerwiec", value: 6 },
                { display: "Lipiec", value: 7 },
                { display: "Sierpień", value: 8 },
                { display: "Wrzesień", value: 9 },
                { display: "Październik", value: 10 },
                { display: "Listopad", value: 11 },
                { display: "Grudzień", value: 12 }
            ]
            textRole: "display"
            valueRole: "value"
            currentIndex: root.currentDate.getMonth()

            onActivated: {
                updateDays()
                updateCurrentDate()
            }
        }

        // Year combobox
        ComboBox {
            id: yearCombo
            Layout.fillWidth: true
            model: {
                var years = []
                var currentYear = root.maxDate.getFullYear()
                for (var y = root.minDate.getFullYear(); y <= currentYear; y++) {
                    years.push(y)
                }
                return years
            }
            currentIndex: model.indexOf(root.currentDate.getFullYear())

            onActivated: {
                updateDays()
                updateCurrentDate()
            }
        }
    }

    // Updates the days combobox based on selected month and year
    function updateDays() {
        var daysInMonth = new Date(
            yearCombo.currentValue,
            monthCombo.currentIndex + 1,
            0
        ).getDate()

        var days = []
        for (var d = 1; d <= daysInMonth; d++) {
            days.push({ display: d, value: d })
        }

        dayCombo.model = days
        dayCombo.currentIndex = Math.min(
            root.currentDate.getDate() - 1,
            daysInMonth - 1
        )
    }

    // Update comboboxes when currentDate property changes externally
    onCurrentDateChanged: {
        if (monthCombo.currentIndex !== currentDate.getMonth()) {
            monthCombo.currentIndex = currentDate.getMonth()
            updateDays()
        }
        if (yearCombo.currentValue !== currentDate.getFullYear()) {
            yearCombo.currentIndex = yearCombo.model.indexOf(currentDate.getFullYear())
            updateDays()
        }
        dayCombo.currentIndex = currentDate.getDate() - 1
    }
}