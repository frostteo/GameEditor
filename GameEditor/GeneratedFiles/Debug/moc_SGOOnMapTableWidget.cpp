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
    QByteArrayData data[19];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOOnMapTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOOnMapTableWidget_t qt_meta_stringdata_SGOOnMapTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SGOOnMapTableWidget"
QT_MOC_LITERAL(1, 20, 15), // "SGOCountChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(4, 60, 16), // "TableRowSelected"
QT_MOC_LITERAL(5, 77, 14), // "QItemSelection"
QT_MOC_LITERAL(6, 92, 8), // "selected"
QT_MOC_LITERAL(7, 101, 10), // "deselected"
QT_MOC_LITERAL(8, 112, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(9, 133, 10), // "pageNumber"
QT_MOC_LITERAL(10, 144, 6), // "onPage"
QT_MOC_LITERAL(11, 151, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(12, 172, 12), // "sectionIndex"
QT_MOC_LITERAL(13, 185, 11), // "UpdateTable"
QT_MOC_LITERAL(14, 197, 16), // "DeleteBtnClicked"
QT_MOC_LITERAL(15, 214, 14), // "EditBtnClicked"
QT_MOC_LITERAL(16, 229, 15), // "CloneBtnClicked"
QT_MOC_LITERAL(17, 245, 10), // "SGODeleted"
QT_MOC_LITERAL(18, 256, 5) // "sgoId"

    },
    "SGOOnMapTableWidget\0SGOCountChanged\0"
    "\0editBtnsStateConfigure\0TableRowSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "PaginatorPageChanged\0pageNumber\0onPage\0"
    "HeaderSectionClicked\0sectionIndex\0"
    "UpdateTable\0DeleteBtnClicked\0"
    "EditBtnClicked\0CloneBtnClicked\0"
    "SGODeleted\0sgoId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOOnMapTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    2,   66,    2, 0x09 /* Protected */,
       8,    2,   71,    2, 0x09 /* Protected */,
      11,    1,   76,    2, 0x09 /* Protected */,
      13,    0,   79,    2, 0x09 /* Protected */,
      14,    0,   80,    2, 0x09 /* Protected */,
      15,    0,   81,    2, 0x09 /* Protected */,
      16,    0,   82,    2, 0x09 /* Protected */,
      17,    1,   83,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void SGOOnMapTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOOnMapTableWidget *_t = static_cast<SGOOnMapTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SGOCountChanged(); break;
        case 1: _t->editBtnsStateConfigure(); break;
        case 2: _t->TableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 3: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->UpdateTable(); break;
        case 6: _t->DeleteBtnClicked(); break;
        case 7: _t->EditBtnClicked(); break;
        case 8: _t->CloneBtnClicked(); break;
        case 9: _t->SGODeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SGOOnMapTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTableWidget::SGOCountChanged)) {
                *result = 0;
                return;
            }
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

// SIGNAL 0
void SGOOnMapTableWidget::SGOCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
