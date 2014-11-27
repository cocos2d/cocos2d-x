/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// independent from idl_parser, since this code is not needed for most clients

#include <string>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#ifdef _WIN32
#include <direct.h>
#define PATH_SEPARATOR "\\"
#define mkdir(n, m) _mkdir(n)
#else
#include <sys/stat.h>
#define PATH_SEPARATOR "/"
#endif

namespace flatbuffers {
namespace go {

static std::string GenGetter(const Type &type);
static std::string GenMethod(const FieldDef &field);
static void GenStructBuilder(const StructDef &struct_def,
                             std::string *code_ptr);
static void GenReceiver(const StructDef &struct_def, std::string *code_ptr);
static std::string GenTypeBasic(const Type &type);
static std::string GenTypeGet(const Type &type);
static std::string TypeName(const FieldDef &field);


// Most field accessors need to retrieve and test the field offset first,
// this is the prefix code for that.
std::string OffsetPrefix(const FieldDef &field) {
  return "{\n\to := flatbuffers.UOffsetT(rcv._tab.Offset(" +
         NumToString(field.value.offset) +
         "))\n\tif o != 0 {\n";
}

// Begin by declaring namespace and imports.
static void BeginFile(const std::string name_space_name,
                      const bool needs_imports,
                      std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "// automatically generated, do not modify\n\n";
  code += "package " + name_space_name + "\n\n";
  if (needs_imports) {
    code += "import (\n";
    code += "\tflatbuffers \"github.com/google/flatbuffers/go\"\n";
    code += ")\n";
  }
}

// Begin a class declaration.
static void BeginClass(const StructDef &struct_def, std::string *code_ptr) {
  std::string &code = *code_ptr;

  code += "type " + struct_def.name + " struct {\n\t";

  // _ is reserved in flatbuffers field names, so no chance of name conflict:
  code += "_tab ";
  code += struct_def.fixed ? "flatbuffers.Struct" : "flatbuffers.Table";
  code += "\n}\n\n";
}

// Begin enum code with a class declaration.
static void BeginEnum(std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "const (\n";
}

// A single enum member.
static void EnumMember(const EnumDef &enum_def, const EnumVal ev,
                       std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "\t";
  code += enum_def.name;
  code += ev.name;
  code += " = ";
  code += NumToString(ev.value) + "\n";
}

// End enum code.
static void EndEnum(std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += ")\n";
}

// Initialize a new struct or table from existing data.
static void NewRootTypeFromBuffer(const StructDef &struct_def,
                                  std::string *code_ptr) {
  std::string &code = *code_ptr;

  code += "func GetRootAs";
  code += struct_def.name;
  code += "(buf []byte, offset flatbuffers.UOffsetT) ";
  code += "*" + struct_def.name + "";
  code += " {\n";
  code += "\tn := flatbuffers.GetUOffsetT(buf[offset:])\n";
  code += "\tx := &" + struct_def.name + "{}\n";
  code += "\tx.Init(buf, n + offset)\n";
  code += "\treturn x\n";
  code += "}\n\n";
}

// Initialize an existing object with other data, to avoid an allocation.
static void InitializeExisting(const StructDef &struct_def,
                               std::string *code_ptr) {
  std::string &code = *code_ptr;

  GenReceiver(struct_def, code_ptr);
  code += " Init(buf []byte, i flatbuffers.UOffsetT) ";
  code += "{\n";
  code += "\trcv._tab.Bytes = buf\n";
  code += "\trcv._tab.Pos = i\n";
  code += "}\n\n";
}

// Get the length of a vector.
static void GetVectorLen(const StructDef &struct_def,
                         const FieldDef &field,
                         std::string *code_ptr) {
  std::string &code = *code_ptr;

  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name) + "Length(";
  code += ") int " + OffsetPrefix(field);
  code += "\t\treturn rcv._tab.VectorLen(o)\n\t}\n";
  code += "\treturn 0\n}\n\n";
}

// Get the value of a struct's scalar.
static void GetScalarFieldOfStruct(const StructDef &struct_def,
                                   const FieldDef &field,
                                   std::string *code_ptr) {
  std::string &code = *code_ptr;
  std::string getter = GenGetter(field.value.type);
  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "() " + TypeName(field) + " { return " + getter;
  code += "(rcv._tab.Pos + flatbuffers.UOffsetT(";
  code += NumToString(field.value.offset) + ")) }\n";
}

// Get the value of a table's scalar.
static void GetScalarFieldOfTable(const StructDef &struct_def,
                                  const FieldDef &field,
                                  std::string *code_ptr) {
  std::string &code = *code_ptr;
  std::string getter = GenGetter(field.value.type);
  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "() " + TypeName(field) + " ";
  code += OffsetPrefix(field) + "\t\treturn " + getter;
  code += "(o + rcv._tab.Pos)\n\t}\n";
  code += "\treturn " + field.value.constant + "\n";
  code += "}\n\n";
}

// Get a struct by initializing an existing struct.
// Specific to Struct.
static void GetStructFieldOfStruct(const StructDef &struct_def,
                                   const FieldDef &field,
                                   std::string *code_ptr) {
  std::string &code = *code_ptr;
  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "(obj *" + TypeName(field);
  code += ") *" + TypeName(field);
  code += " {\n";
  code += "\tif obj == nil {\n";
  code += "\t\tobj = new(" + TypeName(field) + ")\n";
  code += "\t}\n";
  code += "\tobj.Init(rcv._tab.Bytes, rcv._tab.Pos + ";
  code += NumToString(field.value.offset) + ")";
  code += "\n\treturn obj\n";
  code += "}\n";
}

// Get a struct by initializing an existing struct.
// Specific to Table.
static void GetStructFieldOfTable(const StructDef &struct_def,
                                  const FieldDef &field,
                                  std::string *code_ptr) {
  std::string &code = *code_ptr;
  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "(obj *";
  code += TypeName(field);
  code += ") *" + TypeName(field) + " " + OffsetPrefix(field);
  if (field.value.type.struct_def->fixed) {
    code += "\t\tx := o + rcv._tab.Pos\n";
  } else {
    code += "\t\tx := rcv._tab.Indirect(o + rcv._tab.Pos)\n";
  }
  code += "\t\tif obj == nil {\n";
  code += "\t\t\tobj = new(" + TypeName(field) + ")\n";
  code += "\t\t}\n";
  code += "\t\tobj.Init(rcv._tab.Bytes, x)\n";
  code += "\t\treturn obj\n\t}\n\treturn nil\n";
  code += "}\n\n";
}

// Get the value of a string.
static void GetStringField(const StructDef &struct_def,
                           const FieldDef &field,
                           std::string *code_ptr) {
  std::string &code = *code_ptr;
  GenReceiver(struct_def, code_ptr);
  code += " " +  MakeCamel(field.name);
  code += "() " + TypeName(field) + " ";
  code += OffsetPrefix(field) + "\t\treturn " + GenGetter(field.value.type);
  code += "(o + rcv._tab.Pos)\n\t}\n\treturn \"\"\n";
  code += "}\n\n";
}

// Get the value of a union from an object.
static void GetUnionField(const StructDef &struct_def,
                          const FieldDef &field,
                          std::string *code_ptr) {
  std::string &code = *code_ptr;
  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name) + "(";
  code += "obj " + TypeName(field) + ") bool ";
  code += OffsetPrefix(field);
  code += "\t\t" + GenGetter(field.value.type);
  code += "(obj, o)\n\t\treturn true\n\t}\n";
  code += "\treturn false\n";
  code += "}\n\n";
}

// Get the value of a vector's struct member.
static void GetMemberOfVectorOfStruct(const StructDef &struct_def,
                                      const FieldDef &field,
                                      std::string *code_ptr) {
  std::string &code = *code_ptr;
  auto vectortype = field.value.type.VectorType();

  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "(obj *" + TypeName(field);
  code += ", j int) bool " + OffsetPrefix(field);
  code += "\t\tx := rcv._tab.Vector(o)\n";
  code += "\t\tx += flatbuffers.UOffsetT(j) * ";
  code += NumToString(InlineSize(vectortype)) + "\n";
  if (!(vectortype.struct_def->fixed)) {
    code += "\t\tx = rcv._tab.Indirect(x)\n";
  }
  code += "\tif obj == nil {\n";
  code += "\t\tobj = new(" + TypeName(field) + ")\n";
  code += "\t}\n";
  code += "\t\tobj.Init(rcv._tab.Bytes, x)\n";
  code += "\t\treturn true\n\t}\n";
  code += "\treturn false\n";
  code += "}\n\n";
}

// Get the value of a vector's non-struct member. Uses a named return
// argument to conveniently set the zero value for the result.
static void GetMemberOfVectorOfNonStruct(const StructDef &struct_def,
                                         const FieldDef &field,
                                         std::string *code_ptr) {
  std::string &code = *code_ptr;
  auto vectortype = field.value.type.VectorType();

  GenReceiver(struct_def, code_ptr);
  code += " " + MakeCamel(field.name);
  code += "(j int) " + TypeName(field) + " ";
  code += OffsetPrefix(field);
  code += "\t\ta := rcv._tab.Vector(o)\n";
  code += "\t\treturn " + GenGetter(field.value.type) + "(";
  code += "a + flatbuffers.UOffsetT(j * ";
  code += NumToString(InlineSize(vectortype)) + "))\n";
  code += "\t}\n";
  if (vectortype.base_type == BASE_TYPE_STRING) {
    code += "\treturn \"\"\n";
  } else {
    code += "\treturn 0\n";
  }
  code += "}\n\n";
}

// Begin the creator function signature.
static void BeginBuilderArgs(const StructDef &struct_def,
                             std::string *code_ptr) {
  std::string &code = *code_ptr;

  code += "\n";
  code += "func Create" + struct_def.name;
  code += "(builder *flatbuffers.Builder";
}

// Recursively generate arguments for a constructor, to deal with nested
// structs.
static void StructBuilderArgs(const StructDef &struct_def,
                              const char *nameprefix,
                              std::string *code_ptr) {
  for (auto it = struct_def.fields.vec.begin();
       it != struct_def.fields.vec.end();
       ++it) {
    auto &field = **it;
    if (IsStruct(field.value.type)) {
      // Generate arguments for a struct inside a struct. To ensure names
      // don't clash, and to make it obvious these arguments are constructing
      // a nested struct, prefix the name with the struct name.
      StructBuilderArgs(*field.value.type.struct_def,
                        (field.value.type.struct_def->name + "_").c_str(),
                        code_ptr);
    } else {
      std::string &code = *code_ptr;
      code += (std::string)", " + nameprefix;
      code += MakeCamel(field.name, false);
      code += " " + GenTypeBasic(field.value.type);
    }
  }
}

// End the creator function signature.
static void EndBuilderArgs(std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += ") flatbuffers.UOffsetT {\n";
}

// Recursively generate struct construction statements and instert manual
// padding.
static void StructBuilderBody(const StructDef &struct_def,
                              const char *nameprefix,
                              std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "    builder.Prep(" + NumToString(struct_def.minalign) + ", ";
  code += NumToString(struct_def.bytesize) + ")\n";
  for (auto it = struct_def.fields.vec.rbegin();
       it != struct_def.fields.vec.rend();
       ++it) {
    auto &field = **it;
    if (field.padding)
      code += "    builder.Pad(" + NumToString(field.padding) + ")\n";
    if (IsStruct(field.value.type)) {
      StructBuilderBody(*field.value.type.struct_def,
                        (field.value.type.struct_def->name + "_").c_str(),
                        code_ptr);
    } else {
      code += "    builder.Prepend" + GenMethod(field) + "(";
      code += nameprefix + MakeCamel(field.name, false) + ")\n";
    }
  }
}

static void EndBuilderBody(std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "    return builder.Offset()\n";
  code += "}\n";
}

// Get the value of a table's starting offset.
static void GetStartOfTable(const StructDef &struct_def,
                            std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "func " + struct_def.name + "Start";
  code += "(builder *flatbuffers.Builder) { ";
  code += "builder.StartObject(";
  code += NumToString(struct_def.fields.vec.size());
  code += ") }\n";
}

// Set the value of a table's field.
static void BuildFieldOfTable(const StructDef &struct_def,
                              const FieldDef &field,
                              const size_t offset,
                              std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "func " + struct_def.name + "Add" + MakeCamel(field.name);
  code += "(builder *flatbuffers.Builder, ";
  code += MakeCamel(field.name, false) + " ";
  if (!IsScalar(field.value.type.base_type) && (!struct_def.fixed)) {
    code += "flatbuffers.UOffsetT";
  } else {
    code += GenTypeBasic(field.value.type);
  }
  code += ") ";
  code += "{ builder.Prepend";
  code += GenMethod(field) + "Slot(";
  code += NumToString(offset) + ", ";
  if (!IsScalar(field.value.type.base_type) && (!struct_def.fixed)) {
    code += "flatbuffers.UOffsetT";
    code += "(";
    code += MakeCamel(field.name, false) + ")";
  } else {
    code += MakeCamel(field.name, false);
  }
  code += ", " + field.value.constant;
  code += ") }\n";
}

// Set the value of one of the members of a table's vector.
static void BuildVectorOfTable(const StructDef &struct_def,
                               const FieldDef &field,
                               std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "func " + struct_def.name + "Start";
  code += MakeCamel(field.name);
  code += "Vector(builder *flatbuffers.Builder, numElems int) ";
  code += "flatbuffers.UOffsetT { return builder.StartVector(";
  auto vector_type = field.value.type.VectorType();
  auto alignment = InlineAlignment(vector_type);
  auto elem_size = InlineSize(vector_type);
  code += NumToString(elem_size);
  code += ", numElems, " + NumToString(alignment);
  code += ")\n}\n";
}

// Get the offset of the end of a table.
static void GetEndOffsetOnTable(const StructDef &struct_def,
                                std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "func " + struct_def.name + "End";
  code += "(builder *flatbuffers.Builder) flatbuffers.UOffsetT ";
  code += "{ return builder.EndObject() }\n";
}

// Generate the receiver for function signatures.
static void GenReceiver(const StructDef &struct_def, std::string *code_ptr) {
  std::string &code = *code_ptr;
  code += "func (rcv *" + struct_def.name + ")";
}

// Generate a struct field, conditioned on its child type(s).
static void GenStructAccessor(const StructDef &struct_def,
                              const FieldDef &field,
                              std::string *code_ptr) {
  GenComment(field.doc_comment, code_ptr, "");
  if (IsScalar(field.value.type.base_type)) {
    if (struct_def.fixed) {
      GetScalarFieldOfStruct(struct_def, field, code_ptr);
    } else {
      GetScalarFieldOfTable(struct_def, field, code_ptr);
    }
  } else {
    switch (field.value.type.base_type) {
      case BASE_TYPE_STRUCT:
        if (struct_def.fixed) {
          GetStructFieldOfStruct(struct_def, field, code_ptr);
        } else {
          GetStructFieldOfTable(struct_def, field, code_ptr);
        }
        break;
      case BASE_TYPE_STRING:
        GetStringField(struct_def, field, code_ptr);
        break;
      case BASE_TYPE_VECTOR: {
        auto vectortype = field.value.type.VectorType();
        if (vectortype.base_type == BASE_TYPE_STRUCT) {
          GetMemberOfVectorOfStruct(struct_def, field, code_ptr);
        } else {
          GetMemberOfVectorOfNonStruct(struct_def, field, code_ptr);
        }
        break;
      }
      case BASE_TYPE_UNION:
        GetUnionField(struct_def, field, code_ptr);
        break;
      default:
        assert(0);
    }
  }
  if (field.value.type.base_type == BASE_TYPE_VECTOR) {
    GetVectorLen(struct_def, field, code_ptr);
  }
}

// Generate table constructors, conditioned on its members' types.
static void GenTableBuilders(const StructDef &struct_def,
                             std::string *code_ptr) {
  GetStartOfTable(struct_def, code_ptr);

  for (auto it = struct_def.fields.vec.begin();
       it != struct_def.fields.vec.end();
       ++it) {
    auto &field = **it;
    if (field.deprecated) continue;

    auto offset = it - struct_def.fields.vec.begin();
    BuildFieldOfTable(struct_def, field, offset, code_ptr);
    if (field.value.type.base_type == BASE_TYPE_VECTOR) {
      BuildVectorOfTable(struct_def, field, code_ptr);
    }
  }

  GetEndOffsetOnTable(struct_def, code_ptr);
}

// Generate struct or table methods.
static void GenStruct(const StructDef &struct_def,
                      std::string *code_ptr,
                      StructDef *root_struct_def) {
  if (struct_def.generated) return;

  GenComment(struct_def.doc_comment, code_ptr);
  BeginClass(struct_def, code_ptr);
  if (&struct_def == root_struct_def) {
    // Generate a special accessor for the table that has been declared as
    // the root type.
    NewRootTypeFromBuffer(struct_def, code_ptr);
  }
  // Generate the Init method that sets the field in a pre-existing
  // accessor object. This is to allow object reuse.
  InitializeExisting(struct_def, code_ptr);
  for (auto it = struct_def.fields.vec.begin();
       it != struct_def.fields.vec.end();
       ++it) {
    auto &field = **it;
    if (field.deprecated) continue;

    GenStructAccessor(struct_def, field, code_ptr);
  }

  if (struct_def.fixed) {
    // create a struct constructor function
    GenStructBuilder(struct_def, code_ptr);
  } else {
    // Create a set of functions that allow table construction.
    GenTableBuilders(struct_def, code_ptr);
  }
}

// Generate enum declarations.
static void GenEnum(const EnumDef &enum_def, std::string *code_ptr) {
  if (enum_def.generated) return;

  GenComment(enum_def.doc_comment, code_ptr);
  BeginEnum(code_ptr);
  for (auto it = enum_def.vals.vec.begin();
       it != enum_def.vals.vec.end();
       ++it) {
    auto &ev = **it;
    GenComment(ev.doc_comment, code_ptr, "\t");
    EnumMember(enum_def, ev, code_ptr);
  }
  EndEnum(code_ptr);
}

// Returns the function name that is able to read a value of the given type.
static std::string GenGetter(const Type &type) {
  switch (type.base_type) {
    case BASE_TYPE_STRING: return "rcv._tab.String";
    case BASE_TYPE_UNION: return "rcv._tab.Union";
    case BASE_TYPE_VECTOR: return GenGetter(type.VectorType());
    default:
      return "rcv._tab.Get" + MakeCamel(GenTypeGet(type));
  }
}

// Returns the method name for use with add/put calls.
static std::string GenMethod(const FieldDef &field) {
  return IsScalar(field.value.type.base_type)
    ? MakeCamel(GenTypeBasic(field.value.type))
    : (IsStruct(field.value.type) ? "Struct" : "UOffsetT");
}


// Save out the generated code for a Go Table type.
static bool SaveType(const Parser &parser, const Definition &def,
                     const std::string &classcode, const std::string &path,
                     bool needs_imports) {
  if (!classcode.length()) return true;

  std::string namespace_name;
  std::string namespace_dir = path;
  auto &namespaces = parser.namespaces_.back()->components;
  for (auto it = namespaces.begin(); it != namespaces.end(); ++it) {
    if (namespace_name.length()) {
      namespace_name += ".";
      namespace_dir += PATH_SEPARATOR;
    }
    namespace_name = *it;
    namespace_dir += *it;
    mkdir(namespace_dir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
  }


  std::string code = "";
  BeginFile(namespace_name, needs_imports, &code);
  code += classcode;
  std::string filename = namespace_dir + PATH_SEPARATOR + def.name + ".go";
  return SaveFile(filename.c_str(), code, false);
}

static std::string GenTypeBasic(const Type &type) {
  static const char *ctypename[] = {
    #define FLATBUFFERS_TD(ENUM, IDLTYPE, CTYPE, JTYPE, GTYPE, NTYPE) #GTYPE,
      FLATBUFFERS_GEN_TYPES(FLATBUFFERS_TD)
    #undef FLATBUFFERS_TD
  };
  return ctypename[type.base_type];
}

static std::string GenTypePointer(const Type &type) {
  switch (type.base_type) {
    case BASE_TYPE_STRING:
      return "string";
    case BASE_TYPE_VECTOR:
      return GenTypeGet(type.VectorType());
    case BASE_TYPE_STRUCT:
      return type.struct_def->name;
    case BASE_TYPE_UNION:
      // fall through
    default:
      return "*flatbuffers.Table";
  }
}

static std::string GenTypeGet(const Type &type) {
  return IsScalar(type.base_type)
    ? GenTypeBasic(type)
    : GenTypePointer(type);
}

static std::string TypeName(const FieldDef &field) {
  return GenTypeGet(field.value.type);
}

// Create a struct with a builder and the struct's arguments.
static void GenStructBuilder(const StructDef &struct_def,
                             std::string *code_ptr) {
  BeginBuilderArgs(struct_def, code_ptr);
  StructBuilderArgs(struct_def, "", code_ptr);
  EndBuilderArgs(code_ptr);

  StructBuilderBody(struct_def, "", code_ptr);
  EndBuilderBody(code_ptr);
}

}  // namespace go

bool GenerateGo(const Parser &parser,
                const std::string &path,
                const std::string & /*file_name*/,
                const GeneratorOptions & /*opts*/) {
  for (auto it = parser.enums_.vec.begin();
       it != parser.enums_.vec.end(); ++it) {
    std::string enumcode;
    go::GenEnum(**it, &enumcode);
    if (!go::SaveType(parser, **it, enumcode, path, false))
      return false;
  }

  for (auto it = parser.structs_.vec.begin();
       it != parser.structs_.vec.end(); ++it) {
    std::string declcode;
    go::GenStruct(**it, &declcode, parser.root_struct_def);
    if (!go::SaveType(parser, **it, declcode, path, true))
      return false;
  }

  return true;
}

}  // namespace flatbuffers

