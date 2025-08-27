// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Docker Intro</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 03 Docker Intro.cpp -->
// <!-- slides/module_110_introduction/topic_160_docker_intro.cpp -->


// %% [markdown]
//
// ## Docker
// - Docker is a container runtime environment
// - Download: [Docker Website](https://www.docker.com/products/docker-desktop/)
// - Test: `docker info`

// %% [markdown]
//
// ## Docker Images
//
// - Docker images are templates for containers
// - They contain all the necessary information to start a container
// - You can download Docker images from a Docker registry
// - The official registry is [Docker Hub](https://hub.docker.com/)
// - You can also create your own Docker images
// - But this is not necessary to use the Docker images for the course

// %% [markdown]
//
// ## Downloading and Running Docker Images
//
// - `docker pull hello-world`
// - `docker run hello-world`

// %% [markdown]
//
// ## Docker Images for the Course
//
// - You can download the Docker images for the course with the following commands:
// - `docker pull mhoelzl/cam-cpp-notebook:latest`
// - `docker pull mhoelzl/cam-cpp-dev:latest`
// - The images are relatively large because they contain a complete development
//   environment
// - We will see in later videos how you can use the images
