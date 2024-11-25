# Sorting-a-Vector-with-Parallel-Virtual-Machines-in-C

This repository demonstrates the use of PVM (Parallel Virtual Machine) to implement parallel sorting of an integer vector using the Quick Sort algorithm. The project is divided into a master process and multiple slave processes. The master coordinates the workload distribution, while the slaves independently sort portions of the vector in parallel.

💡 Motivation
Sorting large datasets can be computationally expensive. By leveraging PVM, this project distributes the sorting workload across multiple processes (potentially on different hosts), enabling efficient parallel processing. It showcases the practical use of PVM for task coordination and message passing in a distributed system.

🚀 Project Structure
The repository contains the following key files:

ordena.c: The master program that divides the vector, spawns parallel tasks, and merges the sorted sub-vectors.
quick.c: The slave program that performs the Quick Sort on its assigned portion of the vector.
Makefile: A build script for compiling the programs.
🛠️ How It Works
Data Division:

The master program divides the main vector into equal-sized sub-vectors.
Each sub-vector is sent to a slave process for sorting.
Parallel Quick Sort:

The slave program receives a sub-vector and applies the Quick Sort algorithm.
The sorted sub-vector is sent back to the master.
Merging:

The master program collects the sorted sub-vectors from all slaves and merges them into a fully sorted vector.
📂 Repository Contents
ordena.c:

Manages the vector division, task spawning, message passing, and merging.
Uses the PVM library to communicate with slave processes.
quick.c:

Implements the Quick Sort algorithm on a portion of the vector received from the master.
Sends the sorted results back to the master.
Makefile:

Facilitates easy compilation of the source files.
🛠️ Setup and Execution
Requirements
PVM3 Library installed on your machine.
A Unix-based system (tested on Ubuntu and CentOS).
GCC (GNU Compiler Collection).
Compilation
Compile the programs using the provided Makefile:

bash
Copiar código
make ordena
make quick
Alternatively, you can compile manually:

bash
Copiar código
gcc -o ordena ordena.c -lpvm3
gcc -o quick quick.c -lpvm3
Execution
Start the PVM Daemon:

bash
Copiar código
pvm
Inside the PVM console, ensure the machine configuration is correct:

pvm
Copiar código
conf
Run the Master Program:

bash
Copiar código
./ordena
The master program will spawn the slave processes, distribute the vector, and handle the sorting.

🔍 Example Output
For an input vector:

csharp
Copiar código
[9, 7, 5, 3, 1, 8, 6, 4, 2, 0]
The program outputs:

less
Copiar código
Sorted Vector: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
Execution Time (µs): 123456
📖 Learning Outcomes
This project highlights:

Parallel processing using PVM.
Implementing Quick Sort in distributed environments.
Coordination of tasks and message passing.
🧑‍💻 Contributing
Contributions are welcome! Feel free to submit issues or pull requests to enhance this project.

📜 License
This project is licensed under the MIT License. See the LICENSE file for details.

🖇️ References
PVM Official Documentation
Quick Sort Algorithm
