import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
//import com.ics.demo 1.0
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
        //anchors.horizontalCenter: root.horizontalCenter
        //anchors.verticalCenter: root.verticalCenter
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
            //setFilepath(fileDialog.fileUrl.toString())
            root.qmlFilepathChanged(fileDialog.fileUrl.toString());
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


    Server{
            id:cpp_obj
                     // Вы также можете работать как собственные объекты QML
            property int counts: 0

            onFilepathChanged: {
                counts++
                console.log('qml name changed process')
            }
            onCountsChanged: {
                console.log('qml counts changed process')
            }

        }

        Component.onCompleted: {
                     // Способ связывания сигналов и функций обработки сигналов такой же, как и в QML
            root.onQmlFilepathChanged.connect(cpp_obj.slotFilepathChange)
        }


}


