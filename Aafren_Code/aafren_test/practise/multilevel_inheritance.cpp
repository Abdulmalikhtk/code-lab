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
class SmartCamera: public Camera
{
public:
	void FaceDetect()
	{
		cout<<"Face detection"<<endl;
	}
};

int main()
{
	SmartCamera sc;
	sc.FaceDetect();
	sc.capture();
	sc.powerOn();


	Device* dc=new Camera();
	dc->powerOn();
	delete dc;
	dc=NULL:

	Device* ds=new SmartCamera();
	ds->powerOn();
	// ds->capture();		
	delete ds;
	ds=NULL;

	return 0;
}