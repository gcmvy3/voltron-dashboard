/****************************************************************************
** Meta object code from reading C++ file 'LidarThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Threads/LidarThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LidarThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LidarThread_t {
    QByteArrayData data[9];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LidarThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LidarThread_t qt_meta_stringdata_LidarThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LidarThread"
QT_MOC_LITERAL(1, 12, 8), // "finished"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "error"
QT_MOC_LITERAL(4, 28, 9), // "newPacket"
QT_MOC_LITERAL(5, 38, 11), // "LidarPacket"
QT_MOC_LITERAL(6, 50, 6), // "packet"
QT_MOC_LITERAL(7, 57, 5), // "start"
QT_MOC_LITERAL(8, 63, 20) // "readPendingDatagrams"

    },
    "LidarThread\0finished\0\0error\0newPacket\0"
    "LidarPacket\0packet\0start\0readPendingDatagrams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LidarThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       4,    1,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   46,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LidarThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LidarThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->newPacket((*reinterpret_cast< LidarPacket(*)>(_a[1]))); break;
        case 3: _t->start(); break;
        case 4: _t->readPendingDatagrams(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LidarThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LidarThread::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LidarThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LidarThread::error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LidarThread::*)(LidarPacket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LidarThread::newPacket)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LidarThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_LidarThread.data,
    qt_meta_data_LidarThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LidarThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LidarThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LidarThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LidarThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LidarThread::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LidarThread::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LidarThread::newPacket(LidarPacket _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
