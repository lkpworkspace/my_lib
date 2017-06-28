#ifdef __cplusplus
extern "C"{
#endif
#ifndef MY_LIST_H
#define MY_LIST_H


typedef struct my_list_t
{
    struct my_list_t *prev;
    struct my_list_t *next;
}my_list_t;

static inline void my_list_init(my_list_t *head)
{
    head->prev = head->next = head;
}

static inline int my_list_empty(my_list_t* head)
{
    return head == head->next;
}

static inline void __my_list_add(my_list_t *prev,my_list_t *next, my_list_t *node)
{

    prev->next = node;
    node->prev = prev;
    node->next = next;
    next->prev = node;
}

static inline void my_list_add_head(my_list_t* head, my_list_t* node)
{
    __my_list_add(head,head->next,node);
}

static inline void my_list_add_tail(my_list_t* head, my_list_t *node)
{
    __my_list_add(head->prev,head,node);
}

static inline void __my_list_del(my_list_t *prev,my_list_t *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void my_list_del(my_list_t *node)
{
    __my_list_del(node->prev,node->next);
}

static inline void my_list_del_head(my_list_t* head)
{
    __my_list_del(head,head->next->next);
}

static inline void my_list_del_tail(my_list_t* head)
{
    __my_list_del(head->prev->prev,head);
}

static inline void my_list_move_head(my_list_t* head, my_list_t* node)
{
    my_list_del(node);
    my_list_add_head(head, node);
}

static inline void my_list_move_tail(my_list_t* head, my_list_t* node)
{
    my_list_del(node);
    my_list_add_tail(head, node);
}

static inline void my_list_append(my_list_t* to, my_list_t* from)
{
    if(my_list_empty(from))
        return;

    my_list_t* from_tail = from->prev;
    my_list_t* from_head = from->next;

    to->prev->next = from_head;
    from_head->prev = to->prev;

    from_tail->next = to;
    to->prev = from_tail;

    my_list_init(from);
}

#ifndef offsetof
#define offsetof(s, m)   (size_t)&(((s *)0)->m)
#endif

#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr: the pointer to the member.
 * @type: the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({ \
         const typeof( ((type *)0)->member ) *__mptr = (ptr); \
          (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef list_entry
/**
  * list_entry - get the struct for this entry
  * @ptr: the &struct list_head pointer.
  * @type: the type of the struct this is embedded in.
  * @member: the name of the list_struct within the struct.
  */
#define list_entry(ptr, type, member) \
       container_of(ptr, type, member)
#endif

#define my_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/*
Demo:
    typedef struct A{
        my_list_t node;
        int a;
        int b;
    }A;
    my_list_t root;

    int main(void)
    {
        A a1;
        a1.a = 10;
        a1.b = 20;

        my_list_init(&root);
        my_list_add_head(&root,&a1.node);

        // 遍历该链表
        my_list_t *ptr;
        my_list_for_each(ptr,&root)
        {
            A* temp = list_entry(ptr,struct A,node);
            printf("%d\t%d",temp->a,temp->b);
        }

        return 0;
    }
 */
#endif // MY_LIST_H
#ifdef __cplusplus
}
#endif


