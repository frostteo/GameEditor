/****************************************************************************
** Meta object code from reading C++ file 'PointLightWidgetToolBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PointLightWidgetToolBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PointLightWidgetToolBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PointLightWidgetToolBox_t {
    QByteArrayData data[5];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PointLightWidgetToolBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PointLightWidgetToolBox_t qt_meta_stringdata_PointLightWidgetToolBox = {
    {
QT_MOC_LITERAL(0, 0, 23), // "PointLightWidgetToolBox"
QT_MOC_LITERAL(1, 24, 13), // "FilterChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 32), // "on_nameFilterTxt_editingFinished"
QT_MOC_LITERAL(4, 72, 35) // "on_sgoNameFilterTxt_editingFi..."

    },
    "PointLightWidgetToolBox\0FilterChanged\0"
    "\0on_nameFilterTxt_editingFinished\0"
    "on_sgoNameFilterTxt_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PointLightWidgetToolBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x09 /* Protected */,
       4,    0,   31,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PointLightWidgetToolBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PointLightWidgetToolBox *_t = static_cast<PointLightWidgetToolBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FilterChanged(); break;
        case 1: _t->on_nameFilterTxt_editingFinished(); break;
        case 2: _t->on_sgoNameFilterTxt_editingFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PointLightWidgetToolBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PointLightWidgetToolBox::FilterChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PointLightWidgetToolBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PointLightWidgetToolBox.data,
      qt_meta_data_PointLightWidgetToolBox,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PointLightWidgetToolBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PointLightWidgetToolBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PointLightWidgetToolBox.stringdata0))
        return static_cast<void*>(const_cast< PointLightWidgetToolBox*>(this));
    if (!strcmp(_clname, "Ui::PointLightWidgetToolBox"))
        return static_cast< Ui::PointLightWidgetToolBox*>(const_cast< PointLightWidgetToolBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int PointLightWidgetToolBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PointLightWidgetToolBox::FilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
