/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * A sorted tree with optimal access times, where recently-accessed elements
 * are faster to access again.
 */

#ifndef mozilla_SplayTree_h_
#define mozilla_SplayTree_h_

#include "mozilla/Assertions.h"
#include "mozilla/NullPtr.h"

namespace mozilla {

template<class T, class C>
class SplayTree;

template<typename T>
class SplayTreeNode
{
  public:
    template<class A, class B>
    friend class SplayTree;

    SplayTreeNode()
      : left(nullptr), right(nullptr), parent(nullptr)
    {}

  private:
    T* left;
    T* right;
    T* parent;
};


/**
 * Class which represents a splay tree.
 * Splay trees are balanced binary search trees for which search, insert and
 * remove are all amortized O(log n), but where accessing a node makes it
 * faster to access that node in the future.
 *
 * T indicates the type of tree elements, Comparator must have a static
 * compare(const T&, const T&) method ordering the elements. The compare
 * method must be free from side effects.
 */
template<typename T, class Comparator>
class SplayTree
{
    T* root;
    T* freeList;

  public:
    SplayTree()
      : root(nullptr), freeList(nullptr)
    {}

    bool empty() const {
      return !root;
    }

    bool contains(const T& v)
    {
      if (empty())
        return false;

      T* last = lookup(v);
      splay(last);
      checkCoherency(root, nullptr);
      return Comparator::compare(v, *last) == 0;
    }

    bool insert(T* v)
    {
      MOZ_ASSERT(!contains(*v), "Duplicate elements are not allowed.");

      if (!root) {
        root = v;
        return true;
      }
      T* last = lookup(*v);
      int cmp = Comparator::compare(*v, *last);

      T** parentPointer = (cmp < 0) ? &last->left : &last->right;
      MOZ_ASSERT(!*parentPointer);
      *parentPointer = v;
      v->parent = last;

      splay(v);
      checkCoherency(root, nullptr);
      return true;
    }

    T* remove(const T& v)
    {
      T* last = lookup(v);
      MOZ_ASSERT(last, "This tree must contain the element being removed.");
      MOZ_ASSERT(Comparator::compare(v, *last) == 0);

      // Splay the tree so that the item to remove is the root.
      splay(last);
      MOZ_ASSERT(last == root);

      // Find another node which can be swapped in for the root: either the
      // rightmost child of the root's left, or the leftmost child of the
      // root's right.
      T* swap;
      T* swapChild;
      if (root->left) {
        swap = root->left;
        while (swap->right)
          swap = swap->right;
        swapChild = swap->left;
      } else if (root->right) {
        swap = root->right;
        while (swap->left)
          swap = swap->left;
        swapChild = swap->right;
      } else {
        T* result = root;
        root = nullptr;
        return result;
      }

      // The selected node has at most one child, in swapChild. Detach it
      // from the subtree by replacing it with that child.
      if (swap == swap->parent->left)
        swap->parent->left = swapChild;
      else
        swap->parent->right = swapChild;
      if (swapChild)
        swapChild->parent = swap->parent;

      // Make the selected node the new root.
      root = swap;
      root->parent = nullptr;
      root->left = last->left;
      root->right = last->right;
      if (root->left) {
        root->left->parent = root;
      }
      if (root->right) {
        root->right->parent = root;
      }

      checkCoherency(root, nullptr);
      return last;
    }

    T* removeMin()
    {
      MOZ_ASSERT(root, "No min to remove!");

      T* min = root;
      while (min->left)
        min = min->left;
      return remove(*min);
    }

  private:
    /**
     * Returns the node in this comparing equal to |v|, or a node just greater or
     * just less than |v| if there is no such node.
     */
    T* lookup(const T& v)
    {
      MOZ_ASSERT(!empty());

      T* node = root;
      T* parent;
      do {
        parent = node;
        int c = Comparator::compare(v, *node);
        if (c == 0)
          return node;
        else if (c < 0)
          node = node->left;
        else
          node = node->right;
      } while (node);
      return parent;
    }

    /**
     * Rotate the tree until |node| is at the root of the tree. Performing
     * the rotations in this fashion preserves the amortized balancing of
     * the tree.
     */
    void splay(T* node)
    {
      MOZ_ASSERT(node);

      while (node != root) {
        T* parent = node->parent;
        if (parent == root) {
          // Zig rotation.
          rotate(node);
          MOZ_ASSERT(node == root);
          return;
        }
        T* grandparent = parent->parent;
        if ((parent->left == node) == (grandparent->left == parent)) {
          // Zig-zig rotation.
          rotate(parent);
          rotate(node);
        } else {
          // Zig-zag rotation.
          rotate(node);
          rotate(node);
        }
      }
    }

    void rotate(T* node)
    {
      // Rearrange nodes so that node becomes the parent of its current
      // parent, while preserving the sortedness of the tree.
      T* parent = node->parent;
      if (parent->left == node) {
        //     x          y
        //   y  c  ==>  a  x
        //  a b           b c
        parent->left = node->right;
        if (node->right)
          node->right->parent = parent;
        node->right = parent;
      } else {
        MOZ_ASSERT(parent->right == node);
        //   x             y
        //  a  y   ==>   x  c
        //    b c       a b
        parent->right = node->left;
        if (node->left)
          node->left->parent = parent;
        node->left = parent;
      }
      node->parent = parent->parent;
      parent->parent = node;
      if (T* grandparent = node->parent) {
        if (grandparent->left == parent)
          grandparent->left = node;
        else
          grandparent->right = node;
      } else {
        root = node;
      }
    }

    T* checkCoherency(T* node, T* minimum)
    {
#ifdef DEBUG
      MOZ_ASSERT_IF(root, !root->parent);
      if (!node) {
        MOZ_ASSERT(!root);
        return nullptr;
      }
      MOZ_ASSERT_IF(!node->parent, node == root);
      MOZ_ASSERT_IF(minimum, Comparator::compare(*minimum, *node) < 0);
      if (node->left) {
        MOZ_ASSERT(node->left->parent == node);
        T* leftMaximum = checkCoherency(node->left, minimum);
        MOZ_ASSERT(Comparator::compare(*leftMaximum, *node) < 0);
      }
      if (node->right) {
        MOZ_ASSERT(node->right->parent == node);
        return checkCoherency(node->right, node);
      }
      return node;
#else
      return nullptr;
#endif
    }

    SplayTree(const SplayTree&) MOZ_DELETE;
    void operator=(const SplayTree&) MOZ_DELETE;
};

}  /* namespace mozilla */

#endif /* mozilla_SplayTree_h_ */
