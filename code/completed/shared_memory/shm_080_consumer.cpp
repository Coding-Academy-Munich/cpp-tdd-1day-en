// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_080_queue.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstring>
#include <iostream>

namespace bi = boost::interprocess;

int main() {
    // Create a shared memory object.
    bi::shared_memory_object shm(bi::open_only, "MySharedMemory", bi::read_write);

    try {
        // Map the whole shared memory in this process
        bi::mapped_region region(shm, bi::read_write);

        // Get the address of the mapped region
        void* addr {region.get_address()};

        // Obtain a pointer to the shared structure
        auto* data {static_cast<shm080::MessageBuffer*>(addr)};

        // Print messages until the other process marks the end
        bool end_loop {false};
        do {
            bi::scoped_lock<bi::interprocess_mutex> lock(data->mutex);
            if (!data->has_message) {
                data->cond_empty.wait(lock);
            }
            if (std::strcmp(data->message_contents, "last message") == 0) {
                end_loop = true;
            } else {
                // Print the message
                std::cout << data->message_contents << std::endl;
                // Notify the other process that the buffer is empty
                data->has_message = false;
                data->cond_full.notify_one();
            }
        } while (!end_loop);
    } catch (bi::interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

namespace shm080 {

namespace bi = boost::interprocess;

} // namespace shm080
