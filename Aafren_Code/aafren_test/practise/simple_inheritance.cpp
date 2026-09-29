#include <iostream>
using std::endl,std::cout;

class Device
{
public:
	Device()
	{
		cout<<"Device Initialized"<<endl;
	}
	void showDevice()
	{
		cout<<"Device Show"<<endl;
	}
	virtual ~Device()
	{
		cout<<"Device Released"<<endl;
	}
};

class Camera:public Device
{
public:
	Camera()
	{
		cout<<"Camera Initialized"<<endl;
	}
	void showCamera()
	{
		cout<<"Camera show"<<endl;
	}
	~Camera()
	{
		cout<<"Camera Released"<<endl;
	}
};

int main()
{
	Camera* c=new Camera();
	c->showCamera();
	c->showDevice();
	delete c;
	c=NULL;

	Device* d=new Device();
	d->showDevice();
	// d->showCamera();
	delete d;
	d=NULL;

	Device* dc=new Camera();
	dc->showDevice();
	dc->showCamera();
	delete dc;
	dc=NULL;

	return 0;
}