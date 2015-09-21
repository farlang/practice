
我们经常在linux下使用cp命令，将一个文件拷贝为另外一个文件。
cp命令的使用方式如下：

    Usage: cp [OPTION]... [-T] SOURCE DEST
    or:  cp [OPTION]... SOURCE... DIRECTORY
    or:  cp [OPTION]... -t DIRECTORY SOURCE...
    Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.

###我尝试自己实现一个cp命令

###思路
1. 使用标准的C++文件输入输出流
2. 先使用输入流打开文件，并将其内容全部读到buf中
3. 然后使用输出流打开一个文件，将buf中的内容全部写到文件中

###我的代码--v1
``` cpp
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
```
编译并测试发现基本使用没有问题。

###小节
1. 根据自己的思路实现了基本的功能，能够拷贝一些小的文件，但是由于是把整个文件的数据都读到缓存中，如果文件很大，那就会有问题了，这个需要进一步的改进。
2. 代码的规范程度，如何时空格，何时换行存在问题

