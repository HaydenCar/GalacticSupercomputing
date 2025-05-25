# Galactic Supercomputing

An N-body simulation using high-performance computing and real-time 3D visualisation. This project models gravitational interactions between bodies using the **Barnes-Hut algorithm** and **Leapfrog integration**, accelerated with **OpenMP**, and visualised using **OpenGL**. Made as a third year group project.

---

## Group Members

- Hayden Carr  
- Ramazan Iskandarov  
- Isabella Sturzu

---

## Features

- **Barnes-Hut algorithm using Octree**
- **Leapfrog Integration**
- **Multithreaded with OpenMP**
- **3D Renderer using OpenGL (GLEW + GLFW + GLM)**

---

## Requirements

- Linux or macOS
- C++ compiler with OpenMP support
- [GLEW](http://glew.sourceforge.net/)
- [GLFW](https://www.glfw.org/)

---

## Build & Run

### 1. Run the simulation:
- cd parallel
- make
- ./main

### 2. Visualise the results:
- cd ../Engine
- make
- ./main

---

## Controls

- `z` — Zoom in  
- `x` — Zoom out  
- `0-9` — Focus on sun and planets:
  - `0`: Sun  
  - `1`: Earth  
  - `2`: Mercury  
  - `3`: Venus  
  - `4`: Mars  
  - `5`: Jupiter  
  - `6`: Saturn  
  - `7`: Uranus  
  - `8`: Neptune  
  - `9`: Pluto

---

## Results

![Simulation 1](https://github.com/HaydenCar/GalacticSupercomputing/blob/main/results/s-s.png)  
![Simulation 2](https://github.com/HaydenCar/GalacticSupercomputing/blob/main/results/test1.png)  
![Simulation 3](https://github.com/HaydenCar/GalacticSupercomputing/blob/main/results/test2.png)
