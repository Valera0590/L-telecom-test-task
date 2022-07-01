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
    //signal qmlFilepathChanged(string str)
    //signal qmlConnectServer()
    visible: true
    width: 570
    height: 580
    minimumWidth: 570
    minimumHeight: 580

    title: qsTr("Client")
    /*property string button_edit_enable_state: "enabled"

    state: button_edit_enable_state

        states: [
            State {
                name: "enabled"
                PropertyChanges { target: btnConnect; enabled: true }
            },
            State {
                name: "disabled"
                PropertyChanges { target: btnConnect; enabled: false }
            }
        ]*/

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
        onTableValRepUpdate:
        {
            tabModelValRep.updateModelRep(tabl)
        }
        onTableDstLenUpdate:
        {
            tabModelDstLen.updateModelDLen(tabl)
        }
        onConnectSuccess:
        {
            text_connection.text = "<i>Подключено</i>"
        }
        onSentFileToServer:
        {
            text_sent_file.text = "Файл "+strFilename+" был отправлен"
        }
    }

    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: "*.txt"
        selectMultiple: false
        onAccepted:
        {
            console.log("You choose: " + fileDialog.fileUrls)
            client.slotFilepathChange(fileDialog.fileUrl.toString())
        }
        onRejected:
        {
            console.log("Canceled")
        }

    }

    Rectangle
    {
        id:status_connection
        //anchors.left: parent.left
        //anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        width: 150
        height: 40
        anchors.margins: 15
        anchors.rightMargin: 40
//        border.color: "#000"
//        border.width: 3


        Text {
            id: text_connection
            text: "<i>Не подключено</i>"
            anchors.centerIn: parent
            //horizontalAlignment: Text.AlignRight
            //verticalAlignment: Text.AlignVCenter
        }
    }


    Rectangle{
        id:btn1
        anchors.top: parent.top
        anchors.right: status_connection.left
        anchors.left: parent.left
        height: 40
        anchors.margins: 15
        anchors.rightMargin: 10
        anchors.leftMargin: 80
    }

    Button
    {
        id: btnConnect
        implicitWidth: 200
        implicitHeight: 40

        //anchors.right: parent.right
        anchors.fill: btn1

        //Layout.margins: 10
        text: "Подключиться к серверу"
        //enabled: true
        onClicked:
        {
            client.slotConnectToServer()
            //button_edit_enable_state = "disabled"
        }

    }


    Rectangle       //блок с БД
    {
        id: block_database
        anchors.top: btn1.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter
        anchors.margins: 15
        anchors.topMargin: 20
        border.color: "#a5a5a5"
        border.width: 1
    }

    Rectangle
    {
        // Слой с базой данных
        id: db1

        //height: anchors.verticalCenter - rowLayout1.bottom
        anchors.top: block_database.top
        anchors.left: block_database.left
        anchors.right: block_database.right
        anchors.bottom: btn2.top

        anchors.margins: 10
//        anchors.topMargin: 10
        anchors.bottomMargin: 15
    }


    TableView {
        id: tableView1
        //Layout.alignment: parent.fillWidth
        //Layout.fillWidth: true
        //Layout.fillHeight: true
        /*anchors.top: rowLayout2.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom*/
        //anchors.margins: 5
        anchors.fill: db1

        TableViewColumn {
            role: "DT"
            title: "Дата/Время"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 180
        }
        TableViewColumn {
            role: "IP"
            title: "Адрес клиента"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 160
        }
        TableViewColumn {
            role: "Bytes"
            title: "Размер (байты)"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 160
        }

        model: myModel

        // Настройка строки в TableView для перехавата левого клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: {
                    tableView1.selection.clear()
                    tableView1.selection.select(styleData.row)
                    tableView1.currentRow = styleData.row
                    tableView1.focus = true

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

    Rectangle{
        id:btn2
        anchors.left: block_database.left
        anchors.right: block_database.right
        anchors.bottom: block_database.bottom
        height: 40
        anchors.leftMargin: 65
        anchors.rightMargin: 65
        anchors.bottomMargin: 15


    }
    Button
    {
        id: btnMakeRequest
        implicitWidth: 180
        implicitHeight: 40
        anchors.fill: btn2
        //Layout.alignment: Qt.AlignRight
        //Layout.margins: 10
        text: "Получить статистику"
        onClicked:
        {
            database.slotCloseOldDB()
            client.slotMakeRequestToServer()

        }
    }

    Rectangle
    {
        id: block_analyze_file
        anchors.top: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 15
        anchors.topMargin: 10
        border.color: "#a5a5a5"
        border.width: 1
    }

    Rectangle
    {
        id: table1
        anchors.top: block_analyze_file.top
        anchors.left: block_analyze_file.left
        anchors.right: block_analyze_file.horizontalCenter
        //anchors.bottom: block_analyze_file.bottom
        anchors.margins: 10
//        anchors.top: btn2.bottom
//        anchors.left: parent.left
//        anchors.right: parent.horizontalCenter
        anchors.bottom: sent_file.top
//        anchors.margins: 15
//        anchors.topMargin: 10
        anchors.bottomMargin: 15

    }
    Rectangle
    {
        id: table2
        anchors.top: block_analyze_file.top
        anchors.left: block_analyze_file.horizontalCenter
        anchors.right: block_analyze_file.right
//        anchors.bottom: block_analyze_file.bottom
        anchors.margins: 10
//        anchors.top: btn2.bottom
//        anchors.left: parent.horizontalCenter
//        anchors.right: parent.right
        anchors.bottom: btn3.top
//        anchors.margins: 15
//        anchors.topMargin: 10
        anchors.bottomMargin: 15
    }

    TableView {
        id: tableView2
        //Layout.alignment: Qt.AlignLeft
        //Layout.top: parent.top
        //Layout.left: parent.left
        //Layout.bottom: parent.bottom
        implicitWidth: 225
        implicitHeight: 100
        anchors.fill: table1

        TableViewColumn {
            role: "Key"
            title: "Символ"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 90
        }
        TableViewColumn {
            role: "Value"
            title: "Кол-во повторений"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 140
        }

        model: tabModelValRep

        // Настройка строки в TableView для перехавата левого клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            /*Text {
            id: tabledata

            font.pointSize: 12
            anchors.centerIn: parent
        }*/
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: {
                    tableView2.selection.clear()
                    tableView2.selection.select(styleData.row)
                    tableView2.currentRow = styleData.row
                    tableView2.focus = true

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
    TableView {
        id: tableView3
        //Layout.alignment: Qt.AlignLeft
        //Layout.top: parent.top
        //Layout.left: parent.left
        //Layout.bottom: parent.bottom
        //    implicitWidth: 225
        //    implicitHeight: 100
        anchors.fill: table2

        TableViewColumn {
            role: "Key"
            title: "Длина слова"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 110
        }
        TableViewColumn {
            role: "Value"
            title: "Кол-во слов"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            width: 110
        }

        model: tabModelDstLen

        // Настройка строки в TableView для перехавата левого клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: {
                    tableView3.selection.clear()
                    tableView3.selection.select(styleData.row)
                    tableView3.currentRow = styleData.row
                    tableView3.focus = true

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



    Rectangle
    {
        id: btn3
        height: 40
        anchors.bottom: block_analyze_file.bottom
        anchors.left: sent_file.right
        anchors.right: block_analyze_file.right
        anchors.leftMargin: 15
        anchors.rightMargin: 65
        anchors.bottomMargin: 15
    }

    Button
    {
        id: btnSelectFile
        implicitWidth: 180
        implicitHeight: 40
        //anchors.left: tableView2.right
        //anchors.margins: 10
        //Layout.alignment: Qt.AlignVCenter
        anchors.fill: btn3
        text: "Отправить файл"
        onClicked: fileDialog.open()
    }

    Rectangle
    {
        id:sent_file
        height: 40
        implicitWidth: root.width/3.5
        anchors.left: block_analyze_file.left
        anchors.bottom: block_analyze_file.bottom
        //anchors.leftMargin: 150
        anchors.leftMargin: 30
        anchors.bottomMargin: 15


        Text {
            id: text_sent_file
            clip: true
            anchors.fill: parent
            //anchors.centerIn: sent_file
            text: "<i>Файл не выбран</i>"
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
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



}
