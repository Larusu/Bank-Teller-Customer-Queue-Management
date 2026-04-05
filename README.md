# 🏦 BankQueue

**BankQueue** is a C++ command-line application that simulates a bank teller queue system.  
It features separate interfaces for customers and tellers, along with queue management, transaction handling, and statistics tracking.

This project was developed as the **final project for Data Structures and Algorithms**, focusing on queue management, file handling, and modular program design.

## ✨ Features

- **Dual Interface**: Separate menus for customers and tellers
- **Queue Management**: Regular and VIP customer queues with priority handling
- **Customer Transactions**: Deposit, withdrawal, transfer, payments, account viewing
- **Teller Operations**: Serve customers, register new customers, view queue status
- **Statistics Tracking**: Total customers served, average service time, peak queue length
- **Receipt Generation**: Automatic transaction receipts with timestamps
- **Data Persistence**: Customer data stored in text files

## 🧠 What It Does

BankQueue simulates the workflow of a small bank teller system.

- Customers can **register**, **join the queue**, and **perform transactions**.
- Tellers can **serve customers**, **monitor queues**, and **manage customer accounts**.
- The system records **statistics** and generates **receipts** for each transaction.

This project demonstrates the use of **queues**, **file handling**, and **modular program design** in C++.

## 🧠 Concepts Demonstrated

- Queue data structures  
- Priority queue handling  
- File input/output  
- Object-oriented programming  
- Modular program design  
- Command-line interfaces

## 📦 Requirements

- C++17 compatible compiler
- Linux, macOS, or Windows operating system  

## 🏗️ Building

### Linux/macOS

```bash
make
```

### Windows (with CMake)

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## ▶️ Running

### Linux/macOS

```bash
./bank_teller
```

Or use the convenience command:
```bash
make run
```

### Windows

```bash
./bank_teller.exe
```

## 🗂️ File Structure

```
/
├── main.cpp              # Application entry point
├── Makefile              # Build configuration (Linux)
├── CMakeLists.txt        # Build configuration (CMake)
├── include/              # Header files
│   ├── AppController.h
│   ├── BankDetails.h
│   ├── Customer.h
│   ├── CustomerInterface.h
│   ├── QueueManager.h
│   ├── Statistics.h
│   ├── TellerInterface.h
│   └── Utils.h
├── src/                  # Source files
│   ├── AppController.cpp
│   ├── CustomerInterface.cpp
│   ├── QueueManager.cpp
│   ├── Statistics.cpp
│   ├── TellerInterface.cpp
│   └── Utils.cpp
└── data/                 # Runtime data (created on first run)
    ├── customer_queue_id/
    ├── customer_bank_id/
    ├── customer_receipts/
    ├── vip_names.txt
    └── RegisteredCustomers.txt
```
## 🚀 Future Improvements

- Store data using a database instead of text files
- Implement real-time queue updates
- Add transaction history search
