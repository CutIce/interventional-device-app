/****************************************************************************
** Meta object code from reading C++ file 'serial_system.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../header/serial/serial_system.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serial_system.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Serial_System_t {
    QByteArrayData data[19];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Serial_System_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Serial_System_t qt_meta_stringdata_Serial_System = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Serial_System"
QT_MOC_LITERAL(1, 14, 13), // "signal_TxCplt"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "int64_t"
QT_MOC_LITERAL(4, 37, 4), // "flag"
QT_MOC_LITERAL(5, 42, 9), // "port_name"
QT_MOC_LITERAL(6, 52, 13), // "signal_RxCplt"
QT_MOC_LITERAL(7, 66, 4), // "data"
QT_MOC_LITERAL(8, 71, 21), // "signal_DataUnpackCplt"
QT_MOC_LITERAL(9, 93, 16), // "Frame_Data_U2C_t"
QT_MOC_LITERAL(10, 110, 16), // "Frame_Data_C2U_t"
QT_MOC_LITERAL(11, 127, 16), // "Frame_Data_U2I_t"
QT_MOC_LITERAL(12, 144, 16), // "Frame_Data_I2U_t"
QT_MOC_LITERAL(13, 161, 16), // "Frame_Data_C2I_t"
QT_MOC_LITERAL(14, 178, 16), // "Frame_Data_I2C_t"
QT_MOC_LITERAL(15, 195, 15), // "startThreadSlot"
QT_MOC_LITERAL(16, 211, 14), // "txCpltCallback"
QT_MOC_LITERAL(17, 226, 14), // "rxCpltCallback"
QT_MOC_LITERAL(18, 241, 22) // "dataUnpackCpltCallback"

    },
    "Serial_System\0signal_TxCplt\0\0int64_t\0"
    "flag\0port_name\0signal_RxCplt\0data\0"
    "signal_DataUnpackCplt\0Frame_Data_U2C_t\0"
    "Frame_Data_C2U_t\0Frame_Data_U2I_t\0"
    "Frame_Data_I2U_t\0Frame_Data_C2I_t\0"
    "Frame_Data_I2C_t\0startThreadSlot\0"
    "txCpltCallback\0rxCpltCallback\0"
    "dataUnpackCpltCallback"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Serial_System[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       6,    2,  104,    2, 0x06 /* Public */,
       8,    2,  109,    2, 0x06 /* Public */,
       8,    2,  114,    2, 0x06 /* Public */,
       8,    2,  119,    2, 0x06 /* Public */,
       8,    2,  124,    2, 0x06 /* Public */,
       8,    2,  129,    2, 0x06 /* Public */,
       8,    2,  134,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,  139,    2, 0x0a /* Public */,
      16,    2,  140,    2, 0x0a /* Public */,
      17,    2,  145,    2, 0x0a /* Public */,
      18,    2,  150,    2, 0x0a /* Public */,
      18,    2,  155,    2, 0x0a /* Public */,
      18,    2,  160,    2, 0x0a /* Public */,
      18,    2,  165,    2, 0x0a /* Public */,
      18,    2,  170,    2, 0x0a /* Public */,
      18,    2,  175,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 13, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,    7,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 13, QMetaType::QString,    7,    5,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,    7,    5,

       0        // eod
};

void Serial_System::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Serial_System *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_TxCplt((*reinterpret_cast< int64_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->signal_RxCplt((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_U2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_C2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_U2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_I2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_C2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->signal_DataUnpackCplt((*reinterpret_cast< const Frame_Data_I2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->startThreadSlot(); break;
        case 9: _t->txCpltCallback((*reinterpret_cast< int64_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->rxCpltCallback((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_U2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_C2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_U2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_I2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_C2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->dataUnpackCpltCallback((*reinterpret_cast< Frame_Data_I2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Serial_System::*)(int64_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_TxCplt)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(QByteArray , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_RxCplt)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_U2C_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_C2U_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_U2I_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_I2U_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_C2I_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Serial_System::*)(const Frame_Data_I2C_t & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Serial_System::signal_DataUnpackCplt)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Serial_System::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Serial_System.data,
    qt_meta_data_Serial_System,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Serial_System::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Serial_System::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Serial_System.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Serial_System::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Serial_System::signal_TxCplt(int64_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Serial_System::signal_RxCplt(QByteArray _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Serial_System::signal_DataUnpackCplt(const Frame_Data_U2C_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Serial_System::signal_DataUnpackCplt(const Frame_Data_C2U_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Serial_System::signal_DataUnpackCplt(const Frame_Data_U2I_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Serial_System::signal_DataUnpackCplt(const Frame_Data_I2U_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Serial_System::signal_DataUnpackCplt(const Frame_Data_C2I_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Serial_System::signal_DataUnpackCplt(const Frame_Data_I2C_t & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
