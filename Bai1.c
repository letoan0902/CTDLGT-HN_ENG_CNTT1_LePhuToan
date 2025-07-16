#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Task
{
    int id;
    char title[150];
    int priority;
    char deadline[11];
} Task;

typedef struct Node
{
    Task task;
    struct Node *next;
} Node;

typedef struct Node2
{
    Task task;
    struct Node2 *prev;
    struct Node2 *next;
} Node2;

Node *createNode1()
{
    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        printf("Khong the cap phat bo nho");
        exit(1);
    }
    return newNode;
}

Node2 *createNode2()
{
    Node2 *newNode = (Node2 *)calloc(1, sizeof(Node2));
    if (newNode == NULL)
    {
        printf("Khong the cap phat bo nho");
        exit(1);
    }
    return newNode;
}

Node *addTask(Node *head)
{
    char line[150];
    int id, priority;
    char title[150];
    char dealine[11];
    printf("Nhap id: ");
    fgets(line, 150, stdin);
    sscanf(line, "%d", &id);
    printf("Nhap tieu de: ");
    fgets(title, 150, stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("Nhap muc do uu tien: ");
    fgets(line, 150, stdin);
    sscanf(line, "%d", &priority);
    printf("Nhap thoi gian hoan thanh nhiem vu: ");
    fgets(dealine, 11, stdin);
    dealine[strcspn(dealine, "\n")] = '\0';

    Node *newNode = createNode1();
    newNode->task.id = id;
    newNode->task.priority = priority;
    strcpy(newNode->task.title, title);
    strcpy(newNode->task.deadline, dealine);
    newNode->next = NULL;

    if (head == NULL)
    {
        return newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        return head;
    }
}

void printfTasks(Node *head)
{
    if (head == NULL)
    {
        printf("Danh sach rong\n");
        return;
    }
    printf("Danh sach nhiem vu: \n");
    Node *current = head;
    while (current != NULL)
    {
        printf("ID: %d, Tieu de: %s, Muc do uu tien: %d, Thoi gian hoan thanh: %s\n", current->task.id, current->task.title, current->task.priority, current->task.deadline);
        current = current->next;
    }
}

Node *removeTask(Node *head)
{
    if (head == NULL)
    {
        printf("Danh sach rong\n");
        return head;
    }
    int id;
    char line[100];
    printf("Nhap id de xoa: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &id);
    Node *current = head;

    if (head->task.id == id)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        printf("Da xoa nhiem vu\n");
        return head;
    }

    while (current->next != NULL)
    {
        if (current->next->task.id == id)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("Da xoa nhiem vu\n");
            return head;
        }
        current = current->next;
    }
    printf("Khong tim thay id %d\n", id);
    return head;
}

Node *updateTask(Node *head)
{

    if(head==NULL){
        printf("Danh sach rong\n");
        return head;
    }
    int id;
    char line[100];
    printf("Nhap id can cap nhat: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &id);
    Node *current = head;
    while (current != NULL)
    {
        if (current->task.id == id)
        {
            char title[150];
            int priority;
            char dealine[11];
            printf("Nhap tieu de moi: ");
            fgets(title, 150, stdin);
            title[strcspn(title, "\n")] = '\0';
            printf("Nhap muc do uu tien moi: ");
            fgets(line, 150, stdin);
            sscanf(line, "%d", &priority);
            printf("Nhap thoi gian hoan thanh moi: ");
            fgets(dealine, 11, stdin);
            dealine[strcspn(dealine, "\n")] = '\0';
            current->task.priority = priority;
            strcpy(current->task.title, title);
            strcpy(current->task.deadline, dealine);
            printf("Da cap nhat nhiem vu\n");
            return head;
        }
        current = current->next;
    }
    printf("Khong tim thay id %d\n", id);
    return head;
}

Node2 *markCompleted(Node **head, Node2 *headCompleted)
{
    if (*head == NULL)
    {
        printf("Danh sach rong\n");
        return headCompleted;
    }
    int id;
    char line[100];
    printf("Nhap id can danh dau: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &id);
    Node *current = *head;
    while (current != NULL)
    {
        if (current->task.id == id)
        {
            Node2 *newNode = createNode2();
            newNode->task.id = current->task.id;
            newNode->task.priority = current->task.priority;
            strcpy(newNode->task.title, current->task.title);
            strcpy(newNode->task.deadline, current->task.deadline);

            if (headCompleted == NULL)
            {
                headCompleted = newNode;
                newNode->prev = NULL;
                newNode->next = NULL;
            }
            else
            {
                Node2 *temp = headCompleted;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->prev = temp;
                newNode->next = NULL;
            }

            printf("Danh dau thanh cong\n");
            if (*head == current)
            {
                *head = current->next;
                free(current);
            }
            else
            {
                Node *prev = *head;
                while (prev->next != current)
                {
                    prev = prev->next;
                }
                prev->next = current->next;
                free(current);
            }
            return headCompleted;
        }
        current = current->next;
    }

    printf("Khong tim thay id %d\n", id);
    return headCompleted;
}

Node* bubbleSort(Node* head){
    if(head==NULL||head->next==NULL){
        return head;
    }
    Node* current = head;
    int swapped;
    do {
        swapped=0;
        current=head;
        while(current->next!=NULL){
            if(current->task.priority>current->next->task.priority){
                Task temp = current->task;
                current->task=current->next->task;
                current->next->task=temp;
                swapped=1;
            }
            current=current->next;
        } 
    } while(swapped);
    return head;
}

void findTask(Node* head){
    if(head==NULL){
        printf("Danh sach rong\n");
        return;
    }
    char title[150];
    printf("Nhap tieu de can tim kiem: ");
    fgets(title, 150, stdin);
    title[strcspn(title, "\n")] = '\0';
    Node* current = head;
    int found = 0;
    while(current!=NULL){
        if(strstr(current->task.title,title)){
            printf("ID: %d, Tieu de: %s, Muc do uu tien: %d, Thoi gian hoan thanh: %s\n", current->task.id, current->task.title, current->task.priority, current->task.deadline);
            found = 1;
        }
        current = current->next;
    }
    if(!found){
        printf("Khong tim thay nhiem vu nao co tieu de chua: %s\n", title);
    }
}


int main()
{
    char choice[10];
    Node *head = NULL;
    Node2 *headCompleted = NULL;
    while (1)
    {
        printf("-------TASK MANAGER---------\n");
        printf("1. Them nhiem vu\n");
        printf("2. Hien thi danh sach nhiem vu\n");
        printf("3. Xoa nhiem vu\n");
        printf("4. Cap nhat thong tin nhiem vu\n");
        printf("5. Danh dau nhiem vu hoan thanh\n");
        printf("6. Sap xep nhiem vu theo do uu tien\n");
        printf("7. Tim kiem nhiem vu theo tieu de\n");
        printf("8. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        fgets(choice, 10, stdin);
        switch (choice[0])
        {
        case '1':
            head = addTask(head);
            break;
        case '2':
            printfTasks(head);
            break;
        case '3':
            head = removeTask(head);
            break;
        case '4':
            head = updateTask(head);
            break;
        case '5':
            headCompleted = markCompleted(&head, headCompleted);
            break;
        case '6':
            head=bubbleSort(head);
            break;
        case '7':
            findTask(head);
            break;
        case '8':
            printf("Thoat chuong trinh\n");
            while(head!=NULL){
                Node* temp = head;
                head=head->next;
                free(temp);
            }
            while(headCompleted!=NULL){
                Node2 *temp = headCompleted;
                headCompleted=headCompleted->next;
                free(temp);
            }
            return 0;
        default:
            printf("Lua chon khong hop le, vui long nhap lai\n");
            break;
        }
    }

    return 0;
}