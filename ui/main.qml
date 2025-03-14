import QtQuick

Window {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("Dynamic QObject and QML Component Creation")
    color: "#343434"

    property var mDataList: Backend ? Backend.dataList : []

    Item {
        id: recContent
        anchors.fill: parent

        Instantiator {
            model: mDataList

            delegate: DataRect {
                rectData: modelData
                parent: recContent
                parentWidth: recContent.width > 0 ? recContent.width : 800
            }
        }

        Rectangle {
            color: "#ff0000"
            opacity: 0.2
            anchors {
                top: parent.top; bottom: parent.bottom
                left: parent.horizontalCenter; right: parent.right
            }
            z: 1
        }
    }
}
