# Red-Black Trees

Binary Search Trees (BSTs) can easily become highly unbalanced, causing operations such as search, insertion, and deletion to degrade in performance — potentially reaching the same cost as linear operations on a list.

For example, if the root node contains the value 1 and all subsequent elements inserted are greater than 1, the right subtree will contain all elements, while the left subtree remains empty. This results in a degenerated tree, behaving like a linked list.

---

## Red-Black Trees vs AVL Trees

A solution to this problem is to use self-balancing trees, such as Red-Black Trees and AVL Trees, which apply specific algorithms to maintain balance after insertions and deletions.

- **Red-Black Trees** – fewer rotations, faster insertions and deletions.  
- **AVL Trees** – more rotations but slightly better balance and faster lookups.

### Red-Black Trees are used in:
- Various data structures and databases  
- Applications requiring fast lookup  
- C++ STL implementations (e.g., `std::map`, `std::set`)

---

## Properties of Red-Black Trees

A Red-Black Tree is a binary search tree (BST) where each node is either red or black, and the following properties must hold:

1. Every node is either red or black.  
2. The root is always black.  
3. Every leaf (NIL) is black.  
4. If a node is red, both its children are black.  
5. Every path from a node to its descendant NIL nodes contains the same number of black nodes.

---

## Example: Balanced vs Unbalanced BST

- Perfectly balanced BST  
- Unbalanced BST  

---

## Rotations

Insertion and deletion can violate Red-Black Tree properties. To restore them, tree rotations are used.

All missing child pointers and the root’s parent point to a special sentinel node `T.nil`.

### Definitions
- `LEFT_ROTATE(x)` – rotate the subtree around node x to the left  
- `RIGHT_ROTATE(x)` – rotate the subtree around node x to the right  
- `T.nil` – sentinel node  
- `T.root` – root of the tree  
- `x.left`, `x.right`, `x.p` – left child, right child, parent

### LEFT_ROTATE(x)
```
if x.right != T.nil
    y = x.right
    x.right = y.left
    if y.left != T.nil
        y.left.p = x
    y.p = x.p
    if x.p == T.nil
        T.root = y
    elseif x == x.p.left
        x.p.left = y
    else
        x.p.right = y
    y.left = x
    x.p = y
```

### RIGHT_ROTATE(x)
```
y = x.left
x.left = y.right
if y.right != T.nil
    y.right.p = x
y.p = x.p
if y.p == T.nil
    T.root = y
elseif x == x.p.left
    x.p.left = y
else
    x.p.right = y
y.right = x
x.p = y
```

---

## Insertion

Insertion into a Red-Black Tree with n nodes takes **O(log n)** time.

The insertion process is similar to that in a BST, followed by a fix-up procedure to restore the Red-Black properties.

### Main Functions
- `RED_BLACK_INSERT(key)` – inserts a node with key `key`  
- `RED_BLACK_INSERT_FIXUP(z)` – restores Red-Black properties after insertion

### RED_BLACK_INSERT_FIXUP(z)
```
while z.p.color == RED
    if z.p == z.p.p.left
        if z.p.p.right.color == RED
            z.p.color = BLACK
            z.p.p.right.color = BLACK
            z.p.p.color = RED
            z = z.p.p
        else
            if z == z.p.right
                z = z.p
                LEFT_ROTATE(z)
            z.p.color = BLACK
            z.p.p.color = RED
            RIGHT_ROTATE(z.p.p)
    else
        (same as above, with "right" and "left" swapped)
T.root.color = BLACK
```

### RED_BLACK_INSERT(key)
```
z.key = key
z.color = RED
z.left = T.nil
z.right = T.nil
y = T.nil
x = T.root

while x != T.nil
    y = x
    if z.key < x.key
        x = x.left
    else
        x = x.right

if y == T.nil
    T.root = z
elseif z.key < y.key
    y.left = z
else
    y.right = z
z.p = y
RED_BLACK_INSERT_FIXUP(z)
```

---

## Deletion

Deletion, like insertion, also runs in **O(log n)** time.

It uses a helper procedure `RED_BLACK_TRANSPLANT(u, v)` to replace one subtree with another.

### RED_BLACK_TRANSPLANT(u, v)
```
if u.p == T.nil
    T.root = v
elseif u == u.p.left
    u.p.left = v
else
    u.p.right = v
v.p = u.p
```

### TREE_MINIMUM(x)
```
while x.left != T.nil
    x = x.left
return x
```

### RED_BLACK_DELETE(z)
```
y = z
yOriginalColor = y.color
if z.left == T.nil
    x = z.right
    RED_BLACK_TRANSPLANT(z, z.right)
elseif z.right == T.nil
    x = z.left
    RED_BLACK_TRANSPLANT(z, z.left)
else
    y = TREE_MINIMUM(z.right)
    yOriginalColor = y.color
    x = y.right
    if y.p == z
        x.p = y
    else
        RED_BLACK_TRANSPLANT(y, y.right)
        y.right = z.right
        y.right.p = y
    RED_BLACK_TRANSPLANT(z, y)
    y.left = z.left
    y.left.p = y
    y.color = z.color
if yOriginalColor == BLACK
    RED_BLACK_DELETE_FIXUP(x)
```

---

### Cases in RED_BLACK_DELETE_FIXUP(x)
If the deleted node was red, no properties are violated.  
If it was black, there are four cases to handle:

1. **w (sibling) is red**  
2. **w is black, and both children of w are black**  
3. **w is black, right child is black, left child is red**  
4. **w is black, right child is red**

### RED_BLACK_DELETE_FIXUP(x)
```
while x != T.root and x.color == BLACK
    if x == x.p.left
        w = x.p.right
        if w.color == RED
            w.color = BLACK       // Case 1
            x.p.color = RED       // Case 1
            LEFT_ROTATE(x.p)      // Case 1
            w = x.p.right
        if w.left.color == BLACK and w.right.color == BLACK
            w.color = RED         // Case 2
            x = x.p
        else
            if w.right.color == BLACK
                w.left.color = BLACK  // Case 3
                w.color = RED         // Case 3
                RIGHT_ROTATE(w)
                w = x.p.right
            w.color = x.p.color       // Case 4
            x.p.color = BLACK
            w.right.color = BLACK
            LEFT_ROTATE(x.p)
            x = T.root
    else
        (same as above, with "right" and "left" swapped)
x.color = BLACK
```

---

## Searching

The search operation starts from the root, comparing keys and descending into left or right subtrees until either the key is found or a sentinel (`T.nil`) is reached.

### TREE_SEARCH(k)
```
x = T.root
while x != T.nil and x.key != k
    if k < x.key
        x = x.left
    else
        x = x.right
if x == T.nil
    return NULL
else
    return x
```

If the element does not exist, the algorithm returns `NULL`.
