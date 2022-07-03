/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[27];
    char stringdata0[428];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 14), // "databaseUpdate"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 27), // "tableModelValueRepeatUpdate"
QT_MOC_LITERAL(4, 51, 5), // "table"
QT_MOC_LITERAL(5, 57, 29), // "tableModelWordsByLengthUpdate"
QT_MOC_LITERAL(6, 87, 14), // "connectSuccess"
QT_MOC_LITERAL(7, 102, 16), // "sentFileToServer"
QT_MOC_LITERAL(8, 119, 11), // "strFilename"
QT_MOC_LITERAL(9, 131, 12), // "disconnected"
QT_MOC_LITERAL(10, 144, 11), // "errorSocket"
QT_MOC_LITERAL(11, 156, 14), // "strErrorSocket"
QT_MOC_LITERAL(12, 171, 17), // "gotInfoFromServer"
QT_MOC_LITERAL(13, 189, 7), // "strInfo"
QT_MOC_LITERAL(14, 197, 19), // "slotConnectToServer"
QT_MOC_LITERAL(15, 217, 18), // "slotReadingUDPData"
QT_MOC_LITERAL(16, 236, 18), // "slotReadingTcpData"
QT_MOC_LITERAL(17, 255, 12), // "slotSockDisc"
QT_MOC_LITERAL(18, 268, 18), // "slotFilepathChange"
QT_MOC_LITERAL(19, 287, 3), // "str"
QT_MOC_LITERAL(20, 291, 23), // "slotMakeRequestToServer"
QT_MOC_LITERAL(21, 315, 12), // "displayError"
QT_MOC_LITERAL(22, 328, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(23, 357, 11), // "socketError"
QT_MOC_LITERAL(24, 369, 12), // "sendFullFile"
QT_MOC_LITERAL(25, 382, 21), // "slotTimeoutToSendFile"
QT_MOC_LITERAL(26, 404, 23) // "slotTimeoutToConnectUDP"

    },
    "Client\0databaseUpdate\0\0"
    "tableModelValueRepeatUpdate\0table\0"
    "tableModelWordsByLengthUpdate\0"
    "connectSuccess\0sentFileToServer\0"
    "strFilename\0disconnected\0errorSocket\0"
    "strErrorSocket\0gotInfoFromServer\0"
    "strInfo\0slotConnectToServer\0"
    "slotReadingUDPData\0slotReadingTcpData\0"
    "slotSockDisc\0slotFilepathChange\0str\0"
    "slotMakeRequestToServer\0displayError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "sendFullFile\0slotTimeoutToSendFile\0"
    "slotTimeoutToConnectUDP"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    1,  105,    2, 0x06 /* Public */,
       5,    1,  108,    2, 0x06 /* Public */,
       6,    0,  111,    2, 0x06 /* Public */,
       7,    1,  112,    2, 0x06 /* Public */,
       9,    0,  115,    2, 0x06 /* Public */,
      10,    1,  116,    2, 0x06 /* Public */,
      12,    1,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  122,    2, 0x0a /* Public */,
      15,    0,  123,    2, 0x0a /* Public */,
      16,    0,  124,    2, 0x0a /* Public */,
      17,    0,  125,    2, 0x0a /* Public */,
      18,    1,  126,    2, 0x0a /* Public */,
      20,    0,  129,    2, 0x0a /* Public */,
      21,    1,  130,    2, 0x08 /* Private */,
      24,    0,  133,    2, 0x08 /* Private */,
      25,    0,  134,    2, 0x08 /* Private */,
      26,    0,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->databaseUpdate(); break;
        case 1: _t->tableModelValueRepeatUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->tableModelWordsByLengthUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->connectSuccess(); break;
        case 4: _t->sentFileToServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->disconnected(); break;
        case 6: _t->errorSocket((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->gotInfoFromServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->slotConnectToServer(); break;
        case 9: _t->slotReadingUDPData(); break;
        case 10: _t->slotReadingTcpData(); break;
        case 11: _t->slotSockDisc(); break;
        case 12: _t->slotFilepathChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->slotMakeRequestToServer(); break;
        case 14: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 15: _t->sendFullFile(); break;
        case 16: _t->slotTimeoutToSendFile(); break;
        case 17: _t->slotTimeoutToConnectUDP(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::databaseUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Client::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::tableModelValueRepeatUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Client::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::tableModelWordsByLengthUpdate)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::connectSuccess)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::sentFileToServer)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::disconnected)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::errorSocket)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::gotInfoFromServer)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Client::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Client.data,
    qt_meta_data_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Client::databaseUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::tableModelValueRepeatUpdate(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::tableModelWordsByLengthUpdate(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::connectSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Client::sentFileToServer(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Client::errorSocket(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Client::gotInfoFromServer(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
