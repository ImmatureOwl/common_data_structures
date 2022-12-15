#include "linked_list.h"
#include "aiv-cunit.h"

CUNIT_TEST(testAppendOneItem) 
{
    //1. Setup scenario
    StringItem *my_linked_list = NULL;
    //2. stimolate
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Hello World"));

    //3. expectation
    StringItem *string_item = my_linked_list;
    const char* actual = string_item->string;
    const char* expect = "Hello World";

    CUNIT_STRING_EQ(expect, actual);
}

CUNIT_TEST(testAppendTwoItems) 
{
    //1. Setup scenario
    StringItem *my_linked_list = NULL;

    //2. stimolate
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item01"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item02"));

    //3. expectation
    StringItem *string_item = my_linked_list;
    const char* actual = string_item->string;
    const char* expect = "Item01";

    CUNIT_STRING_EQ(expect, actual);
    
    string_item = (StringItem *)string_item->node.next;
    actual = string_item->string;
    expect = "Item02";

    CUNIT_STRING_EQ(expect, actual);
}

CUNIT_TEST(testPopFromOneItemList)
{
    StringItem *my_linked_list = NULL;
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item01"));

    ListNode* popped_node = list_pop((ListNode **)&my_linked_list);
    StringItem *string_item = (StringItem*)popped_node;

    CUNIT_STRING_EQ("Item01", string_item->string);

    CUNIT_IS_NULL(my_linked_list);
}

CUNIT_TEST(testPopFromEmptyList)
{
    StringItem *my_linked_list = NULL;
    
    ListNode* popped_node = list_pop((ListNode **)&my_linked_list);
    
    CUNIT_IS_NULL(popped_node);
    CUNIT_IS_NULL(my_linked_list);
}

CUNIT_TEST(testPopFromTwoItemList)
{
    StringItem *my_linked_list = NULL;
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item01"));
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item02"));

    ListNode* popped_node = list_pop((ListNode **)&my_linked_list);
    StringItem *string_item = (StringItem*)popped_node;

    CUNIT_STRING_EQ("Item01", string_item->string);
    CUNIT_STRING_EQ("Item02", my_linked_list->string);
}

CUNIT_TEST(testRemoveFromEmptyList) 
{
    StringItem *my_linked_list = NULL;

    ListNode* removed = list_remove((ListNode **)&my_linked_list, (cString *)"UnexistentItem");

    CUNIT_IS_NULL(removed);
    CUNIT_IS_NULL(my_linked_list);
}

CUNIT_TEST(testRemoveFromNullList) 
{
    ListNode* removed = list_remove(NULL, (cString *)"UnexistentItem");

    CUNIT_IS_NULL(removed);
}

CUNIT_TEST(testRemoveUnexistenItemFromOneItemList)
{
    StringItem *my_linked_list = NULL;
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item01"));

    ListNode* removed = list_remove((ListNode **)&my_linked_list, (cString *)"UnexistentItem");
    CUNIT_IS_NULL(removed);
}


CUNIT_TEST(testRemoveItemFromOneItemList)
{
    StringItem *my_linked_list = NULL;
    list_append((ListNode **)&my_linked_list, (ListNode *)string_item_new("Item01"));

    ListNode* removed = list_remove((ListNode **)&my_linked_list, (cString *)"Item01");
    StringItem *removed_str = (StringItem*)removed;

    CUNIT_STRING_EQ("Item01", removed_str->string);
}


CUNIT_RUNNER(
    testAppendOneItem, testAppendTwoItems, 
    testPopFromOneItemList, testPopFromEmptyList, testPopFromTwoItemList,
    testRemoveFromEmptyList, testRemoveFromNullList, testRemoveUnexistenItemFromOneItemList, testRemoveItemFromOneItemList
);