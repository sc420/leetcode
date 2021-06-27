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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *left = nullptr;
    ListNode *right = nullptr;
    right = moveNSteps(right, n + 1, head);
    while (right != nullptr) {
      left = moveNSteps(left, 1, head);
      right = moveNSteps(right, 1, head);
    }
    head = deleteNextNode(left, head);
    return head;
  }

  ListNode *moveNSteps(ListNode *node, int numSteps, ListNode *head) {
    if (node == nullptr) {
      node = head;
      numSteps--;
    }
    for (int i = 0; i < numSteps; i++) {
      assert(node != nullptr);
      node = node->next;
    }
    return node;
  }

  ListNode *deleteNextNode(ListNode *node, ListNode *head) {
    if (node) {
      ListNode *nextNode = node->next;
      assert(nextNode != nullptr);
      node->next = nextNode->next;
      delete nextNode;
      return head;
    } else {
      ListNode *nextNode = head->next;
      delete head;
      return nextNode;
    }
  }
};
