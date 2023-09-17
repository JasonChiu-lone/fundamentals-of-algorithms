/*
## 编程题＃2： 文件结构“图”

[来源: POJ](http://bailian.openjudge.cn/practice/2775/) (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

**注意： 总时间限制: 1000ms 内存限制: 65536kB**

### 描述

在计算机上看到文件系统的结构通常很有用。Microsoft Windows上面的"explorer"程序就是这样的一个例子。但是在有图形界面之前，没有图形化的表示方法的，那时候最好的方式是把目录和文件的结构显示成一个"图"的样子，而且使用缩排的形式来表示目录的结构。比如：

```
ROOT
|         dir1
|         |         file1
|         |         file2
|         |         file3
|         dir2
|         dir3
|         |         file1
file1
file2
```

这个图说明：ROOT目录包括两个文件和三个子目录。第一个子目录包含3个文件，第二个子目录是空的，第三个子目录包含一个文件。

### 输入

你的任务是写一个程序读取一些测试数据。每组测试数据表示一个计算机的文件结构。每组测试数据以'*'结尾，而所有合理的输入数据以'#'结尾。一组测试数据包括一些文件和目录的名字（虽然在输入中我们没有给出，但是我们总假设ROOT目录是最外层的目录）。在输入中,以']'表示一个目录的内容的结束。目录名字的第一个字母是'd'，文件名字的第一个字母是'f'。文件名可能有扩展名也可能没有（比如fmyfile.dat和fmyfile）。文件和目录的名字中都不包括空格。

### 输出

在显示一个目录中内容的时候，先显示其中的子目录（如果有的话），然后再显示文件（如果有的话）。文件要求按照名字的字母表的顺序显示（目录不用按照名字的字母表顺序显示，只需要按照目录出现的先后显示）。对每一组测试数据，我们要先输出"DATA SET x:"，这里x是测试数据的编号（从1开始）。在两组测试数据之间要输出一个空行来隔开。

你需要注意的是，我们使用一个'|'和5个空格来表示出缩排的层次。

### 样例输入

```
file1
file2
dir3
dir2
file1
file2
]
]
file4
dir1
]
file3
*
file2
file1
*
#
```

### 样例输出

```
DATA SET 1:
ROOT
|        dir3
|        |        dir2
|        |        file1
|        |        file2
|        dir1
file1
file2
file3
file4

DATA SET 2:
ROOT
file1
file2
```

### 提示

一个目录和它的子目录处于不同的层次

一个目录和它的里面的文件处于同一层次
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<class T>
bool file_cmp(T left, T right){
    // cout << "Comparing " << left.file_name << " and " << right.file_name << endl;
    // 目录优于文件，目录间不排序
    if (left.file_type == 'f' && right.file_type == 'd') return false;
    if (left.file_type == 'd' && right.file_type == 'f') return true;
    if (left.file_type == 'd' && right.file_type == 'd') return false; 
    return left.file_name < right.file_name;
}

class File{
    public:
        vector<File> sub_files;
        File *parent_folder;
        string file_name;
        char file_type;
        File(string file_name_, File *parent_folder_ = NULL){
            file_name = file_name_;
            parent_folder = parent_folder_;
            if (parent_folder == NULL)
                parent_folder = this;
            file_type = file_name.c_str()[0];
        }
        
        File *add_file(File f){
            sub_files.push_back(f);
            // sort(sub_files.begin(), sub_files.end(), file_cmp<File>);
            if (f.file_type == 'd') return &sub_files[sub_files.size() - 1];
            else if (f.file_type == 'R') return this;
            else if (f.file_type == 'f') return this;
            else return this;
        }
        void print_files(int recur_depth){
            stable_sort(sub_files.begin(), sub_files.end(), file_cmp<File>);

            // print the name of this folder
            print_recur(recur_depth);
            cout << file_name << endl;
            // iterate each subfolder and subfile
            vector<File>::iterator it = sub_files.begin();
            for(; it != sub_files.end(); it++){
                if (it->file_type == 'd'){
                    it->print_files(recur_depth + 1);
                }
                else{
                    // print names of subfiles
                    print_recur(recur_depth);
                    cout << it->file_name << endl;
                }
            }
        }
        void print_recur(int recur_depth){
            for (int i = 0; i < recur_depth; i++){
                cout << "|     ";
            }
        }
        File *get_parent_folder(){
            return parent_folder;
        }
};

int main(){
    int data_set_n = 1;
    while (true){ // each dataset
        string in;
        
        
        File root("ROOT");
        File *current_folder = &root;
        while (true){ // each line of input
            cin >> in;
            if (in == "*") break;
            if (in == "#"){
                return 0;
            }
            if (in == "]"){
                current_folder = current_folder->get_parent_folder();
                continue;
            }
            current_folder = current_folder->add_file(File(in, current_folder));
        }

        cout << "DATA SET " << data_set_n << ":" << endl;
        root.print_files(0);
        cout << endl;

        data_set_n += 1;
    }
    return 0;
}

