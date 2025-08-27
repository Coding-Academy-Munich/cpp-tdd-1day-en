// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Docker Images</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 06 Docker Images.cpp -->
// <!-- slides/module_110_introduction/topic_164_docker_images.cpp -->


// %% [markdown]
//
// ## Starting the Docker images manually
//
// - You can also start the images manually if you don't want to use the
//   devcontainer
//
// ```bash
// docker pull mhoelzl/cam-cpp-dev:latest
// docker run -it --rm -v /path/to/code:/root/course mhoelzl/cam-cpp-dev:latest
// ```
//
// - Replace `/path/to/code` with the absolute path to the `code` folder

// %% [markdown]
//
// ### Creating the projects in the container
//
// ```bash
// cd /root/course
// cmake --preset linux-clang
// cmake --build out/build/linux-clang --target hello_world
// ./out/build/linux-clang/completed/hello_world/hello_world
// ```

// %% [markdown]
//
// ### Creating `blocks_sk` (native build)
//
// `blocks_sk` can be built in the container, but cannot be run without additional
// configuration:
//
// ```bash
// cd /root/course
// cmake --preset linux-clang
// cmake --build out/build/linux-clang/ --target blocks_sk
// ./out/build/linux-clang/starter_kits/blocks_sk/blocks_sk # Schlägt fehl
// ```
//
// The configuration of X11 forwarding is beyond the scope of this course.

// %% [markdown]
//
// ### Creating `blocks_sk` (Web build)
//
// Alternatively, `blocks_sk` can also be built as a web application:
//
// ```bash
// cd /root/course
// source /root/emsdk/emsdk_env.sh
// emcmake cmake --preset=web-debug
// emmake cmake --build ./out/build/web-debug --target blocks_sk
// cd out/build/web-debug/starter_kits/blocks_sk
// python -m http.server
// ```

// %% [markdown]
//
// To access the web application, the Docker image must be started with the option
// `-p 8000:8000`:
//
// ```bash
// docker run -it --rm -p 8000:8000 -v /path/to/code:/root/course mhoelzl/cam-cpp-dev:latest
// ```
//
// Then open [http://localhost:8000/blocks_sk.html] in the browser

