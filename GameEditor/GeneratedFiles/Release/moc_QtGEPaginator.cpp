/****************************************************************************
** Meta object code from reading C++ file 'QtGEPaginator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtGEPaginator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtGEPaginator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtGEPaginator_t {
    QByteArrayData data[15];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGEPaginator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGEPaginator_t qt_meta_stringdata_QtGEPaginator = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtGEPaginator"
QT_MOC_LITERAL(1, 14, 11), // "PageChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "pageNumber"
QT_MOC_LITERAL(4, 38, 6), // "onPage"
QT_MOC_LITERAL(5, 45, 19), // "on_firstBtn_clicked"
QT_MOC_LITERAL(6, 65, 18), // "on_prevBtn_clicked"
QT_MOC_LITERAL(7, 84, 18), // "on_nextBtn_clicked"
QT_MOC_LITERAL(8, 103, 18), // "on_lastBtn_clicked"
QT_MOC_LITERAL(9, 122, 26), // "on_pageTxt_editingFinished"
QT_MOC_LITERAL(10, 149, 33), // "on_onPageList_currentIndexCha..."
QT_MOC_LITERAL(11, 183, 5), // "index"
QT_MOC_LITERAL(12, 189, 16), // "UpdatePagingInfo"
QT_MOC_LITERAL(13, 206, 10), // "PagingInfo"
QT_MOC_LITERAL(14, 217, 10) // "pagingInfo"

    },
    "QtGEPaginator\0PageChanged\0\0pageNumber\0"
    "onPage\0on_firstBtn_clicked\0"
    "on_prevBtn_clicked\0on_nextBtn_clicked\0"
    "on_lastBtn_clicked\0on_pageTxt_editingFinished\0"
    "on_onPageList_currentIndexChanged\0"
    "index\0UpdatePagingInfo\0PagingInfo\0"
    "pagingInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGEPaginator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   59,    2, 0x09 /* Protected */,
       6,    0,   60,    2, 0x09 /* Protected */,
       7,    0,   61,    2, 0x09 /* Protected */,
       8,    0,   62,    2, 0x09 /* Protected */,
       9,    0,   63,    2, 0x09 /* Protected */,
      10,    1,   64,    2, 0x09 /* Protected */,
      12,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void QtGEPaginator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGEPaginator *_t = static_cast<QtGEPaginator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_firstBtn_clicked(); break;
        case 2: _t->on_prevBtn_clicked(); break;
        case 3: _t->on_nextBtn_clicked(); break;
        case 4: _t->on_lastBtn_clicked(); break;
        case 5: _t->on_pageTxt_editingFinished(); break;
        case 6: _t->on_onPageList_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpdatePagingInfo((*reinterpret_cast< PagingInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtGEPaginator::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtGEPaginator::PageChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QtGEPaginator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtGEPaginator.data,
      qt_meta_data_QtGEPaginator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtGEPaginator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGEPaginator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtGEPaginator.stringdata0))
        return static_cast<void*>(const_cast< QtGEPaginator*>(this));
    if (!strcmp(_clname, "Ui::QtGEPaginator"))
        return static_cast< Ui::QtGEPaginator*>(const_cast< QtGEPaginator*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtGEPaginator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QtGEPaginator::PageChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
