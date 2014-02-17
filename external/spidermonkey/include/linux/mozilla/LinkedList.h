/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A type-safe doubly-linked list class. */

/*
 * The classes LinkedList<T> and LinkedListElement<T> together form a
 * convenient, type-safe doubly-linked list implementation.
 *
 * The class T which will be inserted into the linked list must inherit from
 * LinkedListElement<T>.  A given object may be in only one linked list at a
 * time.
 *
 * A LinkedListElement automatically removes itself from the list upon
 * destruction, and a LinkedList will fatally assert in debug builds if it's
 * non-empty when it's destructed.
 *
 * For example, you might use LinkedList in a simple observer list class as
 * follows.
 *
 *   class Observer : public LinkedListElement<Observer>
 *   {
 *     public:
 *       void observe(char* topic) { ... }
 *   };
 *
 *   class ObserverContainer
 *   {
 *     private:
 *       LinkedList<Observer> list;
 *
 *     public:
 *       void addObserver(Observer* observer) {
 *         // Will assert if |observer| is part of another list.
 *         list.insertBack(observer);
 *       }
 *
 *       void removeObserver(Observer* observer) {
 *         // Will assert if |observer| is not part of some list.
 *         observer.remove();
 *         // Or, will assert if |observer| is not part of |list| specifically.
 *         // observer.removeFrom(list);
 *       }
 *
 *       void notifyObservers(char* topic) {
 *         for (Observer* o = list.getFirst(); o != nullptr; o = o->getNext())
 *           o->observe(topic);
 *       }
 *   };
 *
 */

#ifndef mozilla_LinkedList_h
#define mozilla_LinkedList_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Move.h"
#include "mozilla/NullPtr.h"

#ifdef __cplusplus

namespace mozilla {

template<typename T>
class LinkedList;

template<typename T>
class LinkedListElement
{
    /*
     * It's convenient that we return nullptr when getNext() or getPrevious()
     * hits the end of the list, but doing so costs an extra word of storage in
     * each linked list node (to keep track of whether |this| is the sentinel
     * node) and a branch on this value in getNext/getPrevious.
     *
     * We could get rid of the extra word of storage by shoving the "is
     * sentinel" bit into one of the pointers, although this would, of course,
     * have performance implications of its own.
     *
     * But the goal here isn't to win an award for the fastest or slimmest
     * linked list; rather, we want a *convenient* linked list.  So we won't
     * waste time guessing which micro-optimization strategy is best.
     *
     *
     * Speaking of unnecessary work, it's worth addressing here why we wrote
     * mozilla::LinkedList in the first place, instead of using stl::list.
     *
     * The key difference between mozilla::LinkedList and stl::list is that
     * mozilla::LinkedList stores the prev/next pointers in the object itself,
     * while stl::list stores the prev/next pointers in a list element which
     * itself points to the object being stored.
     *
     * mozilla::LinkedList's approach makes it harder to store an object in more
     * than one list.  But the upside is that you can call next() / prev() /
     * remove() directly on the object.  With stl::list, you'd need to store a
     * pointer to its iterator in the object in order to accomplish this.  Not
     * only would this waste space, but you'd have to remember to update that
     * pointer every time you added or removed the object from a list.
     *
     * In-place, constant-time removal is a killer feature of doubly-linked
     * lists, and supporting this painlessly was a key design criterion.
     */

  private:
    LinkedListElement* next;
    LinkedListElement* prev;
    const bool isSentinel;

  public:
    LinkedListElement()
      : next(MOZ_THIS_IN_INITIALIZER_LIST()),
        prev(MOZ_THIS_IN_INITIALIZER_LIST()),
        isSentinel(false)
    { }

    LinkedListElement(LinkedListElement<T>&& other)
      : isSentinel(other.isSentinel)
    {
      if (!other.isInList()) {
        next = this;
        prev = this;
        return;
      }

      MOZ_ASSERT(other.next->prev == &other);
      MOZ_ASSERT(other.prev->next == &other);

      /*
       * Initialize |this| with |other|'s prev/next pointers, and adjust those
       * element to point to this one.
       */
      next = other.next;
      prev = other.prev;

      next->prev = this;
      prev->next = this;

      /*
       * Adjust |other| so it doesn't think it's in a list.  This makes it
       * safely destructable.
       */
      other.next = &other;
      other.prev = &other;
    }

    ~LinkedListElement() {
      if (!isSentinel && isInList())
        remove();
    }

    /*
     * Get the next element in the list, or nullptr if this is the last element
     * in the list.
     */
    T* getNext() {
      return next->asT();
    }
    const T* getNext() const {
      return next->asT();
    }

    /*
     * Get the previous element in the list, or nullptr if this is the first
     * element in the list.
     */
    T* getPrevious() {
      return prev->asT();
    }
    const T* getPrevious() const {
      return prev->asT();
    }

    /*
     * Insert elem after this element in the list.  |this| must be part of a
     * linked list when you call setNext(); otherwise, this method will assert.
     */
    void setNext(T* elem) {
      MOZ_ASSERT(isInList());
      setNextUnsafe(elem);
    }

    /*
     * Insert elem before this element in the list.  |this| must be part of a
     * linked list when you call setPrevious(); otherwise, this method will
     * assert.
     */
    void setPrevious(T* elem) {
      MOZ_ASSERT(isInList());
      setPreviousUnsafe(elem);
    }

    /*
     * Remove this element from the list which contains it.  If this element is
     * not currently part of a linked list, this method asserts.
     */
    void remove() {
      MOZ_ASSERT(isInList());

      prev->next = next;
      next->prev = prev;
      next = this;
      prev = this;
    }

    /*
     * Identical to remove(), but also asserts in debug builds that this element
     * is in list.
     */
    void removeFrom(const LinkedList<T>& list) {
      list.assertContains(asT());
      remove();
    }

    /*
     * Return true if |this| part is of a linked list, and false otherwise.
     */
    bool isInList() const {
      MOZ_ASSERT((next == this) == (prev == this));
      return next != this;
    }

  private:
    friend class LinkedList<T>;

    enum NodeKind {
      NODE_KIND_NORMAL,
      NODE_KIND_SENTINEL
    };

    LinkedListElement(NodeKind nodeKind)
      : next(MOZ_THIS_IN_INITIALIZER_LIST()),
        prev(MOZ_THIS_IN_INITIALIZER_LIST()),
        isSentinel(nodeKind == NODE_KIND_SENTINEL)
    { }

    /*
     * Return |this| cast to T* if we're a normal node, or return nullptr if
     * we're a sentinel node.
     */
    T* asT() {
      if (isSentinel)
        return nullptr;

      return static_cast<T*>(this);
    }
    const T* asT() const {
      if (isSentinel)
        return nullptr;

      return static_cast<const T*>(this);
    }

    /*
     * Insert elem after this element, but don't check that this element is in
     * the list.  This is called by LinkedList::insertFront().
     */
    void setNextUnsafe(T* elem) {
      LinkedListElement *listElem = static_cast<LinkedListElement*>(elem);
      MOZ_ASSERT(!listElem->isInList());

      listElem->next = this->next;
      listElem->prev = this;
      this->next->prev = listElem;
      this->next = listElem;
    }

    /*
     * Insert elem before this element, but don't check that this element is in
     * the list.  This is called by LinkedList::insertBack().
     */
    void setPreviousUnsafe(T* elem) {
      LinkedListElement<T>* listElem = static_cast<LinkedListElement<T>*>(elem);
      MOZ_ASSERT(!listElem->isInList());

      listElem->next = this;
      listElem->prev = this->prev;
      this->prev->next = listElem;
      this->prev = listElem;
    }

  private:
    LinkedListElement& operator=(const LinkedListElement<T>& other) MOZ_DELETE;
    LinkedListElement(const LinkedListElement<T>& other) MOZ_DELETE;
};

template<typename T>
class LinkedList
{
  private:
    LinkedListElement<T> sentinel;

  public:
    LinkedList() : sentinel(LinkedListElement<T>::NODE_KIND_SENTINEL) { }

    LinkedList(LinkedList<T>&& other)
      : sentinel(mozilla::Move(other.sentinel))
    { }

    ~LinkedList() {
      MOZ_ASSERT(isEmpty());
    }

    /*
     * Add elem to the front of the list.
     */
    void insertFront(T* elem) {
      /* Bypass setNext()'s this->isInList() assertion. */
      sentinel.setNextUnsafe(elem);
    }

    /*
     * Add elem to the back of the list.
     */
    void insertBack(T* elem) {
      sentinel.setPreviousUnsafe(elem);
    }

    /*
     * Get the first element of the list, or nullptr if the list is empty.
     */
    T* getFirst() {
      return sentinel.getNext();
    }
    const T* getFirst() const {
      return sentinel.getNext();
    }

    /*
     * Get the last element of the list, or nullptr if the list is empty.
     */
    T* getLast() {
      return sentinel.getPrevious();
    }
    const T* getLast() const {
      return sentinel.getPrevious();
    }

    /*
     * Get and remove the first element of the list.  If the list is empty,
     * return nullptr.
     */
    T* popFirst() {
      T* ret = sentinel.getNext();
      if (ret)
        static_cast<LinkedListElement<T>*>(ret)->remove();
      return ret;
    }

    /*
     * Get and remove the last element of the list.  If the list is empty,
     * return nullptr.
     */
    T* popLast() {
      T* ret = sentinel.getPrevious();
      if (ret)
        static_cast<LinkedListElement<T>*>(ret)->remove();
      return ret;
    }

    /*
     * Return true if the list is empty, or false otherwise.
     */
    bool isEmpty() const {
      return !sentinel.isInList();
    }

    /*
     * Remove all the elements from the list.
     *
     * This runs in time linear to the list's length, because we have to mark
     * each element as not in the list.
     */
    void clear() {
      while (popFirst())
        continue;
    }

    /*
     * In a debug build, make sure that the list is sane (no cycles, consistent
     * next/prev pointers, only one sentinel).  Has no effect in release builds.
     */
    void debugAssertIsSane() const {
#ifdef DEBUG
      const LinkedListElement<T>* slow;
      const LinkedListElement<T>* fast1;
      const LinkedListElement<T>* fast2;

      /*
       * Check for cycles in the forward singly-linked list using the
       * tortoise/hare algorithm.
       */
      for (slow = sentinel.next,
           fast1 = sentinel.next->next,
           fast2 = sentinel.next->next->next;
           slow != &sentinel && fast1 != &sentinel && fast2 != &sentinel;
           slow = slow->next, fast1 = fast2->next, fast2 = fast1->next)
      {
        MOZ_ASSERT(slow != fast1);
        MOZ_ASSERT(slow != fast2);
      }

      /* Check for cycles in the backward singly-linked list. */
      for (slow = sentinel.prev,
           fast1 = sentinel.prev->prev,
           fast2 = sentinel.prev->prev->prev;
           slow != &sentinel && fast1 != &sentinel && fast2 != &sentinel;
           slow = slow->prev, fast1 = fast2->prev, fast2 = fast1->prev)
      {
        MOZ_ASSERT(slow != fast1);
        MOZ_ASSERT(slow != fast2);
      }

      /*
       * Check that |sentinel| is the only node in the list with
       * isSentinel == true.
       */
      for (const LinkedListElement<T>* elem = sentinel.next;
           elem != &sentinel;
           elem = elem->next)
      {
        MOZ_ASSERT(!elem->isSentinel);
      }

      /* Check that the next/prev pointers match up. */
      const LinkedListElement<T>* prev = &sentinel;
      const LinkedListElement<T>* cur = sentinel.next;
      do {
          MOZ_ASSERT(cur->prev == prev);
          MOZ_ASSERT(prev->next == cur);

          prev = cur;
          cur = cur->next;
      } while (cur != &sentinel);
#endif /* ifdef DEBUG */
    }

  private:
    friend class LinkedListElement<T>;

    void assertContains(const T* t) const {
#ifdef DEBUG
      for (const T* elem = getFirst();
           elem;
           elem = elem->getNext())
      {
        if (elem == t)
          return;
      }
      MOZ_CRASH("element wasn't found in this list!");
#endif
    }

    LinkedList& operator=(const LinkedList<T>& other) MOZ_DELETE;
    LinkedList(const LinkedList<T>& other) MOZ_DELETE;
};

} /* namespace mozilla */

#endif /* __cplusplus */

#endif /* mozilla_LinkedList_h */
