# CPU Scheduling Simulator

This project is a simulator for various CPU scheduling algorithms, implemented in C++. It allows you to visualize and understand how different scheduling algorithms manage process execution in a CPU.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Algorithms Implemented](#algorithms-implemented)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

CPU scheduling is a fundamental aspect of operating systems that determines which processes run at any given time. This simulator provides a hands-on way to explore and compare different scheduling strategies. It is particularly useful for students and professionals who want to understand the intricacies of CPU scheduling.

## Features

- **Multiple Scheduling Algorithms:** The simulator includes a variety of common CPU scheduling algorithms.
- **Process Visualization:** Visualize how processes are scheduled over time.
- **Customizable Inputs:** Input your own set of processes and burst times to see how they are handled by different algorithms.
- **Performance Metrics:** Calculate and display metrics such as average waiting time and turnaround time.

## Algorithms Implemented

The following CPU scheduling algorithms are implemented in this simulator:

1. **First-Come, First-Served (FCFS):**
   - Non-preemptive scheduling algorithm.
   - Processes are executed in the order they arrive.

2. **Shortest Job Next (SJN) / Shortest Job First (SJF):**
   - Non-preemptive scheduling algorithm.
   - The process with the shortest burst time is executed next.

3. **Priority Scheduling:**
   - Can be preemptive or non-preemptive.
   - Processes are executed based on priority. Higher priority processes are executed first.

4. **Round Robin (RR):**
   - Preemptive scheduling algorithm.
   - Each process is given a fixed time slice (quantum) in a cyclic order.

5. **Shortest Remaining Time (SRT):**
   - Preemptive version of SJF.
   - The process with the shortest remaining burst time is executed next.

6. **Multilevel Queue Scheduling:**
   - Processes are divided into multiple queues based on priority.
   - Each queue may have its own scheduling algorithm.

7. **Multilevel Feedback Queue Scheduling:**
   - Similar to multilevel queue scheduling but allows processes to move between queues based on their behavior and aging.

## Installation

To run the CPU Scheduling Simulator, you need to have a C++ compiler installed on your machine. Follow these steps to set up the project:

1. Clone the repository:
   ```bash
   git clone https://github.com/osaidnur/CPU-Scheduling-Simulator.git
   cd CPU-Scheduling-Simulator
    ```
2. Compile the Code:
    ```bash
    g++ -o cpu_scheduler main.cpp scheduler.cpp
3. Run the simulator:
```bash
./cpu_scheduler 
```

## Usage

Once the simulator is running, you can input your own set of processes. Follow the prompts to enter process details such as arrival time, burst time, and priority. The simulator will then display the scheduling results for the selected algorithm.

Example input:
```
Enter the number of processes: 3
Enter the details for process 1 (arrival time, burst time, priority): 0 5 2
Enter the details for process 2 (arrival time, burst time, priority): 1 3 1
Enter the details for process 3 (arrival time, burst time, priority): 2 8 3
```
The simulator will output the scheduling order, waiting times, turnaround times, and other relevant metrics.

