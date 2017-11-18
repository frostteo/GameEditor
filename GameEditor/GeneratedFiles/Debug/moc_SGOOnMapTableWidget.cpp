/****************************************************************************
** Meta object code from reading C++ file 'SGOOnMapTableWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SGOOnMapTableWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SGOOnMapTableWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGOOnMapTableWidget_t {
    QByteArrayData data[18];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOOnMapTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOOnMapTableWidget_t qt_meta_stringdata_SGOOnMapTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SGOOnMapTableWidget"
QT_MOC_LITERAL(1, 20, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 16), // "TableRowSelected"
QT_MOC_LITERAL(4, 61, 14), // "QItemSelection"
QT_MOC_LITERAL(5, 76, 8), // "selected"
QT_MOC_LITERAL(6, 85, 10), // "deselected"
QT_MOC_LITERAL(7, 96, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(8, 117, 10), // "pageNumber"
QT_MOC_LITERAL(9, 128, 6), // "onPage"
QT_MOC_LITERAL(10, 135, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(11, 156, 12), // "sectionIndex"
QT_MOC_LITERAL(12, 169, 11), // "UpdateTable"
QT_MOC_LITERAL(13, 181, 16), // "DeleteBtnClicked"
QT_MOC_LITERAL(14, 198, 14), // "EditBtnClicked"
QT_MOC_LITERAL(15, 213, 15), // "CloneBtnClicked"
QT_MOC_LITERAL(16, 229, 10), // "SGODeleted"
QT_MOC_LITERAL(17, 240, 5) // "sgoId"

    },
    "SGOOnMapTableWidget\0editBtnsStateConfigure\0"
    "\0TableRowSelected\0QItemSelection\0"
    "selected\0deselected\0PaginatorPageChanged\0"
    "pageNumber\0onPage\0HeaderSectionClicked\0"
    "sectionIndex\0UpdateTable\0DeleteBtnClicked\0"
    "EditBtnClicked\0CloneBtnClicked\0"
    "SGODeleted\0sgoId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOOnMapTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x09 /* Protected */,
       3,    2,   60,    2, 0x09 /* Protected */,
       7,    2,   65,    2, 0x09 /* Protected */,
      10,    1,   70,    2, 0x09 /* Protected */,
      12,    0,   73,    2, 0x09 /* Protected */,
      13,    0,   74,    2, 0x09 /* Protected */,
      14,    0,   75,    2, 0x09 /* Protected */,
      15,    0,   76,    2, 0x09 /* Protected */,
      16,    1,   77,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void SGOOnMapTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOOnMapTableWidget *_t = static_cast<SGOOnMapTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editBtnsStateConfigure(); break;
        case 1: _t->TableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 2: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->UpdateTable(); break;
        case 5: _t->DeleteBtnClicked(); break;
        case 6: _t->EditBtnClicked(); break;
        case 7: _t->CloneBtnClicked(); break;
        case 8: _t->SGODeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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

const QMetaObject SGOOnMapTableWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SGOOnMapTableWidget.data,
      qt_meta_data_SGOOnMapTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SGOOnMapTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGOOnMapTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGOOnMapTableWidget.stringdata0))
        return static_cast<void*>(const_cast< SGOOnMapTableWidget*>(this));
    if (!strcmp(_clname, "Ui::SGOOnMapTableWidget"))
        return static_cast< Ui::SGOOnMapTableWidget*>(const_cast< SGOOnMapTableWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SGOOnMapTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
