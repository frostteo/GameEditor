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
    QByteArrayData data[28];
    char stringdata0[423];
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
QT_MOC_LITERAL(5, 60, 15), // "BeforeDeleteSgo"
QT_MOC_LITERAL(6, 76, 5), // "sgoId"
QT_MOC_LITERAL(7, 82, 10), // "SGODeleted"
QT_MOC_LITERAL(8, 93, 9), // "SGOEdited"
QT_MOC_LITERAL(9, 103, 20), // "on_addSGOBtn_clicked"
QT_MOC_LITERAL(10, 124, 21), // "on_editSGOBtn_clicked"
QT_MOC_LITERAL(11, 146, 23), // "on_deleteSGOBtn_clicked"
QT_MOC_LITERAL(12, 170, 22), // "editBtnsStateConfigure"
QT_MOC_LITERAL(13, 193, 19), // "SGOtableRowSelected"
QT_MOC_LITERAL(14, 213, 14), // "QItemSelection"
QT_MOC_LITERAL(15, 228, 8), // "selected"
QT_MOC_LITERAL(16, 237, 10), // "deselected"
QT_MOC_LITERAL(17, 248, 20), // "PaginatorPageChanged"
QT_MOC_LITERAL(18, 269, 10), // "pageNumber"
QT_MOC_LITERAL(19, 280, 6), // "onPage"
QT_MOC_LITERAL(20, 287, 20), // "HeaderSectionClicked"
QT_MOC_LITERAL(21, 308, 12), // "sectionIndex"
QT_MOC_LITERAL(22, 321, 24), // "on_previewSGOBtn_clicked"
QT_MOC_LITERAL(23, 346, 22), // "on_addToMapBtn_clicked"
QT_MOC_LITERAL(24, 369, 20), // "on_SGODeletedFromMap"
QT_MOC_LITERAL(25, 390, 2), // "id"
QT_MOC_LITERAL(26, 393, 11), // "UpdateTable"
QT_MOC_LITERAL(27, 405, 17) // "CountOnMapChanged"

    },
    "SGOTableWidget\0AddToMap\0\0"
    "StaticGameObjectDbInfo&\0gameObject\0"
    "BeforeDeleteSgo\0sgoId\0SGODeleted\0"
    "SGOEdited\0on_addSGOBtn_clicked\0"
    "on_editSGOBtn_clicked\0on_deleteSGOBtn_clicked\0"
    "editBtnsStateConfigure\0SGOtableRowSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "PaginatorPageChanged\0pageNumber\0onPage\0"
    "HeaderSectionClicked\0sectionIndex\0"
    "on_previewSGOBtn_clicked\0"
    "on_addToMapBtn_clicked\0on_SGODeletedFromMap\0"
    "id\0UpdateTable\0CountOnMapChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       7,    1,  100,    2, 0x06 /* Public */,
       8,    1,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  106,    2, 0x09 /* Protected */,
      10,    0,  107,    2, 0x09 /* Protected */,
      11,    0,  108,    2, 0x09 /* Protected */,
      12,    0,  109,    2, 0x09 /* Protected */,
      13,    2,  110,    2, 0x09 /* Protected */,
      17,    2,  115,    2, 0x09 /* Protected */,
      20,    1,  120,    2, 0x09 /* Protected */,
      22,    0,  123,    2, 0x09 /* Protected */,
      23,    0,  124,    2, 0x09 /* Protected */,
      24,    1,  125,    2, 0x09 /* Protected */,
      26,    0,  128,    2, 0x0a /* Public */,
      27,    1,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,

       0        // eod
};

void SGOTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOTableWidget *_t = static_cast<SGOTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddToMap((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 1: _t->BeforeDeleteSgo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SGODeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SGOEdited((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 4: _t->on_addSGOBtn_clicked(); break;
        case 5: _t->on_editSGOBtn_clicked(); break;
        case 6: _t->on_deleteSGOBtn_clicked(); break;
        case 7: _t->editBtnsStateConfigure(); break;
        case 8: _t->SGOtableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 9: _t->PaginatorPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->HeaderSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_previewSGOBtn_clicked(); break;
        case 12: _t->on_addToMapBtn_clicked(); break;
        case 13: _t->on_SGODeletedFromMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->UpdateTable(); break;
        case 15: _t->CountOnMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
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
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::BeforeDeleteSgo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SGOTableWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::SGODeleted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SGOTableWidget::*_t)(StaticGameObjectDbInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOTableWidget::SGOEdited)) {
                *result = 3;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
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
void SGOTableWidget::BeforeDeleteSgo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SGOTableWidget::SGODeleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SGOTableWidget::SGOEdited(StaticGameObjectDbInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
