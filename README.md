# Railway Station Platform Management System

This project is a C-based console application for managing trains and passenger queues at a railway station. It supports adding/searching trains, managing a priority-based passenger queue, and saving/loading queue data to a file.

## Features

- Add Train: Register new trains in the system
- Display Trains: View all registered trains
- Search Train: Find a train by its number
- Add Passenger: Add a passenger to the queue (with priority support)
- Serve Passenger: Dequeue the next passenger (priority served first)
- Display Passenger Queue: View all passengers in the queue
- Search Passenger: Find a passenger in the queue
- Save/Load Queue: Persist the passenger queue to a file (`queue_data.txt`)

## Files

- `main.c` — Main program with menu-driven interface
- `passenger.c` — Passenger and queue management logic
- `passenger.h` — Header file for passenger and queue functions
- `queue_data.txt` — Data file for saving/loading the passenger queue
- `railway_station_management.exe` — Compiled executable (Windows)

## How to Compile

Open a terminal in the project directory and run:

```sh
gcc main.c passenger.c -o railway_station_management.exe
```

## How to Run

```sh
./railway_station_management.exe
```
Or double-click the executable on Windows.

## Requirements

- GCC compiler (for building from source)
- Windows OS (for provided executable)

## Usage

Follow the on-screen menu to manage trains and passengers. Data is saved to `queue_data.txt` for persistence.
