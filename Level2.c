#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int start;
    int end;
} Interval;

int compareIntervals(const void* a, const void* b) {
    Interval* i1 = (Interval*)a;
    Interval* i2 = (Interval*)b;
    return i1->start - i2->start;
}

void mergeIntervals(Interval* intervals, int* size, Interval newInterval) {
    
    intervals[*size] = newInterval;
    (*size)++;
    
    
    qsort(intervals, *size, sizeof(Interval), compareIntervals);
    
    
    int writeIndex = 1;
    for (int readIndex = 1; readIndex < *size; readIndex++) {
        if (intervals[readIndex].start <= intervals[writeIndex - 1].end) {
            intervals[writeIndex - 1].end = (intervals[writeIndex - 1].end > intervals[readIndex].end) ? intervals[writeIndex - 1].end : intervals[readIndex].end;
        } else {
            intervals[writeIndex++] = intervals[readIndex];
        }
    }
    
    
    *size = writeIndex;
}


void printIntervals(Interval* intervals, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("[%d, %d]", intervals[i].start, intervals[i].end);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int capacity = 100;
    Interval* intervals = (Interval*)malloc(capacity * sizeof(Interval));
    int size = 0;
    
    
    int choice;
    while (1) {
        printf("\n1. Add interval\n");
        printf("2. Get intervals\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int start, end;
                printf("Enter start of interval: ");
                scanf("%d", &start);
                printf("Enter end of interval: ");
                scanf("%d", &end);
                Interval newInterval = {start, end};
                mergeIntervals(intervals, &size, newInterval);
                break;
            }
            case 2:
                printf("Current intervals: ");
                printIntervals(intervals, size);
                break;
            case 3:
                free(intervals);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
