#ifndef SkViewPriv_DEFINED
#define SkViewPriv_DEFINED

#include "SkView.h"
#include "SkTagList.h"

struct Layout_SkTagList : SkTagList {
	SkView::Layout*	fLayout;

	Layout_SkTagList(SkView::Layout* layout)
		: SkTagList(kViewLayout_SkTagList), fLayout(layout)
	{
		SkASSERT(layout);
		layout->ref();
	}
	virtual ~Layout_SkTagList()
	{
		fLayout->unref();
	}
};

struct Artist_SkTagList : SkTagList {
	SkView::Artist*	fArtist;

	Artist_SkTagList(SkView::Artist* artist)
		: SkTagList(kViewArtist_SkTagList), fArtist(artist)
	{
		SkASSERT(artist);
		artist->ref();
	}
	virtual ~Artist_SkTagList()
	{
		fArtist->unref();
	}
};

#endif

