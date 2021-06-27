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
    ListNode root(0, head);
    ListNode *left = &root;
    ListNode *right = &root;
    right = moveNSteps(right, n + 1);
    while (right != nullptr) {
      left = moveNSteps(left, 1);
      right = moveNSteps(right, 1);
    }
    deleteNextNode(left);
    head = root.next;
    return head;
  }

  ListNode *moveNSteps(ListNode *node, int numSteps) {
    for (int i = 0; i < numSteps; i++) {
      assert(node != nullptr);
      node = node->next;
    }
    return node;
  }

  void deleteNextNode(ListNode *node) {
    ListNode *nextNode = node->next;
    assert(nextNode != nullptr);
    node->next = nextNode->next;
    delete nextNode;
  }
};
