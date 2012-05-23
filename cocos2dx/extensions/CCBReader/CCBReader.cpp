#include "CCBReader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CCBReader::CCBReader() {
    
}

CCBReader::~CCBReader() {
    if(this->mBytes) {
        delete this->mBytes;
        this->mBytes = NULL;
    }

    if(this->mStringCache) {
        delete this->mStringCache;
        this->mStringCache = NULL;
    }
}

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBFileName, CCNode * pOwner) {   
    const char * path = CCFileUtils::fullPathFromRelativePath(pCCBFileName);
    
    CCFileUtils::ccLoadFileIntoMemory(path, &this->mBytes);

    this->mCurrentByte = 0;
    this->mCurrentBit = 0;
    
    if(!this->readHeader()) {
        return NULL;
    }
    
    if(!this->readStringCache()) {
        return NULL;
    }
    
    return this->readNodeGraph();
}

bool CCBReader::readHeader() {
	/* If no bytes loaded, don't crash about it. */
	if(this->mBytes == NULL) {
        return false;
    }

    /* Read magic bytes */
    int magicBytes = *((int*)(this->mBytes + this->mCurrentByte));
    this->mCurrentByte += 4;

    if(magicBytes != 'ccbi') {
        return false; 
    }

    /* Read version. */
    int version = this->readInt(false);
    if(version != kCCBVersion) {
        CCLog("WARNING! Incompatible ccbi file version (file: %d reader: %d)", version, kCCBVersion);
        return false;
    }
    
    return true;
}

bool CCBReader::readStringCache() {
    return true;
}

int CCBReader::readInt(bool pSign) {
    int numBits = 0;
    while(!this->getBit()) {
        numBits++;
    }
    
    long long current = 0;
    for(int a = numBits - 1; a >= 0; a--) {
        if(this->getBit()) {
            current |= 1 << a;
        }
    }
    current |= 1 << numBits;
    
    int num;
    if(pSign) {
        int s = current % 2;
        if(s) {
            num = (int)(current / 2);
        } else {
            num = (int)(-current / 2);
        }
    } else {
        num = current-1;
    }
    
    this->alignBits();
    
    return num;
}

bool CCBReader::getBit() {
    bool bit;
    unsigned char byte = *(this->mBytes + this->mCurrentByte);
    if(byte & (1 << this->mCurrentBit)) {
        bit = true;
    } else {
        bit = false;
    }
            
    this->mCurrentBit++;

    if(this->mCurrentBit >= 8) {
        this->mCurrentBit = 0;
        this->mCurrentBit++;
    }
    
    return bit;
}

void CCBReader::alignBits() {
    if(this->mCurrentBit) {
        this->mCurrentBit = 0;
        this->mCurrentByte++;
    }
}

CCNode * CCBReader::readNodeGraph() {
    CCLayerColor * ccLayerColor = CCLayerColor::node();

    CCSize size;
    size.setSize(100, 100);
    ccLayerColor->setContentSize(size);

    ccColor3B color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    ccLayerColor->setColor(color);
    ccLayerColor->setOpacity(255);

    return ccLayerColor;
}