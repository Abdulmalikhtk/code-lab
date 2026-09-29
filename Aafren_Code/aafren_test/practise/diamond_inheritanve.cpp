#include <iostream>
using std::endl,std::cout;

class Registerblock
{
public:
	int reg;
	Registerblock()
	{
		cout<<"Registerblock mapped"<<endl;
		reg=0;
	}
};	

class CameraDriver: virtual public Registerblock
{
public:
	void cameraConfig()
	{
		reg=10;
		cout<<"camera configured"<<endl;
	}
};

class AudioDriver: virtual public Registerblock
{
public:
	void auidoConfig()
	{
		reg=20;
		cout<<"audio configured"<<endl;
	}
};

class MultimediaDriver: public CameraDriver,public AudioDriver
{
public:
	void showReg()
	{
		cout<<"Register value:"<<reg<<endl;
	}
};

int main()
{
	MultimediaDriver md;
	// md.cameraConfig();
	md.showReg();

	return 0;
}