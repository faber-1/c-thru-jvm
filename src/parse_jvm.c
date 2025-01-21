#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "types.h"

#define READ_FIELD(file, cons, size, mssg)                                     \
  if (fread(&cons, size, 1, file) != 1) {                                      \
    fprintf(stderr, "%s\n", mssg);                                             \
    return 1;                                                                  \
  }

void free_class_file(class_file *c);
int parse_constant(FILE *f, cp_info *c);
int parse_class_file(FILE *f, class_file *c);

int parse_constant(FILE *f, cp_info *c) {
  READ_FIELD(f, c->generic_cp_info.tag, 1, "Trouble getting constant tag");

  switch (c->generic_cp_info.tag) {
  case 7: // CONSTANT_Class
    printf("\tCONSTANT_Class:\n");

    READ_FIELD(f, c->CONSTANT_Class.name_index, 2,
               "Trouble getting name_index in Class constant");
    c->CONSTANT_Class.name_index = ntohs(c->CONSTANT_Class.name_index);
    printf("\t\tname index: %d\n", c->CONSTANT_Class.name_index);
    break;
  case 9: // CONSTANT_Fieldref
    printf("\tCONSTANT_Fieldref:\n");

    READ_FIELD(f, c->CONSTANT_Fieldref.class_index, 2,
               "Trouble getting class_index in Fieldref constant");
    c->CONSTANT_Fieldref.class_index =
        ntohs(c->CONSTANT_Fieldref.class_index);
    printf("\t\tclass index: %d\n", c->CONSTANT_Fieldref.class_index);

    READ_FIELD(f, c->CONSTANT_Fieldref.name_and_type_index, 2,
               "Trouble getting name_and_type_index in Fieldref constant");
    c->CONSTANT_Fieldref.name_and_type_index =
        ntohs(c->CONSTANT_Fieldref.name_and_type_index);
    printf("\t\tname and type index: %d\n", c->CONSTANT_Fieldref.name_and_type_index);
    break;
  case 10: // CONSTANT_Methodref
    printf("\tCONSTANT_Methodref:\n");

    READ_FIELD(f, c->CONSTANT_Methodref.class_index, 2,
               "Trouble getting class_index in Methodref constant");
    c->CONSTANT_Methodref.class_index =
        ntohs(c->CONSTANT_Methodref.class_index);
    printf("\t\tclass index: %d\n", c->CONSTANT_Methodref.class_index);

    READ_FIELD(f, c->CONSTANT_Methodref.name_and_type_index, 2,
               "Trouble getting name_and_type_index in Methodref constant");
    c->CONSTANT_Methodref.name_and_type_index =
        ntohs(c->CONSTANT_Methodref.name_and_type_index);
    printf("\t\tname and type index: %d\n", c->CONSTANT_Methodref.name_and_type_index);
    break;
  case 11: // CONSTANT_InterfaceMethodref
    printf("\tCONSTANT_InterfaceMethodref:\n");

    READ_FIELD(f, c->CONSTANT_InterfaceMethodref.class_index, 2,
               "Trouble getting class_index in InterfaceMethodref constant");
    c->CONSTANT_InterfaceMethodref.class_index =
        ntohs(c->CONSTANT_InterfaceMethodref.class_index);
    printf("\t\tclass index: %d\n", c->CONSTANT_InterfaceMethodref.class_index);

    READ_FIELD(f, c->CONSTANT_InterfaceMethodref.name_and_type_index, 2,
               "Trouble getting name_and_type_index in InterfaceMethodref constant");
    c->CONSTANT_InterfaceMethodref.name_and_type_index =
        ntohs(c->CONSTANT_InterfaceMethodref.name_and_type_index);
    printf("\t\tname and type index: %d\n", c->CONSTANT_InterfaceMethodref.name_and_type_index);
    break;
  case 8: // CONSTANT_String
    printf("\tCONSTANT_String:\n");
    READ_FIELD(f, c->CONSTANT_String.string_index, 2,
               "Trouble getting string_index in String constant");
    c->CONSTANT_String.string_index = ntohs(c->CONSTANT_String.string_index);
    printf("\t\tstring index: %d\n", c->CONSTANT_String.string_index);
    break;
  case 3: // CONSTANT_Integer
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 4: // CONSTANT_Float
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 5: // CONSTANT_Long
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 6: // CONSTANT_Double
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 12: // CONSTANT_NameAndType
    printf("\tCONSTANT_NameAndType:\n");
    READ_FIELD(f, c->CONSTANT_NameAndType.name_index, 2,
               "Trouble finding name_index tag in NameAndType constant");
    READ_FIELD(f, c->CONSTANT_NameAndType.descriptor_index, 2,
               "Trouble finding name_index tag in NameAndType constant");

    c->CONSTANT_NameAndType.name_index =
        ntohs(c->CONSTANT_NameAndType.name_index);
    c->CONSTANT_NameAndType.descriptor_index =
        ntohs(c->CONSTANT_NameAndType.descriptor_index);
    printf("\t\tname index: %d\n", c->CONSTANT_NameAndType.name_index);
    printf("\t\tdescriptor index: %d\n",
           c->CONSTANT_NameAndType.descriptor_index);
    break;
  case 1: // CONSTANT_Utf8
    printf("\tCONSTANT_Utf8:\n");
    READ_FIELD(f, c->CONSTANT_Utf8.length, 2,
               "Trouble getting length of Utf8 constant");
    c->CONSTANT_Utf8.length = ntohs(c->CONSTANT_Utf8.length);
    c->CONSTANT_Utf8.bytes = calloc(c->CONSTANT_Utf8.length, sizeof(uint8_t) + 1);
    printf("\t\tlength: %d\n", c->CONSTANT_Utf8.length);

    int i = 0;
    while (i < c->CONSTANT_Utf8.length) {
      READ_FIELD(f, c->CONSTANT_Utf8.bytes[i], 1,
                 "Trouble reading bytes from Utf8 constant");
      i++;
    }
    printf("\t\tbytes: %s\n", c->CONSTANT_Utf8.bytes);

    break;
  case 15: // CONSTANT_MethodHandle
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 16: // CONSTANT_MethodType
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  case 18: // CONSTANT_InvokeDynamic
    fprintf(stderr, "Tag not implemented: %d\n", c->generic_cp_info.tag);
    exit(0);
  default:
    fprintf(stderr, "Invalid constant tag: %d\n", c->generic_cp_info.tag);
    return 1;
  }

  return 0;
}

// parses whole file.
int parse_class_file(FILE *f, class_file *c) {
  // get magic
  READ_FIELD(f, c->magic, 4, "Trouble reading magic");
  c->magic = ntohl(c->magic);

  // the magic for class files is 0xCAFEBABE.
  if (c->magic != 0xCAFEBABE) {
    fprintf(stderr, "Magic invalid. Not a class file.\n");
    return 1;
  }
  printf("magic: 0x%X\n", c->magic);

  // get minor version
  READ_FIELD(f, c->minor_version, 2, "Trouble reading minor_version");
  c->minor_version = ntohs(c->minor_version);
  printf("minor version: %d\n", c->minor_version);

  // get major version
  READ_FIELD(f, c->major_version, 2, "Trouble reading major_version");
  c->major_version = ntohs(c->major_version);
  printf("major version: %d\n", c->major_version);

  // get constant pool count
  READ_FIELD(f, c->constant_pool_count, 2, "Trouble reading constant_pool_count");
  c->constant_pool_count = ntohs(c->constant_pool_count);
  printf("constant pool count: %d\n", c->constant_pool_count);

  // get constant pool
  c->constant_pool = calloc(c->constant_pool_count - 1, sizeof(cp_info));

  if (c == NULL) {
    fprintf(stderr, "Error allocating room for constants!\n");
    return 1;
  }

  printf("constants:\n");
  int i = 0;
  while (i < c->constant_pool_count - 1) {
    if (parse_constant(f, &c->constant_pool[i]) != 0) {
      fprintf(stderr, "Trouble reading constant_pool\n");
      return 1;
    }
    i++;
  }

  READ_FIELD(f, c->access_flags, 2, "Trouble reading access_flags");
  c->access_flags = ntohs(c->access_flags);
  printf("access flags: %d\n", c->access_flags);

  READ_FIELD(f, c->this_class, 2, "Trouble reading this_class");
  c->this_class = ntohs(c->this_class);
  printf("this class: %d\n", c->this_class);

  READ_FIELD(f, c->super_class, 2, "Trouble reading super_class");
  c->super_class = ntohs(c->super_class);
  printf("super class: %d\n", c->super_class);

  READ_FIELD(f, c->interfaces_count, 2, "Trouble reading interfaces_count");
  c->interfaces_count = ntohs(c->interfaces_count);
  printf("interfaces count: %d\n", c->interfaces_count);

  c->interfaces = calloc(c->interfaces_count, sizeof(uint16_t));
  i = 0;
  while (i < c->interfaces_count) {
    READ_FIELD(f, c->interfaces[i], 2, "Trouble getting interface");
    c->interfaces[i] = ntohs(c->interfaces[i]);
    printf("\t%d", c->interfaces[i]);
    i++;
  }

  READ_FIELD(f, c->fields_count, 2, "Trouble reading fields_count");
  c->fields_count = ntohs(c->fields_count);
  printf("fields count: %d\n", c->fields_count);

  return 0;
}

int main(int argc, char **argv) {
  
  // can only pass one file (might change this later)
  if (argc != 2) {
    fprintf(stderr,
            "Incorrect argument count: %d. Please attach only one file!\n",
            argc - 1);
    exit(1);
  }

  FILE *f = fopen(argv[1], "rb");  // byte mode yippee

  if (!f) {
    fprintf(stderr, "No file found with name %s\n", argv[1]);
    exit(1);
  }

  printf("File: %s\n", argv[1]);
  printf("----------------\n");

  class_file class;
  int a = parse_class_file(f, &class);

  if (a) {
    fprintf(stderr, "Error parsing class file.\n");
    exit(a);
  }

  fclose(f);
}