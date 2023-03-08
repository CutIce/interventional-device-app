/****************************************************************************
** Meta object code from reading C++ file 'serial_demo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../header/serial/serial_demo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serial_demo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serial_demo_t {
    QByteArrayData data[13];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serial_demo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serial_demo_t qt_meta_stringdata_serial_demo = {
    {
QT_MOC_LITERAL(0, 0, 11), // "serial_demo"
QT_MOC_LITERAL(1, 12, 6), // "rotate"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "data"
QT_MOC_LITERAL(4, 25, 5), // "slide"
QT_MOC_LITERAL(5, 31, 5), // "curve"
QT_MOC_LITERAL(6, 37, 7), // "Drotate"
QT_MOC_LITERAL(7, 45, 6), // "Dslide"
QT_MOC_LITERAL(8, 52, 6), // "Dcurve"
QT_MOC_LITERAL(9, 59, 8), // "demoLoop"
QT_MOC_LITERAL(10, 68, 9), // "printData"
QT_MOC_LITERAL(11, 78, 27), // "on_OpenSerialButton_clicked"
QT_MOC_LITERAL(12, 106, 34) // "on_lineEdit_input0_editingFin..."

    },
    "serial_demo\0rotate\0\0data\0slide\0curve\0"
    "Drotate\0Dslide\0Dcurve\0demoLoop\0printData\0"
    "on_OpenSerialButton_clicked\0"
    "on_lineEdit_input0_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serial_demo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       5,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       7,    1,   76,    2, 0x0a /* Public */,
       8,    1,   79,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void serial_demo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serial_demo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rotate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->slide((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->curve((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->Drotate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->Dslide((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->Dcurve((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->demoLoop(); break;
        case 7: _t->printData(); break;
        case 8: _t->on_OpenSerialButton_clicked(); break;
        case 9: _t->on_lineEdit_input0_editingFinished(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serial_demo::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_serial_demo.data,
    qt_meta_data_serial_demo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serial_demo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serial_demo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serial_demo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int serial_demo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
