#include "passenger.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

Passenger* createPassenger() {
    Passenger *p = (Passenger*)malloc(sizeof(Passenger));
    if (!p) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    char temp[100];
    printf("Enter Passenger Name: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    while (!isValidName(temp)) {
        printf("Invalid name. Enter again: ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = 0;
    }
    strncpy(p->name, temp, NAME_LEN);

    printf("Enter Passenger ID: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    while (!isValidID(temp)) {
        printf("Invalid ID. Enter again: ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = 0;
    }
    strncpy(p->id, temp, ID_LEN);

    printf("Enter Age: ");
    while (scanf("%d", &p->age) != 1 || p->age <= 0) {
        printf("Invalid age. Enter again: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    printf("Is this a priority passenger? (1=Senior/Emergency, 0=Normal): ");
    while (scanf("%d", &p->priority) != 1 || (p->priority != 0 && p->priority != 1)) {
        printf("Invalid input. Enter 1 for priority, 0 for normal: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    printf("Enter Train Number: ");
    while (scanf("%d", &p->train_no) != 1 || p->train_no <= 0) {
        printf("Invalid train number. Enter again: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    p->next = NULL;
    return p;
}

void enqueue(Queue *q, Passenger *p) {
    if (q->rear == NULL) {
        q->front = q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
    printf("Passenger added to queue.\n");
}

void enqueuePriority(Queue *q, Passenger *p) {
    if (q->front == NULL || q->front->priority == 0) {
        p->next = q->front;
        q->front = p;
        if (q->rear == NULL) q->rear = p;
    } else {
        Passenger *curr = q->front;
        while (curr->next && curr->next->priority == 1) {
            curr = curr->next;
        }
        p->next = curr->next;
        curr->next = p;
        if (p->next == NULL) q->rear = p;
    }
    printf("Priority passenger added to queue.\n");
}

void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    Passenger *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    printf("Passenger %s (ID: %s) removed from queue.\n", temp->name, temp->id);
    free(temp);
}

void displayQueue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("\n--- Passenger Queue ---\n");
    Passenger *curr = q->front;
    int pos = 1;
    while (curr) {
        printf("%d. Name: %s | ID: %s | Age: %d | %s | Train No: %d\n", pos++, curr->name, curr->id, curr->age, curr->priority ? "PRIORITY" : "Normal", curr->train_no);
        curr = curr->next;
    }
}

void searchPassenger(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    char key[NAME_LEN];
    printf("Enter Name, ID, or Train Number to search: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;
    Passenger *curr = q->front;
    int found = 0, pos = 1;
    while (curr) {
        if (strcasecmp(curr->name, key) == 0 || strcasecmp(curr->id, key) == 0 || atoi(key) == curr->train_no) {
            printf("Found at position %d: Name: %s | ID: %s | Age: %d | %s | Train No: %d\n", pos, curr->name, curr->id, curr->age, curr->priority ? "PRIORITY" : "Normal", curr->train_no);
            found = 1;
        }
        curr = curr->next;
        pos++;
    }
    if (!found) printf("Passenger not found.\n");
}

void saveQueueToFile(Queue *q) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("Error opening file for saving!\n");
        return;
    }
    Passenger *curr = q->front;
    while (curr) {
        fprintf(fp, "%s,%s,%d,%d,%d\n", curr->name, curr->id, curr->age, curr->priority, curr->train_no);
        curr = curr->next;
    }
    fclose(fp);
    printf("Queue saved to file.\n");
}

void loadQueueFromFile(Queue *q) {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("No saved queue found.\n");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        Passenger *p = (Passenger*)malloc(sizeof(Passenger));
        if (!p) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        sscanf(line, "%49[^,],%19[^,],%d,%d,%d", p->name, p->id, &p->age, &p->priority, &p->train_no);
        p->next = NULL;
        if (p->priority)
            enqueuePriority(q, p);
        else
            enqueue(q, p);
    }
    fclose(fp);
    printf("Queue loaded from file.\n");
}

int isValidName(const char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i]; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return 0;
    }
    return 1;
}

int isValidID(const char *id) {
    if (strlen(id) == 0) return 0;
    for (int i = 0; id[i]; i++) {
        if (!isalnum(id[i])) return 0;
    }
    return 1;
}

// Train management functions
void addTrain(Train trains[], int *train_count) {
    if (*train_count >= MAX_TRAINS) {
        printf("Train list is full!\n");
        return;
    }
    Train *t = &trains[*train_count];
    printf("Enter Train Number: ");
    scanf("%d", &t->train_no);
    while(getchar() != '\n');
    printf("Enter Train Name: ");
    fgets(t->train_name, NAME_LEN, stdin);
    t->train_name[strcspn(t->train_name, "\n")] = 0;
    printf("Enter Arrival Time (HH:MM): ");
    fgets(t->arrival_time, sizeof(t->arrival_time), stdin);
    t->arrival_time[strcspn(t->arrival_time, "\n")] = 0;
    printf("Enter Departure Time (HH:MM): ");
    fgets(t->departure_time, sizeof(t->departure_time), stdin);
    t->departure_time[strcspn(t->departure_time, "\n")] = 0;
    printf("Enter Platform Number: ");
    scanf("%d", &t->platform_no);
    while(getchar() != '\n');
    (*train_count)++;
    printf("Train added successfully!\n");
}

void displayTrains(Train trains[], int train_count) {
    if (train_count == 0) {
        printf("No trains available.\n");
        return;
    }
    printf("\n--- Train List ---\n");
    for (int i = 0; i < train_count; i++) {
        printf("%d. Train No: %d | Name: %s | Arrival: %s | Departure: %s | Platform: %d\n",
            i+1, trains[i].train_no, trains[i].train_name, trains[i].arrival_time, trains[i].departure_time, trains[i].platform_no);
    }
}

int findTrainIndex(Train trains[], int train_count, int train_no) {
    for (int i = 0; i < train_count; i++) {
        if (trains[i].train_no == train_no) return i;
    }
    return -1;
}

void searchTrain(Train trains[], int train_count) {
    int train_no;
    printf("Enter Train Number to search: ");
    scanf("%d", &train_no);
    while(getchar() != '\n');
    int idx = findTrainIndex(trains, train_count, train_no);
    if (idx == -1) {
        printf("Train not found.\n");
    } else {
        Train *t = &trains[idx];
        printf("Train No: %d | Name: %s | Arrival: %s | Departure: %s | Platform: %d\n",
            t->train_no, t->train_name, t->arrival_time, t->departure_time, t->platform_no);
    }
}
