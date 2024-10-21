#include <iostream>
using namespace std;

class A{
	public:
		int x = 2;
};
class B: public virtual A{
	public:
		int x = x+2;

};
class C: public virtual A{

};

class D: public B, public C{

};


void mainn(){
	D d1;
	cout<<d1.x;
}
