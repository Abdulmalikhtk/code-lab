#include <iostream>
using std::endl,std::cout;

class Device
{
public:	
	Device()
	{
		cout<<"Device Initialized"<<endl;
	}
	virtual void init()=0;
	virtual void start()=0;

	virtual ~Device()
	{
		cout<<"Device Released"<<endl;
	}
};

class Camera: public Device
{
public:
	Camera()
	{
		cout<<"Camera Constrctor"<<endl;
	}

	void init()
	{
		cout<<"Camera sensor Initialized"<<endl;
	}
	void start()
	{
		cout<<"Camera streaming started"<<endl;
	}
	~Camera()
	{
		cout<<"Camera Destructor"<<endl;
	}

};
class Audio: public Device
{
public:

	Audio()
	{
		cout<<"Audio Constrctor"<<endl;
	}

	void init()
	{
		cout<<"Audio sensor Initialized"<<endl;
	}
	void start()
	{
		cout<<"Audio streaming started"<<endl;
	}
	~Audio()
	{
		cout<<"Audio Destructor"<<endl;
	}


};

int main()
{
	Device* dev;
	dev=new Camera();
	dev->init();
	dev->start();
	delete dev;

	cout<<"--------------------------------"<<endl;

	Device* dev1;
	dev=new Audio();
	dev->init();
	dev->start();
	delete dev;


}