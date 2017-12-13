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
    QByteArrayData data[16];
    char stringdata0[266];
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
QT_MOC_LITERAL(5, 111, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(6, 134, 11), // "RowSelected"
QT_MOC_LITERAL(7, 146, 14), // "QItemSelection"
QT_MOC_LITERAL(8, 161, 8), // "selected"
QT_MOC_LITERAL(9, 170, 10), // "deselected"
QT_MOC_LITERAL(10, 181, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(11, 202, 10), // "pageNumber"
QT_MOC_LITERAL(12, 213, 6), // "onPage"
QT_MOC_LITERAL(13, 220, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(14, 241, 12), // "sectionIndex"
QT_MOC_LITERAL(15, 254, 11) // "UpdateTable"

    },
    "PointLightTableWidget\0on_addPointLightBtn_clicked\0"
    "\0on_editPointLightBtn_clicked\0"
    "on_deletePointLightBtn_clicked\0"
    "editBtnsStateConfigure\0RowSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "PaginatorPageChanged\0pageNumber\0onPage\0"
    "HeaderSectionClicked\0sectionIndex\0"
    "UpdateTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PointLightTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x09 /* Protected */,
       3,    0,   55,    2, 0x09 /* Protected */,
       4,    0,   56,    2, 0x09 /* Protected */,
       5,    0,   57,    2, 0x09 /* Protected */,
       6,    2,   58,    2, 0x09 /* Protected */,
      10,    2,   63,    2, 0x09 /* Protected */,
      13,    1,   68,    2, 0x09 /* Protected */,
      15,    0,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,

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
        case 3: _t->editBtnsStateConfigure(); break;
        case 4: _t->RowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 5: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpdateTable(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
