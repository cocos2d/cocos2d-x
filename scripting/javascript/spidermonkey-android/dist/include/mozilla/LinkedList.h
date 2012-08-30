/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 tw=80 et cin:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Code.
 *
 * The Initial Developer of the Original Code is
 *   The Mozilla Foundation
 * Portions created by the Initial Developer are Copyright (C) 2012
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Justin Lebar <justin.lebar@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* A type-safe doubly-linked list class. */

/*
 * The classes LinkedList<T> and LinkedListElement<T> together form a
 * convenient, type-safe doubly-linked list implementation.
 *
 * The class T which will be inserted into the linked list must inherit from
 * LinkedListElement<T>.  A given object may be in only one linked list at a
 * time.
 *
 * For example, you might use LinkedList in a simple observer list class as
 * follows.
 *
 *   class Observer : public LinkedListElement<Observer>
 *   {
 *     void observe(char* topic) { ... }
 *   };
 *
 *   class ObserverContainer
 *   {
 *   private:
 *     LinkedList<ElemType> list;
 *
 *   public:
 *
 *     void addObserver(Observer* observer)
 *     {
 *       // Will assert if |observer| is part of another list.
 *       list.insertBack(observer);
 *     }
 *
 *     void removeObserver(Observer* observer)
 *     {
 *       // Will assert if |observer| is not part of some list.
 *       observer.remove();
 *     }
 *
 *     void notifyObservers(char* topic)
 *     {
 *       for (Observer* o = list.getFirst();
 *            o != NULL;
 *            o = o->getNext()) {
 *         o->Observe(topic);
 *       }
 *     }
 *   };
 *
 */

#ifndef mozilla_LinkedList_h_
#define mozilla_LinkedList_h_

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"

#ifdef __cplusplus

namespace mozilla {

template<typename T>
class LinkedList;

template<typename T>
class LinkedListElement
{
    /*
     * It's convenient that we return NULL when getNext() or getPrevious() hits
     * the end of the list, but doing so costs an extra word of storage in each
     * linked list node (to keep track of whether |this| is the sentinel node)
     * and a branch on this value in getNext/getPrevious.
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
        : next(this)
        , prev(this)
        , isSentinel(false)
    {
    }

    /*
     * Get the next element in the list, or NULL if this is the last element in
     * the list.
     */
    T* getNext()
    {
        return next->asT();
    }

    /*
     * Get the previous element in the list, or NULL if this is the first element
     * in the list.
     */
    T* getPrevious()
    {
        return prev->asT();
    }

    /*
     * Insert elem after this element in the list.  |this| must be part of a
     * linked list when you call setNext(); otherwise, this method will assert.
     */
    void setNext(T* elem)
    {
        MOZ_ASSERT(isInList());
        setNextUnsafe(elem);
    }

    /*
     * Insert elem before this element in the list.  |this| must be part of a
     * linked list when you call setPrevious(); otherwise, this method will
     * assert.
     */
    void setPrevious(T* elem)
    {
        MOZ_ASSERT(isInList());
        setPreviousUnsafe(elem);
    }

    /*
     * Remove this element from the list which contains it.  If this element is
     * not currently part of a linked list, this method asserts.
     */
    void remove()
    {
        MOZ_ASSERT(isInList());

        prev->next = next;
        next->prev = prev;
        next = this;
        prev = this;
    }

    /*
     * Return true if |this| part is of a linked list, and false otherwise.
     */
    bool isInList()
    {
        MOZ_ASSERT((next == this) == (prev == this));
        return next != this;
    }

private:
    LinkedListElement& operator=(const LinkedList<T>& other) MOZ_DELETE;
    LinkedListElement(const LinkedList<T>& other) MOZ_DELETE;

    friend class LinkedList<T>;

    enum NodeKind {
        NODE_KIND_NORMAL,
        NODE_KIND_SENTINEL
    };

    LinkedListElement(NodeKind nodeKind)
        : next(this)
        , prev(this)
        , isSentinel(nodeKind == NODE_KIND_SENTINEL)
    {
    }

    /*
     * Return |this| cast to T* if we're a normal node, or return NULL if we're
     * a sentinel node.
     */
    T* asT()
    {
        if (isSentinel)
            return NULL;

        return static_cast<T*>(this);
    }

    /*
     * Insert elem after this element, but don't check that this element is in
     * the list.  This is called by LinkedList::insertFront().
     */
    void setNextUnsafe(T* elem)
    {
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
    void setPreviousUnsafe(T* elem)
    {
        LinkedListElement<T>* listElem = static_cast<LinkedListElement<T>*>(elem);
        MOZ_ASSERT(!listElem->isInList());

        listElem->next = this;
        listElem->prev = this->prev;
        this->prev->next = listElem;
        this->prev = listElem;
    }
};

template<typename T>
class LinkedList
{
private:
    LinkedListElement<T> sentinel;

public:
    LinkedList& operator=(const LinkedList<T>& other) MOZ_DELETE;
    LinkedList(const LinkedList<T>& other) MOZ_DELETE;

    LinkedList()
        : sentinel(LinkedListElement<T>::NODE_KIND_SENTINEL)
    {
    }

    /*
     * Add elem to the front of the list.
     */
    void insertFront(T* elem)
    {
        /* Bypass setNext()'s this->isInList() assertion. */
        sentinel.setNextUnsafe(elem);
    }

    /*
     * Add elem to the back of the list.
     */
    void insertBack(T* elem)
    {
        sentinel.setPreviousUnsafe(elem);
    }

    /*
     * Get the first element of the list, or NULL if the list is empty.
     */
    T* getFirst()
    {
        return sentinel.getNext();
    }

    /*
     * Get the last element of the list, or NULL if the list is empty.
     */
    T* getLast()
    {
        return sentinel.getPrevious();
    }

    /*
     * Get and remove the first element of the list.  If the list is empty,
     * return NULL.
     */
    T* popFirst()
    {
        T* ret = sentinel.getNext();
        if (ret)
            static_cast<LinkedListElement<T>*>(ret)->remove();

        return ret;
    }

    /*
     * Get and remove the last element of the list.  If the list is empty,
     * return NULL.
     */
    T* popLast()
    {
        T* ret = sentinel.getPrevious();
        if (ret)
            static_cast<LinkedListElement<T>*>(ret)->remove();

        return ret;
    }

    /*
     * Return true if the list is empty, or false otherwise.
     */
    bool isEmpty()
    {
        return !sentinel.isInList();
    }

    /*
     * Remove all the elements from the list.
     *
     * This runs in time linear to the list's length, because we have to mark
     * each element as not in the list.
     */
    void clear()
    {
        while (popFirst())
            continue;
    }

    /*
     * In a debug build, make sure that the list is sane (no cycles, consistent
     * next/prev pointers, only one sentinel).  Has no effect in release builds.
     */
    void debugAssertIsSane()
    {
#ifdef DEBUG
        /*
         * Check for cycles in the forward singly-linked list using the
         * tortoise/hare algorithm.
         */
        for (LinkedListElement<T>* slow = sentinel.next,
                                 * fast1 = sentinel.next->next,
                                 * fast2 = sentinel.next->next->next;
             slow != sentinel && fast1 != sentinel && fast2 != sentinel;
             slow = slow->next,
             fast1 = fast2->next,
             fast2 = fast1->next) {

            MOZ_ASSERT(slow != fast1);
            MOZ_ASSERT(slow != fast2);
        }

        /* Check for cycles in the backward singly-linked list. */
        for (LinkedListElement<T>* slow = sentinel.prev,
                                 * fast1 = sentinel.prev->prev,
                                 * fast2 = sentinel.prev->prev->prev;
             slow != sentinel && fast1 != sentinel && fast2 != sentinel;
             slow = slow->prev,
             fast1 = fast2->prev,
             fast2 = fast1->prev) {

            MOZ_ASSERT(slow != fast1);
            MOZ_ASSERT(slow != fast2);
        }

        /*
         * Check that |sentinel| is the only node in the list with
         * isSentinel == true.
         */
        for (LinkedListElement<T>* elem = sentinel.next;
             elem != sentinel;
             elem = elem->next) {

          MOZ_ASSERT(!elem->isSentinel);
        }

        /* Check that the next/prev pointers match up. */
        LinkedListElement<T>* prev = sentinel;
        LinkedListElement<T>* cur = sentinel.next;
        do {
            MOZ_ASSERT(cur->prev == prev);
            MOZ_ASSERT(prev->next == cur);

            prev = cur;
            cur = cur->next;
        } while (cur != sentinel);
#endif /* ifdef DEBUG */
    }
};

} /* namespace mozilla */

#endif /* ifdef __cplusplus */
#endif /* ifdef mozilla_LinkedList_h_ */
