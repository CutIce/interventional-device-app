/****************************************************************************
** Meta object code from reading C++ file 'protocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../header/serial/protocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Protocol_t {
    QByteArrayData data[19];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Protocol_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Protocol_t qt_meta_stringdata_Protocol = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Protocol"
QT_MOC_LITERAL(1, 9, 19), // "signal_DataPackCplt"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "port_name"
QT_MOC_LITERAL(4, 40, 7), // "tx_pack"
QT_MOC_LITERAL(5, 48, 21), // "signal_DataUnpackCplt"
QT_MOC_LITERAL(6, 70, 16), // "Frame_Data_U2C_t"
QT_MOC_LITERAL(7, 87, 4), // "data"
QT_MOC_LITERAL(8, 92, 16), // "Frame_Data_C2U_t"
QT_MOC_LITERAL(9, 109, 16), // "Frame_Data_U2I_t"
QT_MOC_LITERAL(10, 126, 16), // "Frame_Data_I2U_t"
QT_MOC_LITERAL(11, 143, 16), // "Frame_Data_C2I_t"
QT_MOC_LITERAL(12, 160, 16), // "Frame_Data_I2C_t"
QT_MOC_LITERAL(13, 177, 21), // "signal_DataUnpackFail"
QT_MOC_LITERAL(14, 199, 13), // "Unpack_Step_e"
QT_MOC_LITERAL(15, 213, 9), // "fail_step"
QT_MOC_LITERAL(16, 223, 14), // "dataAppend2Buf"
QT_MOC_LITERAL(17, 238, 10), // "dataUnpack"
QT_MOC_LITERAL(18, 249, 22) // "dataUnpackFailCallback"

    },
    "Protocol\0signal_DataPackCplt\0\0port_name\0"
    "tx_pack\0signal_DataUnpackCplt\0"
    "Frame_Data_U2C_t\0data\0Frame_Data_C2U_t\0"
    "Frame_Data_U2I_t\0Frame_Data_I2U_t\0"
    "Frame_Data_C2I_t\0Frame_Data_I2C_t\0"
    "signal_DataUnpackFail\0Unpack_Step_e\0"
    "fail_step\0dataAppend2Buf\0dataUnpack\0"
    "dataUnpackFailCallback"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Protocol[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    2,   74,    2, 0x06 /* Public */,
       5,    2,   79,    2, 0x06 /* Public */,
       5,    2,   84,    2, 0x06 /* Public */,
       5,    2,   89,    2, 0x06 /* Public */,
       5,    2,   94,    2, 0x06 /* Public */,
       5,    2,   99,    2, 0x06 /* Public */,
      13,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    2,  107,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    1,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    7,    3,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    7,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void Protocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Protocol *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_DataPackCplt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_U2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_C2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_U2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_I2U_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_C2I_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->signal_DataUnpackCplt((*reinterpret_cast< Frame_Data_I2C_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->signal_DataUnpackFail((*reinterpret_cast< Unpack_Step_e(*)>(_a[1]))); break;
        case 8: _t->dataAppend2Buf((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->dataUnpack(); break;
        case 10: _t->dataUnpackFailCallback((*reinterpret_cast< Unpack_Step_e(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Protocol::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataPackCplt)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_U2C_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_C2U_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_U2I_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_I2U_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_C2I_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Frame_Data_I2C_t , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackCplt)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Protocol::*)(Unpack_Step_e );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Protocol::signal_DataUnpackFail)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Protocol::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Protocol.data,
    qt_meta_data_Protocol,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Protocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Protocol::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Protocol.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Protocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Protocol::signal_DataPackCplt(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Protocol::signal_DataUnpackCplt(Frame_Data_U2C_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Protocol::signal_DataUnpackCplt(Frame_Data_C2U_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Protocol::signal_DataUnpackCplt(Frame_Data_U2I_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Protocol::signal_DataUnpackCplt(Frame_Data_I2U_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Protocol::signal_DataUnpackCplt(Frame_Data_C2I_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Protocol::signal_DataUnpackCplt(Frame_Data_I2C_t _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Protocol::signal_DataUnpackFail(Unpack_Step_e _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
