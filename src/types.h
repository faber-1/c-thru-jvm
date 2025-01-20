#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
cp_info - union type for different kinds of constants
*/
typedef union cp_info {
  struct generic_cp_info {
    uint8_t tag;
    uint8_t info[];
  } generic_cp_info;
  
  struct CONSTANT_Class_info {
    uint8_t tag;
    uint16_t name_index;
  } CONSTANT_Class;

  struct CONSTANT_Fieldref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
  } CONSTANT_Fieldref;

  struct CONSTANT_Methodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
  } CONSTANT_Methodref;

  struct CONSTANT_InterfaceMethodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
  } CONSTANT_InterfaceMethodref;

  struct CONSTANT_String_info {
    uint8_t tag;
    uint16_t string_index;
  } CONSTANT_String;

  struct CONSTANT_Integer_info {
    uint8_t tag;
    uint32_t bytes;
  } CONSTANT_Integer;

  struct CONSTANT_Float_info {
    uint8_t tag;
    uint32_t bytes;
  } CONSTANT_Float;

  struct CONSTANT_Long_info {
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
  } CONSTANT_Long;

  struct CONSTANT_Double_info {
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
  } CONSTANT_Double;

  struct CONSTANT_NameAndType_info {
    uint8_t tag;
    uint16_t name_index;
    uint16_t descriptor_index;
  } CONSTANT_NameAndType;

  struct CONSTANT_Utf8_info {
    uint8_t tag;
    uint16_t length;
    uint8_t *bytes;
  } CONSTANT_Utf8;

  struct CONSTANT_MethodHandle_info {
    uint8_t tag;
    uint8_t reference_kind;
    uint16_t reference_index;
  } CONSTANT_MethodHandle;

  struct CONSTANT_MethodType_info {
    uint8_t tag;
    uint16_t descriptor_index;
  } CONSTANT_MethodType;

  struct CONSTANT_InvokeDynamic_info {
    uint8_t tag;
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
  } CONSTANT_InvokeDynamic;
} cp_info;

typedef struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t *info;
} attribute_info;

typedef struct field_info {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes;
} field_info;

typedef struct method_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    attribute_info *attributes;
} method_info;

typedef struct class_file {
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  cp_info *constant_pool;
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;
  uint16_t interfaces_count;
  uint16_t *interfaces;
  uint16_t fields_count;
  field_info *fields;
  uint16_t methods_count;
  method_info *methods;
  uint16_t attributes_count;
  attribute_info *attributes;
} class_file;

#endif