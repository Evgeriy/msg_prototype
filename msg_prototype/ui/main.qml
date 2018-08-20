import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    Connections {
        target: tabAuthorization
        onSigNextPage: {
            swipeView.setCurrentIndex(1);
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        AuthorizationPage {
            id: tabAuthorization
        }

        FriendsPage {
            id: tabFriends
        }

        MessagesPage {
            id: tabMessages
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Authorization")
//            onClicked: {
//                tabBar.setCurrentIndex(2)
//            }
        }

        TabButton {
            text: qsTr("Friends")
        }

        TabButton {
            text: qsTr("Messages")
        }
    }
}
