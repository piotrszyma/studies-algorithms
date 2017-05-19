from enum import Enum


class Tree:
    def __init__(self):
        self.size = 0
        self.nil = {'left': None, 'right': None}
        self.nil = TreeNode(None, None, self)
        self.nil.color = Color.BLACK
        self.root = self.nil

    def length(self):
        return self.size

    def __len__(self):
        return self.size

    def __iter__(self):
        return self.root.__iter__()

    def insert(self, value):
        if self.root == self.nil:
            self.root = TreeNode(value, self.nil, self)
            self.root.color = Color.BLACK
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


class TreeNode:
    def __init__(self, value, parent, tree):
        self.value = value
        self.tree = tree
        self.left = self.tree.nil
        self.right = self.tree.nil
        self.parent = parent
        self.color = Color.RED

    def add(self, value):
        if value > self.value:
            if self.right == self.tree.nil:
                self.right = TreeNode(value, self, self.tree)
                self.right.rb_properties()
            else:
                self.right.add(value)
        else:
            if self.left == self.tree.nil:
                self.left = TreeNode(value, self, self.tree)
                self.left.rb_properties()
            else:
                self.left.add(value)

    def show(self):
        if self.left != self.tree.nil:
            self.left.show()
        print(self.value)
        if self.right != self.tree.nil:
            self.right.show()

    def min(self):
        if self.left == self.tree.nil:
            return self
        else:
            return self.left.min()

    def max(self):
        if self.right == self.tree.nil:
            return self
        else:
            return self.right.max()

    def delete(self, value):
        if self.value == value:
            if self.left == self.tree.nil and self.right == self.tree.nil:
                if self == self.tree.root:
                    self.tree.root = None
                elif self.parent.value > self.value:
                    self.parent.left = None
                else:
                    self.parent.right = None
            elif self.left == self.tree.nil:
                if self == self.tree.root:
                    self.tree.root = self.right
                elif self.parent.value > self.value:
                    self.parent.left = self.right
                else:
                    self.parent.right = self.right
            elif self.right == self.tree.nil:
                if self == self.tree.root:
                    self.tree.root = self.left
                elif self.parent.value > self.value:
                    self.parent.left = self.left
                else:
                    self.parent.right = self.left
            else:
                m = self.right.min()
                self.value = m.value
                m.delete(m.value)
        else:
            if self.value > value:
                if self.left == self.tree.nil:
                    raise Exception("No such an element")
                else:
                    self.left.delete(value)
            else:
                if self.right == self.tree.nil:
                    raise Exception("No such an element")
                else:
                    self.right.delete(value)

    def find(self, value):
        if self.value == value:
            return True
        elif self.value > value:
            if self.left == self.tree.nil:
                return False
            else:
                return self.left.find(value)
        else:
            if self.right == self.tree.nil:
                return False
            else:
                return self.right.find(value)

    def right_rotate(self):
        if self == self.tree.root:
            self.tree.root = self.left
            self.left.parent = self.tree.nil
            self.left = self.tree.root.right
            self.tree.root.right = self
        else:
            if self.parent.value > self.value:
                self.parent.left = self.left
            else:
                self.parent.right = self.left
            self.left.parent = self.parent
            self.parent = self.left
            self.left = self.parent.right
            self.parent.right = self

    def left_rotate(self):
        if self == self.tree.root:
            self.tree.root = self.right
            self.right.parent = self.tree.nil
            self.right = self.tree.root.left
            self.tree.root.left = self
        else:
            if self.parent.value > self.value:
                self.parent.left = self.right
            else:
                self.parent.right = self.right
            self.right.parent = self.parent
            self.parent = self.right
            self.right = self.parent.left
            self.parent.left = self

    def rb_properties(self):
        z = self
        while z.parent.color == Color.RED:
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right
                if y.color == Color.RED:
                    z.parent.color = Color.BLACK
                    y.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    z = z.parent.parent
                elif z == z.parent.right:
                    z = z.parent
                    z.left_rotate()
                z.parent.color = Color.BLACK
                if z.parent.parent is not None:
                    z.parent.parent.color = Color.RED
                    z.parent.parent.right_rotate()
            else:
                y = z.parent.parent.left
                if y.color == Color.RED:
                    z.parent.color = Color.BLACK
                    y.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    z = z.parent.parent
                elif z == z.parent.left:
                    z = z.parent
                    z.right_rotate()
                z.parent.color = Color.BLACK
                if z.parent.parent is not None:
                    z.parent.parent.color = Color.RED
                    z.parent.parent.left_rotate()
        self.tree.root.color = Color.BLACK

    def check_color(self):
        self.rec_check_color()

    def rec_check_color(self):
        if self.left != self.tree.nil:
            self.left.rec_check_color()

            if self.color == Color.RED:
                if self.parent.color == Color.RED:
                    print("BUG")

        if self.right != self.tree.nil:
            self.right.rec_check_color()


class Color(Enum):
    BLACK = 1
    RED = 2
