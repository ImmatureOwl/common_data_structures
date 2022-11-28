#include <stddef.h>
#include <stdio.h>
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

ListNode *list_get_tail(ListNode **head)
{
    ListNode *current_node = *head;
    ListNode *last_node = NULL;
    while (current_node)
    {
    last_node = current_node;
    current_node = current_node->next;
    }
    return last_node;
}

ListNode *list_append(ListNode **head, ListNode *item)
{
    ListNode *tail = list_get_tail(head);
    if (!tail)
    {
    *head = item;
    }
    else
    {
    tail->next = item;
    }
    item->next = NULL;
    return item;
}

ListNode *list_pop(ListNode **head)
{
    ListNode *current_head = *head;
    if (!current_head)
    {
    return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

ListNode *list_remove(ListNode **head, cString *item)
{
    ListNode *previous_item = NULL;
    ListNode *current_item = *head;
    StringItem *current_string = (StringItem *)current_item;
    while (current_string->string != item)
    {
        previous_item = current_item;
        current_item = current_item->next;
        current_string = (StringItem *)current_item;
        if (!current_item->next) //check for end of nodes
        {
            return NULL;
        }
    }
    previous_item->next = current_item->next;
    return current_item;
}

StringItem *string_item_new(cString *string)
{
    StringItem *item = allocate_size_of_string;
    if (!item)
    {
    return NULL;
    }
    item->string = string;
    return item;
}

int main()
{
    StringItem *my_linked_list = NULL;
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("This line will be popped"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Hello World"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Test001"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("This line will be removed"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Test002"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Last Item of the Linked List"));

    list_pop((ListNode **)&my_linked_list);
    list_remove((ListNode **)&my_linked_list, (cString *)"This line will be removed");

    StringItem *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (StringItem *)string_item->node.next;
    }
    return 0;
}