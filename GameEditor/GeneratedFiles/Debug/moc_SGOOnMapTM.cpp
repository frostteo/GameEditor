/****************************************************************************
** Meta object code from reading C++ file 'SGOOnMapTM.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SGOOnMapTM.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SGOOnMapTM.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGOOnMapTM_t {
    QByteArrayData data[15];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOOnMapTM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOOnMapTM_t qt_meta_stringdata_SGOOnMapTM = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SGOOnMapTM"
QT_MOC_LITERAL(1, 11, 15), // "SGOCountChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "id"
QT_MOC_LITERAL(4, 31, 15), // "FreezeSgoSignal"
QT_MOC_LITERAL(5, 47, 17), // "UnfreezeSgoSignal"
QT_MOC_LITERAL(6, 65, 16), // "SelectionChanged"
QT_MOC_LITERAL(7, 82, 16), // "std::vector<int>"
QT_MOC_LITERAL(8, 99, 14), // "selectedSgoIds"
QT_MOC_LITERAL(9, 114, 20), // "ClearSelectionSignal"
QT_MOC_LITERAL(10, 135, 12), // "EditPosition"
QT_MOC_LITERAL(11, 148, 1), // "x"
QT_MOC_LITERAL(12, 150, 1), // "y"
QT_MOC_LITERAL(13, 152, 1), // "z"
QT_MOC_LITERAL(14, 154, 12) // "EditRotation"

    },
    "SGOOnMapTM\0SGOCountChanged\0\0id\0"
    "FreezeSgoSignal\0UnfreezeSgoSignal\0"
    "SelectionChanged\0std::vector<int>\0"
    "selectedSgoIds\0ClearSelectionSignal\0"
    "EditPosition\0x\0y\0z\0EditRotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOOnMapTM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,
       6,    1,   58,    2, 0x06 /* Public */,
       9,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    4,   62,    2, 0x0a /* Public */,
      14,    4,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,   11,   12,   13,

       0        // eod
};

void SGOOnMapTM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOOnMapTM *_t = static_cast<SGOOnMapTM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SGOCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->FreezeSgoSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->UnfreezeSgoSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SelectionChanged((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 4: _t->ClearSelectionSignal(); break;
        case 5: _t->EditPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 6: _t->EditRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SGOOnMapTM::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::SGOCountChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SGOOnMapTM::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::FreezeSgoSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SGOOnMapTM::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::UnfreezeSgoSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SGOOnMapTM::*_t)(std::vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::SelectionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SGOOnMapTM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::ClearSelectionSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject SGOOnMapTM::staticMetaObject = {
    { &GETable<SGOOnMapDbInfo>::staticMetaObject, qt_meta_stringdata_SGOOnMapTM.data,
      qt_meta_data_SGOOnMapTM,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SGOOnMapTM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGOOnMapTM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGOOnMapTM.stringdata0))
        return static_cast<void*>(const_cast< SGOOnMapTM*>(this));
    return GETable<SGOOnMapDbInfo>::qt_metacast(_clname);
}

int SGOOnMapTM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GETable<SGOOnMapDbInfo>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SGOOnMapTM::SGOCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SGOOnMapTM::FreezeSgoSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SGOOnMapTM::UnfreezeSgoSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SGOOnMapTM::SelectionChanged(std::vector<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SGOOnMapTM::ClearSelectionSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
