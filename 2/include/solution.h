/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *curNode = new ListNode();
    ListNode *head = curNode;
    int carry = 0;
    while (true) {
      const int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
      carry = sum / 10;
      curNode->val = sum % 10;
      l1 = l1 ? l1->next : l1;
      l2 = l2 ? l2->next : l2;
      if (!l1 && !l2 && !carry) {
        break;
      }
      curNode->next = new ListNode();
      curNode = curNode->next;
    }
    delete curNode->next;
    curNode->next = nullptr;
    return head;
  }
};
