#include "widget.h"
#include "ui_widget.h"
#include<windows.h>
#include<QDebug>
#include<QMessageBox>
#define hookcode 0x0F //jz的机器码
#define codelong 6
//最简单的改jmp是0xe9长度是5
int adress;
int a;//截获内容地址
int b;//截获标题地址
char c[20]="hooked ";
BYTE *oldmemory = (BYTE *)malloc(sizeof(codelong));//原来的机器码
BYTE *newmemory = (BYTE *)malloc(sizeof(codelong));//修改为jmp xxxxxx
void *p = NULL;//messagebox函数地址
HMODULE hmodule=0;//user32.dll模块地址
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
void fun()//hook功能
{
    //messagebox 跳转到此

    WriteProcessMemory(GetCurrentProcess(),p,oldmemory,codelong,NULL);//恢复MessageboxA
   //平衡栈 读取信息
   asm("add $24,%esp");
   asm("add $0x2c,%esp");
   asm volatile("movl (%%esp),%0" : "=r" (a) );//截获内容地址
   asm("add $0x4,%esp");
   asm volatile("movl (%%esp),%0" : "=r" (b) );//截获标题地址
   asm("sub $0x4,%esp");
   asm("sub $0x2c,%esp");
   asm("add $8,%esp");
   MessageBoxA(NULL,(char*)a,(char*)b,3);
   WriteProcessMemory(GetCurrentProcess(),p,newmemory,codelong,NULL);//修改MessageboxA
   asm("nop");

}
void Widget::on_pushButton_2_clicked()//messgeboxA按钮
{
    MessageBoxA(NULL,"text hook text","caption hook caption ",0);

}

void Widget::on_pushButton_clicked()//hook按钮
{
    hmodule=GetModuleHandleA("user32.dll");//获取模块地址
    p = (void*)GetProcAddress(hmodule, "MessageBoxA");//获取函数地址
    if(*(BYTE*)p!=hookcode)
    {
        memcpy(oldmemory,p,codelong);//保存原来的5个字节
        *newmemory=hookcode;//机器码jz
        *(newmemory+1)=0x85;
        adress=((int)fun)-(int)p-codelong;//计算地址
        WriteProcessMemory(GetCurrentProcess(),newmemory+2,&adress,4,NULL);//写入地址
        WriteProcessMemory(GetCurrentProcess(),p,newmemory,codelong,NULL);//修改MessageboxA

    }
}

void Widget::on_pushButton_3_clicked()
{
   WriteProcessMemory(GetCurrentProcess(),p,oldmemory,codelong,NULL);//恢复MessageboxA
}
