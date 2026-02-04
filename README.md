# Travelers-ECS

---

## Overview

**Travelers-ECS** is a cross-platform Entity Component System (ECS) written in C++17.  
The goal is to provide a simple, lightweight, and high-performance ECS implementation.

---

## 🚧 Current Development Status

I have achieved excellent performance for entity creation and destruction, as well as component and tag addition, removal, and access.

Queries currently have decent performance, but they're not yet at the same level as other operations. Query time complexity is O(n) based on the number of entities in archetypes matching the query. I already have several ideas to optimize this further.

---

## 📊 Benchmarks

Performance benchmarks across platforms:

**Test Hardware:**
- **CPU:** Intel Core i7-12700K
- **RAM:** 32GB @ 4400MHz
- **Storage:** SSD

> 📁 **Benchmark repository:** [Travelers-ECS-Benchmark](https://github.com/Smalleater/Travelers-ECS-Benchmark)

### 1,000 Entities
| Operation | Windows | Linux |
|-----------|---------|-------|
| Create entity | 30 ns | 26 ns |
| Destroy entity | 16 ns | 11 ns |
| Add tag | 22 ns | 13 ns |
| Remove tag | 21 ns | 9 ns |
| Add component | 118 ns | 135 ns |
| Remove component | 82 ns | 84 ns |
| Get component | 45 ns | 27 ns |
| Set component | 31 ns | 24 ns |
| Update system | 31.0 µs | 21.2 µs |

### 10,000 Entities
| Operation | Windows | Linux |
|-----------|---------|-------|
| Create entity | 21 ns | 26 ns |
| Destroy entity | 14 ns | 10 ns |
| Add tag | 22 ns | 13 ns |
| Remove tag | 21 ns | 9 ns |
| Add component | 91 ns | 101 ns |
| Remove component | 81 ns | 85 ns |
| Get component | 45 ns | 27 ns |
| Set component | 30 ns | 23 ns |
| Update system | 308.6 µs | 229.5 µs |

### 100,000 Entities
| Operation | Windows | Linux |
|-----------|---------|-------|
| Create entity | 34 ns | 26 ns |
| Destroy entity | 16 ns | 12 ns |
| Add tag | 23 ns | 13 ns |
| Remove tag | 21 ns | 9 ns |
| Add component | 88 ns | 100 ns |
| Remove component | 80 ns | 86 ns |
| Get component | 45 ns | 28 ns |
| Set component | 29 ns | 24 ns |
| Update system | 3.47 ms | 2.49 ms |

> **Note:** Linux generally shows better performance for most operations, particularly for tags and system updates.  
> System update times are O(n) relative to the number of entities in archetypes matching the query.  
> During tests, queries typically returned all entities used in the test (worst-case scenario).

---

## ⚙️ Technologies

* **Language:** C++17
* **Platforms:** Windows and Linux
* **Compilers:** MSVC for Windows, GCC for Linux

---

## 📘 Learning Purpose

This project is part of a personal journey to learn and improve my skills in **C++** and **engine architecture**.  
The ECS library is developed with learning, experimentation, and long-term improvement in mind.  
New features and enhancements will continue to be added as I explore and grow.

---

## 📫 Contact

For questions, suggestions, or feedback:  
📬 [My GitHub profile](https://github.com/Smalleater)
