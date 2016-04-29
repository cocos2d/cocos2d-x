// Copyright 2013 Howling Moon Software. All rights reserved.
// See http://chipmunk2d.net/legal.php for more information.

/// cpHastySpace is exclusive to Chipmunk Pro
/// Currently it enables ARM NEON optimizations in the solver, but in the future will include other optimizations such as
/// a multi-threaded solver and multi-threaded collision broadphases.

struct cpHastySpace;
typedef struct cpHastySpace cpHastySpace;

/// Create a new hasty space.
/// On ARM platforms that support NEON, this will enable the vectorized solver.
/// cpHastySpace also supports multiple threads, but runs single threaded by default for determinism.
CP_EXPORT cpSpace *cpHastySpaceNew(void);
CP_EXPORT void cpHastySpaceFree(cpSpace *space);

/// Set the number of threads to use for the solver.
/// Currently Chipmunk is limited to 2 threads as using more generally provides very minimal performance gains.
/// Passing 0 as the thread count on iOS or OS X will cause Chipmunk to automatically detect the number of threads it should use.
/// On other platforms passing 0 for the thread count will set 1 thread.
CP_EXPORT void cpHastySpaceSetThreads(cpSpace *space, unsigned long threads);

/// Returns the number of threads the solver is using to run.
CP_EXPORT unsigned long cpHastySpaceGetThreads(cpSpace *space);

/// When stepping a hasty space, you must use this function.
CP_EXPORT void cpHastySpaceStep(cpSpace *space, cpFloat dt);
