/****************************************************************************
** Meta object code from reading C++ file 'PointLightTableWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PointLightTableWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PointLightTableWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PointLightTableWidget_t {
    QByteArrayData data[22];
    char stringdata0[331];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PointLightTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PointLightTableWidget_t qt_meta_stringdata_PointLightTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "PointLightTableWidget"
QT_MOC_LITERAL(1, 22, 27), // "on_addPointLightBtn_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 28), // "on_editPointLightBtn_clicked"
QT_MOC_LITERAL(4, 80, 30), // "on_deletePointLightBtn_clicked"
QT_MOC_LITERAL(5, 111, 29), // "on_configureRelPosBtn_clicked"
QT_MOC_LITERAL(6, 141, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(7, 164, 11), // "RowSelected"
QT_MOC_LITERAL(8, 176, 14), // "QItemSelection"
QT_MOC_LITERAL(9, 191, 8), // "selected"
QT_MOC_LITERAL(10, 200, 10), // "deselected"
QT_MOC_LITERAL(11, 211, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(12, 232, 10), // "pageNumber"
QT_MOC_LITERAL(13, 243, 6), // "onPage"
QT_MOC_LITERAL(14, 250, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(15, 271, 12), // "sectionIndex"
QT_MOC_LITERAL(16, 284, 11), // "UpdateTable"
QT_MOC_LITERAL(17, 296, 25), // "PointLightPositionChanged"
QT_MOC_LITERAL(18, 322, 2), // "id"
QT_MOC_LITERAL(19, 325, 1), // "x"
QT_MOC_LITERAL(20, 327, 1), // "y"
QT_MOC_LITERAL(21, 329, 1) // "z"

    },
    "PointLightTableWidget\0on_addPointLightBtn_clicked\0"
    "\0on_editPointLightBtn_clicked\0"
    "on_deletePointLightBtn_clicked\0"
    "on_configureRelPosBtn_clicked\0"
    "editBtnsStateConfigure\0RowSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "PaginatorPageChanged\0pageNumber\0onPage\0"
    "HeaderSectionClicked\0sectionIndex\0"
    "UpdateTable\0PointLightPositionChanged\0"
    "id\0x\0y\0z"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PointLightTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    2,   69,    2, 0x09 /* Protected */,
      11,    2,   74,    2, 0x09 /* Protected */,
      14,    1,   79,    2, 0x09 /* Protected */,
      16,    0,   82,    2, 0x0a /* Public */,
      17,    4,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,   18,   19,   20,   21,

       0        // eod
};

void PointLightTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PointLightTableWidget *_t = static_cast<PointLightTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_addPointLightBtn_clicked(); break;
        case 1: _t->on_editPointLightBtn_clicked(); break;
        case 2: _t->on_deletePointLightBtn_clicked(); break;
        case 3: _t->on_configureRelPosBtn_clicked(); break;
        case 4: _t->editBtnsStateConfigure(); break;
        case 5: _t->RowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 6: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->UpdateTable(); break;
        case 9: _t->PointLightPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    }
}

const QMetaObject PointLightTableWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PointLightTableWidget.data,
      qt_meta_data_PointLightTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PointLightTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PointLightTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PointLightTableWidget.stringdata0))
        return static_cast<void*>(const_cast< PointLightTableWidget*>(this));
    if (!strcmp(_clname, "Ui::PointLightTableWidget"))
        return static_cast< Ui::PointLightTableWidget*>(const_cast< PointLightTableWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PointLightTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
