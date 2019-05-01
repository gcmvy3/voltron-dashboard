/****************************************************************************
** Meta object code from reading C++ file 'CANCodeManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CANCodeManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CANCodeManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CANCodeManager_t {
    QByteArrayData data[11];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CANCodeManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CANCodeManager_t qt_meta_stringdata_CANCodeManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CANCodeManager"
QT_MOC_LITERAL(1, 15, 20), // "newCodesFileSelected"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "filePath"
QT_MOC_LITERAL(4, 46, 14), // "newCodesLoaded"
QT_MOC_LITERAL(5, 61, 17), // "QVector<CANCode*>"
QT_MOC_LITERAL(6, 79, 8), // "newCodes"
QT_MOC_LITERAL(7, 88, 11), // "openCANFile"
QT_MOC_LITERAL(8, 100, 12), // "loadFromFile"
QT_MOC_LITERAL(9, 113, 6), // "QFile*"
QT_MOC_LITERAL(10, 120, 4) // "file"

    },
    "CANCodeManager\0newCodesFileSelected\0"
    "\0filePath\0newCodesLoaded\0QVector<CANCode*>\0"
    "newCodes\0openCANFile\0loadFromFile\0"
    "QFile*\0file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CANCodeManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   40,    2, 0x0a /* Public */,
       8,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void CANCodeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CANCodeManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newCodesFileSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->newCodesLoaded((*reinterpret_cast< QVector<CANCode*>(*)>(_a[1]))); break;
        case 2: _t->openCANFile(); break;
        case 3: _t->loadFromFile((*reinterpret_cast< QFile*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<CANCode*> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFile* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANCodeManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CANCodeManager::newCodesFileSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CANCodeManager::*)(QVector<CANCode*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CANCodeManager::newCodesLoaded)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CANCodeManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CANCodeManager.data,
    qt_meta_data_CANCodeManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CANCodeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANCodeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CANCodeManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CANCodeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CANCodeManager::newCodesFileSelected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CANCodeManager::newCodesLoaded(QVector<CANCode*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
