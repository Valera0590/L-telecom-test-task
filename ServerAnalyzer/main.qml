import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import CPP.MyComponents 1.0



Window {
    id: root

    signal qmlFilepathChanged(string str)

    visible: true
    width: 640
    height: 480
    title: qsTr("Server Analyzer")


    Button
    {
        id: btnSelectFile
        width: parent-width
        anchors.centerIn: parent
        text: "Open FileDialog"
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
            root.qmlFilepathChanged(fileDialog.fileUrl.toString());
        }
        onRejected: {
            console.log("Canceled")

        }

    }

    Dialog
    {
        id: someDialog
        title: "Greetings"
        Text{
            text: "Hello there!"
        }
    }


    Server{
            id:cpp_obj

        }

        Component.onCompleted: {
                     //связывание сигналов и функций обработки сигналов интерфейсной части(QML) и кода
            root.onQmlFilepathChanged.connect(cpp_obj.slotFilepathChange)
        }


}


