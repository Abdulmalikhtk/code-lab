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

class Camera: public Device
{
public:
	void capture()
	{
		cout<<"camera captured"<<endl;
	}	
};
class Display: public Device
{
public:
	void show()
	{
		cout<<"Display show"<<endl;
	}	
};



int main()
{
	Display dis;
	dis.show();
	dis.powerOn();

	Camera cam;
	cam.capture();
	cam.powerOn();


	cout<<"--------------------------"<<endl;

	Device* dc;
	dc=new Camera();
	dc->powerOn();
	// dc->capture();
	delete dc;
	dc=NULL;

	Device* dd;
	dd=new Display();
	dd->powerOn();
	dd=NULL;
	// dd->show();
	delete dd;

	return 0;
}