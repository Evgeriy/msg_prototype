import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: pageId
    width: 600
    height: 400
    signal sigNextPage()

    header: Label {
        text: qsTr("Friends")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 10

        model: friendListModel
        delegate: Item {
            x: 10
            width: parent.width
            height: 20

            Row {
                id: row1
                width: parent.width
                height: parent.height

                Column {
                    id: col1
                    width: (listView.width - col4.width) / 3
                    Text {
                        text: model.phoneNumber
                    }
                }

                Column {
                    id: col2
                    width: (listView.width - col4.width) / 3
                    Text {
                        text: model.firstName
                    }
                }

                Column {
                    id: col3
                    width: (listView.width - col4.width) / 3
                    Text {
                        text: model.secondName
                    }
                }

                Column {
                    id: col4
                    width: 25

                    Text {
                        id: col4Text
                        text: ""
                    }
                }
            }
//            Text {
//                id: textFields
//                text: model.phoneNumber + " " + model.firstName + " " + model.secondName
//            }

            MouseArea {
                anchors.fill: row1
                onClicked: {
                    if (col4Text.text != "") {
                        col4Text.text = "";
                    } else {
                        col4Text.text = "#";
                    }

                }
            }
        }
    }
}
