class ListNode {
  val: number;
  next: ListNode | null;
  constructor(val?: number, next?: ListNode | null) {
    this.val = val === undefined ? 0 : val;
    this.next = next === undefined ? null : next;
  }
}

function addTwoNumbers(
  l1: ListNode | null,
  l2: ListNode | null,
): ListNode | null {
  let head: ListNode | null = null;
  let tail: ListNode | null = null;
  let c = 0;
  while (l1 || l2 || c) {
    let s = (l1?.val ?? 0) + (l2?.val ?? 0) + c;
    c = Math.floor(s / 10);

    let n = new ListNode(s % 10);
    if (!head) {
      head = tail = n;
    } else {
      tail!.next = n;
      tail = n;
    }
    l1 = l1?.next || null;
    l2 = l2?.next || null;
  }

  return head;
}
