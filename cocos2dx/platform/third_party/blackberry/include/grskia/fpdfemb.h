// FPDFEMB.H - Header file for FPDFEMB SDK
// Copyright (c) 2007-2008 Foxit Software Company, All Right Reserved.

// Date: 2008-04-07

// Embedded platforms have many different aspects from desktop platforms,
// among them, the followings are most important for PDF processing:
//
// 1.	Embedded platforms have only limited memory, and there is no virtual memory.
//		PDF is a very complicated format, processing PDF may consumes quite
//		large amount of memory, even for some smaller PDFs. And, in order to 
//		increase the performance of PDF parsing and rendering, cache memory
//		is often used. For some big PDFs with many pages, the cache may grow
//		while user browing through pages, eventually, for some PDFs, the memory
//		on the device may run out.
//
//		FPDFEMB SDK allows graceful out-of-memory (OOM) handling by returning 
//		OOM error code for all functions that may involve memory allocation. 
//		When an application detects OOM situation, it can do one of the followings:
//
//			a) Give user some prompt and quit the application or close the document;
//			b) Or better, try to recover from the error. Sometimes OOM can be caused
//				by ever-growing cache. For example, when user browses a 1000-page 
//				document, let's say OOM happen at page #300. In this case, the
//				application might close the whole document (cache will be gone with
//				it), reopen the document, then go directly to page #300. It's likely
//				the process will go through this time. This is called "OOM recovery".
//				If OOM happens again during a recovery, then, it's not possible to finish
//				the process, the application must quit of close the document.
//
// 2.	Embedded platforms has only limited computing power. Since some PDFs
//		can be very complicated and require a lot of processing to be displayed,
//		it may take a lot of time for the process to finish. This may cause
//		some problem with user experience, especially for devices like mobile
//		phones, when an application may need to be put on hold any time. Therefore, 
//		it's important to break lengthy process into small steps which can be 
//		stopped or resumed at any time. We call this kind of process as 
//		"progressive process".
//
//		FPDFEMB SDK allows progressive page parsing and rendering, the most time-
//		consuming part of PDF processing.
//
// IMPORTANT:
//		FPDFEMB module is not intended to run in multi-threaded environment.

// Components inside FPDFEMB:
//		* Library Memory Management
//		* Document Operations
//		* Page Basic Operations
//		* Page Parsing
//		* Page Rendering
//		* Coordination Conversion
//		* Text Search
//		* Text Information
//		* Device Independant Bitmap
//		* Custom Font Handler and CJK Support
//		* Bookmark Information
//		* Hyperlink Information
//		* Graphic Output

#ifndef _FPDFEMB_H_
#define _FPDFEMB_H_

#ifdef __cplusplus
extern "C" {
#endif

// Standard return type for many FPDFEMB functions: FPDFERR_SUCCESS for success, otherwise error code
typedef int FPDFEMB_RESULT;

// Standard boolean type: 0 for false, non-zero for true
typedef int FPDFEMB_BOOL;

// Unicode character. FPDFEMB uses UTF16LE format for unicode string.
typedef unsigned short FPDFEMB_WCHAR;

// Error codes
#define FPDFERR_SUCCESS		0
#define FPDFERR_MEMORY		1		// Out of memory
#define FPDFERR_ERROR		2		// Error of any kind, without specific reason
#define FPDFERR_PASSWORD	3		// Incorrect password
#define FPDFERR_FORMAT		4		// Not PDF format
#define FPDFERR_FILE		5		// File access error
#define FPDFERR_PARAM		6		// Parameter error
#define FPDFERR_STATUS		7		// Not in correct status
#define FPDFERR_TOBECONTINUED	8	// To be continued
#define FPDFERR_NOTFOUND	9		// Search result not found

/********************************************************************************************
****
****		Library Memory Management
****
********************************************************************************************/

// Structure: FPDFEMB_MEMMGR
//			Including interfaces implemented by host application, providing memory allocation
//			facilities. All members are required.
//			A memory manager structure is required to be valid during the entire period
//			when an application using FPDFEMB module.
//
//			IMPORTANT NOTE: using of this interface is strongly not recommended, because
//			FPDFEMB now internally use FPDFEMB_MEMMGR_EX interface, which allows more
//			advanced memory management. This interface is retained for backward compatibility
//			only, and maybe discontinued in the future.
//
struct FPDFEMB_MEMMGR {
	// Interface: Alloc
	//		Allocate a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		size		-	Number of bytes for the memory block.
	// Return Value:
	//		The pointer to allocated memory block. NULL if no memory available.
	// Comments:
	//		In order to handle OOM situation, application can use longjmp() inside 
	//		implementation of this function. If underlying memory manager fails to 
	//		allocate enough memory, then application can use longjmp() to jump to
	//		OOM handling codes.
	//
	void*	(*Alloc)(struct FPDFEMB_MEMMGR* pMgr, unsigned int size);

	// Interface: AllocNL
	//		Allocate a memory block, without leaving
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		size		-	Number of bytes for the memory block.
	// Return Value:
	//		The pointer to allocated memory block. NULL if no memory available.
	// Comments:
	//		Implementation MUST return NULL if no memory available, no exception
	//		or longjmp() can be used.
	//
	void*	(*AllocNL)(struct FPDFEMB_MEMMGR* pMgr, unsigned int size);

	// Interfce: Realloc
	//		Reallocate a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		pointer		-	An existing memory block, or NULL.
	//		new_size	-	New size (number of bytes) of the memory block. Can be zero.
	// Return value:
	//		The pointer of reallocated memory block, it could be a new block, or just
	//		the previous block with size modified.
	// Comments:
	//		If an existing memory block specified, the data in the memory block will
	//		be copied to the new block, if reallocated.
	//
	//		In order to handle OOM situation, application can use longjmp() inside 
	//		implementation of this function. If underlying memory manager fails to 
	//		allocate enough memory, then application can use longjmp() to jump to
	//		OOM handling codes.
	//
	void*	(*Realloc)(struct FPDFEMB_MEMMGR* pMgr, void* pointer, unsigned int new_size);

	// Interface: Free
	//		Free a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		pointer		-	An existing memory block.
	// Return Value:
	//		None.
	//
	void	(*Free)(struct FPDFEMB_MEMMGR* pMgr, void* pointer);
};

// Function: FPDFEMB_Init
//			Initialize the FPDFEMB module
// Parameters:
//			mem_mgr		-	Pointer to memory manager structure
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			This function will allocate necessary internal data structure for
//			the whole module to operate.
FPDFEMB_RESULT FPDFEMB_Init(FPDFEMB_MEMMGR* mem_mgr);

typedef void (*FPDFEMB_FIXED_OOM_HANDLER)(void* memory, int size);

// Function: FPDFEMB_InitFixedMemory
//			Initialize the FPDFEMB module, providing a fixed memory heap
// Parameters:
//			memory		-	Pointer to a pre-allocated memory block
//			size		-	Number of bytes in the memory block
//			oom_handler	-	Pointer to a function which will be called when OOM happens. Can be
//							NULL if application doesn't want to be notified om OOM.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			In many embedded system, memory usage are predetermined. The application
//			is assigned with fixed size of available memory, then it can pre-allocate
//			a memory block with maximum size and pass to this function to initialize
//			FPDFEMB module. In this case, FPDFEMB won't need any additional memory
//			allocation.
//
//			In case the pre-allocated memory has run out, the "oom_proc" callback
//			function will be called to notify the application that an OOM recovery
//			procedure needs to be performed.
//
FPDFEMB_RESULT FPDFEMB_InitFixedMemory(void* memory, int size, FPDFEMB_FIXED_OOM_HANDLER oom_handler);

// Memory Management Flags
#define FPDFEMB_NONLEAVE		1
#define FPDFEMB_MOVABLE			2
#define FPDFEMB_DISCARDABLE		4

// Structure: FPDFEMB_MEMMGR_EX
//			This is an extended version of memory manager interface, allowing advanced
//			memory management, including movable and discardable memory blocks.
//
//			Use this interface with FPDFEMB_InitExt function.
//
struct FPDFEMB_MEMMGR_EX {
	// Interface: Alloc
	//		Allocate a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		size		-	Number of bytes for the memory block.
	//		flags		-	A combination of flags defined above.
	// Return Value:
	//		The pointer to allocated memory block. NULL if no memory available.
	//		If FPDFEMB_MOVABLE flag is used, implementation should return a handle
	//		to the memory block, if it supports movable block allocation.
	// Comments:
	//		The implementation should not do any action if no memory available,
	//		just return NULL. OOM handling can be done in OOM_Handler interface.
	//
	void*	(*Alloc)(struct FPDFEMB_MEMMGR_EX* pMgr, unsigned int size, int flags);

	// Interface: OOM_Handler
	//		OOM (out-of-memory) situation handler
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	// Return Value:
	//		None.
	// Comments:
	//		In order to handle OOM situation, application can use longjmp() inside 
	//		implementation of this function.
	//
	void	(*OOM_Handler)(struct FPDFEMB_MEMMGR_EX* pMgr);

	// Interfce: Realloc
	//		Reallocate a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		pointer		-	Pointer to an existing memory block, or handle to a movable
	//						block. Can not be NULL.
	//		new_size	-	New size (number of bytes) of the memory block. Can not be zero.
	// Return value:
	//		The pointer of reallocated memory block, it could be a new block, or just
	//		the previous block with size modified.
	//		If FPDFEMB_MOVABLE flag is used, implementation should return a handle
	//		to the memory block, if it supports movable block allocation.
	// Comments:
	//		If an existing memory block specified, the data in the memory block should
	//		be copied to the new block, if reallocated.
	//
	//		The implementation should not do any action if no memory available,
	//		just return NULL. OOM handling can be done in OOM_Handler interface.
	//
	void*	(*Realloc)(struct FPDFEMB_MEMMGR_EX* pMgr, void* pointer, unsigned int new_size, int flags);

	// Interface: Lock
	//		Lock a movable memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		handle		-	Handle to movable memory block, returned by Alloc or Realloc.
	// Return Value:
	//		The pointer of the memory block. NULL if the block was discarded.
	// Comments:
	//		This interface is optional, if implementation doesn't support movable memory
	//		block, then this interface can be set to NULL.
	//
	void*	(*Lock)(struct FPDFEMB_MEMMGR_EX* pMgr, void* handle);

	// Interface: Unlock
	//		Unlock a locked movable memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		handle		-	Handle to movable memory block, returned by Alloc or Realloc.
	// Return Value:
	//		None.
	// Comments:
	//		This interface is optional, if implementation doesn't support movable memory
	//		block, then this interface can be set to NULL.
	//
	void	(*Unlock)(struct FPDFEMB_MEMMGR_EX* pMgr, void* handle);

	// Interface: Free
	//		Free a memory block
	// Parameters:
	//		pMgr		-	Pointer to the memory manager.
	//		pointer		-	Pointer to an existing memory block, or handle to a movable block.
	// Return Value:
	//		None.
	//
	void	(*Free)(struct FPDFEMB_MEMMGR_EX* pMgr, void* pointer, int flags);

	void*	user;		// A user pointer, used by the application
};

// Function: FPDFEMB_LoadJbig2Decoder
// Function: FPDFEMB_LoadJpeg2000Decoder
//			Enable JBIG2 or JPEG2000 image decoder 
// Parameters:
//			None.
// Return Value:
//			None.
// Comments:
//			If you want to display JBIG2 or JPEG2000 encoded images, you need to call 
//			these functions after FPDFEMB initialized.
//
//			Calling these functions will increase code size by about 200K-400K bytes.
//			Also JPEG2000 decoder may not be available on some platforms.
//
void FPDFEMB_LoadJbig2Decoder();
void FPDFEMB_LoadJpeg2000Decoder();

// Function: FPDFEMB_InitEx
//			Initialize the FPDFEMB module with the extended memory manager
// Parameters:
//			mem_mgr		-	Pointer to memory manager structure
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			This function will allocate necessary internal data structure for
//			the whole module to operate.
FPDFEMB_RESULT FPDFEMB_InitEx(FPDFEMB_MEMMGR_EX* mem_mgr);

// Function: FPDFEMB_Exit
//			Stop using FPDFEMB module and release all resources
// Parameters:
//			None.
// Return Value:
//			None.
// Comments:
//			All loaded documents and pages will become invalid after this call.
//
//			This function is useful for OOM recovery: when your application hits
//			an OOM situation, calling this function will clear all memory allocated
//			by FPDFEMB module, then you can call one of the initialization functions,
//			reopen the document and recovery from OOM.
//
void FPDFEMB_Exit();

// Function: FPDFEMB_AllocMemory
//			Allocate memory
// Parameters:
//			size		-	Number of bytes
// Return Value:
//			The allocated buffer pointer. NULL for out of memory.
//
void* FPDFEMB_AllocMemory(unsigned int size);

// Function: FPDFEMB_FreeMemory
//			Free allocated memory
// Parameters:
//			pointer		-	Pointer returned by FPDFEMB_AllocMemory
// Return Value:
//			None.
//
void FPDFEMB_FreeMemory(void* pointer);

// Function: FPDFEMB_FreeCaches
//			Free all expendable caches used by FPDFEMB in order to save memory
// Parameters:
//			None.
// Return Value:
//			None.
// Comments:
//			When an application memory manager runs out of memory, before an OOM situation 
//			is raised, the application can try this 
//
void FPDFEMB_FreeCaches();

/********************************************************************************************
****
****		Document Operations
****
********************************************************************************************/

// Structure: FPDFEMB_FILE_ACCESS
//		Describe the way to access a file (readonly).
struct FPDFEMB_FILE_ACCESS {
	// Inteface: GetSize
	//		Get total size of the file
	// Parameters:
	//		file		-	Pointer to this file access structure
	// Return Value:
	//		File size, in bytes. Implementation can return 0 for any error.
	// 
	unsigned int	(*GetSize)(struct FPDFEMB_FILE_ACCESS* file);

	// Interface: ReadBlock
	//		Read a data block from the file
	// Parameters:
	//		file		-	Pointer to this file access structure
	//		buffer		-	Pointer to a buffer receiving read data
	//		offset		-	Byte offset for the block, from beginning of the file
	//		size		-	Number of bytes for the block.
	// Return Value:
	//		Error code, or FPDFERR_SUCCESS for success.
	//
	FPDFEMB_RESULT	(*ReadBlock)(struct FPDFEMB_FILE_ACCESS* file, void* buffer, 
									unsigned int offset, unsigned int size);

	void*		user;		// A user pointer, used by the application
};

// Structure: FPDFEMB_PAUSE
//			An interface for pausing a progressive process.
struct FPDFEMB_PAUSE {
	// Interface: NeedPauseNow
	//		Check if we need to pause a progressive proccess now
	// Parameters:
	//		pause		-	Pointer to the pause structure
	// Return Value:
	//		Non-zero for pause now, 0 for continue.
	// Comments:
	//		Typically implementation of this interface compares the current system tick
	//		with the previous one, if the time elapsed exceeds certain threshold, then
	//		the implementation returns TRUE, indicating a pause is needed.
	//
	FPDFEMB_BOOL (*NeedPauseNow)(struct FPDFEMB_PAUSE* pause);

	void*		user;		// A user pointer, used by the application
};

typedef void* FPDFEMB_DOCUMENT;

// Function: FPDFEMB_StartLoadDocument
//			Start loading a PDF document
// Parameters:
//			file		-	Pointer to file access structure.
//							This structure must be kept valid as long as the document is open.
//			password	-	Pointer to a zero-terminated byte string, for the password.
//							Or NULL for no password.
//			document	-	Receiving the document handle
//			pause		-	A callback mechanism allowing the document loading process
//							to be paused before it's finished. This can be NULL if you
//							don't want to pause.
// Return Value:
//			FPDFERR_SUCCESS: document successfully loaded.
//			FPDFERR_TOBECONTINUED: The document loading can't be finished now.
//					See comments below.
//			FPDFERR_PASSWORD: incorrect password.
//			FPDFERR_FORMAT: not a PDF or corrupted PDF.
//			FPDFERR_FILE: file access error.
//			FPDFERR_MEMORY: out of memory.
// Comments:
//			Document loading is a progressive process. It might take a long time to
//			load a document, especiall when a file is corrupted, FPDFEMB will try to
//			recover the document contents by scanning the whole file. If "pause" parameter
//			is provided, this function may return FPDFERR_TOBECONTINUED any time during
//			the document loading.
//
//			When FPDFERR_TOBECONTINUED is returned, the "document" parameter will
//			still receive a valid document handle, however, no further operations can
//			be performed on the document, except the "FPDFEMB_ContineLoadDocument" function
//			call, which resume the document loading.
//
FPDFEMB_RESULT FPDFEMB_StartLoadDocument(FPDFEMB_FILE_ACCESS* file, const char* password, 
									FPDFEMB_DOCUMENT* document, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_ContinueLoadDocument
//			Continue loading a PDF document
// Parameters:
//			document	-	Document handle returned by FPDFEMB_StartLoadDocument function
//			pause		-	A callback mechanism allowing the document loading process
//							to be paused before it's finished. This can be NULL if you
//							don't want to pause.
// Return Value:
//			FPDFERR_SUCCESS: document successfully loaded.
//			FPDFERR_TOBECONTINUED: The document loading can't be finished now.
//					Further call to this function is needed.
//			FPDFERR_PASSWORD: incorrect password.
//			FPDFERR_FORMAT: not a PDF or corrupted PDF.
//			FPDFERR_FILE: file access error.
//			FPDFERR_MEMORY: out of memory.
//			FPDFERR_STATUS: document already loaded.
//			FPDFERR_PARAM: invalid parameter (like NULL document handle)
//
FPDFEMB_RESULT FPDFEMB_ContinueLoadDocument(FPDFEMB_DOCUMENT document, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_CloseDocument
//			Close a PDF document and free all associated resources
// Parameters:
//			document	-	Document handle
// Return Value:
//			Error code. FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_CloseDocument(FPDFEMB_DOCUMENT document);

// Function: Get page count
//			Get number of pages in the document
// Parameters:
//			document	-	Document handle
// Return Value:
//			Number of pages.
//
int FPDFEMB_GetPageCount(FPDFEMB_DOCUMENT document);

// Function: FPDFEMB_SetFileBufferSize
//			Set size of internal buffer used to read from source file.
// Parameters:
//			size		-	Number of bytes
// Return Value:
//			None.
// Comments:
//			Currently FPDFEMB uses 512 bytes as default buffer size. The new buffer size 
//			takes effect next time you call FPDFEMB_StartLoadDocument.
//
void FPDFEMB_SetFileBufferSize(int size);

/********************************************************************************************
****
****		Page Basic Operations
****
********************************************************************************************/

typedef void* FPDFEMB_PAGE;

// Function: FPDFEMB_LoadPage
//			Load a page
// Parameters:
//			document	-	Document handle
//			index		-	Page index, starting from zero
//			page		-	Receiving the loaded page handler
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_LoadPage(FPDFEMB_DOCUMENT document, int index, FPDFEMB_PAGE* page);

// Function: FPDFEMB_ClosePage
//			Close a page and release all related resources
// Parameters:
//			page		-	Page handle
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_ClosePage(FPDFEMB_PAGE page);

// Function: FPDFEMB_GetPageSize
//			Get size of a page
// Parameters:
//			page		-	Page handle
//			width		-	Receiving page width, in hundredth of points
//			height		-	Receiving page height, in hundredth of points
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_GetPageSize(FPDFEMB_PAGE page, int* width, int* height);

// Structure: FPDFEMB_RECT
//			Rectangle area in device or page coordination system
//
struct FPDFEMB_RECT
{
	// For device system, coordinations are measured in pixels;
	// For page system, coordinations are measured in hundredth of points.
	int		left;
	int		top;
	int		right;
	int		bottom;
};

// Function: FPDFEMB_GetPageBBox
//			Get displayable area (bounding box) of a page
// Parameters:
//			page		-	Page handle
//			rect		-	Pointer to a structure receiving the rectangle
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_GetPageBBox(FPDFEMB_PAGE page, FPDFEMB_RECT* rect);

/********************************************************************************************
****
****		Page Parsing
****
********************************************************************************************/

// Function: FPDFEMB_StartParse
//			Start parsing a page, so it can get rendered or searched
// Parameters:
//			page		-	Page handle
//			text_only	-	flag for parsing texts only (used for searching)
//			pause		-	A structure that can pause the parsing process.
//							Or NULL if you don't want to pause the process.
// Return Value:
//			FPDFERR_SUCCESS: parsing successfully finished;
//			FPDFERR_TOBECONTINUED: parsing started successfully, but not finished;
//			FPDFERR_STATUS: page already parsed, or parsing already started. 
//			Other return value: error code.
// Comments:
//			Parsing is a progressive process. This function starts the parsing process,
//			and may return before parsing is finished, if a pause structure is provided.
//
//			Application should call FPDFEMB_ContinueParse repeatedly to finish the parsing
//			when return value is FPDFERR_TOBECONTINUED.
//
//			There can be only one parsing procedure active for a page, and if a page
//			has already been parsed, you can't start a parsing again.
//
FPDFEMB_RESULT FPDFEMB_StartParse(FPDFEMB_PAGE page, FPDFEMB_BOOL text_only, 
												FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_ContinueParse
//			Continue the page parsing
// Parameters:
//			page		-	Page handle
//			pause		-	A structure that can pause the parsing process.
//							Or NULL if you don't want to pause the process.
// Return Value:
//			FPDFERR_SUCCESS: parsing successfully finished;
//			FPDFERR_TOBECONTINUED: parsing performed successfully, but not finished;
//			FPDFERR_STATUS: page already parsed (or parsing not started). 
//			Other return value: error code.
// Comments:
//			FPDFEMB_StartParse should be called before on the page.
//
//			Application should call FPDFEMB_ContinueParse repeatedly to finish the parsing
//			when return value is FPDFERR_TOBECONTINUED.
//
FPDFEMB_RESULT FPDFEMB_ContinueParse(FPDFEMB_PAGE page, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_GetParseProgress
//			Get an estimated parsing progress in percentage
// Parameters:
//			page		-	Page handle
// Return Value:
//			An integer between 0 and 100 (inclusive) indicating the parsing progress.
//			The result is just a rough estimation.
//
int FPDFEMB_GetParseProgress(FPDFEMB_PAGE page);

/********************************************************************************************
****
****		Page Rendering
****
********************************************************************************************/

typedef void* FPDFEMB_BITMAP;

// Function: FPDFEMB_StartQuickDraw
//			Start drawing a quick preview of a page
// Parameters:
//			dib			-	DIB handle, as the rendering device
//			page		-	Page handle. The page has to be parsed first.
//			start_x		-	Left pixel position of the display area in the device coordination
//			start_y		-	Top pixel position of the display area in the device coordination
//			size_x		-	Horizontal size (in pixels) for displaying the page
//			size_y		-	Vertical size (in pixels) for displaying the page
//			rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
//								2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
//			flags		-	Reserved, must be zero.
//			pause		-	Pointer to a structure that can pause the rendering process.
//							Can be NULL if no pausing is needed.
// Return Value:
//			FPDFERR_SUCCESS: quickdraw successly finished;
//			FPDFERR_TOBECONTINUED: quickdraw started successfully, but not finished.
//							FPDFEMB_ContinueQuickDraw needs to be called to finish the quickdraw;
//			FPDFERR_STATUS: quickdraw already in progress, or page not parsed;
//			Other return value: error code.
// Comments:
//			It's often useful to present user a quick preview of a page, right after the
//			page is parsed. This preview renders only a limited set of easy features in the
//			page, so it'll be rather quick to finish this process.
//
FPDFEMB_RESULT FPDFEMB_StartQuickDraw(FPDFEMB_BITMAP dib, FPDFEMB_PAGE page,
							int start_x, int start_y, int size_x, int size_y, int rotate,
							int flags, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_ContinueQuickDraw
//			Continue a quick draw processing
// Parameters:
//			page		-	Page handle. The page has to be parsed first.
//			pause		-	Pointer to a structure that can pause the rendering process.
//							Can be NULL if no pausing is needed.
// Return Value:
//			FPDFERR_SUCCESS: quickdraw successly finished;
//			FPDFERR_TOBECONTINUED: quickdraw started successfully, but not finished.
//							more calls to this function needed to finish the quickdraw;
//			FPDFERR_STATUS: quickdraw not started yet; 
//			Other return value: error code.
//
FPDFEMB_RESULT FPDFEMB_ContinueQuickDraw(FPDFEMB_PAGE page, FPDFEMB_PAUSE* pause);

#define FPDFEMB_ANNOT			0x01		// Set if annotations are to be rendered
#define FPDFEMB_LCD_TEXT		0x02		// Set if using text rendering optimized for LCD display
#define FPDFEMB_BGR_STRIPE		0x04		// Set if the device is using BGR LCD stripe

// Function: FPDFEMB_StartRender
//			Start rendering of a page.
// Parameter:
//			dib			-	DIB handle, as the rendering device
//			page		-	Page handle. The page has to be parsed first.
//			start_x		-	Left pixel position of the display area in the device coordination
//			start_y		-	Top pixel position of the display area in the device coordination
//			size_x		-	Horizontal size (in pixels) for displaying the page
//			size_y		-	Vertical size (in pixels) for displaying the page
//			rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
//								2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
//			flags		-	0 for normal display, or combination of flags defined above
//			clip		-	Pointer to clip rectangle (in DIB device coordinations),
//							or NULL if no clipping needed.
//			pause		-	Pointer to a structure that can pause the rendering process.
//							Can be NULL if no pausing is needed.
// Return Value:
//			FPDFERR_SUCCESS: rendering successfully finished;
//			FPDFERR_TOBECONTINUED: rendering started successfully, but not finished;
//			Other return value: error code.
// Comments:
//			Rendering is a progressive process. This function starts the rendering process,
//			and may return before rendering is finished, if a pause structure is provided.
//
//			Application should call FPDFEMB_ContinueRender repeatedly to finish the rendering 
//			when return value is FPDFERR_TOBECONTINUED.
//
//			There can be only one rendering procedure for a page at any time. And rendering
//			can be started over and over again for the same page. If a page rendering is already
//			active, starting another one will cancel the previous rendering.
//
//			Rendering of a page doesn't draw the page background, therefore, you usually need
//			to draw the background in the DIB yourself.
//
FPDFEMB_RESULT FPDFEMB_StartRender(FPDFEMB_BITMAP dib, FPDFEMB_PAGE page,
						int start_x, int start_y, int size_x, int size_y, int rotate, int flags,
						FPDFEMB_RECT* clip, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_ContinueRender
//			Continue the page rendering
// Parameters:
//			page		-	Page handle
//			pause		-	Pointer to a structure that can pause the rendering process.
//							Can be NULL if no pausing is needed.
// Return Value:
//			FPDFERR_SUCCESS: rendering successfully finished.
//			FPDFERR_TOBECONTINUED: rendering needs to be continued;
//			Other return value: error code.
// Comments:
//			This function may return any time when the pause interface indicates 
//			a pause is needed. Application can call FPDFEMB_ContinueRender any number
//			of times, until FPDFERR_TOBECONTINUED is not returned.
//
FPDFEMB_RESULT FPDFEMB_ContinueRender(FPDFEMB_PAGE page, FPDFEMB_PAUSE* pause);

// Function: FPDFEMB_GetRenderProgress
//			Get an estimated rendering progress in percentage
// Parameters:
//			page		-	Page handle
// Return Value:
//			An integer between 0 and 100 (inclusive) indicating the rendering progress.
//			The result is just a rough estimation.
//			If the rendering just finished, this function will return 0.
//
int FPDFEMB_GetRenderProgress(FPDFEMB_PAGE page);

// Function: FPDFEMB_SetHalftoneLimit
//			Set pixel count limit for using halftone when display image
// Parameter:
//			limit		-	Number of pixels for the limit
// Return Value:
//			None.
// Comments:
//			By default, FPDFEMB displays all bitmaps using downsamping, which means
//			if the image is shrinked onto screen, only part of pixels will be picked
//			and displayed. This saves a lot of calculation, especially for big images
//			with millions of pixels. However the display quality can be bad. In order to
//			reach a balance between performance and quality, application can use this
//			function to set a limit, if number of pixels in an image is more than this
//			limit, then FPDFEMB will use downsampling for quick drawing, otherwise, if
//			the image has less pixels, FPDFEMB will use halftoning for better quality.
//
void FPDFEMB_SetHalftoneLimit(int limit);

/********************************************************************************************
****
****		Coordination Conversion
****
********************************************************************************************/

// Structure: FPDFEMB_POINT
//			A point in device or page coordination system
//
struct FPDFEMB_POINT
{
	// For device system, coordinations are measured in pixels;
	// For page system, coordinations are measured hundredth of points.
	int		x;
	int		y;
};

// Function: FPDFEMB_DeviceToPagePoint, FPDFEMB_DeviceToPageRect
//			Convert the device coordinations of a point or a rectangle to page coordinations.
// Parameters:
//			page		-	Handle to the page. Returned by FPDFEMB_LoadPage function.
//			start_x		-	Left pixel position of the display area in the device coordination
//			start_y		-	Top pixel position of the display area in the device coordination
//			size_x		-	Horizontal size (in pixels) for displaying the page
//			size_y		-	Vertical size (in pixels) for displaying the page
//			rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
//								2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
//			point		-	A point structure with device coordinations upon the call,
//							also receiving the result page coordinations.
//			rect		-	A rectangle structure with device coordinations upon the call,
//							also receiving the result page coordinations.
// Return value:
//			None.
// Comments:
//			The page coordination system has its origin at left-bottom corner of the page, 
//			with X axis goes along the bottom side to the right, and Y axis goes along the 
//			left side upward. No matter how you zoom, scroll, or rotate a page, a particular
//			element (like text or image) on the page should always have the same coordination 
//			values in the page coordination system. 
//
//			The device coordination system is device dependant. For bitmap device, its origin 
//			is at left-top corner of the window. You must make sure the start_x, start_y, size_x, 
//			size_y and rotate parameters have exactly same values as you used in 
//			FPDFEMB_StartRender() function call.
//
//			For rectangle conversion, the result rectangle is always "normalized", meaning for
//			page coordinations, left is always smaller than right, bottom is smaller than top.
//
void FPDFEMB_DeviceToPagePoint(FPDFEMB_PAGE page, 
						int start_x, int start_y, int size_x, int size_y, int rotate, 
						FPDFEMB_POINT* point);

void FPDFEMB_DeviceToPageRect(FPDFEMB_PAGE page, 
						int start_x, int start_y, int size_x, int size_y, int rotate, 
						FPDFEMB_RECT* rect);

// Function: FPDFEMB_PageToDevicePoint, FPDFEMB_PageToDeviceRect
//			Convert the page coordinations of a point or a rectangle to device coordinations.
// Parameters:
//			page		-	Handle to the page. Returned by FPDFEMB_LoadPage function.
//			start_x		-	Left pixel position of the display area in the device coordination
//			start_y		-	Top pixel position of the display area in the device coordination
//			size_x		-	Horizontal size (in pixels) for displaying the page
//			size_y		-	Vertical size (in pixels) for displaying the page
//			rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
//								2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
//			point		-	A point structure with page coordinations upon the call,
//							also receiving the result device coordinations.
//			rect		-	A rectangle structure with page coordinations upon the call,
//							also receiving the result device coordinations.
// Return value:
//			None
// Comments:
//			For rectangle conversion, the result rectangle is always "normalized", meaning for
//			device coordinations, left is always smaller than right, top is smaller than bottom.
//
void FPDFEMB_PageToDevicePoint(FPDFEMB_PAGE page, 
						int start_x, int start_y, int size_x, int size_y, int rotate, 
						FPDFEMB_POINT* point);

void FPDFEMB_PageToDeviceRect(FPDFEMB_PAGE page, 
						int start_x, int start_y, int size_x, int size_y, int rotate, 
						FPDFEMB_RECT* rect);

/********************************************************************************************
****
****		Text Search
****
********************************************************************************************/

// Search flags for FPDFEMB_FindFirst function
#define FPDFEMB_MATCHCASE		1		// whether matching case
#define FPDFEMB_MATCHWHOLEWORD	2		// whether matching whole word
#define FPDFEMB_CONSECUTIVE		4		// whether matching consecutively (for example, "CC" will
										// match twice in "CCC").

// Function: FPDFEMB_FindFirst
//			Find first occurance of a pattern string in a page
// Parameters:
//			page		-	Page handle.
//			pattern		-	A zero-terminated unicode string to be found. 
//			from_last	-	Whether we start from the end of page
//			flags		-	Search flags, see above defined constants
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//			Is not found, FPDFERR_NOTFOUND is returned.
// Comments:
//			A page must be parsed first before it can be searched.
//			There can be only one search in progress for a page. A new search will 
//			cancel the previous one.
//
//			IMPORTANT: this function is now obsolete and kept for back compatibility
//			only, please use FPDFEMB_FindFrom function below.
//
FPDFEMB_RESULT FPDFEMB_FindFirst(FPDFEMB_PAGE page, const FPDFEMB_WCHAR* pattern, 
								 FPDFEMB_BOOL from_last, unsigned int flags);

// Function: FPDFEMB_FindFrom
//			Find first occurance of a pattern string in a page, from a particular position
// Parameters:
//			page		-	Page handle.
//			pattern		-	A zero-terminated unicode string to be found. 
//			pos			-	The position, returned from FPDFEMB_GetSearchPos.
//							Or 0 from the beginning of page, -1 from the end of page.
//			flags		-	Search flags, see above defined constants
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//			Is not found, FPDFERR_NOTFOUND is returned.
// Comments:
//			A page must be parsed first before it can be searched.
//			There can be only one search in progress for a page. A new search will 
//			cancel the previous one.
//
FPDFEMB_RESULT FPDFEMB_FindFrom(FPDFEMB_PAGE page, const FPDFEMB_WCHAR* pattern, 
								 int pos, unsigned int flags);

// Function: FPDFEMB_FindNext
//			Find next occurance of a search
// Parameters:
//			page		-	Page handle. 
//							FPDFEMB_FindFirst must be called for this page first.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//			Is not found, FPDFERR_NOTFOUND is returned.
//
FPDFEMB_RESULT FPDFEMB_FindNext(FPDFEMB_PAGE page);

// Function: FPDFEMB_FindPrev
//			Find previous occurance of a search
// Parameters:
//			page		-	Page handle.
//							FPDFEMB_FindFirst must be called for this page first.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//			Is not found, FPDFERR_NOTFOUND is returned.
//
FPDFEMB_RESULT FPDFEMB_FindPrev(FPDFEMB_PAGE page);

// Function: FPDFEMB_CountFoundRects
//			Get number of rectangles for last found result
// Parameters:
//			page		-	Page handle.
// Return Value:
//			Number of rectangles for last found result. 0 for not found or failure.
//
int FPDFEMB_CountFoundRects(FPDFEMB_PAGE page);

// Function: FPDFEMB_GetFoundRect
//			Get a particular found rectangle
// Parameters:
//			page		-	Page handle.
//			index		-	Zero-based index for the rectangle.
//			rect		-	Receiving the result rectangle, in hundredth of points
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			Application should always call FPDFEMB_CountFoundRects first to get
//			number of rectangles, then use this function to get each rectangle.
//
//			The returned rectangle uses page coordination system.
//
FPDFEMB_RESULT FPDFEMB_GetFoundRect(FPDFEMB_PAGE page, int index, FPDFEMB_RECT* rect);

// Function: FPDFEMB_GetSearchPos
//			Return position of current search result
// Parameters:
//			page		-	Page handle.
// Return Value:
//			Zero based character index for the current search result. -1 if not found.
//
int FPDFEMB_GetSearchPos(FPDFEMB_PAGE page);

// Function: FPDFEMB_QuickSearch
//			Search a pattern in a page quickly, without the page to be parsed
// Parameters:
//			document	-	Document handle returned by FPDFEMB_StartLoadDocument function
//			page_index	-	Zero-based index of the page
//			pattern		-	A zero-terminated unicode string to be found. 
//			case_sensitive	-	Non-zero for case-sensitive searching, zero for case-insensitive
// Return Value:
//			FPDFERR_SUCCESS if pattern found, FPDFERR_NOTFOUND if pattern not found.
//			Otherwise error code is returned.
// Comments:
//			This function does a rough and quick search in a page, before the page is loaded. 
//			The quick search will not generate an exact result saying where the pattern is
//			found, and, it might be possible if a quick search result is "pattern found", and
//			a real search for the same pattern, in the same page, will result in "not found".
//
//			However, if quick search doesn't find a pattern in a page, then we can be sure the
//			pattern won't be found in this page when we do a real search. So, this function is 
//			very useful when we search in a multiple-page document, and we want to quickly skip
//			those pages in which the pattern can't possibly be found.
//
FPDFEMB_RESULT FPDFEMB_QuickSearch(FPDFEMB_DOCUMENT document, int page_index, 
								   const FPDFEMB_WCHAR* pattern, int case_sensitive);

/********************************************************************************************
****
****		Text Information
****
********************************************************************************************/

// Function: FPDFEMB_GetCharCount
//			Get number of characters in the page
// Parameters:
//			page		-	Page handle
//			count		-	Receiving number of characters
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_GetCharCount(FPDFEMB_PAGE page, int* count);

// Structure: FPDFEMB_CHAR_INFO
//			Character information.
struct FPDFEMB_CHAR_INFO {
	int		unicode;		// Unicode for the character. 0 if not available.
							// Space and new line charcters (U+0020 and U+000A) may be generated
							// according to the text formatting.
	FPDFEMB_POINT	origin;	// X/Y position for the character origin, in hundredth of points
	FPDFEMB_RECT	bbox;	// Bounding box of the character, in hundredth of points
							// Maybe an empty box (left == right or top == bottom).
};

// Function: FPDFEMB_GetCharInfo
//			Get character information
// Parameters:
//			page		-	Page handle
//			index		-	Character index, starting from zero
//			char_info	-	Receiving the character info
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			Application must call FPDFEMB_GetCharCount first before it can call this function
//			for any particular characters.
//			
FPDFEMB_RESULT FPDFEMB_GetCharInfo(FPDFEMB_PAGE page, int index, FPDFEMB_CHAR_INFO* char_info);

// Function: FPDFEMB_GetCharIndexAtPos()
//			Get index of character nearest to a certain position on the page
// Parameters:
//			page		-	Page handle
//			x			-	X position in PDF page coordination system
//			y			-	Y position in PDF page coordination system
//			index		-	Pointer to an integer receiving zero-based character index.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			This function finds the character that's nearest to the particular page position.
//			If there is no character, the output index will be -1.
//			
FPDFEMB_RESULT FPDFEMB_GetCharIndexAtPos(FPDFEMB_PAGE page, double x, double y, int* index);

/********************************************************************************************
****
****		Device Independant Bitmap
****
********************************************************************************************/

#define FPDFDIB_BGR		1	// 3 bytes per pixel, byte order: Blue, Green, Red
#define FPDFDIB_BGRx	2	// 4 bytes per pixel, byte order: Blue, Green, Red, not used
#define FPDFDIB_BGRA	3	// 4 bytes per pixel, byte order: Blue, Green, Red, Alpha
#define FPDFDIB_GRAY	4	// 1 byte per pixel (grayscale)

// Function: FPDFEMB_CreateDIB
//			Create a DIB (Device Independant Bitmap)
// Parameters:
//			width		-	Width pixels;
//			height		-	Height pixels;
//			format		-	Format type. See FPDFDIB_xxx constants
//			buffer		-	External buffer provided for the DIB,
//							or NULL if new buffer is to be allocated.
//			stride		-	Number of bytes for each scan line, for external buffer only.
//							If not specified, 4-byte alignment assumed.
//			dib			-	Receiving the created DIB handle
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			If "buffer" parameter is not NULL, then the provided buffer must conform
//			to standard DIB format (see comments of FPDFEMB_GetDIBData function below).
//
//			This function doesn't initialize the pixels inside the DIB buffer. So if you
//			want to use the DIB to display a PDF page, you usually need to initialize
//			the DIB to white background by youself.
//
FPDFEMB_RESULT FPDFEMB_CreateDIB(int width, int height, int format, 
									   void* buffer, int stride, FPDFEMB_BITMAP* dib);

// Function: FPDFEMB_DestroyDIB
//			Destroy a DIB
// Parameters:
//			dib			-	DIB handle
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			If external buffer is used (specified in "buffer" parameter when calling
//			FPDFEMB_CreateDIB), the buffer will not be destroyed.
//
FPDFEMB_RESULT FPDFEMB_DestroyDIB(FPDFEMB_BITMAP dib);

// Function: FPDFEMB_GetDIBWidth
//			Get width (in pixels) of a DIB
// Parameters:
//			dib			-	DIB handle
// Return Value:
//			DIB width in pixels.
//
int FPDFEMB_GetDIBWidth(FPDFEMB_BITMAP dib);

// Function: FPDFEMB_GetDIBHeight
//			Get height (in pixels) of a DIB
// Parameters:
//			dib			-	DIB handle
// Return Value:
//			DIB height in pixels.
//
int FPDFEMB_GetDIBHeight(FPDFEMB_BITMAP dib);

// Function: FPDFEMB_GetDIBData
//			Get data pointer to a DIB
// Parameters:
//			dib			-	DIB handle
// Return Value:
//			Pointer to the DIB data.
// Comments:
//			DIB data are organized in scanlines, from top down.
//
void* FPDFEMB_GetDIBData(FPDFEMB_BITMAP dib);

// Function: FPDFEMB_GetDIBStride
//			Get scan line stride of a DIB
// Parameters:
//			dib			-	DIB handle
// Return Value:
//			Number of bytes occupied by a scanline
//
int FPDFEMB_GetDIBStride(FPDFEMB_BITMAP dib);

// Function: FPDFEMB_GetRotatedDIB
//			Swap X/Y dimensions of a DIB to generate a rotated new DIB
// Parameters:
//			dib			-	DIB handle
//			flip_x		-	Whether flip pixels on the destination X dimension (left/right)
//			flip_y		-	Whether flip pixels on the destination Y dimension (up/down)
//			result_dib	-	Receiving the result DIB handle
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_GetRotatedDIB(FPDFEMB_BITMAP dib, 
									 FPDFEMB_BOOL bFlipX, FPDFEMB_BOOL bFlipY,
									 FPDFEMB_BITMAP* result_dib);

// Function: FPDFEMB_StretchDIB
//			Stretch a source DIB into another destination DIB
// Parameters:
//			dest_dib	-	The destination DIB handle
//			dest_left	-	Left position in the destination DIB
//			dest_top	-	Top position in the destination DIB
//			dest_width	-	Destination width, in pixels. Can be negative for horizontal flipping
//			dest_height	-	Destination height, in pixels. Can be negative for vertical flipping
//			clip		-	Destination clipping rectangle, or NULL for no clipping.
//							The coordinations are measured in destination bitmap.
//			src_dib		-	Source DIB handle.
//			interpol	-	Whether we use interpolation to improve the result quality
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_StretchDIB(FPDFEMB_BITMAP dest_dib, int dest_left, int dest_top,
								  int dest_width, int dest_height, FPDFEMB_RECT* clip_rect, 
								  FPDFEMB_BITMAP src_dib, FPDFEMB_BOOL interpol);

// Function: FPDFEMB_TransformDIB
//			Transform a source DIB into another destination DIB
// Parameters:
//			dest_dib	-	The destination DIB handle
//			clip		-	Destination clipping rectangle, or NULL for no clipping.
//							The coordinations are measured in destination bitmap.
//			src_dib		-	Source DIB handle.
//			x			-	X coordination of the dest origin
//			y			-	Y coordination of the dest origin
//			xx			-	X distance of the dest X vector
//			yx			-	Y distance of the dest X vector
//			xy			-	X distance of the dest Y vector
//			yy			-	Y distance of the dest Y vector
//			interpol	-	Whether we use interpolation to improve the result quality
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			All coordinations and distances are measured in destination bitmap system.
//
//			This function places the bottom-left pixel of the image at the destination
//			origin, then the bottom sideline along the destination X vector, and left 
//			sideline along the destination Y vector.
//			
FPDFEMB_RESULT FPDFEMB_TransformDIB(FPDFEMB_BITMAP dest_dib, FPDFEMB_RECT* clip_rect, 
								  FPDFEMB_BITMAP src_dib, int x, int y, int xx, int yx,
								  int xy, int yy, FPDFEMB_BOOL interpol);

/********************************************************************************************
****
****		Custom Font Handler and CJK Support
****
********************************************************************************************/

// FPDFEMB comes with standard fonts for Latin characters. If your device is targeted to
// Eastern Asian markets, then system fonts must be provided and registered with FPDFEMB.
// Depending on your device configuration, those system fonts might be in TrueType or Type1
// format, or some other non-standard compact format. For the first case, you should register
// a font mapper so FPDFEMB can pick the right font file, and for the second case, you
// should register a glyph provider so FPDFEMB can get glyph bitmap for each character.

#define FPDFEMB_CHARSET_DEFAULT		0
#define FPDFEMB_CHARSET_GB			936
#define FPDFEMB_CHARSET_BIG5		950
#define FPDFEMB_CHARSET_JIS			932
#define FPDFEMB_CHARSET_KOREA		949
#define FPDFEMB_CHARSET_UNICODE		1200

#define FPDFEMB_FONT_FIXEDPITCH		1
#define FPDFEMB_FONT_SERIF			2
#define FPDFEMB_FONT_SYMBOLIC		4
#define FPDFEMB_FONT_SCRIPT			8
#define FPDFEMB_FONT_NONSYMBOLIC	32
#define FPDFEMB_FONT_ITALIC			64
#define FPDFEMB_FONT_ALLCAP			0x10000
#define FPDFEMB_FONT_SMALLCAP		0x20000
#define FPDFEMB_FONT_FORCEBOLD		0x40000

// Structure: FPDFEMB_FONT_MAPPER
//			Defines interface for system font mapper.
//
struct FPDFEMB_FONT_MAPPER
{
	// Interface: MapFont
	//		Find font file path for a particular PDF font
	// Parameters:
	//		mapper		-	Pointer to the FPDFEMB_FONT_MAPPER structure
	//		name		-	Font name
	//		charset		-	Charset ID (see above FPDFEMB_CHARSET_xxx constants)
	//		flags		-	Font flags (see above FPDFEMB_FONT_xxx constants)
	//		weight		-	Weight of the font. Range from 100 to 900. 400 is normal,
	//						700 is bold.
	//		path		-	Receiving the full file path. The buffer size is 512 bytes.
	//		face_index	-	Receiving an zero-based index value for the font face, if the 
	//						mapped font file is a "collection" (meaning a number of faces 
	//						are stored in the same file). If the font file is not a 
	//						collection, the index value should be zero.
	// Return Value:
	//		Non-zero for success, 0 for failure.
	//
	FPDFEMB_BOOL	(*MapFont)(struct FPDFEMB_FONT_MAPPER* mapper, const char* name, int charset,
									unsigned int flags,	int weight,
									char* path, int* face_index);

	void*		user;		// A user pointer, used by the application
};

// Function: FPDFEMB_SetFontMapper
//			Use a system font mapper (typically for Chinese/Japanese/Korean charsets)
// Parameters:
//			mapper		-	Pointer to FPDFEMB_FONT_MAPPER structure.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			This function is used with devices that come with one or more system fonts,
//			and those fonts are in standard TT or T1 format.
//
FPDFEMB_RESULT FPDFEMB_SetFontMapper(FPDFEMB_FONT_MAPPER* mapper);

// Structure: FPDFEMB_GLYPH_PROVIDER
//			Interface for providing glyph bitmap of non-latin characters.
//			This is usually used for embedded devices with Chinese/Japanese/Korean 
//			fonts installed, but those fonts are not in TrueType or Type1 format.
//
struct FPDFEMB_GLYPH_PROVIDER
{
	// Interface: MapFont
	//		Return an internal handle for a font
	// Parameters:
	//		provider	-	Pointer to this structure
	//		name		-	Font name
	//		charset		-	Charset ID (see above FPDFEMB_CHARSET_xxx constants)
	//		flags		-	Font flags (see above FPDFEMB_FONT_xxx constants)
	//		weight		-	Weight of the font. Range from 100 to 900. 400 is normal,
	//						700 is bold.
	// Return Value:
	//		An internal handle to the mapped font. If the embedded device supports
	//		multiple fonts, then this value can serve as an identifier to differentiate
	//		among them. If the device supports only one font, then implementation of
	//		this function can simply return NULL.
	//
	void*	(*MapFont)(struct FPDFEMB_GLYPH_PROVIDER* provider, const char* name, int charset,
									unsigned int flags,	int weight);
	// Interface: GetGlyphBBox
	//		Get glyph bounding box
	// Parameters:
	//		provider	-	Pointer to this structure
	//		font		-	Internal handle to the font. Returned by MapFont interface.
	//		unicode		-	Unicode of the character
	//		CID			-	Adobe CID for this character. Or zero if not available.
	//		bbox		-	Receiving the result bounding box. See comments below.
	// Return Value:
	//		None.
	// Comments:
	//		The bounding box is measure in a glyph coordination system, in which the
	//		origin is set to character origin, and unit is set to one-thousandth of
	//		"em size" (representing the font size).
	//
	//		In most CJK fonts, all CJK characters (except some symbols or western 
	//		characters) have same glyph bounding box:
	//		left = 0, right = 1000, bottom = -220, top = 780.
	//
	//		It's OK to return a box that's larger than the actual glyph box.
	//
	void	(*GetGlyphBBox)(struct FPDFEMB_GLYPH_PROVIDER* provider, void* font,
									FPDFEMB_WCHAR unicode, unsigned short CID,
									FPDFEMB_RECT* bbox);

	// Interface: GetGlyphBitmap
	//		Get bitmap of a glyph
	// Parameters:
	//		provider	-	Pointer to this structure
	//		font		-	Internal handle to the font. Returned by MapFont interface.
	//		unicode		-	Unicode of the character
	//		CID			-	Adobe CID for this character. Or zero if not available.
	//		font_width	-	Width of the font em square, measured in device units.
	//		font_height	-	Height of the font em square, measured in device units.
	//		left		-	Receiving the left offset, from the character origin, of the
	//						result glyph bitmap. Positive value will move the bitmap to
	//						the right side, negative to the left.
	//		top			-	Receiving the top offset, from the character origin, of the
	//						result glyph bitmap. Positive value will move the bitmap upward,
	//						negative downward.
	//		bitmap_width -	Receiving number of width pixels in the result bitmap
	//		bitmap_height -	Receiving number of height pixels in the result bitmap
	//		buffer		-	Receiving a data buffer pointer, allocated by the implementation.
	//						See comments below.
	//		stride		-	Receiving number of bytes per scanline, in the data buffer.
	//		pdf_width	-	Width of the character specified in PDF. It is measured in one-
	//						thousandth of the font width. It can be 0 if width not specified
	//						in PDF. See comments below.
	// Return Value:
	//		Non-zero for success. 0 for failure. In this case the glyph can not be displayed.
	// Comments:
	//		The buffer should be allocated by implemenation. And it must be allocated
	//		using FPDFEMB_AllocMemory function. The result buffer will be destroyed by
	//		FPDFEMB SDK, so implementation should not destroy it.
	//
	//		The implementation should write "coverage" data into allocated buffer, one byte 
	//		for each pixel, from top scanline to bottom scanline, within each scan line, 
	//		from left pixel to right. Coverage 0 means the pixel is outside the glyph, 
	//		coverage 255 means the pixel is inside the glyph.
	//
	//		The "pdf_width" parameter can be used to scale the character in system font
	//		horizontally to match the font width specified in PDF. For example, if we have
	//		a PDF file which requires a character in half-width (pdf_width is 500), but
	//		in the system font the character has full-width (1000), then the glyph provider
	//		implementation should scale the font horizontally to half of its original width.
	//
	FPDFEMB_BOOL (*GetGlyphBitmap)(struct FPDFEMB_GLYPH_PROVIDER* provider, void* font,
									FPDFEMB_WCHAR unicode, unsigned short CID,
									double font_width, double font_height, int* left, int* top,
									int* bitmap_width, int* bitmap_height, 
									void** buffer, int* stride, int pdf_width);

	void*		user;		// A user pointer, used by the application
};

// Function: FPDFEMB_SetGlyphProvider
//			Make use of a glyph provider: generating glyph bitmap for non-Latin characters
// Parameters:
//			provider	-	Pointer to the glyph provider structure.
//							This structure must stay valid throughout usage of FPDFEMB module.
// Return Value:
//			None.
// Comments:
//			FPDFEMB embeds some standard fonts for Latin characters and symbols, like
//			Times, Courier and Helvetica (Arial). For non-Latin characters, however,
//			FPDFEMB has to ask glyph provide for help.
//
//			If an embedded device carries fonts for non-Latin character sets, especially
//			those for CJK markets, then the application can implement a glyph provider,
//			allowing PDFs using non-embedded CJK fonts to be properly displayed.
//
void FPDFEMB_SetGlyphProvider(FPDFEMB_GLYPH_PROVIDER* provider);

// Function: FPDFEMB_LoadCMap_GB
// Function: FPDFEMB_LoadCMap_GB_Ext
// Function: FPDFEMB_LoadCMap_CNS
// Function: FPDFEMB_LoadCMap_Korean
// Function: FPDFEMB_LoadCMap_Japan
// Function: FPDFEMB_LoadCMap_Japan_Ext
//			Make use of character encoding maps embedded with FPDFEMB
// Parameters:
//			None.
// Return Value:
//			None.
// Comments:
//			These functions add character encoding data to your application. Each call
//			will increase the code size of your application. Total data size for all
//			character sets is 151K bytes.
void FPDFEMB_LoadCMap_GB();
void FPDFEMB_LoadCMap_GB_Ext();		// Load full code table for GB
void FPDFEMB_LoadCMap_CNS();
void FPDFEMB_LoadCMap_Korea();
void FPDFEMB_LoadCMap_Japan();
void FPDFEMB_LoadCMap_Japan_Ext();	// Load full code table for Japan

/********************************************************************************************
****
****		Document Information
****
********************************************************************************************/

// Function: PDFEMB_GetDocInfoString
//			Get information string about the document, like creator, modifcation date, etc.
// Parameters:
//			document	-	Handle to the document
//			key			-	A byte string for the information key. Currently can be one of the followings:
//							"Title", "Author", "Subject", "Keywords", "Creator", "Producer", "CreationDate",
//							"ModDate", or some custom information key, if supported by the PDF file.
//			buffer		-	A buffer allocated by the application, or NULL.
//			bufsize		-	[IN/OUT] A pointer to a number indicating the buffer size (number of bytes),
//							before this function call. After return, this place will store
//							number of bytes used by the output (including terminator).
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			The string is output in Unicode, using UTF-16LE format. It's terminated by
//			two consecutive zero bytes.
//
//			If the "buffer" parameter is NULL, then the "bufsize" parameter will receive
//			number of bytes required to store the string (including the two-byte terminator).
//
FPDFEMB_RESULT FPDFEMB_GetDocInfoString(FPDFEMB_DOCUMENT document, const char* key, void* buffer, unsigned int* bufsize);

/********************************************************************************************
****
****		Action (Destination) Information
****
********************************************************************************************/

typedef void* FPDFEMB_ACTION;

// Action types supported by FPDFEMB
#define FPDFEMB_DEST_NONE			0		// No or unsupported destination
#define FPDFEMB_DEST_PAGE			1		// A page inside the same document
#define FPDFEMB_DEST_DOC			2		// An external PDF document
#define FPDFEMB_DEST_URL			3		// An external URL
#define FPDFEMB_ACTION_LAUNCH		4		// Launch an external file or command

// Zoom mode for destination
#define FPDFEMB_ZOOM_NONE			0		// Zoom mode not specified
#define FPDFEMB_ZOOM_FACTOR			1		// Specific zoom factor is used
#define FPDFEMB_ZOOM_FITPAGE		2		// Fit the whole page on screen
#define FPDFEMB_ZOOM_FITWIDTH		3		// Fit width of the page on screen
#define FPDFEMB_ZOOM_FITHEIGHT		4		// Fit height of the page on screen
#define FPDFEMB_ZOOM_FITRECT		5		// Fit a particular rectangle on screen
#define FPDFEMB_ZOOM_FITCONTENT		6		// Fit whole content of page on screen
#define FPDFEMB_ZOOM_FITCONTENTW	7		// Fit content width of page on screen
#define FPDFEMB_ZOOM_FITCONTENTH	8		// Fit content height of page on screen

// Data structure for page destination
struct FPDFEMB_PAGEDEST
{
	int				page_index;		// Zero based index for the page
	int				zoom_mode;		// See FPDFEMB_ZOOM_xxx definition above
	int				zoom_factor;	// For FPDFEMB_ZOOM_FACTOR only: the zoom factor (in percentage)
	FPDFEMB_RECT	position;		// Specify position inside the page. Depends on the zoom mode,
									// different members of the rectangle are used:
									// FPDFEMB_ZOOM_NONE:			left, top
									// FPDFEMB_ZOOM_FACTOR:			left, top
									// FPDFEMB_ZOOM_FITPAGE:		none
									// FPDFEMB_ZOOM_FITWIDTH:		top
									// FPDFEMB_ZOOM_FITHEIGHT:		left
									// FPDFEMB_ZOOM_FITRECT:		left, top, bottom, right
									// FPDFEMB_ZOOM_FITCONTENT:		none
									// FPDFEMB_ZOOM_FITCONTENTW:	top
									// FPDFEMB_ZOOM_FITCONTENTH:	left
};

// Data structure for document destination
struct FPDFEMB_DOCDEST
{
	FPDFEMB_PAGEDEST	page_data;	// page data
	char*				file_name;	// The file name, encoded in original charset (maybe MBCS)
};

// Data structure for URL destination
struct FPDFEMB_URLDEST
{
	char*				url;		// URL encoded in 7-bit ASCII
};

// Data structure for Launch action
struct FPDFEMB_LAUNCHACTION
{
	int					new_window;	// Whether a new window should be opened
	char*				file_name;	// The file name, encoded in original charset (maybe MBCS)
};

// Function: FPDFEMB_Action_GetType
//			Get type of an action
// Parameters:
//			document	-	Handle to the document
//			action		-	Handle to the action
//			dest_type	-	Pointer to an integer receiving type of the destination. See the above
//							FPDFEMB_DEST_xxx definitions
//			data_size	-	Pointer to an integer receiving data block size for the destination.
//							If this parameter is NULL, then data size won't be retrieved.
// Comments:
//			Each different type of destination has different data structure. The "data_size" result
//			indicates how many bytes is required to hold the destination data structure. The application
//			can then allocate sufficient buffer and then call FPDFEMB_Bookmark_GetDest function to
//			get the real data.
//
FPDFEMB_RESULT FPDFEMB_Action_GetType(FPDFEMB_DOCUMENT document, FPDFEMB_ACTION action, int* dest_type, int* data_size);

// Function: FPDFEMB_Action_GetData
//			Get detailed data of a particular action
// Parameters:
//			document	-	Handle to the document
//			action		-	Handle to the action
//			buffer		-	Application allocated buffer receiving the destination data
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			See data structure definition for different action type above. Please note
//			the actual action data might use more space than the structure definition
//			shows, to store things like file name or URL. So you should always call
//			FPDFEMB_Action_GetType first to get data size then allocate enough buffer
//			for this call.
//
FPDFEMB_RESULT FPDFEMB_Action_GetData(FPDFEMB_DOCUMENT document, FPDFEMB_ACTION action, void* buffer);

// Function: FPDFEMB_Action_GetNext
//			Get next action in an action chain
// Parameters:
//			document	-	Handle to the document
//			action		-	Handle to current action
//			next		-	Receiving handle to next action.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			If there is no next action, the "next" parameter will be set to NULL after the function returns.
//
FPDFEMB_RESULT FPDFEMB_Action_GetNext(FPDFEMB_ACTION action, FPDFEMB_ACTION* next);

/********************************************************************************************
****
****		Bookmark Information
****
********************************************************************************************/

typedef void* FPDFEMB_BOOKMARK;

// Function: FPDFEMB_Bookmark_GetFirstChild
//			Get first child of a bookmark item, or first top level bookmark item
// Parameters: 
//			document	-	Handle to the document
//			parent		-	Handle to the parent bookmark. 
//							Can be NULL if you want to get the first top level item.
//			bookmark	-	Receiving handle to the first child or top level bookmark item. 
//							If result is NULL, then bookmark not found.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_Bookmark_GetFirstChild(FPDFEMB_DOCUMENT document, FPDFEMB_BOOKMARK parent,
											  FPDFEMB_BOOKMARK* bookmark);

// Function: FPDFEMB_Bookmark_GetFirstChild
//			Get next sibling of a bookmark item
// Parameters: 
//			document	-	Handle to the document
//			bookmark	-	Handle to the bookmark 
//			sibling		-	Receiving the handle of next sibling.
//							If result is NULL, then this is the last bookmark in this level.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
//
FPDFEMB_RESULT FPDFEMB_Bookmark_GetNextSibling(FPDFEMB_DOCUMENT document, FPDFEMB_BOOKMARK bookmark,
											  FPDFEMB_BOOKMARK* sibling);

// Function: FPDFEMB_Bookmark_GetTitle
//			Get title of a bookmark
// Parameters: 
//			bookmark	-	Handle to the bookmark 
//			buffer		-	A buffer allocated by the application, or NULL.
//			bufsize		-	[IN/OUT] A pointer to a number indicating the buffer size,
//							before this function call. After return, this place will store
//							number of bytes used by the output (including terminator).
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			The title is output in Unicode, using UTF-16LE format. It's terminated by
//			two consecutive zero bytes.
//
//			If the "buffer" parameter is NULL, then the "bufsize" parameter will receive
//			number of bytes required to store the bookmark title (including the two-
//			byte terminator).
//
//			If the buffer provided is smaller than the required size, then this function
//			will not copy any data, return FPDFEMB_PARAM, and the required buffer size will 
//			also be put in "bufsize" parameter.
//
FPDFEMB_RESULT FPDFEMB_Bookmark_GetTitle(FPDFEMB_BOOKMARK bookmark, void* buffer, unsigned int* bufsize);

// Function: FPDFEMB_Bookmark_GetPage
//			Get page number of a bookmark pointing to
// Parameters:
//			document	-	Handle to the document
//			bookmark	-	Handle to the bookmark 
//			page		-	Receiving the page number. -1 if this bookmark doesn't actually
//							point to a page inside the document.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success
// Comments:
//			Some bookmark might not point to a page, some bookmark might have more than one destination
//			(action), for detailed information about a bookmark, you should call FPDFEMB_Bookmark_GetAction.
//
FPDFEMB_RESULT FPDFEMB_Bookmark_GetPage(FPDFEMB_DOCUMENT document, FPDFEMB_BOOKMARK bookmark, int* page);

// Function: FPDFEMB_Bookmark_GetAction
//			Get action(s) associated with a particular bookmark
// Parameters:
//			document	-	Handle to the document
//			bookmark	-	Handle to the bookmark 
//			action		-	Receiving handle of first action
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_Bookmark_GetAction(FPDFEMB_DOCUMENT document, FPDFEMB_BOOKMARK bookmark, FPDFEMB_ACTION* action);

/********************************************************************************************
****
****		Hyperlink Information
****
********************************************************************************************/

// Function: FPDFEMB_Link_GetCount
//			Get number of hyperlinks inside a page
// Parameters:
//			page		-	Page handle.
//			link_count	-	Pointer to an integer receiving the number of links
//			reserved	-	Must be zero now.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			This function must be called before any other link related function can
//			be called for the page.
//
FPDFEMB_RESULT FPDFEMB_Link_GetCount(FPDFEMB_PAGE page, int* link_count, int reserved);

// Function: FPDFEMB_Link_GetAction
//			Get action(s) associated with a particular hyperlink
// Parameters:
//			page		-	Page handle
//			link_index	-	Zero-based index for the link
//			action		-	Receiving handle of first action
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_Link_GetAction(FPDFEMB_PAGE page, int link_index, FPDFEMB_ACTION* action);

// Function: FPDFEMB_Link_GetAreaCount
//			Get number of area (quadrilaterals) for a link
// Parameters:
//			page		-	Page handle
//			link_index	-	Zero-based index for the link
//			count		-	Pointer to an integer receiving number of quadrilaterals
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_Link_GetAreaCount(FPDFEMB_PAGE page, int link_index, int* count);

// Function: FPDFEMB_Link_GetArea
//			Get a particular quadrilateral for a link
// Parameters:
//			page		-	Page handle
//			link_index	-	Zero-based index for the link
//			area_index	-	Zero-based index for the quadrilateral
//			points		-	Pointer to an array consists 4 points, receiving coordinations
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			The result in "points" array are the X/Y coordinations for the four vertices
//			of the quadrilateral. Vertices are in the following order: lower left, lower
//			right, upper right, upper left.
//
FPDFEMB_RESULT FPDFEMB_Link_GetArea(FPDFEMB_PAGE page, int link_index, int area_index, 
									FPDFEMB_POINT* points);

/********************************************************************************************
****
****		Graphic Output (onto DIB)
****
********************************************************************************************/

typedef void* FPDFEMB_FONT;

// Function: FPDFEMB_OpenStandardFont
//			Get ready to use a standard PDF font
// Parameters:
//			font_name	-	Name of the font. See a list of supported fonts below.
//			font_handle	-	Receiving the font handle.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			Currently supported standard fonts:
//			Courier, Courier-Bold, Courier-BoldOblique, Courier-Oblique,
//			Helvetica, Helvetica-Bold, Helvetica-BoldOblique, Helvetica-Oblique,
//			Times-Roman, Times-Bold, Times-Italic, Times-BoldItalic,
//			Symbol, ZapfDingbats.
//
FPDFEMB_RESULT FPDFEMB_OpenStandardFont(const char* font_name, FPDFEMB_FONT* font_handle);

// Function: FPDFEMB_OpenSystemFont
//			Get ready to use a system font
// Parameters:
//			font_name	-	Font name
//			charset		-	Charset ID (see above FPDFEMB_CHARSET_xxx constants)
//			flags		-	Font flags (see above FPDFEMB_FONT_xxx constants)
//			weight		-	Weight of the font. Range from 100 to 900. 400 is normal,
//							700 is bold.
//			font_handle	-	Receiving the font handle.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
// Comments:
//			System font is supported only if either FPDFEMB_SetFontMapper or
//			FPDFEMB_SetGlyphProvider is called.
//			Font attributes (name, charset, flags and weight) can be all optional, if the
//			font mapper or glyph provider doesn't make use of them.
//
FPDFEMB_RESULT FPDFEMB_OpenSystemFont(const char* font_name, int charset, unsigned int flags, int weight,
									  FPDFEMB_FONT* font_handle);

// Function: FPDFEMB_CloseFont
//			Close a font handle.
// Parameters:
//			font_handle	-	Handle to the font.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_CloseFont(FPDFEMB_FONT font_handle);

struct FPDFEMB_TEXTMATRIX
{
	double	a, b, c, d;
};

// Function: FPDFEMB_OutputText
//			Output text string onto a DIB device.
// Parameters:
//			dib			-	DIB handle, as the output device
//			x, y		-	DIB coordinations for the origin point of the first character.
//			font_handle	-	Handle to the font
//			font_size	-	Font size in pixels
//			matrix		-	Matrix for the text output. Can be NULL.
//			text		-	Zero-terminated unicode text string
//			argb		-	Color of the text, in 0xaarrggbb format.
// Return Value:
//			Error code, or FPDFERR_SUCCESS for success.
//
FPDFEMB_RESULT FPDFEMB_OutputText(FPDFEMB_BITMAP dib, int x, int y, FPDFEMB_FONT font_handle, double font_size,
								  FPDFEMB_TEXTMATRIX* matrix, const FPDFEMB_WCHAR* text, unsigned long argb);

#ifdef __cplusplus
};
#endif

#endif	// #ifdef _FPDFEMB_H_
