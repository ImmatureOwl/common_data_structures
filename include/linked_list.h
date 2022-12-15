#include <stdlib.h>

#define cString const char
#define allocate_size_of_string malloc(sizeof(StringItem))
#define ListNode struct list_node
#define StringItem struct string_item

struct list_node
{
    ListNode *next;
};

struct string_item
{
    ListNode node;
    cString *string;
};

ListNode *list_append(ListNode **head, ListNode *item);
StringItem *string_item_new(cString *string);
ListNode *list_pop(ListNode **head);
ListNode *list_remove(ListNode **head, cString *item);