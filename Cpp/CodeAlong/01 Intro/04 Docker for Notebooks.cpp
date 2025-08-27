// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Docker for Notebooks</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 04 Docker for Notebooks.cpp -->
// <!-- slides/module_110_introduction/topic_170_docker_for_notebooks.cpp -->
//
//

// %% [markdown]
//
// ## Docker Images for Notebooks
//
// ```bash
// docker pull mhoelzl/cam-cpp-notebook:latest
// docker run -p 8888:8888 -v /path/to/slides:/root/course mhoelzl/cam-cpp-notebook:latest
// ```
//
// - `/path/to/slides` is the absolute path to the folder containing the slides on your computer
// - On Windows this path typically starts with `C:\Users\...`
// - The path `/root/course` must remain exactly as it is (including the colon)
// - You can also specify a parameter `--name <name>` to give a name to the container

// %% [markdown]
//
// - To access the notebooks:
//   - URL: [http://localhost:8888]
//   - Password: `CAM`
