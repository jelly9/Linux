#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Node
{
    int _val;
    struct Node *_next;
}Node;

pthread_cond_t g_cond;
pthread_mutex_t g_lock;

Node* CreateNode(int val);
void DestroyNode(Node *node);
void InitList(Node **head);
void Push(Node *head, int val);
void Pop(Node *head, int *val);
void PrintList(Node *head);

Node* CreateNode(int val)
{
    Node *ret = (Node*)malloc(sizeof(Node));
    ret->_val = val;
    ret->_next = NULL;
    return ret;
}

void DestroyNode(Node *node)
{
    free(node);
}

void InitList(Node **head)
{
    *head = CreateNode(-1);
}

void Push(Node *head, int val)
{
    Node *cur = CreateNode(val);
    cur->_next = head->_next;
    head->_next = cur;
}

void Pop(Node *head, int *val)
{
    if(head->_next != NULL){
        Node *del = head->_next;
        head->_next = del->_next;
        if(val)
            *val = del->_val;
        DestroyNode(del);
        return ;
    }
    sleep(1);
}

Node *head;

void *Producer(void *arg)
{
    (void)arg;
    int val = 0;
    while(1){
        pthread_mutex_lock(&g_lock);

        Push(head, ++val);
        printf("producer: %d\n", val);

        pthread_mutex_unlock(&g_lock);
        pthread_cond_signal(&g_cond);
        
        usleep(789123);
    }
}

void *Consumer(void *arg)
{
    (void)arg;
    int val;
    while(1){
        pthread_cond_wait(&g_cond, &g_lock);
        pthread_mutex_lock(&g_lock);

        Pop(head, &val);

        printf("consumer:     %d\n", val);

        pthread_mutex_unlock(&g_lock);
        usleep(123456);
    }
}

void PrintList(Node *head)
{
    printf("head -> ");
    Node *cur = head->_next;
    while(cur){
        printf("%d -> ", cur->_val);
        cur = cur->_next;
    }       
    printf("NULL\n");
}

int main()
{
    InitList(&head);
    Push(head, 1);
    Push(head, 2);
    Push(head, 3);
    Push(head, 4);
    PrintList(head);

    Pop(head, NULL);
    Pop(head, NULL);
    PrintList(head);

    pthread_cond_init(&g_cond, NULL);
    pthread_mutex_init(&g_lock, NULL);
    InitList(&head);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, Producer, NULL);
    pthread_create(&tid2, NULL, Consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_lock);

  return 0;
}
