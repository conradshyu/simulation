# Particle WebAssembly Project

This project implements an ideal particle simulation in C++ and compiles it to WebAssembly using Emscripten.

## Prerequisites

- Emscripten SDK
- C++17 compiler

## Build

```bash
em++ particle_sim.cpp \
  -O3 \
  --bind \
  -s MODULARIZE=0 \
  -o particle.js
```

This generates:

```bash
- particle.js
- particle.wasm
```

## Run Locally

Start a web server inside the project directory:

```bash
python3 -m http.server 8000
```

Open:

`http://localhost:8000`

## Simulation Model

- Particles move with constant velocity.
- No inter-particle forces.
- Elastic wall reflections.
- Suitable as a simple ideal gas style demonstration.

## Files

- particle_sim.cpp : C++ WebAssembly source
- index.html : Browser visualization
- README.md : Deployment instructions
