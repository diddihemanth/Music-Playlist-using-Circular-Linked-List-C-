#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100

// Node (song)
typedef struct Node {
    char title[MAX_TITLE];
    struct Node *next;
} Node;

// Playlist
Node *head = NULL;
Node *current = NULL;

// Create a new node
Node* createNode(char *title) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->title, title);
    newNode->next = NULL;
    return newNode;
}

// Add new song at end (circular)
void addSong(char *title) {
    Node *newNode = createNode(title);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;   // circular
        current = head;
    } else {
        Node *temp = head;

        // go to last node
        while (temp->next != head)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = head;   // circular link
    }

    printf("Song added: %s\n", title);
}

// Delete song by title
void deleteSong(char *title) {
    if (head == NULL) {
        printf("Playlist empty.\n");
        return;
    }

    Node *temp = head, *prev = NULL;

    // If deleting head
    if (strcmp(head->title, title) == 0) {

        // only one node
        if (head->next == head) {
            free(head);
            head = current = NULL;
            printf("Song deleted.\n");
            return;
        }

        // find last node to fix circular link
        Node *last = head;
        while (last->next != head)
            last = last->next;

        last->next = head->next;
        head = head->next;
        free(temp);
        current = head;

        printf("Song deleted.\n");
        return;
    }

    // Search for song
    do {
        prev = temp;
        temp = temp->next;

        if (strcmp(temp->title, title) == 0) {
            prev->next = temp->next;
            if (temp == current)
                current = prev->next;
            free(temp);
            printf("Song deleted.\n");
            return;
        }

    } while (temp != head);

    printf("Song not found.\n");
}

// Move to next
void moveNext() {
    if (current == NULL) {
        printf("Playlist empty.\n");
        return;
    }
    current = current->next;
    printf("Current song: %s\n", current->title);
}

// Move to previous (requires traversal)
void movePrevious() {
    if (current == NULL) {
        printf("Playlist empty.\n");
        return;
    }

    Node *temp = head;

    while (temp->next != current)
        temp = temp->next;

    current = temp;
    printf("Current song: %s\n", current->title);
}

// Jump to head
void jumpHead() {
    if (head == NULL) {
        printf("Playlist empty.\n");
        return;
    }
    current = head;
    printf("Jumped to first song: %s\n", current->title);
}

// Jump to tail
void jumpTail() {
    if (head == NULL) {
        printf("Playlist empty.\n");
        return;
    }

    Node *temp = head;
    while (temp->next != head)
        temp = temp->next;

    current = temp;
    printf("Jumped to last song: %s\n", current->title);
}

// Display playlist
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist empty.\n");
        return;
    }

    Node *temp = head;
    printf("Playlist:\n");

    do {
        if (temp == current)
            printf("> %s\n", temp->title); // mark current
        else
            printf("  %s\n", temp->title);

        temp = temp->next;
    } while (temp != head);
}

int main() {
    int choice;
    char title[MAX_TITLE];

    while (1) {
        printf("\n--- Music Playlist Menu ---\n");
        printf("1. Add new song\n");
        printf("2. Delete song\n");
        printf("3. Move to next song\n");
        printf("4. Move to previous song\n");
        printf("5. Jump to first song\n");
        printf("6. Jump to last song\n");
        printf("7. Display playlist\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                addSong(title);
                break;

            case 2:
                printf("Enter song title to delete: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                deleteSong(title);
                break;

            case 3:
                moveNext();
                break;

            case 4:
                movePrevious();
                break;

            case 5:
                jumpHead();
                break;

            case 6:
                jumpTail();
                break;

            case 7:
                displayPlaylist();
                break;

            case 8:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
