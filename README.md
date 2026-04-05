# BankQueue

A C++ command-line application for managing bank teller customer queues. Features dual interfaces for both customers and tellers, with queue management, transaction handling, and statistics tracking.

## Features

- **Dual Interface**: Separate menus for customers and tellers
- **Queue Management**: Regular and VIP customer queues with priority handling
- **Customer Transactions**: Deposit, withdrawal, transfer, payments, account viewing
- **Teller Operations**: Serve customers, register new customers, view queue status
- **Statistics Tracking**: Total customers served, average service time, peak queue length
- **Receipt Generation**: Automatic transaction receipts with timestamps
- **Data Persistence**: Customer data stored in text files

## What It Does

BankQueue simulates a bank teller system where:
- Customers can register, join queue, and perform transactions
- Tellers can serve next customers, view queue, and manage customer accounts
- The system tracks statistics and generates receipts for each transaction

## Building

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

## Running

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

## File Structure

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

## Requirements

- C++17 compatible compiler
- Linux or Windows OS
