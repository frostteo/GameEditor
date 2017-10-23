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
    QByteArrayData data[26];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOTableWidget_t qt_meta_stringdata_SGOTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SGOTableWidget"
QT_MOC_LITERAL(1, 15, 8), // "AddToMap"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 23), // "StaticGameObjectDbInfo&"
QT_MOC_LITERAL(4, 49, 10), // "gameObject"
QT_MOC_LITERAL(5, 60, 10), // "SGODeleted"
QT_MOC_LITERAL(6, 71, 5), // "sgoId"
QT_MOC_LITERAL(7, 77, 9), // "SGOEdited"
QT_MOC_LITERAL(8, 87, 20), // "on_addSGOBtn_clicked"
QT_MOC_LITERAL(9, 108, 21), // "on_editSGOBtn_clicked"
QT_MOC_LITERAL(10, 130, 23), // "on_deleteSGOBtn_clicked"
QT_MOC_LITERAL(11, 154, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(12, 177, 19), // "SGOtableRowSelected"
QT_MOC_LITERAL(13, 197, 14), // "QItemSelection"
QT_MOC_LITERAL(14, 212, 8), // "selected"
QT_MOC_LITERAL(15, 221, 10), // "deselected"
QT_MOC_LITERAL(16, 232, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(17, 253, 10), // "pageNumber"
QT_MOC_LITERAL(18, 264, 6), // "onPage"
QT_MOC_LITERAL(19, 271, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(20, 292, 12), // "sectionIndex"
QT_MOC_LITERAL(21, 305, 24), // "on_previewSGOBtn_clicked"
QT_MOC_LITERAL(22, 330, 22), // "on_addToMapBtn_clicked"
QT_MOC_LITERAL(23, 353, 20), // "on_SGODeletedFromMap"
QT_MOC_LITERAL(24, 374, 2), // "id"
QT_MOC_LITERAL(25, 377, 11) // "UpdateTable"

    },
    "SGOTableWidget\0AddToMap\0\0"
    "StaticGameObjectDbInfo&\0gameObject\0"
    "SGODeleted\0sgoId\0SGOEdited\0"
    "on_addSGOBtn_clicked\0on_editSGOBtn_clicked\0"
    "on_deleteSGOBtn_clicked\0editBtnsStateConfigure\0"
    "SGOtableRowSelected\0QItemSelection\0"
    "selected\0deselected\0PaginatorPageChanged\0"
    "pageNumber\0onPage\0HeaderSectionClicked\0"
    "sectionIndex\0on_previewSGOBtn_clicked\0"
    "on_addToMapBtn_clicked\0on_SGODeletedFromMap\0"
    "id\0UpdateTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   93,    2, 0x09 /* Protected */,
       9,    0,   94,    2, 0x09 /* Protected */,
      10,    0,   95,    2, 0x09 /* Protected */,
      11,    0,   96,    2, 0x09 /* Protected */,
      12,    2,   97,    2, 0x09 /* Protected */,
      16,    2,  102,    2, 0x09 /* Protected */,
      19,    1,  107,    2, 0x09 /* Protected */,
      21,    0,  110,    2, 0x09 /* Protected */,
      22,    0,  111,    2, 0x09 /* Protected */,
      23,    1,  112,    2, 0x09 /* Protected */,
      25,    0,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,

       0        // eod
};

void SGOTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOTableWidget *_t = static_cast<SGOTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddToMap((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 1: _t->SGODeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SGOEdited((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 3: _t->on_addSGOBtn_clicked(); break;
        case 4: _t->on_editSGOBtn_clicked(); break;
        case 5: _t->on_deleteSGOBtn_clicked(); break;
        case 6: _t->editBtnsStateConfigure(); break;
        case 7: _t->SGOtableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 8: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_previewSGOBtn_clicked(); break;
        case 11: _t->on_addToMapBtn_clicked(); break;
        case 12: _t->on_SGODeletedFromMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->UpdateTable(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
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
            typedef void (SGOTableWidget::*_t)(StaticGameObjectDbInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::AddToMap)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SGOTableWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::SGODeleted)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SGOTableWidget::*_t)(StaticGameObjectDbInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::SGOEdited)) {
                *result = 2;
                return;
            }
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SGOTableWidget::AddToMap(StaticGameObjectDbInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SGOTableWidget::SGODeleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SGOTableWidget::SGOEdited(StaticGameObjectDbInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
