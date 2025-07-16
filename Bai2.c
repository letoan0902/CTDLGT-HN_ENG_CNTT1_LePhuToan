#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operation{
    char action;
    char value;
} Operation;

typedef struct Stack{
    Operation* data;
    int top;
    int maxSize;
} Stack;

Stack* createStack(){
    Stack* s = (Stack*)calloc(1, sizeof(Stack));
    if(s == NULL){
        printf("Khong the cap phat bo nho");
        exit(1);
    }
    s->data = (Operation*)calloc(1000, sizeof(Operation));
    if(s->data == NULL){
        printf("Khong the cap phat bo nho");
        free(s);
        exit(1);
    }
    s->top = -1;
    s->maxSize = 1000;
    return s;
}

int isEmpty(Stack* s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

int isFull(Stack* s){
    if(s->top == s->maxSize - 1){
        return 1;
    }
    return 0;
}

void push(Stack* s, Operation op){
    if(isFull(s)){
        printf("Ngan xep day\n");
        return;
    }
    s->top++;
    s->data[s->top] = op;
}

Operation pop(Stack* s){
    Operation emptyOp = {'\0', '\0'};
    if(isEmpty(s)){
        return emptyOp;
    }
    return s->data[s->top--];
}

void freeStack(Stack* s){
    if(s != NULL){
        if(s->data != NULL){
            free(s->data);
        }
        free(s);
    }
}

void insertChar(char* text, Stack* undoStack, Stack* redoStack, char character){
    int len = strlen(text);
    if(len >= 999){
        printf("Van ban da day\n");
        return;
    }
    
    text[len] = character;
    text[len+1] = '\0';
    
    Operation op;
    op.action = 'I';
    op.value = character;
    
    push(undoStack, op);
    
    // Xóa nội dung stack REDO khi thực hiện thao tác mới
    redoStack->top = -1; // Reset redoStack thay vì giải phóng
}

void undoOperation(char* text, Stack* undoStack, Stack* redoStack){
    if(isEmpty(undoStack)){
        printf("Khong co thao tac nao de hoan tac\n");
        return;
    }
    
    Operation op = pop(undoStack);
    
    int len = strlen(text);
    if(len > 0){
        // Lưu thao tác vào REDO stack
        push(redoStack, op);
        
        // Xóa ký tự cuối
        text[len-1] = '\0';
    }
}

void redoOperation(char* text, Stack* undoStack, Stack* redoStack){
    if(isEmpty(redoStack)){
        printf("Khong co thao tac nao de phuc hoi\n");
        return;
    }
    
    Operation op = pop(redoStack);
    
    int len = strlen(text);
    if(len >= 999){
        printf("Van ban da day\n");
        return;
    }
    
    // Thêm ký tự từ thao tác REDO
    text[len] = op.value;
    text[len+1] = '\0';
    
    // Lưu thao tác vào UNDO stack
    push(undoStack, op);
}

void displayText(char* text){
    if(strlen(text) == 0){
        printf("Van ban hien tai: [rong]\n");
    } else {
        printf("Van ban hien tai: %s\n", text);
    }
}

int main(){
    char text[1000]="";
    Stack* undoStack = createStack();
    Stack* redoStack = createStack();

    char choice[100];
    char buffer[10];

    while(1){
        printf("--------TEXT EDITOR--------\n");
        printf("1. INSERT x\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. HIEN THI\n");
        printf("5. THOAT\n");
        printf("Nhap lua chon: ");
        fgets(choice,100,stdin);
        switch (choice[0])
        {
        case '1':
            printf("Nhap ky tu can chen: ");
            fgets(buffer, 10, stdin);
            insertChar(text, undoStack, redoStack, buffer[0]);
            break;
        case '2':
            undoOperation(text, undoStack, redoStack);
            break;
        case '3':
            redoOperation(text, undoStack, redoStack);
            break;
        case '4':
            displayText(text);
            break;
        case '5':
            printf("Thoat chuong trinh\n");
            freeStack(undoStack);
            freeStack(redoStack);
            return 0;
        default:
            printf("Lua chon khong hop le, vui long chon lai\n");
            break;
        }
    }

    return 0;
}