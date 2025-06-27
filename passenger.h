#ifndef PASSENGER_H
#define PASSENGER_H

#define NAME_LEN 50
#define ID_LEN 20
#define FILENAME "queue_data.txt"
#define MAX_TRAINS 100

#include <stdio.h>

// Train structure
typedef struct Train {
    int train_no;
    char train_name[NAME_LEN];
    char arrival_time[10];
    char departure_time[10];
    int platform_no;
} Train;

// Train management functions
void addTrain(Train trains[], int *train_count);
void displayTrains(Train trains[], int train_count);
int findTrainIndex(Train trains[], int train_count, int train_no);
void searchTrain(Train trains[], int train_count);

// Updated Passenger structure to link to train
typedef struct Passenger {
    char name[NAME_LEN];
    char id[ID_LEN];
    int age;
    int priority; // 1 for priority, 0 for normal
    int train_no; // Link passenger to a train
    struct Passenger *next;
} Passenger;

typedef struct Queue {
    Passenger *front;
    Passenger *rear;
} Queue;

void initQueue(Queue *q);
Passenger* createPassenger();
void enqueue(Queue *q, Passenger *p);
void enqueuePriority(Queue *q, Passenger *p);
void dequeue(Queue *q);
void displayQueue(Queue *q);
void searchPassenger(Queue *q);
void saveQueueToFile(Queue *q);
void loadQueueFromFile(Queue *q);
int isValidName(const char *name);
int isValidID(const char *id);

#endif // PASSENGER_H
