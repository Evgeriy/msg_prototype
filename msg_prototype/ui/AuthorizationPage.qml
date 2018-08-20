import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: pageId
    width: 600
    height: 400
    signal sigNextPage()

    header: Label {
        text: qsTr("Authorization")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    GridLayout {
        id: gridLayoutAuthorizationPage

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        rows: 3
        columns: 2
        columnSpacing: 30
        rowSpacing: 30

        Label {

            id: labelPhoneNumber

            text: qsTr("Phone number:")
            font.pixelSize: Qt.application.font.pixelSize * 2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.row: 1
            Layout.column: 1
        }

        TextEdit {
            id: textEditPhoneNumber

            text: client.getPhoneNumber()
            font.pixelSize: Qt.application.font.pixelSize * 2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.row: 1
            Layout.column: 2
        }

        Label {
            id: labelCode

            text: qsTr("Code:")
            font.pixelSize: Qt.application.font.pixelSize * 2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.row: 2
            Layout.column: 1
        }



        TextEdit {
            id: textEditCode

            text: client.getCode()
            font.pixelSize: Qt.application.font.pixelSize * 2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.row: 2
            Layout.column: 2
        }

        Button {
            id: buttonSignIn

            text: qsTr("Sign In")
            font.pixelSize: Qt.application.font.pixelSize * 2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 1
            Layout.columnSpan: 2
            Layout.row: 3
            Layout.column: 1

            onClicked: {
                client.setPhoneNumber(textEditPhoneNumber.text);
                client.setCode(textEditCode.text);
                client.sendAuthorizationData();
                pageId.sigNextPage()
            }
        }
    }




}
