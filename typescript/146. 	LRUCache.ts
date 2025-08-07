class Node {
  prev: Node | null;
  next: Node | null;
  key: number;
  val: number;
  constructor(key: number, val: number) {
    this.prev = null;
    this.next = null;
    this.key = key;
    this.val = val;
  }
}

class LinkedList {
  head: Node | null;
  tail: Node | null;
  capacity: number;
  size: number;

  constructor(capacity: number) {
    this.head = null;
    this.tail = null;
    this.capacity = capacity;
    this.size = 0;
  }

  addNode(node: Node) {
    const n = node;
    n.next = this.head;
    if (this.head) this.head.prev = n;
    this.head = n;
    if (!this.tail) this.tail = n;
    this.size++;
  }

  removeNode(n: Node): Node {
    if (n.prev) n.prev.next = n.next;
    if (n.next) n.next.prev = n.prev;
    if (n === this.tail) this.tail = n.prev;
    if (n === this.head) this.head = n.next;
    n.prev = null;
    n.next = null;
    this.size--;
    return n;
  }
}

class LRUCache {
  ll: LinkedList;
  map: Map<number, Node>;

  constructor(capacity: number) {
    this.ll = new LinkedList(capacity);
    this.map = new Map();
  }

  put(key: number, val: number) {
    if (this.map.has(key)) {
      const node = this.map.get(key);
      if (node) {
        node.val = val;
        this.ll.removeNode(node);
        this.ll.addNode(node);
      }
      return;
    }
    if (this.ll.size === this.ll.capacity) {
      if (this.ll.tail) {
        const node = this.ll.removeNode(this.ll.tail);
        this.map.delete(node.key);
      }
    }
    const n = new Node(key, val);
    this.map.set(key, n);
    this.ll.addNode(n);
  }
  get(key: number): number {
    if (this.map.has(key)) {
      const n = this.map.get(key);
      if (n) {
        this.ll.removeNode(n);
        this.ll.addNode(n);
        return n.val;
      }
    }
    return -1;
  }
}
