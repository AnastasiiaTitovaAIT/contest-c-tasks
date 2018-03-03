#include<stdio.h>
#include<stdlib.h>
struct elem
{
    FILE *f;
    int data;
    struct elem *next;
};
struct elem
*add_elem(struct elem *head, const char *name)
{
    FILE *f = fopen(name, "r");
    int data;
    if (f == NULL) {
        fclose(f);
        return head;
    }
    if (head == NULL) {
        if (fscanf(f, "%d", &data) > 0) {
            head = calloc(1, sizeof(*head));
            head->f = f;
            head->data = data;
            head->next = NULL;
            return head;
        }
        fclose(f);
        return head;
    }
    if (fscanf(f, "%d", &data) == EOF) {
        fclose(f);
        return head;
    }
    struct elem *cur = head;
    struct elem *new_elem = calloc(1, sizeof(*new_elem));
    new_elem->f = f;
    new_elem->data = data;
    new_elem->next = NULL;
    while (cur) {
        if (new_elem->data >= cur->data) {
            if (cur->next) {
                if (new_elem->data < cur->next->data){
                    new_elem->next = cur->next;
                    cur->next = new_elem;
                    return head;
                }
                cur = cur->next;
                continue;
            } else {
                cur->next = new_elem;
                return head;
            }
        } else {
            new_elem->next = head;
            head = new_elem;
            return head;
        }
    }
    return head;
}
void
remove_elem(struct elem *head)
{
    struct elem *temp = NULL;
    fclose(head->f);
    temp = head;
    head = head->next;
    free(temp);
    return;
}
struct elem
*move_elem(struct elem *head)
{
    struct elem *temp = NULL;
    struct elem *cur = NULL;
    struct elem *prev = NULL;
    if (head->next == NULL) {
        return head;
    }
    if (head->data > head->next->data) {
        temp = head;
        head = head->next;
    } else {
        return head;
    }
    cur = head;
    while (temp->data > cur->data) {
        if (cur->next == NULL) {
            cur->next = temp;
            temp->next = NULL;
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    temp->next = cur;
    prev->next = temp;
    return head;
}
int
main(int argc, const char **argv)
{
    int data;
    struct elem *temp = NULL;
    struct elem *first = NULL;
    for (int i = 1; i < argc; i++) {
        first = add_elem(first, argv[i]);
    }
    if (first == NULL) {
        return 0;
    }
    while (first->next != NULL) {
        while (first->data <= first->next->data) {
            printf("%d ", first->data);
            if (fscanf(first->f, "%d", &data) == EOF) {
                temp = first->next;
                remove_elem(first);
                first = temp;
                if (first->next == NULL) {
                    break;
                }
            } else {
                first->data = data;
            }
        }
        first = move_elem(first);
    }
    if (first != NULL) {
        printf("%d ", first->data);
        while (fscanf(first->f, "%d", &first->data) != EOF) {
            printf("%d ", first->data);
        }
        fclose(first->f);
        free(first);
    }
    printf("\n");
    return 0;
}
