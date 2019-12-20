/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_ContainerUtil_h
#define Spine_ContainerUtil_h

#include <spine/Extension.h>
#include <spine/Vector.h>
#include <spine/HashMap.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

#include <assert.h>

namespace spine {
	class SP_API ContainerUtil : public SpineObject {
	public:
		/// Finds an item by comparing each item's name.
		/// It is more efficient to cache the results of this method than to call it multiple times.
		/// @return May be NULL.
		template<typename T>
		static T* findWithName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0; i < items.size(); ++i) {
				T* item = items[i];
				if (item->getName() == name) {
					return item;
				}
			}

			return NULL;
		}

		/// @return -1 if the item was not found.
		template<typename T>
		static int findIndexWithName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0, len = items.size(); i < len; ++i) {
				T* item = items[i];
				if (item->getName() == name) {
					return static_cast<int>(i);
				}
			}

			return -1;
		}

		/// Finds an item by comparing each item's name.
		/// It is more efficient to cache the results of this method than to call it multiple times.
		/// @return May be NULL.
		template<typename T>
		static T* findWithDataName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0; i < items.size(); ++i) {
				T* item = items[i];
				if (item->getData().getName() == name) {
					return item;
				}
			}

			return NULL;
		}

		/// @return -1 if the item was not found.
		template<typename T>
		static int findIndexWithDataName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0, len = items.size(); i < len; ++i) {
				T* item = items[i];
				if (item->getData().getName() == name) {
					return static_cast<int>(i);
				}
			}

			return -1;
		}

		template<typename T>
		static void cleanUpVectorOfPointers(Vector<T*>& items) {
			for (int i = (int)items.size() - 1; i >= 0; i--) {
				T* item = items[i];

				delete item;

				items.removeAt(i);
			}
		}

	private:
		// ctor, copy ctor, and assignment should be private in a Singleton
		ContainerUtil();
		ContainerUtil(const ContainerUtil&);
		ContainerUtil& operator=(const ContainerUtil&);
	};
}

#endif /* Spine_ContainerUtil_h */
