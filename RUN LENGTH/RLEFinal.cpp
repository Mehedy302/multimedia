#include <iostream>
#include <fstream>
using namespace std;

void Compress()
{
	char c, old_c;
	int count = 0;

	ifstream readFile;

	readFile.open("run_in.txt");

	if(readFile.is_open())
	{

		readFile >> noskipws >> c;

		while(readFile)
		{

			old_c = c;

			count = 1;

			while(readFile >> noskipws >> c && old_c == c)
			{
				count++;
			}

			if (c == old_c && count == 1)
			{
				break;
			}

			ofstream writeFile;

			writeFile.open("run_encoded.txt", ios::app);

			if (writeFile.is_open())
			{
				writeFile << int(old_c) << " " << count << endl;

				writeFile.close();
			}
			else
			{
				cout << "can not open the file" << endl;
			}

		}

		readFile.close();
	}
	else
	{
		cout << "can not open the file" << endl;
	}
}

void Decompress()
{

	int  asciiCode, count;

	ifstream readFile;

	readFile.open("run_encoded.txt");

	if (readFile.is_open())
	{


		while(readFile >> asciiCode >> count)
		{

			ofstream writeFile;

			writeFile.open("run_decoded.txt", ios::app);

			if (writeFile.is_open())
			{
				for (int i = 0; i < count; ++i)
				{
					writeFile << char(asciiCode);
				}


				writeFile.close();
			}
			else
			{
				cout << "can not open the file" << endl;
			}

		}

		readFile.close();
	}
	else
	{
		cout << "can not open the file" << endl;
	}
}

int main()
{
	Compress();

	Decompress();

	return 0;
}
