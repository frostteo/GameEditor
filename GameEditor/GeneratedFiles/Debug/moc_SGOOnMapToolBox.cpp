/****************************************************************************
** Meta object code from reading C++ file 'SGOOnMapToolBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SGOOnMapToolBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SGOOnMapToolBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGOOnMapToolBox_t {
    QByteArrayData data[7];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOOnMapToolBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOOnMapToolBox_t qt_meta_stringdata_SGOOnMapToolBox = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SGOOnMapToolBox"
QT_MOC_LITERAL(1, 16, 13), // "FilterChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 35), // "on_SGONameFilterTxt_editingFi..."
QT_MOC_LITERAL(4, 67, 40), // "on_instanceNameFilterTxt_edit..."
QT_MOC_LITERAL(5, 108, 43), // "on_gameObjectTypeFilter_curre..."
QT_MOC_LITERAL(6, 152, 5) // "index"

    },
    "SGOOnMapToolBox\0FilterChanged\0\0"
    "on_SGONameFilterTxt_editingFinished\0"
    "on_instanceNameFilterTxt_editingFinished\0"
    "on_gameObjectTypeFilter_currentIndexChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOOnMapToolBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    0,   36,    2, 0x09 /* Protected */,
       5,    1,   37,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void SGOOnMapToolBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOOnMapToolBox *_t = static_cast<SGOOnMapToolBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FilterChanged(); break;
        case 1: _t->on_SGONameFilterTxt_editingFinished(); break;
        case 2: _t->on_instanceNameFilterTxt_editingFinished(); break;
        case 3: _t->on_gameObjectTypeFilter_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SGOOnMapToolBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapToolBox::FilterChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SGOOnMapToolBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SGOOnMapToolBox.data,
      qt_meta_data_SGOOnMapToolBox,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SGOOnMapToolBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGOOnMapToolBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGOOnMapToolBox.stringdata0))
        return static_cast<void*>(const_cast< SGOOnMapToolBox*>(this));
    if (!strcmp(_clname, "Ui::SGOOnMapToolBox"))
        return static_cast< Ui::SGOOnMapToolBox*>(const_cast< SGOOnMapToolBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int SGOOnMapToolBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SGOOnMapToolBox::FilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
