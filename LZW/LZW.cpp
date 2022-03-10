#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <filesystem>
#include<sstream>


using namespace std;


#include <sys/stat.h>

long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}


template <typename Iterator>
Iterator compress(const string &uncompressed, Iterator result) {

  int dictSize = 256;
  map<string,int> dictionary;
  for (int i = 0; i < dictSize; i++)
    dictionary[string(1, i)] = i;

  string w;
  for (string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];

      dictionary[wc] = dictSize++;
      w = string(1, c);
    }
  }


  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}


template <typename Iterator>
string decompress(Iterator begin, Iterator end) {

  int dictSize = 256;
  map<int,string> dictionary;
  for (int i = 0; i < dictSize; i++)
    dictionary[i] = string(1, i);

  string w(1, *begin++);
  string result = w;
  string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";

    result += entry;


    dictionary[dictSize++] = w + entry[0];

    w = entry;
  }
  return result;
}



int main() {
  vector<int> compressed;
  string path = "input.txt";

    long inputfilesize = GetFileSize(path);
    cout<< "Input File Size : " <<inputfilesize<<endl;


    string myText;


ifstream f(path);

   if(f) {
      ostringstream ss;
      ss << f.rdbuf();
      myText = ss.str();
   }
   f.close();
   ofstream outfile;
   outfile.open("compressed.txt");

  compress(myText, back_inserter(compressed));
  string s(compressed.begin(), compressed.end());
  for(int i = 0;i< s.length();i++)
  {
     outfile << (int)s[i] <<',';

  }
  outfile.close();
   path = "compressed.txt";

   long outputfilesize = GetFileSize(path);

   cout<<"Compressed File size : "<<outputfilesize<<endl;

   cout<<"compression Ratio : "<<(float)((inputfilesize*1.0)/outputfilesize);


  cout << endl;
  string decompressed = decompress(compressed.begin(), compressed.end());





  outfile.open("decompressed.txt");





  outfile<<decompressed<<endl;
  outfile.close();


  return 0;
}
