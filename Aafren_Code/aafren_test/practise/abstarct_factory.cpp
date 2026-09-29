#include <iostream>
using std::endl,std::cout;


class Camera
{
public:
	virtual void open()=0;
	virtual ~Camera(){};
};	
class Buffer
{
public:
	virtual void allocate()=0;
	virtual ~Buffer(){};
};

class QualcommCamera: public Camera
{
public:
	void open() override
	{
		cout<<"Qualcomm camera opened"<<endl;
	}

};

class QualcommBuffer: public Buffer
{
public:
	void allocate() override
	{
		cout<<"Qualcomm buffer allocated"<<endl;
	}
};

class SamsungCamera: public Camera
{
public:
	void open() override
	{
		cout<<"Samsung camera opened"<<endl;
	}

};

class SamsungBuffer: public Buffer
{
public:
	void allocate() override
	{
		cout<<"Samsung buffer allocated"<<endl;
	}
};


class DeviceFactory
{
public:
	virtual Camera* createCamera()=0;
	virtual Buffer* createBuffer()=0;
	virtual ~DeviceFactory(){}
};

class QualcommFactory: public DeviceFactory
{
public:
	Camera* createCamera() override
	{
		return new QualcommCamera();
	}
	Buffer* createBuffer() override
	{
		return new QualcommBuffer();
	}
};

class SamsungFactory: public DeviceFactory
{
public:
	Camera* createCamera() override
	{
		return new SamsungCamera();
	}
	Buffer* createBuffer() override
	{
		return new SamsungBuffer();
	}
};

int main()
{	
	DeviceFactory* factory;
	factory = new QualcommFactory();

	Camera* cam=factory->createCamera();
	Buffer* buf=factory->createBuffer();

	cam->open();
	buf->allocate();

	delete cam;
	delete buf;
	delete factory;

	return 0;
}