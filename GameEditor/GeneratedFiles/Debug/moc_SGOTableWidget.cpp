/****************************************************************************
** Meta object code from reading C++ file 'SGOTableWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SGOTableWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SGOTableWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGOTableWidget_t {
    QByteArrayData data[17];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOTableWidget_t qt_meta_stringdata_SGOTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SGOTableWidget"
QT_MOC_LITERAL(1, 15, 20), // "on_addSGOBtn_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "on_editSGOBtn_clicked"
QT_MOC_LITERAL(4, 59, 23), // "on_deleteSGOBtn_clicked"
QT_MOC_LITERAL(5, 83, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(6, 106, 19), // "SGOtableRowSelected"
QT_MOC_LITERAL(7, 126, 14), // "QItemSelection"
QT_MOC_LITERAL(8, 141, 8), // "selected"
QT_MOC_LITERAL(9, 150, 10), // "deselected"
QT_MOC_LITERAL(10, 161, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(11, 182, 10), // "pageNumber"
QT_MOC_LITERAL(12, 193, 6), // "onPage"
QT_MOC_LITERAL(13, 200, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(14, 221, 12), // "sectionIndex"
QT_MOC_LITERAL(15, 234, 11), // "UpdateTable"
QT_MOC_LITERAL(16, 246, 24) // "on_previewSGOBtn_clicked"

    },
    "SGOTableWidget\0on_addSGOBtn_clicked\0"
    "\0on_editSGOBtn_clicked\0on_deleteSGOBtn_clicked\0"
    "editBtnsStateConfigure\0SGOtableRowSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "PaginatorPageChanged\0pageNumber\0onPage\0"
    "HeaderSectionClicked\0sectionIndex\0"
    "UpdateTable\0on_previewSGOBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOTableWidget[] = {

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
       3,    0,   60,    2, 0x09 /* Protected */,
       4,    0,   61,    2, 0x09 /* Protected */,
       5,    0,   62,    2, 0x09 /* Protected */,
       6,    2,   63,    2, 0x09 /* Protected */,
      10,    2,   68,    2, 0x09 /* Protected */,
      13,    1,   73,    2, 0x09 /* Protected */,
      15,    0,   76,    2, 0x09 /* Protected */,
      16,    0,   77,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SGOTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOTableWidget *_t = static_cast<SGOTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_addSGOBtn_clicked(); break;
        case 1: _t->on_editSGOBtn_clicked(); break;
        case 2: _t->on_deleteSGOBtn_clicked(); break;
        case 3: _t->editBtnsStateConfigure(); break;
        case 4: _t->SGOtableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 5: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpdateTable(); break;
        case 8: _t->on_previewSGOBtn_clicked(); break;
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

const QMetaObject SGOTableWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SGOTableWidget.data,
      qt_meta_data_SGOTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SGOTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGOTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGOTableWidget.stringdata0))
        return static_cast<void*>(const_cast< SGOTableWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SGOTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
