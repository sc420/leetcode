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
    int carry = 0;
    while (l1 || l2 || carry > 0) {
      const int sum = getValue(l1) + getValue(l2) + carry;
      l1 = next(l1);
      l2 = next(l2);
      addOutputDigit(sum % 10);
      carry = sum / 10;
    }
    return m_head;
  }

  int getValue(const ListNode *node) {
    return node ? node->val : 0;
  }

  ListNode *next(ListNode *node) {
    return node ? node->next : node;
  }

  void addOutputDigit(const int digit) {
    ListNode *newNode = new ListNode();
    if (m_tail) {
      m_tail->next = newNode;
      m_tail = newNode;
    } else {
      m_head = newNode;
      m_tail = newNode;
    }
    m_tail->val = digit;
  }

  ListNode *m_head = nullptr;
  ListNode *m_tail = nullptr;
};
