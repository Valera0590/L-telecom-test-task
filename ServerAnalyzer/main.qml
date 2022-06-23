import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3



Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Server Analyzer")

    Button
    {
        width: parent-width

        text: "Open FileDialog"
        //onClicked: someDialog.open()
        onClicked: fileDialog.open()
    }

    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: "*.txt"
        selectMultiple: false
        onAccepted: {
            console.log("You choose: " + fileDialog.fileUrls)
            //Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
        //Component.onCompleted: visible = true
    }

    Dialog
    {
        id: someDialog
        title: "Greetings"
        Text{
            text: "Hello there!"
        }
    }
}


