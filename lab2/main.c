#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_QUEUE_SIZE 10000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

typedef struct {
    WordCount data[MAX_QUEUE_SIZE];
    int head;
    int tail;
} Queue;

void initQueue(Queue *q) {
    q->head = 0;
    q->tail = -1;
}

WordCount dequeue(Queue *q) {
    WordCount wc = q->data[q->head];
    q->head++;
    return wc;
}

int isQueueEmpty(Queue q) {
    return (q.head > q.tail);
}

int isAlpha(char c) {
    return (isalpha(c) || c == '-');
}

void removePunctuations(char *word) {
    int len = strlen(word);
    while (len > 0 && !isalpha(word[len - 1])) {
        word[len - 1] = '\0';
        len--;
    }
}

int isQueueFull(Queue *q) {
    return q->tail == MAX_QUEUE_SIZE - 1;
}

void enqueue(Queue *q, WordCount item) {
    if (isQueueFull(q)) {
        printf("Queue is full.\n");
        exit(1);
    }
    q->tail++;
    q->data[q->tail] = item;
}

void sortByLength(Queue *queue) {
    int i, j;
    WordCount temp;
    for (i = queue->head; i <= queue->tail; i++) {
        for (j = i+1; j <= queue->tail; j++) {
            if (strlen(queue->data[i].word) > strlen(queue->data[j].word)) {
                temp = queue->data[i];
                queue->data[i] = queue->data[j];
                queue->data[j] = temp;
            }
        }
    }
}


void desSortByLength(Queue *queue) {
    int i, j;
    WordCount temp;
    for (i = queue->head; i <= queue->tail; i++) {
        for (j = i+1; j <= queue->tail; j++) {
            if (strlen(queue->data[i].word) < strlen(queue->data[j].word)) {
                temp = queue->data[i];
                queue->data[i] = queue->data[j];
                queue->data[j] = temp;
            }
        }
    }
}



int main() {
    int maxShortWordLength, maxShortWordOccurrence, minLongWordLength, minLongWordOccurrence;
    printf("Enter the maximum length of short words: ");
    scanf("%d", &maxShortWordLength);
    printf("Enter the maximum occurrence of short words: ");
    scanf("%d", &maxShortWordOccurrence);
    printf("Enter the minimum length of long words: ");
    scanf("%d", &minLongWordLength);
    printf("Enter the minimum occurrence of long words: ");
    scanf("%d", &minLongWordOccurrence);

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Queue shortWords, longWords;
    initQueue(&shortWords);
    initQueue(&longWords);

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        int wordLen = strlen(word);
        if (wordLen <= maxShortWordLength) {
            int isAlphaOnly = 1;
            for (int i = 0; i < wordLen; i++) {
                if (!isAlpha(word[i])) {
                    isAlphaOnly = 0;
                    break;
                }
            }
            if (isAlphaOnly) {
                removePunctuations(word);
                int found = 0;
                for (int i = shortWords.head; i <= shortWords.tail; i++) {
                    if (strcmp(shortWords.data[i].word, word) == 0) {
                        shortWords.data[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    WordCount wc;
                    strcpy(wc.word, word);
                    wc.count = 1;
                    enqueue(&shortWords, wc);
                }
            }
        } else if (wordLen >= minLongWordLength) {
            int isAlphaOnly = 1;
            for (int i = 0; i < wordLen; i++) {
                if (!isAlpha(word[i])) {
                    isAlphaOnly = 0;
                    break;
                }
            }
            if (isAlphaOnly) {
                removePunctuations(word);
                int found = 0;
                for (int i = longWords.head; i <= longWords.tail; i++) {
                    if (strcmp(longWords.data[i].word, word) == 0) {
                        longWords.data[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    WordCount wc;
                    strcpy(wc.word, word);
                    wc.count = 1;
                    enqueue(&longWords, wc);
                }
            }
        }
    }

    sortByLength(&shortWords);
    desSortByLength(&longWords);

    FILE* NewFile = fopen("compress.txt","w+");
    char buffer[1024];
    size_t num;
    while((num = fread(buffer, sizeof(char), 1024, file)) > 0)  //чтение копируемого файла до конца
    {
        fwrite(buffer, sizeof(char), num, NewFile);//запись копии в новый файл
    }
    /*
  while(fgets(buffer,512,file) != NULL){
        int i = 0;
        while(!isQueueEmpty(longWords)) {
            char *pos, temp[512];
            int index = 0;
            // Пока находим вхождения подстроки
            while ((pos = strstr(buffer, shortWords.data[i].word)) != NULL) {
                // Копируем все до начала вхождения
                strncpy(temp + index,buffer, pos - buffer);
                index += pos - buffer;

                // Копируем новую строку
                strncpy(temp + index, longWords.data[i].word, strlen(longWords.data[i].word));
                index += strlen(longWords.data[i].word);

            }
            i++;
        }

        fwrite(buffer,1,512,NewFile);
    }
*/


    printf("Short words:\n");
    while (!isQueueEmpty(shortWords)) {
        WordCount wc = dequeue(&shortWords);
        if (strlen(wc.word) <= maxShortWordLength && wc.count <= maxShortWordOccurrence) {
            printf("%s (%d occurrences)\n", wc.word, wc.count);
        }
    }

    printf("Long words:\n");
    while (!isQueueEmpty(longWords)) {
        WordCount wc = dequeue(&longWords);
        if (strlen(wc.word) >= minLongWordLength && wc.count >= minLongWordOccurrence) {
            printf("%s (%d occurrences)\n", wc.word, wc.count);
        }
    }
    fclose(file);
    fclose(NewFile);
    return 0;
}