/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.14.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // D:/github_desktop/myQT/yanglegeyang/yanglegeyang/Data.ini
  0x0,0x0,0x0,0x17,
  0x5b,
  0x44,0x61,0x74,0x61,0x5d,0xd,0xa,0x6e,0x75,0x6d,0x3d,0x32,0xd,0xa,0x30,0x3d,
  0x32,0xd,0xa,0x31,0x3d,0x36,
  
};

static const unsigned char qt_resource_name[] = {
  // Data.ini
  0x0,0x8,
  0x8,0xa4,0x49,0x9,
  0x0,0x44,
  0x0,0x61,0x0,0x74,0x0,0x61,0x0,0x2e,0x0,0x69,0x0,0x6e,0x0,0x69,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/Data.ini
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x85,0x1,0xd2,0x88,0x17,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_dataini)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_dataini)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_dataini)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_dataini)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_dataini)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_dataini)(); }
   } dummy;
}
