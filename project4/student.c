#include "student.h"
#include <string.h>
#include <stdio.h>

int string_check(const char string[]);

Student new_student(const char name[], unsigned int id, float shoe_size){
   int type;
  Student student;
  student.id = id;
  student.shoe_size = shoe_size;
  type = string_check(name);
    if(type == 1){
      strcpy(student.name, name);
    } else if(type == -1){
      strcpy(student.name, "");
    } else{
      strncpy(student.name, name, NAME_LEN-1);
    }
  return student;
}

void init_student(Student *const student, const char name[], unsigned int id,
                  float shoe_size){
  int type;
  if(student != NULL){
    student->id = id;               
    student->shoe_size = shoe_size;
    type = string_check(name);
    if(type == 1){
      strcpy(student->name, name);
    } else if(type == -1){
      strcpy(student->name, "");
    } else{
      strncpy(student->name, name, NAME_LEN-1);
    }
  }
}

unsigned int has_id(Student student, unsigned int id){
  return (student.id == id) ? (1) : (0);
}

unsigned int has_name(Student student, const char name[]){
  return (name!=NULL ? (!strcmp(student.name, name) ? 1 : 0) : 0);
}

unsigned int get_id(Student student){
  return student.id;
}

float get_shoe_size(Student student){
  return student.shoe_size;
}

Student change_shoe_size(Student student, float new_shoe_size){
  student.shoe_size = new_shoe_size;
  return student;
}

void change_name(Student *const student, const char new_name[]){
  int type;
  if(student != NULL){
    type = string_check(new_name);
    if(type == 1){
      strcpy(student->name, new_name);
    } else if(type == -1){
        strcpy(student->name, "");
    } else{
        strncpy(student->name, new_name, NAME_LEN-1);
    }
  }
}

int string_check(const char string[]){
  if(string == NULL){
    return -1;
  }
  if(strlen(string)>NAME_LEN-1){
    return 0;
  }
  return 1;
}
