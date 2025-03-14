import QtQuick

import Challenge 1.0

Rectangle {
    id: dataRect
    width: 160
    height: 80
    radius: 5
    color: dataColor
    y: dataY
    x: dataX

    property var rectData: ({})
    property DataSource dataSource: rectData.dataSource

    property real parentWidth: 800
    property string dataId: rectData.id ? rectData.id : 0
    property real dataX: rectData.x ? Math.min(rectData.x, parentWidth - dataRect.width) : 0
    property real dataY: rectData.y ? rectData.y : 0
    property string dataColor: rectData["color-hex"] ? rectData["color-hex"] : "#ffffff"

    property bool shouldBeUpdate: dataRect.x + dataRect.width < parentWidth / 2
    onShouldBeUpdateChanged: {
        if (dataSource) {
            dataSource.active = dataRect.shouldBeUpdate
        }
    }

    // Animation to move left and right endlessly
    property int speed: 100 // Adjust this to control speed (200 px/sec)

    Text {
        id: txtValue
        anchors.centerIn: parent
        font.pointSize: 12
        color: "#ffffff"
        text: dataSource && dataSource.active ?
                  qsTr("%1: %2").arg(dataId).arg(dataSource.val) :
                  qsTr("XXXXX")
    }

    SequentialAnimation on x {
        loops: Animation.Infinite
        running: (parentWidth - dataRect.width) - dataX > 0 &&
                parentWidth - dataRect.width > 0 &&
                dataX > 0

        // Move right to right edge
        PropertyAnimation {
            to: parentWidth - dataRect.width
            duration: ((parentWidth - dataRect.width) - dataX) / dataRect.speed * 1000
            easing.type: Easing.Linear
        }

        // Move left past dataX (mirrored distance)
        PropertyAnimation {
            to: 0
            duration: (parentWidth - dataRect.width) / dataRect.speed * 1000
            easing.type: Easing.Linear
        }

        // Return to dataX
        PropertyAnimation {
            to: dataX
            duration: dataX / dataRect.speed * 1000
            easing.type: Easing.Linear
        }
    }
}


