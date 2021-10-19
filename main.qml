import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("AOB Test Project")

    Component {
        id: jsonDelegate

        Item {
            id: item
            required property string name
            required property string icon
            required property int index

            width: gridView.cellWidth;
            height: gridView.cellHeight

            Rectangle {
                id: flat
                anchors.fill: parent
                color: "transparent"
                border.color: "gray"
                border.width: 1

                Column {
                    id: item1
                    spacing: 20
                    topPadding: 10
                    anchors.fill: parent

                    Image {
                        width: 40
                        height: 40
                        fillMode: Image.PreserveAspectFit
                        sourceSize.width: 40
                        sourceSize.height: 40
                        source: icon
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: item.name
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent

                    onClicked: {
                        gridView.currentIndex = item.index
                        jsonModel.open(item.index);
                    }
                }
            }
        }
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        Button {
            id: upBtn
            text: qsTr("Level up")
            width: 100
            height: 30
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 20
            anchors.leftMargin: 20
            flat: false
            enabled: !jsonModel.isRoot
            onClicked: jsonModel.levelUp()

        }

        GridView {
            id: gridView
            anchors.fill: parent
            anchors.topMargin: 70
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            cellWidth: 100;
            cellHeight: 100
            highlight: Rectangle { color: "lightblue" }
            focus: true

            model: jsonModel
            delegate: jsonDelegate
        }
    }
}
