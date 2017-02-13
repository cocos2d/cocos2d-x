// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_CSARMATURENODE_FLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_CSARMATURENODE_FLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

#include "CSParseBinary_generated.h"

namespace flatbuffers {

struct CSArmatureNodeOption;

struct ResourceItemData;

struct CSArmatureNodeOption FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NODEOPTIONS = 4,
    VT_FILEDATA = 6,
    VT_ISLOOP = 8,
    VT_ISAUTOPLAY = 10,
    VT_CURRENTANIMATIONNAME = 12
  };
  const flatbuffers::WidgetOptions *nodeOptions() const { return GetPointer<const flatbuffers::WidgetOptions *>(VT_NODEOPTIONS); }
  const ResourceItemData *fileData() const { return GetPointer<const ResourceItemData *>(VT_FILEDATA); }
  bool isLoop() const { return GetField<uint8_t>(VT_ISLOOP, 1) != 0; }
  bool isAutoPlay() const { return GetField<uint8_t>(VT_ISAUTOPLAY, 1) != 0; }
  const flatbuffers::String *currentAnimationName() const { return GetPointer<const flatbuffers::String *>(VT_CURRENTANIMATIONNAME); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_NODEOPTIONS) &&
           verifier.VerifyTable(nodeOptions()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_FILEDATA) &&
           verifier.VerifyTable(fileData()) &&
           VerifyField<uint8_t>(verifier, VT_ISLOOP) &&
           VerifyField<uint8_t>(verifier, VT_ISAUTOPLAY) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_CURRENTANIMATIONNAME) &&
           verifier.Verify(currentAnimationName()) &&
           verifier.EndTable();
  }
};

struct CSArmatureNodeOptionBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_nodeOptions(flatbuffers::Offset<flatbuffers::WidgetOptions> nodeOptions) { fbb_.AddOffset(CSArmatureNodeOption::VT_NODEOPTIONS, nodeOptions); }
  void add_fileData(flatbuffers::Offset<ResourceItemData> fileData) { fbb_.AddOffset(CSArmatureNodeOption::VT_FILEDATA, fileData); }
  void add_isLoop(bool isLoop) { fbb_.AddElement<uint8_t>(CSArmatureNodeOption::VT_ISLOOP, static_cast<uint8_t>(isLoop), 1); }
  void add_isAutoPlay(bool isAutoPlay) { fbb_.AddElement<uint8_t>(CSArmatureNodeOption::VT_ISAUTOPLAY, static_cast<uint8_t>(isAutoPlay), 1); }
  void add_currentAnimationName(flatbuffers::Offset<flatbuffers::String> currentAnimationName) { fbb_.AddOffset(CSArmatureNodeOption::VT_CURRENTANIMATIONNAME, currentAnimationName); }
  CSArmatureNodeOptionBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  CSArmatureNodeOptionBuilder &operator=(const CSArmatureNodeOptionBuilder &);
  flatbuffers::Offset<CSArmatureNodeOption> Finish() {
    auto o = flatbuffers::Offset<CSArmatureNodeOption>(fbb_.EndTable(start_, 5));
    return o;
  }
};

inline flatbuffers::Offset<CSArmatureNodeOption> CreateCSArmatureNodeOption(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::WidgetOptions> nodeOptions = 0,
    flatbuffers::Offset<ResourceItemData> fileData = 0,
    bool isLoop = true,
    bool isAutoPlay = true,
    flatbuffers::Offset<flatbuffers::String> currentAnimationName = 0) {
  CSArmatureNodeOptionBuilder builder_(_fbb);
  builder_.add_currentAnimationName(currentAnimationName);
  builder_.add_fileData(fileData);
  builder_.add_nodeOptions(nodeOptions);
  builder_.add_isAutoPlay(isAutoPlay);
  builder_.add_isLoop(isLoop);
  return builder_.Finish();
}

inline flatbuffers::Offset<CSArmatureNodeOption> CreateCSArmatureNodeOptionDirect(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::WidgetOptions> nodeOptions = 0,
    flatbuffers::Offset<ResourceItemData> fileData = 0,
    bool isLoop = true,
    bool isAutoPlay = true,
    const char *currentAnimationName = nullptr) {
  return CreateCSArmatureNodeOption(_fbb, nodeOptions, fileData, isLoop, isAutoPlay, currentAnimationName ? _fbb.CreateString(currentAnimationName) : 0);
}

struct ResourceItemData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TYPE = 4,
    VT_PATH = 6
  };
  int32_t type() const { return GetField<int32_t>(VT_TYPE, 0); }
  const flatbuffers::String *path() const { return GetPointer<const flatbuffers::String *>(VT_PATH); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_TYPE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_PATH) &&
           verifier.Verify(path()) &&
           verifier.EndTable();
  }
};

struct ResourceItemDataBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(int32_t type) { fbb_.AddElement<int32_t>(ResourceItemData::VT_TYPE, type, 0); }
  void add_path(flatbuffers::Offset<flatbuffers::String> path) { fbb_.AddOffset(ResourceItemData::VT_PATH, path); }
  ResourceItemDataBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ResourceItemDataBuilder &operator=(const ResourceItemDataBuilder &);
  flatbuffers::Offset<ResourceItemData> Finish() {
    auto o = flatbuffers::Offset<ResourceItemData>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<ResourceItemData> CreateResourceItemData(flatbuffers::FlatBufferBuilder &_fbb,
    int32_t type = 0,
    flatbuffers::Offset<flatbuffers::String> path = 0) {
  ResourceItemDataBuilder builder_(_fbb);
  builder_.add_path(path);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<ResourceItemData> CreateResourceItemDataDirect(flatbuffers::FlatBufferBuilder &_fbb,
    int32_t type = 0,
    const char *path = nullptr) {
  return CreateResourceItemData(_fbb, type, path ? _fbb.CreateString(path) : 0);
}

inline const flatbuffers::CSArmatureNodeOption *GetCSArmatureNodeOption(const void *buf) {
  return flatbuffers::GetRoot<flatbuffers::CSArmatureNodeOption>(buf);
}

inline bool VerifyCSArmatureNodeOptionBuffer(flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<flatbuffers::CSArmatureNodeOption>(nullptr);
}

inline void FinishCSArmatureNodeOptionBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<flatbuffers::CSArmatureNodeOption> root) {
  fbb.Finish(root);
}

}  // namespace flatbuffers

#endif  // FLATBUFFERS_GENERATED_CSARMATURENODE_FLATBUFFERS_H_
