#include <iostream>
#include <fstream>

using namespace std;

/*I try to use standard C++ to implement the copy command*/
void useage();

int main(int argc, char **argv)
{
    if(argc < 3){
        useage();
        return 1;
    }
    fstream fis;
    fis.open(argv[1], ios::in|ios::binary);
    if(fis.is_open()){
      fstream fis2;
      fis2.open(argv[2], ios::out|ios::binary);
      if(fis2.is_open()) {
        fis.seekg(0, fis.end);
        int length = fis.tellg();
        fis.seekg(0, fis.beg);
        char * buffer = new char[length];
        fis.read(buffer,length);
        fis2.write(buffer,length);
      } else {
        cout << "open dest file error" << endl;
      }
    } else {
        cout << "no such file or dictionary" << endl;
    }
    return 0;
}

void useage(){
   cout << "useage:" << endl
        << "Copy SOURCE... DEST" << endl;
}

