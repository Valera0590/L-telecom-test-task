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


    /* С помощью объекта Connections
         * Устанавливаем соединение с классом ядра приложения
         * */
    Connections {
        target: client // Указываем целевое соединение
        onDatabaseUpdate:   //при обновлении БД
        {
            database.slotOpenNewDB()
            myModel.updateModel()
        }
        onTableModelValueRepeatUpdate:  //при обновлении данных в таблице 1
        {
            tabModelValRep.updateModelValueRepeat(table)
        }
        onTableModelWordsByLengthUpdate:    //при обновлении данных в таблице 2
        {
            tabModelDstLen.updateModelWordsByLength(table)
        }
        onConnectSuccess:           //при успешном подключении
        {
            text_connection.text = "<i>Подключено</i>"
            btnMakeRequest.enabled = true
            btnSelectFile.enabled = true
        }
        onSentFileToServer:         //при успешной отправке клиентом файла на сервер
        {
            text_sent_file.text = "<i>Файл "+strFilename+" был отправлен</i>"
        }
        onGotInfoFromServer:        //после получения новой информации от сервера и освобождении сокета
        {
            btnMakeRequest.enabled = true
            btnSelectFile.enabled = true
            someDialog.title = "Информация"
            text_someDialog.text = strInfo
            someDialog.open()
        }
        onErrorSocket:              //при ошибке подключения к серверу
        {
            someDialog.title = "Ошибка"
            text_someDialog.text = strErrorSocket
            someDialog.open()
            btnConnect.enabled = true
        }
    }

    function disableButton1 ()
    {
        //btn1.enabled = false;
        btnConnect.enabled = false
    }

    Rectangle
    {
        id:status_connection
        anchors.right: parent.right
        anchors.top: parent.top
        width: 150
        height: 40
        anchors.margins: 15
        anchors.rightMargin: 40


        Text {
            id: text_connection
            text: "<i>Не подключено</i>"
            anchors.centerIn: parent
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
        anchors.fill: btn1
        text: "Подключиться к серверу"
        onClicked:
        {
            client.slotConnectToServer()
            //button_edit_enable_state = "disabled"
            btnConnect.enabled = false
            //btn1.enabled = false
            //disableButton1()
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
        id: db1
        anchors.top: block_database.top
        anchors.left: block_database.left
        anchors.right: block_database.right
        anchors.bottom: btn2.top

        anchors.margins: 10
        anchors.bottomMargin: 15
    }


    TableView {
        id: tableView1
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

        // Настройка строки в TableView для перехавата клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked:
                {
                    tableView1.selection.clear()
                    tableView1.selection.select(styleData.row)
                    tableView1.currentRow = styleData.row
                    tableView1.focus = true

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
        enabled: false
        text: "Получить статистику"
        onClicked:
        {
            database.slotCloseOldDB()
            client.slotMakeRequestToServer()
            btnMakeRequest.enabled = false
            btnSelectFile.enabled = false
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
        anchors.margins: 10
        anchors.bottom: sent_file.top
        anchors.bottomMargin: 15

    }
    Rectangle
    {
        id: table2
        anchors.top: block_analyze_file.top
        anchors.left: block_analyze_file.horizontalCenter
        anchors.right: block_analyze_file.right
        anchors.margins: 10
        anchors.bottom: btn3.top
        anchors.bottomMargin: 15
    }

    TableView {
        id: tableView2
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

        // Настройка строки в TableView для перехавата клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked:
                {
                    tableView2.selection.clear()
                    tableView2.selection.select(styleData.row)
                    tableView2.currentRow = styleData.row
                    tableView2.focus = true
                }
            }
        }
    }
    TableView {
        id: tableView3
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

        // Настройка строки в TableView для перехавата клика мыши
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked:
                {
                    tableView3.selection.clear()
                    tableView3.selection.select(styleData.row)
                    tableView3.currentRow = styleData.row
                    tableView3.focus = true
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
        anchors.fill: btn3
        enabled: false
        text: "Отправить файл"
        onClicked:
        {
            fileDialog.open()
            btnMakeRequest.enabled = false
            btnSelectFile.enabled = false
        }
    }

    Rectangle
    {
        id:sent_file
        height: 40
        implicitWidth: root.width/3.5
        anchors.left: block_analyze_file.left
        anchors.bottom: block_analyze_file.bottom
        anchors.leftMargin: 30
        anchors.bottomMargin: 15


        Text {
            id: text_sent_file
            clip: true
            anchors.fill: parent
            text: "<i>Файл не выбран</i>"
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
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
            btnMakeRequest.enabled = true
            btnSelectFile.enabled = true
        }

    }



    Dialog
    {
        id: someDialog
        title: "Greetings"
        Text{
            id: text_someDialog
            text: "Hello there!"
        }
    }



}
