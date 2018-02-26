from enum import Enum


class Tree:
    def __init__(self):
        self.root = None
        self.size = 0
        self.operations = 0

    def length(self):
        return self.size

    def __len__(self):
        return self.size

    def __iter__(self):
        return self.root.__iter__()

    def insert(self, value):
        if self.root is None:
            self.root = TreeNode(value, None, self)
        else:
            self.root.add(value)

    def show(self):
        if self.root is None:
            raise Exception("Tree is empty")
        else:
            self.root.show()

    def min(self):
        return self.root.min().value

    def max(self):
        return self.root.max().value

    def delete(self, value):
        if self.root is None:
            raise Exception("No such element")
        else:
            self.root.delete(value)

    def find(self, value):
        return 1 if self.root.find(value) else 0

    def os_select(self, x, i):
        if x is None:
            raise Exception("No such element")
        elif x.left is None:
            r = 1
        else:
            r = x.left.size + 1
        if i == r:
            return x
        elif i < r:
            return self.os_select(x.left, i)
        else:
            return self.os_select(x.right, i - r)

    def os_rank(self, x):
        if x.left is None:
            r = 1
        else:
            r = x.left.size + 1
        y = x
        while y != self.root:
            if y == y.parent.right:
                if y.parent.left is None:
                    r = r + 1
                else:
                    r = r + y.parent.left.size + 1
            y = y.parent
        return r

    def clear_operations_counter(self):
        self.operations = 0


class TreeNode:
    def __init__(self, value, parent, tree):
        self.value = value
        self.left = None
        self.right = None
        self.parent = parent
        self.tree = tree
        self.size = 1

    def add(self, value):
        self.size += 1
        if value > self.value:
            if self.right is None:
                self.right = TreeNode(value, self, self.tree)
            else:
                self.right.add(value)
        else:
            if self.left is None:
                self.left = TreeNode(value, self, self.tree)
            else:
                self.left.add(value)

    def show(self):
        if self.left is not None:
            self.left.show()
        print(self.value)
        if self.right is not None:
            self.right.show()

    def min(self):
        if self.left is None:
            return self
        else:
            return self.left.min()

    def max(self):
        if self.right is None:
            return self
        else:
            return self.right.max()

    def delete(self, value):
        if self.value == value:
            if self.left is None and self.right is None:
                if self == self.tree.root:
                    self.tree.root = None
                elif self.parent.value > self.value:
                    self.parent.left = None
                else:
                    self.parent.right = None
            elif self.left is None:
                if self == self.tree.root:
                    self.tree.root = self.right
                    self.right.parent = None
                elif self.parent.value > self.value:
                    self.parent.left = self.right
                    self.right.parent = self.parent
                else:
                    self.parent.right = self.right
                    self.right.parent = self.parent
            elif self.right is None:
                if self == self.tree.root:
                    self.tree.root = self.left
                    self.left.parent = None
                elif self.parent.value > self.value:
                    self.parent.left = self.left
                    self.left.parent = self.parent
                else:
                    self.parent.right = self.left
                    self.left.parent = self.parent
            else:
                self.size -= 1
                t = self.right
                while t.left is not None:
                    t.size -= 1
                    t = t.left
                self.value = t.value
                t.delete(t.value)
        else:
            if self.value > value:
                if self.left is None:
                    raise Exception("No such an element")
                else:
                    self.size -= 1
                    self.left.delete(value)
            else:
                if self.right is None:
                    raise Exception("No such an element")
                else:
                    self.size -= 1
                    self.right.delete(value)

    def find(self, value):
        if self.value == value:
            return True
        elif self.value > value:
            if self.left is None:
                return False
            else:
                return self.left.find(value)
        else:
            if self.right is None:
                return False
            else:
                return self.right.find(value)
