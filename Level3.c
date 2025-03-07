#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct CacheEntry {
    char* key;
    char* value;
    time_t expiryTime;
    struct CacheEntry* next;
} CacheEntry;


typedef struct Cache {
    int size;
    CacheEntry** entries;
} Cache;

// Function to create a new cache entry
CacheEntry* createCacheEntry(const char* key, const char* value, time_t expiryTime) {
    CacheEntry* entry = (CacheEntry*)malloc(sizeof(CacheEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->expiryTime = expiryTime;
    entry->next = NULL;
    return entry;
}


Cache* createCache(int size) {
    Cache* cache = (Cache*)malloc(sizeof(Cache));
    cache->size = size;
    cache->entries = (CacheEntry**)calloc(size, sizeof(CacheEntry*));
    return cache;
}

int hash(const char* key, int size) {
    int hashValue = 0;
    for (int i = 0; key[i]; i++) {
        hashValue += key[i];
    }
    return hashValue % size;
}

void set(Cache* cache, const char* key, const char* value, time_t expiryTime) {
    int index = hash(key, cache->size);
    CacheEntry* current = cache->entries[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            current->expiryTime = expiryTime;
            return;
        }
        current = current->next;
    }
    
    
    CacheEntry* newEntry = createCacheEntry(key, value, expiryTime);
    newEntry->next = cache->entries[index];
    cache->entries[index] = newEntry;
}

char* get(Cache* cache, const char* key) {
    int index = hash(key, cache->size);
    CacheEntry* current = cache->entries[index];
    
    
    while (current != NULL && current->next != NULL) {
        if (current->next->expiryTime < time(NULL)) {
            CacheEntry* expired = current->next;
            current->next = expired->next;
            free(expired->key);
            free(expired->value);
            free(expired);
        } else {
            current = current->next;
        }
    }
    
    
    current = cache->entries[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0 && current->expiryTime >= time(NULL)) {
            return current->value;
        }
        current = current->next;
    }
    
    return NULL;
}


void printCache(Cache* cache) {
    for (int i = 0; i < cache->size; i++) {
        CacheEntry* current = cache->entries[i];
        printf("Index %d:\n", i);
        while (current != NULL) {
            printf("Key: %s, Value: %s, Expiry Time: %ld\n", current->key, current->value, current->expiryTime);
            current = current->next;
        }
    }
}

int main() {
    Cache* cache = createCache(10);
    
    int choice;
    
    while (1) {
        printf("\n1. Set key-value pair\n");
        printf("2. Get value by key\n");
        printf("3. Print cache entries\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                char key[100], value[100];
                int expiryTimeSecs;

                printf("Enter key: ");
                scanf("%s", key);

                printf("Enter value: ");
                scanf("%s", value);

                while (1) { 
                    printf("Enter expiry time in seconds: ");
                    if (scanf("%d", &expiryTimeSecs) == 1 && expiryTimeSecs > 0) break; 
                    else printf("Invalid input. Please enter a positive integer.\n");
                }

                time_t expiryTime = time(NULL) + expiryTimeSecs; 
                set(cache, key, value, expiryTime);

                break;
            }
            case 2: {
                char key[100];
                printf("Enter key: ");
                scanf("%s", key);

                char* value = get(cache, key);
                if (value != NULL)
                    printf("Value for key '%s': %s\n", key, value);
                else
                    printf("Key '%s' does not exist or has expired.\n", key);

                break;
            }
            case 3:
                printCache(cache);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    
    for (int i = 0; i < cache->size; i++) {
        CacheEntry* current = cache->entries[i];
        while (current != NULL) {
            CacheEntry* next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }

    free(cache->entries);
    free(cache);

    return 0;
}
