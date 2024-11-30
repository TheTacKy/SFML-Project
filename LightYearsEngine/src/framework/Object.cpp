#include "framework/Object.h"
#include "framework/Core.h"
namespace ly
{
	unsigned int Object::uniqueIDCounter = 0;
	Object::Object() 
		: mIsPendingDestroy{false},
		mUniqueID{GetNextAvailableID()}
	{

	}

	Object::~Object()
	{
		LOG("Object Destoryed");
	}
	void Object::Destroy()
	{
		
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;

	}
	weak<Object> Object::GetWeakRef()
	{
		return shared_from_this();
	}
	weak<const Object> Object::GetWeakRef() const
	{
		return shared_from_this();
	}
	unsigned int Object::GetNextAvailableID()
	{
		return uniqueIDCounter++;
	}
}
