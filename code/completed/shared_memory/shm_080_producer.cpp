// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_080_queue.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdio>
#include <iostream>

namespace bi = boost::interprocess;

namespace shm080 {
void produce_message(int i, shm080::MessageBuffer* buffer);
const int num_msg {100};
} // namespace shm080

int main() {

    // Erase previous shared memory and schedule erasure on exit
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a shared memory object.
    bi::shared_memory_object shm(bi::create_only, "MySharedMemory", bi::read_write);
    try {
        // Set size
        shm.truncate(sizeof(shm080::MessageBuffer));

        // Map the whole shared memory in this process
        bi::mapped_region region(shm, bi::read_write);

        // Get the address of the mapped region
        void* addr {region.get_address()};

        // Construct the shared structure in memory
        // Note that buffer->has_message is false at this point
        auto* buffer {new (addr) shm080::MessageBuffer};

        for (int i {0}; i < shm080::num_msg; ++i) {
            // Produce a message
            shm080::produce_message(i, buffer);
        }
    } catch (bi::interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

namespace shm080 {

namespace bi = boost::interprocess;

void write_message_data(int i, MessageBuffer* buffer);

void produce_message(int i, MessageBuffer* buffer) {
    bi::scoped_lock<bi::interprocess_mutex> lock(buffer->mutex);

    if (buffer->has_message) {
        buffer->cond_full.wait(lock);
    }
    write_message_data(i, buffer);

    // Notify to the other process that there is a message
    buffer->cond_empty.notify_one();

    // Mark message buffer as full
    buffer->has_message = true;
}

void write_message_data(int i, MessageBuffer* buffer) {
    if (i == (num_msg - 1)) {
        snprintf(buffer->message_contents, contents_size, "%s", "last message");
    } else {
        snprintf(buffer->message_contents, contents_size, "%s_%d", "my_trace", i);
    }
}

} // namespace shm080
