
#include <iostream>
#include <vector>
#include "../synth-master/olcNoiseMaker.h"
using namespace std;

double w(double dhertz) 
{
 	return dhertz * 2.0 * PI;
}

double osc(double dhertz, double dtime, int ntype)
{
	switch (ntype)
	{
	case 0:
		return sin(w(dhertz) * dtime);
	case 1:
		return sin(w(dhertz) * dtime) > 0.0 ? 1.0 : -1.0;
	case 2:
		return asin(sin(w(dhertz) * dtime)* 2.0/PI);
	default:
		return 0.0;
	}
}
atomic <double> frequencyOutput = 0.0;

double MakeNoise(double dtime) {
	double doutput = osc(frequencyOutput,dtime,2);
	return doutput * 3.0;
	/*
	if (doutput > 0.0)
		return 0.2;
	else
		return -0.2;
	*/
}
int main()
{
	wcout << "My first project"<<endl;
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	for (auto d : devices) wcout << "Output Device" << d << endl;

	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	sound.SetUserFunction(MakeNoise);

	double doctaveBasefrequency = 110.0;
	double d12thRootof2 = pow(2.0, 1.0 / 12.0);

	while (1)
	{
		//keyboard key state check.
		//piano keyboard layout
		bool bkeypressed = false;
		for (int k = 0;k < 15;k++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
			{
				frequencyOutput = doctaveBasefrequency * pow(d12thRootof2, k);
				bkeypressed = true;
			}
		}
		if (!bkeypressed)
		{
			frequencyOutput = 0.0;
		}

	}



	return 0;
}
