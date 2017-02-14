#ifndef COCOS2D_STROKE_SCAN_H
#define COCOS2D_STROKE_SCAN_H

#include <cstdint>
#include <cstdlib>

namespace cocos2d
{
    struct FontStroke;
        
    namespace detail
    {
        class LineBounds;
        
        class StrokeScan
        {
        public:
            StrokeScan
            ( std::uint8_t* matrix, std::size_t matrixWidth,
              unsigned char*& src, int& width, int& height,
              const FontStroke& stroke, int strokeSize );

            void run();

        private:
            enum class Progress;

        private:
            void scan();
            void queueBounds( LineBounds& bounds, int bottomLine ) const;
            
            std::size_t boundedScan
            ( std::size_t destIndex, int startx, int endx, int desty ) const;
            
            int scanDestinationLine
            ( int destIndex, int startx, int endx, int desty ) const;

            Progress apply
            ( int destx, int desty, std::uint32_t& destColor ) const;

            int findFirstNonTransparent( int desty ) const;
            int findLastNonTransparent( int desty ) const;
            void fillTransparent
            ( std::size_t upperIndex, int lowerx, int upperx ) const;
            void applyInRange
            ( std::size_t upperIndex, int lowerx, int upperx, int desty ) const;

        private:
            std::uint8_t* const _matrix;
            const std::size_t _matrixWidth;
            unsigned char*& _src;
            int& _width;
            int& _height;
            const FontStroke& _stroke;

            const int _strokeSize;
            const int _destWidth;
            const int _destHeight;
            unsigned char* _dest;
            const std::uint32_t _strokeColor;
        };
    }
}

#endif
