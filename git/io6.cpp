#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

char ch[512*513];

int main (void)
{

	ifstream iFile;
	iFile.open("lena.bmp", ios::binary);

	ofstream oFile;
	oFile.open("negative.bmp", ios::binary);

	if(iFile.is_open() && oFile.is_open())
	{
		//unsigned
		//char ch;
		//iFile >> ch;
		int i=0;
		iFile.get(ch[i]);

		while (!iFile.eof())
		{
			//oFile << ch;
			//iFile >> ch;
			i++;
			iFile.get(ch[i]);
		}

		int size = i+1;
		cout << size << endl;

		for(int j=0; j<512*512; j++)
		{
			int iValue = (int) ch[i];
			if(iValue<0) iValue=0;
			else iValue=255;
			int oValue = 255-iValue;
			char oCharValue = (char) oValue;
			ch[i] = oCharValue;
			i--;
		}

		for(int k=0; k<size; k++)
		{
			oFile << ch[k];
		}

		iFile.close();
		oFile.close();
	}
	else
	{
		cout << "Could not open file" << endl;
	}
	return 0;
}





























