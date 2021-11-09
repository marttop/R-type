

#include <EntityLoad.hpp>

int main()
{
  std::cout << "loader" << std::endl;

  /* on Linux, use "./myclass.so" */
  // void* handle = dlopen("./basicMob1.so", RTLD_LOCAL | RTLD_LAZY);


  // IEntity* (*create)();
  // void (*destroy)(IEntity*);

  // create = (IEntity* (*)())dlsym(handle, "allocator");
  // destroy = (void (*)(IEntity*))dlsym(handle, "deleter");

  // IEntity* myClass = (IEntity*)create();
  // myClass->update();
  // destroy( myClass );

  EntityLoad loader = EntityLoad();

  loader.loadEntityWithPath("./basicMob1.so", "basicMob1");

  auto mob1 = loader.createEntityWithName("basicMob1");

  // mob1->update();

  // std::cout << mob1->isColliding(mob1) << std::endl;


  // loader.close(loader.dlOpens[0]);

  // loader.destroyEntityWithName("basicMob1", mob1);

  return 0;
}
