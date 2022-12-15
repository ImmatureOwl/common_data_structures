#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define cString const char
#define allocate_size_of_string malloc(sizeof(StringItem))
#define ListNode struct list_node
#define StringItem struct string_item

struct list_node
{
    ListNode *prev;
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

ListNode *list_append (ListNode **head, ListNode *item)
{
    ListNode *tail = list_get_tail (head);
    if (!tail)
    {
    * head = item;
    }
    else
    {
    tail->next = item;
    }
    item->prev = tail;
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

ListNode *list_find_item_with_string(ListNode **head, cString *item)
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
    return current_item;
}

ListNode *list_remove(ListNode **head, cString *item)
{
    ListNode *current_item = list_find_item_with_string(head, item);
    ListNode *next_item = current_item->next;
    ListNode *previous_item = current_item->prev;
    previous_item->next = next_item;
    next_item->prev = previous_item;
    return current_item;
}

ListNode *list_insert_after(ListNode **head, cString *string, ListNode *item)
{
    ListNode *current_item = list_find_item_with_string(head, string);
    ListNode *next_next_item = current_item->next;
    current_item->next = item;
    item->next = next_next_item;
    item->prev = current_item;
    next_next_item->prev = item;
}

ListNode *list_insert_before(ListNode **head, cString *string, ListNode *item)
{
    ListNode *current_item = list_find_item_with_string(head, string);
    ListNode *prev_prev_item = current_item->prev;
    current_item->prev = item;
    item->prev = prev_prev_item;
    item->next = current_item;
    prev_prev_item->next = item;
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
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Last Item of the Doubly Linked List"));

    list_pop((ListNode **)&my_linked_list);
    StringItem *removedItem = list_remove((ListNode **)&my_linked_list, (cString *)"This line will be removed");
    list_insert_after((ListNode **)&my_linked_list, (cString *)"Hello World", (ListNode *)string_item_new("ths line is after -Hello World-"));
    list_insert_before((ListNode **)&my_linked_list, (cString *)"Test002", (ListNode *)string_item_new("this line is before -Test002-"));

    StringItem *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (StringItem *)string_item->node.next;
    }
    // used to verify content of list_remove()
    printf("removed line: %s\n", removedItem->string);
    return 0;
}