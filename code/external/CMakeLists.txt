set(EXTERNAL_LIBRARIES Catch2 GSL raylib etl)

foreach (LIB ${EXTERNAL_LIBRARIES})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${LIB})
        add_subdirectory(${LIB} EXCLUDE_FROM_ALL)
    endif ()
endforeach ()

if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/boost)
    set(BOOST_INCLUDE_LIBRARIES interprocess date_time)
    add_subdirectory(boost EXCLUDE_FROM_ALL)
endif ()