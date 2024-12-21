# Metalmax - Electrical Network Diagnosis

## 📋 Problem Description

Metalmax, a major steel company, uses a complex electrical network consisting of:
- **Generators**: Points that supply energy to the network.
- **Consumers**: Points that consume energy, with specific demands.
- **Connections**: Unidirectional paths in the network with maximum transmission capacities.

The program performs the following analyses:
1. **Maximum Network Capacity**: Determines the network's operational capacity.
2. **Unmet Energy Demand**: Calculates the amount of energy insufficient to meet demands.
3. **Energy Loss**: Measures the amount of energy lost in the network.
4. **Critical Connections**: Identifies connections operating at maximum capacity.

## 🔧 Implementation

- Language: **C++**
- Main data structure: **Graphs**
- Algorithms used:
  - Maximum Flow (**Edmonds-Karp**)
  - Bottleneck identification in graphs
  - Demand and energy loss calculations
