#ifdef __cplusplus
extern "C" {
#endif

/** Extended interfaces for JPEG, JPEG2000 and JBIG2 decoders **/
typedef struct
{
	/** Initialize the decoding context, with memory allocator provided by FPDFEMB.
	   Implementation should return a pointer to the decoding context.
	*/
	void*	(*Init)(void* (*alloc_func)(unsigned int), void (*free_func)(void*));

	/** Finish with the decoding. */
	void	(*Finish)(void* pContext);

	/** Input JPEG encoded data from the source.
		This function may be called multiple times during decoding progress.
	*/
	void	(*Input)(void* pContext, const unsigned char* src_buf, unsigned long src_size);

	/** Read the header information. Return non-zero for success, 0 for failure */
	int		(*ReadHeader)(void* pContext);

	/** Get info from the decoder, including image width, height and number of components */
	void	(*GetInfo)(void* pContext, int* width, int* height, int* nComps);

	/** Read one scanline from decoded image */
	int		(*ReadScanline)(void* pContext, unsigned char* dest_buf);

	/** Get number of available source bytes left in the input stream */
	unsigned long	(*GetAvailInput)(void* pContext);
} FPDFEMB_JPEG_DECODER;

void FPDFEMB_SetJpegDecoder(FPDFEMB_JPEG_DECODER* pDecoder);

typedef struct 
{
	/** Initialize the decoder with the full source data.
		Implementation should return a pointer to the context.
	*/
	void*	(*Init)(const unsigned char* src_buf, unsigned long src_size);

	/** Destroy the context */
	void	(*Finish)(void* context);

	/** Get image info from the context, including width, height, number of components
		in original codestream, and number of components in output image. For some
		particular type of encoded image, like paletted image, these two numbers of 
		components may vary.
	*/
	void	(*GetInfo)(void* context, unsigned long* width, unsigned long* height, 
				unsigned long* codestream_nComps, unsigned long* output_nComps);

	/** Do the real data decoding, output to a pre-allocated buffer.
		bTranslateColor indicates whether the decoder should use JPEG2000 embedded
		color space info to translate image into sRGB color space.
		"offsets" array describes the byte order of all components. For example,
		{2,1,0} means the first components is output to last byte.
	*/
	void	(*Decode)(void* context, unsigned char* dest_buf, int pitch, 
				int bTranslateColor, unsigned char* offsets);
} FPDFEMB_JPEG2000_DECODER;

void FPDFEMB_SetJpeg2000Decoder(FPDFEMB_JPEG2000_DECODER* pDecoder);

typedef struct
{
	/** Do the whole decoding process. Supplied parameters include width, height, source image
		data and size, global data and size (can be shared among different images), destination
		buffer and scanline pitch in dest buffer.
	*/
	void	(*Decode)(unsigned long width, unsigned long height, const unsigned char* src_buf,
				unsigned long src_size, const unsigned char* global_buf, unsigned long global_size, 
				unsigned char* dest_buf, int dest_pitch);
} FPDFEMB_JBIG2_DECODER;

void FPDFEMB_SetJbig2Decoder(FPDFEMB_JBIG2_DECODER* pDecoder);

#ifdef __cplusplus
};
#endif
