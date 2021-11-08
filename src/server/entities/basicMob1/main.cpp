

#include "IEntity.hpp"
#include <dlfcn.h>

int main()
{
  std::cout << "loader" << std::endl;

  /* on Linux, use "./myclass.so" */
  void* handle = dlopen("./basicMob1.so", RTLD_LOCAL | RTLD_LAZY);

  IEntity* (*create)();
  void (*destroy)(IEntity*);

  create = (IEntity* (*)())dlsym(handle, "allocator");
  destroy = (void (*)(IEntity*))dlsym(handle, "deleter");

  IEntity* myClass = (IEntity*)create();
  myClass->update();
  destroy( myClass );

  return 0;
}
