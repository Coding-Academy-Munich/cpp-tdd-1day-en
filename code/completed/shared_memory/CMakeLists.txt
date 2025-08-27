add_executable(shm_010_starter
        shm_010_starter.cpp
        shm_010_starter.h
        utils.h)
target_link_libraries(shm_010_starter Boost::interprocess)

add_executable(shm_020_mapped_region
        shm_020_mapped_region.cpp
        shm_020_mapped_region.h
        utils.h)
target_link_libraries(shm_020_mapped_region Boost::interprocess)

add_executable(shm_025_mapped_region_multi
        shm_025_mapped_region_multi.cpp
        shm_025_mapped_region_multi.h
        utils.h)
target_link_libraries(shm_025_mapped_region_multi Boost::interprocess)

add_executable(shm_030_managed_segment
        shm_030_managed_segment.cpp
        shm_030_managed_segment.h
        utils.h)
target_link_libraries(shm_030_managed_segment Boost::interprocess)

add_executable(shm_035_managed_segment_multi
        shm_035_managed_segment_multi.cpp
        shm_035_managed_segment_multi.h
        utils.h)
target_link_libraries(shm_035_managed_segment_multi Boost::interprocess)

add_executable(shm_040_named_objects
        shm_040_named_objects.cpp
        shm_040_named_objects.h
        utils.h)
target_link_libraries(shm_040_named_objects Boost::interprocess)

add_executable(shm_050_bad_pointer
        shm_050_bad_pointer.cpp
        shm_050_bad_pointer.h
        utils.h)
target_link_libraries(shm_050_bad_pointer Boost::interprocess)

add_executable(shm_060_offset_pointer
        shm_060_offset_pointer.cpp
        shm_060_offset_pointer.h
        utils.h)
target_link_libraries(shm_060_offset_pointer Boost::interprocess)

add_executable(shm_070_allocator
        shm_070_allocator.cpp
        shm_070_allocator.h
        utils.h)
target_link_libraries(shm_070_allocator Boost::interprocess)

add_executable(shm_080_producer
        shm_080_producer.cpp
        shm_080_queue.h)
target_link_libraries(shm_080_producer Boost::interprocess)

add_executable(shm_080_consumer
        shm_080_consumer.cpp
        shm_080_queue.h)
target_link_libraries(shm_080_consumer Boost::interprocess)
