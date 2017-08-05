/****************************************************************************
** Meta object code from reading C++ file 'GameEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GameEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameEditor_t {
    QByteArrayData data[10];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameEditor_t qt_meta_stringdata_GameEditor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameEditor"
QT_MOC_LITERAL(1, 11, 25), // "on_addStaticGOBtn_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 26), // "on_editStaticGOBtn_clicked"
QT_MOC_LITERAL(4, 65, 28), // "on_deleteStaticGOBtn_clicked"
QT_MOC_LITERAL(5, 94, 29), // "on_previewStaticGOBtn_clicked"
QT_MOC_LITERAL(6, 124, 32), // "staticGameObjectTableRowSelected"
QT_MOC_LITERAL(7, 157, 14), // "QItemSelection"
QT_MOC_LITERAL(8, 172, 8), // "selected"
QT_MOC_LITERAL(9, 181, 10) // "deselected"

    },
    "GameEditor\0on_addStaticGOBtn_clicked\0"
    "\0on_editStaticGOBtn_clicked\0"
    "on_deleteStaticGOBtn_clicked\0"
    "on_previewStaticGOBtn_clicked\0"
    "staticGameObjectTableRowSelected\0"
    "QItemSelection\0selected\0deselected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    2,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,

       0        // eod
};

void GameEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameEditor *_t = static_cast<GameEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_addStaticGOBtn_clicked(); break;
        case 1: _t->on_editStaticGOBtn_clicked(); break;
        case 2: _t->on_deleteStaticGOBtn_clicked(); break;
        case 3: _t->on_previewStaticGOBtn_clicked(); break;
        case 4: _t->staticGameObjectTableRowSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
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

const QMetaObject GameEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GameEditor.data,
      qt_meta_data_GameEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GameEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameEditor.stringdata0))
        return static_cast<void*>(const_cast< GameEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GameEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
