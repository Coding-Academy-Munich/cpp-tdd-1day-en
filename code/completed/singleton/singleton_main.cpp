#include "singleton.h"

using namespace singleton;

int main()
{
    SingletonNonThreadSafe& s1{SingletonNonThreadSafe::instance()};
    SingletonNonThreadSafe& s2{SingletonNonThreadSafe::instance()};
    check_singleton("SingletonNonThreadSafe", s1, s2);

    SingletonWithMutex& s3{SingletonWithMutex::instance()};
    SingletonWithMutex& s4{SingletonWithMutex::instance()};
    check_singleton("SingletonWithMutex", s3, s4);

    SingletonWithCallOnce& s5{SingletonWithCallOnce::instance()};
    SingletonWithCallOnce& s6{SingletonWithCallOnce::instance()};
    check_singleton("SingletonWithCallOnce", s5, s6);

    Singleton& s7{Singleton::instance()};
    Singleton& s8{Singleton::instance()};
    check_singleton("Meyer's Singleton", s7, s8);
}
