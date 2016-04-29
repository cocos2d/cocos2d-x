// Copyright 2013 Howling Moon Software. All rights reserved.
// See http://chipmunk2d.net/legal.php for more information.

/// Function type used as a callback from the marching squares algorithm to sample an image function.
/// It passes you the point to sample and your context pointer, and you return the density.
typedef cpFloat (*cpMarchSampleFunc)(cpVect point, void *data);

/// Function type used as a callback from the marching squares algorithm to output a line segment.
/// It passes you the two endpoints and your context pointer.
typedef void (*cpMarchSegmentFunc)(cpVect v0, cpVect v1, void *data);

/// Trace an anti-aliased contour of an image along a particular threshold.
/// The given number of samples will be taken and spread across the bounding box area using the sampling function and context.
/// The segment function will be called for each segment detected that lies along the density contour for @c threshold.
CP_EXPORT void cpMarchSoft(
  cpBB bb, unsigned long x_samples, unsigned long y_samples, cpFloat threshold,
  cpMarchSegmentFunc segment, void *segment_data,
  cpMarchSampleFunc sample, void *sample_data
);

/// Trace an aliased curve of an image along a particular threshold.
/// The given number of samples will be taken and spread across the bounding box area using the sampling function and context.
/// The segment function will be called for each segment detected that lies along the density contour for @c threshold.
CP_EXPORT void cpMarchHard(
  cpBB bb, unsigned long x_samples, unsigned long y_samples, cpFloat threshold,
  cpMarchSegmentFunc segment, void *segment_data,
  cpMarchSampleFunc sample, void *sample_data
);
