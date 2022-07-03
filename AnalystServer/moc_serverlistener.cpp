/****************************************************************************
** Meta object code from reading C++ file 'serverlistener.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serverlistener.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverlistener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerListener_t {
    QByteArrayData data[11];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerListener_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerListener_t qt_meta_stringdata_ServerListener = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ServerListener"
QT_MOC_LITERAL(1, 15, 18), // "incomingConnection"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "qintptr"
QT_MOC_LITERAL(4, 43, 16), // "socketDescriptor"
QT_MOC_LITERAL(5, 60, 23), // "startTcpServerListening"
QT_MOC_LITERAL(6, 84, 4), // "port"
QT_MOC_LITERAL(7, 89, 16), // "slotReadyReadTcp"
QT_MOC_LITERAL(8, 106, 23), // "slotFileReadyForAnalyze"
QT_MOC_LITERAL(9, 130, 12), // "sendToClient"
QT_MOC_LITERAL(10, 143, 21) // "timeoutToSendDatabase"

    },
    "ServerListener\0incomingConnection\0\0"
    "qintptr\0socketDescriptor\0"
    "startTcpServerListening\0port\0"
    "slotReadyReadTcp\0slotFileReadyForAnalyze\0"
    "sendToClient\0timeoutToSendDatabase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerListener[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::UShort,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ServerListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerListener *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->incomingConnection((*reinterpret_cast< qintptr(*)>(_a[1]))); break;
        case 1: _t->startTcpServerListening((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->slotReadyReadTcp(); break;
        case 3: _t->slotFileReadyForAnalyze(); break;
        case 4: _t->sendToClient(); break;
        case 5: _t->timeoutToSendDatabase(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerListener::staticMetaObject = { {
    &QTcpServer::staticMetaObject,
    qt_meta_stringdata_ServerListener.data,
    qt_meta_data_ServerListener,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerListener::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerListener.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int ServerListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
