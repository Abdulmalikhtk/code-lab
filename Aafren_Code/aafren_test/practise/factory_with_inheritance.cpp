#include <iostream>
using std::endl,std::cout;

enum DeviceType {CAMERA,AUDIO};

class Device
{
public:
	virtual void start()=0;
	virtual ~Device(){}
};

class Camera: public Device
{
public:

	void start()
	{
		cout<<"Camera started"<<endl;
	}
};

class Audio: public Device
{
public:

	void start()
	{
		cout<<"Audio started"<<endl;
	}

};


Device* DeviceFactory(DeviceType type)
{
	if(type==CAMERA) return new Camera();
	if(type==AUDIO) return new	Audio();
	return nullptr;
}

int main()
{
	Device* dev=DeviceFactory(CAMERA);
	dev->start();
	delete dev;
	dev=NULL;
	return 0;
}