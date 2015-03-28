#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Simulated Hierarchy and Polymorphism (from Java to C)

/*
 * Class Person
 */

struct Person_class {
  void*   super;
  char* (* toString ) (void*, char*, int);
};

struct Person {
  struct Person_class* class;
  char* name;
};

char* Person_toString (void* this, char* buff, int n){
  struct Person* p = this;
  snprintf(buff, n, "Name: %s", p->name);
  return buff;
}

struct Person_class Person_class_obj = {NULL, Person_toString};

struct Person* new_Person(char* name) {
  struct Person* obj = malloc (sizeof (struct Person));
  obj->class = &Person_class_obj;
  obj->name = strdup(name); 
  return obj;
}


/*
 * Class Student extends Person
 */

struct Student_class {
  struct Person_class* super;
  char*         (* toString ) (void*, char*, int);
};

struct Student {
  struct Student_class* class;
  char* name;
  int sid;
};

char* Student_toString (void* this, char* buff, int n) {
  struct Student* s = this;
  snprintf(buff, n, "Name: %s, SID: %i", s->name, s->sid);
  return buff;
}

struct Student_class Student_class_obj = {&Person_class_obj, Student_toString};

struct Student* new_Student(char* name, int sid) {
  struct Student* obj = malloc (sizeof (struct Student));
  obj->class = &Student_class_obj;
  obj->name = strdup(name);
  obj->sid = sid; 
  return obj;
}

/*
 * Main
 */

void print(void* var){
  struct Person* p = var;
  char buff[100];
  char* string = p->class->toString(p, buff, 100);
  printf("%s\n", string);
}

int main(int argc, char** argv){
  void* people[2] = {new_Person("Alex"), new_Student("Alice", 300)};  for (int i=0; i < 2; i++)
    print(people[i]);
} 
