// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Ports and Adapters Architecture</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 06 Ports and Adapters Architecture.cpp -->
// <!-- slides/module_500_solid_grasp/topic_600_ports_and_adapters.cpp -->


// %% [markdown]
//
// ## What is Ports and Adapters Architecture?
//
// - Also known as **Hexagonal Architecture**.
// - An architectural pattern that decouples the **application core logic** from
//   the **outside world** (infrastructure).
// - The core logic should know nothing about its environment.

// %% [markdown]
//
// ## Ports and Adapters Architecture
//
// <img src="img/ports-and-adapters-01.png"
//      style="display:block;margin:auto;width:40%"/>

// %% [markdown]
//
// <img src="img/ports-and-adapters-01.png"
//      style="float: right; margin-left: 10px; width: 20%;"/>
//
// ## The Core Components
//
// 1. **Hexagon (inner layers):**
//    - Domain models, business logic, use cases.
//    - Technology-agnostic.
// 2. **Hexagon (outer layer):**
//    - Infrastructure.
//    - GUI, databases, APIs, file systems.
// 3. **Ports (interfaces):**
//    - Define how to communicate with the inner layers.
// 4. **Adapters:**
//    - Technology-specific implementations of the ports.
//    - Translate between the two layers.

// %% [markdown]
//
// ## Dependency Structure
//
// <img src="img/ports-and-adapters-02.png"
//      style="display:block;margin:auto;width:40%"/>

// %% [markdown]
//
// ### Ports: Driving vs. Driven
//
// - **Primary Ports (inbound or driving ports):**
//   - Define the **API of the application core**.
//   - Are called by the outside world to "drive" the application.
//   - Example: A REST service that places an order.
// - **Outbound Ports (Driven Ports):**
//   - Define the **needs of the application core**.
//   - Are called by the core to communicate with the outside world.
//   - Example: A database interface that stores an order.
// - This distinction is not always meaningful.

// %% [markdown]
//
// ## ⬡ + TDD: A Perfect Match
//
// - Inner layers can be fully tested in isolation.
// - Tests often lead to primary ports.
// - Outbound ports are often implemented with test doubles.
// - Outside-In TDD and London School often lead to a port-and-adapter structure

// %% [markdown]
//
// - ## Related Architectures
//
// - [Onion
// Architecture](https://jeffreypalermo.com/2008/07/the-onion-architecture-part-1/)
// - Clean Architecture
