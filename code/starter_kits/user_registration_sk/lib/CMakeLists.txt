add_library(user_registration_sk_lib
        user_registration_service.cpp
        user_registration_service.h
)
target_include_directories(user_registration_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
