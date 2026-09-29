#include <iostream>
using std::endl,std::cout;

class Device
{
public:
	void powerOn()
	{
		cout<<"Device power on"<<endl;
	}
};

class Camera
{
public:
	void capture()
	{
		cout<<"camera captured"<<endl;
	}	
};
class Display
{
public:
	void show()
	{
		cout<<"Display show"<<endl;
	}	
};

class SmartPhone: public Camera,public Display
{
public:
	void showSmartphone()
	{
		cout<<"showSmartphone show"<<endl;
	}
};

int main()
{
	SmartPhone sp;
	sp.show();
	sp.capture();
	sp.showSmartphone();

	cout<<"------------------------------------"<<endl;

	Camera* c=new SmartPhone();
	c->capture();
	delete c;	
	// c->showSmartphone();
	c=NULL;
	

	return 0;

}