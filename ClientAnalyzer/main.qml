/*import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.1*/
import QtQuick 2.5
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import CPP.MyComponents 2.0

Window {
    id:root
    signal qmlFilepathChanged(string str)
    signal qmlConnectServer()
    visible: true
    width: 640
    height: 480
    title: qsTr("Client")

    /* С помощью объекта Connections
         * Устанавливаем соединение с классом ядра приложения
         * */
    Connections {
        target: client // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        onDatabaseUpdate:
        {
            database.slotOpenNewDB()
            myModel.updateModel()
        }
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
            client.slotFilepathChange(fileDialog.fileUrl.toString())
            //root.qmlFilepathChanged(fileDialog.fileUrl.toString())


        }
        onRejected: {
            console.log("Canceled")

        }

    }

    // Слой с TaxtField`ами и Button для занесения записей в базу данных
        RowLayout {
            id: rowLayout
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            spacing: 10
            Button
            {
                id: btnConnect
                width: parent-width
                //anchors.horizontalCenter: parent.width
                text: "Подключиться к серверу"
                onClicked:
                {
                    //visible: false
                    //root.qmlConnectServer()
                    client.slotConnectToServer()
                }
            }

            Button
            {
                id: btnSelectFile
                width: parent-width
                Layout.alignment: parent-right
                text: "Отправить файл"
                onClicked: fileDialog.open()
            }

            Button
            {
                id: btnMakeRequest
                width: parent-width
                Layout.alignment: parent-right
                text: "Получить статистику"
                onClicked:
                {
                    database.slotCloseOldDB()
                    client.slotMakeRequestToServer()

                }
            }

            /*Text {text: qsTr("Имя")}
            TextField {id: fnameField}
            Text {text: qsTr("Фамилия")}
            TextField { id: snameField}
            Text {text: qsTr("НИК")}
            TextField {id: nikField}*/

        }

        TableView {
            id: tableView
            anchors.top: rowLayout.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 5

            TableViewColumn {
                role: "DT"
                title: "Дата/Время"
            }
            TableViewColumn {
                role: "IP"
                title: "Адрес"
            }
            TableViewColumn {
                role: "Bytes"
                title: "Размер (байты)"
            }

            model: myModel /*cpp_obj.slotGetModelTable()*/

            // Настройка строки в TableView для перехавата левого клика мыши
            rowDelegate: Rectangle {
                anchors.fill: parent
                color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        tableView.selection.clear()
                        tableView.selection.select(styleData.row)
                        tableView.currentRow = styleData.row
                        tableView.focus = true

                        switch(mouse.button) {
                        case Qt.RightButton:
                            someDialog.open() // Вызываем контексткное меню
                            break
                        default:
                            break
                        }
                    }
                }
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


    Client{
            id:cpp_obj

        }

        Component.onCompleted: {
                     //связывание сигналов и функций обработки сигналов интерфейсной части(QML) и кода
            root.onQmlFilepathChanged.connect(cpp_obj.slotFilepathChange)
            root.onQmlConnectServer.connect(cpp_obj.slotConnectToServer)
        }
}
