/********************************************************************************
FileName:	singleton.h
Version:	1.0
Date:		2015.10.14
********************************************************************************/

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Z
{
	template<class T>
		class Singleton{
			public:
				static T* instace(){
					static T This;
					return &This;
				}
			protected:
				Singleton() {}
				~Singleton() {}
		};
}

#endif
