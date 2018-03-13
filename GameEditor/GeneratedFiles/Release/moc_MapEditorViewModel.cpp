/****************************************************************************
** Meta object code from reading C++ file 'MapEditorViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MapEditorViewModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditorViewModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapEditorViewModel_t {
    QByteArrayData data[19];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapEditorViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapEditorViewModel_t qt_meta_stringdata_MapEditorViewModel = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MapEditorViewModel"
QT_MOC_LITERAL(1, 19, 22), // "PointLightCountChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 2), // "id"
QT_MOC_LITERAL(4, 46, 16), // "SGODbInfoDeleted"
QT_MOC_LITERAL(5, 63, 11), // "sgoDbInfoId"
QT_MOC_LITERAL(6, 75, 15), // "SGODbInfoEdited"
QT_MOC_LITERAL(7, 91, 23), // "StaticGameObjectDbInfo&"
QT_MOC_LITERAL(8, 115, 22), // "staticGameObjectDbInfo"
QT_MOC_LITERAL(9, 138, 9), // "FreezeSgo"
QT_MOC_LITERAL(10, 148, 11), // "UnfreezeSgo"
QT_MOC_LITERAL(11, 160, 16), // "SelectionChanged"
QT_MOC_LITERAL(12, 177, 16), // "std::vector<int>"
QT_MOC_LITERAL(13, 194, 14), // "selectedSgoIds"
QT_MOC_LITERAL(14, 209, 22), // "PointLightDbInfoEdited"
QT_MOC_LITERAL(15, 232, 17), // "PointLightDbInfo&"
QT_MOC_LITERAL(16, 250, 10), // "pointLight"
QT_MOC_LITERAL(17, 261, 23), // "PointLightDbInfoDeleted"
QT_MOC_LITERAL(18, 285, 12) // "pointLightId"

    },
    "MapEditorViewModel\0PointLightCountChanged\0"
    "\0id\0SGODbInfoDeleted\0sgoDbInfoId\0"
    "SGODbInfoEdited\0StaticGameObjectDbInfo&\0"
    "staticGameObjectDbInfo\0FreezeSgo\0"
    "UnfreezeSgo\0SelectionChanged\0"
    "std::vector<int>\0selectedSgoIds\0"
    "PointLightDbInfoEdited\0PointLightDbInfo&\0"
    "pointLight\0PointLightDbInfoDeleted\0"
    "pointLightId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapEditorViewModel[] = {

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
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      11,    1,   69,    2, 0x0a /* Public */,
      14,    1,   72,    2, 0x0a /* Public */,
      17,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void MapEditorViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapEditorViewModel *_t = static_cast<MapEditorViewModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PointLightCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SGODbInfoDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SGODbInfoEdited((*reinterpret_cast< StaticGameObjectDbInfo(*)>(_a[1]))); break;
        case 3: _t->FreezeSgo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->UnfreezeSgo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SelectionChanged((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 6: _t->PointLightDbInfoEdited((*reinterpret_cast< PointLightDbInfo(*)>(_a[1]))); break;
        case 7: _t->PointLightDbInfoDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MapEditorViewModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapEditorViewModel::PointLightCountChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MapEditorViewModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MapEditorViewModel.data,
      qt_meta_data_MapEditorViewModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MapEditorViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapEditorViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditorViewModel.stringdata0))
        return static_cast<void*>(const_cast< MapEditorViewModel*>(this));
    return QObject::qt_metacast(_clname);
}

int MapEditorViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MapEditorViewModel::PointLightCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
