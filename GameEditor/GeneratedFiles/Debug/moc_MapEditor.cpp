/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MapEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapEditor_t {
    QByteArrayData data[16];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapEditor_t qt_meta_stringdata_MapEditor = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MapEditor"
QT_MOC_LITERAL(1, 10, 6), // "AddSGO"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 15), // "SGOOnMapDbInfo&"
QT_MOC_LITERAL(4, 34, 8), // "sgoOnMap"
QT_MOC_LITERAL(5, 43, 9), // "DeleteSGO"
QT_MOC_LITERAL(6, 53, 2), // "id"
QT_MOC_LITERAL(7, 56, 7), // "EditSGO"
QT_MOC_LITERAL(8, 64, 16), // "SGODbInfoDeleted"
QT_MOC_LITERAL(9, 81, 11), // "sgoDbInfoId"
QT_MOC_LITERAL(10, 93, 15), // "SGODbInfoEdited"
QT_MOC_LITERAL(11, 109, 23), // "StaticGameObjectDbInfo&"
QT_MOC_LITERAL(12, 133, 6), // "dbInfo"
QT_MOC_LITERAL(13, 140, 20), // "SetSelectedObjectIds"
QT_MOC_LITERAL(14, 161, 16), // "std::vector<int>"
QT_MOC_LITERAL(15, 178, 17) // "selectedObjectIds"

    },
    "MapEditor\0AddSGO\0\0SGOOnMapDbInfo&\0"
    "sgoOnMap\0DeleteSGO\0id\0EditSGO\0"
    "SGODbInfoDeleted\0sgoDbInfoId\0"
    "SGODbInfoEdited\0StaticGameObjectDbInfo&\0"
    "dbInfo\0SetSelectedObjectIds\0"
    "std::vector<int>\0selectedObjectIds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
      10,    1,   56,    2, 0x0a /* Public */,
      13,    1,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void MapEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapEditor *_t = static_cast<MapEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddSGO((*reinterpret_cast< SGOOnMapDbInfo(*)>(_a[1]))); break;
        case 1: _t->DeleteSGO((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->EditSGO((*reinterpret_cast< SGOOnMapDbInfo(*)>(_a[1]))); break;
        case 3: _t->SGODbInfoDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SGODbInfoEdited((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 5: _t->SetSelectedObjectIds((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MapEditor::staticMetaObject = {
    { &QtDirectXWidget::staticMetaObject, qt_meta_stringdata_MapEditor.data,
      qt_meta_data_MapEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MapEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditor.stringdata0))
        return static_cast<void*>(const_cast< MapEditor*>(this));
    if (!strcmp(_clname, "Ui::MapEditor"))
        return static_cast< Ui::MapEditor*>(const_cast< MapEditor*>(this));
    return QtDirectXWidget::qt_metacast(_clname);
}

int MapEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtDirectXWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
