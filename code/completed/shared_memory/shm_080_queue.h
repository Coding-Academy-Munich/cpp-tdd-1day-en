// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_080_QUEUE_H
#define COMPLETED_SHARED_MEMORY_SHM_080_QUEUE_H

#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

namespace shm080 {

constexpr int contents_size {100};

struct MessageBuffer {
    // Mutex to protect access to the queue
    boost::interprocess::interprocess_mutex mutex;

    // Condition to wait when the queue is empty
    boost::interprocess::interprocess_condition cond_empty;

    // Condition to wait when the queue is full
    boost::interprocess::interprocess_condition cond_full;

    // Message contents
    char message_contents[contents_size] {};

    // Is there any message
    bool has_message {false};
};
} // namespace shm080

#endif // COMPLETED_SHARED_MEMORY_SHM_080_QUEUE_H
