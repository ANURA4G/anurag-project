#include <stdio.h>
#include "passenger.h"

#define MAX_TRAINS 100
int main() {
    Queue q;
    Train trains[MAX_TRAINS];
    int train_count = 0;
    initQueue(&q);
    int choice;
    loadQueueFromFile(&q);
    while (1) {
        printf("\n--- Railway Station Platform Management System ---\n");
        printf("1. Add Train\n");
        printf("2. Display Trains\n");
        printf("3. Search Train\n");
        printf("4. Add Passenger\n");
        printf("5. Serve (Dequeue) Passenger\n");
        printf("6. Display Passenger Queue\n");
        printf("7. Search Passenger\n");
        printf("8. Save Queue to File\n");
        printf("9. Load Queue from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n'); // clear input buffer
        switch (choice) {
            case 1:
                addTrain(trains, &train_count);
                break;
            case 2:
                displayTrains(trains, train_count);
                break;
            case 3:
                searchTrain(trains, train_count);
                break;
            case 4: {
                if (train_count == 0) {
                    printf("Add a train first!\n");
                    break;
                }
                Passenger *p = createPassenger();
                printf("Enter Train Number for this passenger: ");
                scanf("%d", &p->train_no);
                while(getchar() != '\n');
                if (findTrainIndex(trains, train_count, p->train_no) == -1) {
                    printf("Invalid train number! Passenger not added.\n");
                    free(p);
                    break;
                }
                if (p->priority)
                    enqueuePriority(&q, p);
                else
                    enqueue(&q, p);
                break;
            }
            case 5:
                dequeue(&q);
                break;
            case 6:
                displayQueue(&q);
                break;
            case 7:
                searchPassenger(&q);
                break;
            case 8:
                saveQueueToFile(&q);
                break;
            case 9:
                loadQueueFromFile(&q);
                break;
            case 0:
                saveQueueToFile(&q);
                printf("Exiting...\n");
                while (q.front) dequeue(&q);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
