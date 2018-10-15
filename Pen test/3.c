（1）什么是预编译，何时需要预编译：

答案：

１、总是使用不经常改动的大型代码体。

２、程序由多个模块组成，所有模块都使用一组标准的包含文件和相同的编译选项。在这种情况下，可以将所有包含文件预编译为一个预编译头。

 预编译指令指示了在程序正式编译前就由编译器进行的操作，可以放在程序中的任何位置。

（2）char * constp      char const * p     const char *p 上述三个有什么区别？

答案：

char * const p; //常量指针，p的值不可以修改

char const * p；//指向常量的指针，指向的常量值不可以改 const char *p； //和char const *p

char * const p是一个char型指针，指针是常量，不允许修改，即类似p=q的语句是错误的；
char const * p和const char * p是同一种char型指针，指针指向的字符被看作是常量，不允许修改，即类似*p = q的语句是错误的。

（3）char str1[] = "abc"; charstr2[] = "abc"; const char str3[] = "abc"; const charstr4[] = "abc"; const char *str5 = "abc"; const char *str6= "abc"; char *str7 = "abc"; char *str8 = "abc";cout < < ( str1 == str2 ) < < endl; cout < < ( str3 == str4 )< < endl; cout < < ( str5 == str6 ) < < endl; cout < <( str7 == str8 ) < < endl;

结果是：0 0 1 1str1,str2,str3,str4是数组变量，它们有各自的内存空间；而str5,str6,str7,str8是指针，它们指向相同的常量区域。

 

（4）以下代码中的两个sizeof用法有问题吗？

[C易] void UpperCase( char str[] ) // 将 str 中的小写字母转换成大写字母{    for( size_t i=0; i <sizeof(str)/sizeof(str[0]); ++i)        if( 'a' <=str[i] &&str[i] <='z')            str[i] -=('a'-'A' ); } char str[] = "aBcDe"; cout < < "str字符长度为: " < <sizeof(str)/sizeof(str[0]) < < endl; UpperCase( str ); cout < < str< < endl; 答案：函数内的sizeof有问题。根据语法，sizeof如用于数组，只能测出静态数组的大小，无法检测动态分配的或外部数组大小。函数外的str是一个静态定义的数组，因此其大小为6，因为还有'\0'，函数内的str实际只是一个指向字符串的指针，没有任何额外的与数组相关的信息，因此sizeof作用于上只将其当指针看，一个指针为4个字节，因此返回4。

 

（5）一个32位的机器,该机器的指针是多少位答案：

指针是多少位只要看地址总线的位数就行了。80386以后的机子都是32的数据总线。所以指针的位数就是4个字节了。

 

6 main()

{ 

inta[5]={1,2,3,4,5};   

int *ptr=(int*)(&a+1);   

printf("%d,%d",*(a+1),*(ptr-1));

}

答案：2。5 *(a+1）就是a[1]，*(ptr-1)就是a[4],执行结果是2，5 &a+1不是首地址+1，系统会认为加一个a数组的偏移，是偏移了一个数组的大小（本例是5个int） int *ptr=(int *)(&a+1); 则ptr实际是&(a[5]),也就是a+5 原因如下： &a是数组指针，其类型为 int (*)[5]; 而指针加1要根据指针类型加上一定的值，不同类型的指针+1之后增加的大小不同 a是长度为5的int数组指针，所以要加5*sizeof(int) 所以ptr实际是a[5] 但是prt与(&a+1)类型是不一样的(这点很重要) 所以prt-1只会减去sizeof(int*) a,&a的地址是一样的，但意思不一样，a是数组首地址，也就是a[0]的地址，&a是对象（数组）首地址，a+1是数组下一元素的地址，即a[1],&a+1是下一个对象的地址，即a[5].

 

7。请问以下代码有什么问题：

int  main() { chara; char *str=&a; strcpy(str,"hello"); printf(str); return 0; }

答案：没有为str分配内存空间，将会发生异常问题出在将一个字符串复制进一个字符变量指针所指地址。虽然可以正确输出结果，但因为越界进行内在读写而导致程序崩溃。

 

8。char* s="AAA"; printf("%s",s); s[0]='B'; printf("%s",s);有什么错？

答案："AAA"是字符串常量。s是指针，指向这个字符串常量，所以声明s的时候就有问题。 cosnt char*s="AAA"; 然后又因为是常量，所以对是s[0]的赋值操作是不合法的。

 

9。写一个“标准”宏，这个宏输入两个参数并返回较小的一个。

答案：.#defineMin(X, Y) ((X)>(Y)?(Y):(X))  //结尾没有‘；’

 

10。嵌入式系统中经常要用到无限循环，你怎么用C编写死循环。

答案：while(1){}或者for(;;)

 

11。关键字static的作用是什么？

答案：定义静态变量

 

12。关键字const有什么含意？

答案：表示常量不可以修改的变量。

 

13。关键字volatile有什么含意？并举出三个不同的例子？

答案：提示编译器对象的值可能在编译器未监测到的情况下改变。

 

14。int (*s[10])(int) 表示的是什么啊？

答案：int(*s[10])(int) 函数指针数组，每个指针指向一个int func(int param)的函数。

 

15。有以下表达式： int a=248; b=4;int const c=21;const int *d=&a; int *conste=&b;int const *f const =&a; 请问下列表达式哪些会被编译器禁止？为什么？

答案：*c=32;d=&b;*d=43;e=34;e=&a;f=0x321f; *c 这是个什么东东，禁止 *d 说了是const， 禁止 e = &a 说了是const 禁止 const *fconst =&a; 禁止

 

16交换两个变量的值，不使用第三个变量。即a=3,b=5,交换之后a=5,b=3;

答案：有两种解法, 一种用算术算法, 一种用^(异或) a = a + b; b = a - b; a = a - b; or a = a^b;// 只能对int,char.. b = a^b; a = a^b; or a^= b ^= a;

 

17.c和c++中的struct有什么不同？

答案：c和c++中struct的主要区别是c中的struct不可以含有成员函数，而c++中的struct可以。c++中struct和class的主要区别在于默认的存取权限不同，struct默认为public，而class默认为private

18.

#include <stdio.h> 

#include <stdlib.h> 

void getmemory(char *p) 

{   

p=(char *)malloc(100);   

strcpy(p,"helloworld"); 

} 

int main( ) 

{   

char*str=NULL;   

getmemory(str);   

printf("%s/n",str);   

free(str);   return 0;  

}

 答案：程序崩溃，getmemory中的malloc 不能返回动态内存， free（）对str操作很危险

 

19.charszstr[10];  strcpy(szstr,"0123456789");  产生什么结果？为什么？

答案：  长度不一样，会造成非法的OS

 

20.列举几种进程的同步机制，并比较其优缺点。答案：  原子操作 信号量机制    自旋锁    管程，会合，分布式系统

 

21.进程之间通信的途径

答案：共享存储系统消息传递系统管道：以文件系统为基础

 

22.进程死锁的原因

答案：资源竞争及进程推进顺序非法

 

23.死锁的4个必要条件

答案：互斥、请求保持、不可剥夺、环路

 

24.死锁的处理

答案：鸵鸟策略、预防策略、避免策略、检测与解除死锁

 

25. 操作系统中进程调度策略有哪几种？

答案：FCFS(先来先服务)，优先级，时间片轮转，多级反馈

 

26.类的静态成员和非静态成员有何区别？

答案：类的静态成员每个类只有一个，非静态成员每个对象一个

 

27.纯虚函数如何定义？使用时应注意什么？

答案：virtualvoid f()=0; 是接口，子类必须要实现

 

28.数组和链表的区别

答案：数组：数据顺序存储，固定大小连表：数据可以随机存储，大小可动态改变

29.ISO的七层模型是什么？

tcp/udp是属于哪一层？tcp/udp有何优缺点？

答案：应用层表示层会话层运输层网络层物理链路层物理层 tcp /udp属于运输层 TCP 服务提供了数据流传输、可靠性、有效流控制、全双工操作和多路复用技术等。与 TCP 不同， UDP 并不提供对 IP 协议的可靠机制、流控制以及错误恢复功能等。由于 UDP 比较简单， UDP 头包含很少的字节，比 TCP 负载消耗少。 tcp: 提供稳定的传输服务，有流量控制，缺点是包头大，冗余性不好 udp: 不提供稳定的服务，包头小，开销小 

 

30：(void *)ptr 和 (*(void**))ptr的结果是否相同？其中ptr为同一个指针

答案：.(void*)ptr 和(*(void**))ptr值是相同的

 

31：int main()    {    intx=3;    printf("%d",x);    return1;      } 问函数既然不会被其它函数调用，为什么要返回1？

答案：mian中，c标准认为0表示成功，非0表示错误。具体的值是某中具体出错信息

 

32，要对绝对地址0x100000赋值，我们可以用 (unsigned int*)0x100000 =1234; 那么要是想让程序跳转到绝对地址是0x100000去执行，应该怎么做？

答案：*((void(*)( ))0x100000 ) ( ); 首先要将0x100000强制转换成函数指针,即: (void(*)())0x100000 然后再调用它:*((void (*)())0x100000)(); 用typedef可以看得更直观些: typedef void(*)() voidFuncPtr; *((voidFuncPtr)0x100000)();

 

33，已知一个数组table，用一个宏定义，求出数据的元素个数

答案：#defineNTBL #define NTBL (sizeof(table)/sizeof(table[0]))

 

34。线程与进程的区别和联系? 线程是否具有相同的堆栈? dll是否有独立的堆栈?

答案：进程是死的，只是一些资源的集合，真正的程序执行都是线程来完成的，程序启动的时候操作系统就帮你创建了一个主线程。每个线程有自己的堆栈。 DLL中有没有独立的堆栈，这个问题不好回答，或者说这个问题本身是否有问题。因为DLL中的代码是被某些线程所执行，只有线程拥有堆栈，如果DLL中的代码是EXE中的线程所调用，那么这个时候是不是说这个DLL没有自己独立的堆栈？如果DLL中的代码是由DLL自己创建的线程所执行，那么是不是说DLL有独立的堆栈？以上讲的是堆栈，如果对于堆来说，每个DLL有自己的堆，所以如果是从DLL中动态分配的内存，最好是从DLL中删除，如果你从DLL中分配内存，然后在EXE中，或者另外一个DLL中删除，很有可能导致程序崩溃

 

35。unsigned short A = 10; printf("~A = %u\n", ~A); charc=128; printf("c=%d\n",c); 输出多少？并分析过程

答案：第一题，～A ＝0xfffffff5,int值 为－11，但输出的是uint。所以输出4294967285 第二题，c＝0x10,输出的是int，最高位为1，是负数，所以它的值就是0x00的补码就是128，所以输出－128。这两道题都是在考察二进制向int或uint转换时的最高位处理。 

 

（二）

1. -1,2,7,28,,126请问28和126中间那个数是什么？为什么？

答案：第一题的答案应该是4^3-1=63规律是n^3-1(当n为偶数0，2，4)     n^3+1(当n为奇数1，3，5)

 

2.用两个栈实现一个队列的功能？要求给出算法和思路！

答案：设2个栈为A,B, 一开始均为空. 入队: 将新元素push入栈A; 出队: (1)判断栈B是否为空； (2)如果不为空，则将栈A中所有元素依次pop出并push到栈B； (3)将栈B的栈顶元素pop出；这样实现的队列入队和出队的平摊复杂度都还是O(1), 比上面的几种方法要好。

 

3.在c语言库函数中将一个字符转换成整型的函数是atol()吗，这个函数的原型是什么？

答案：函数名: atol 功 能: 把字符串转换成长整型数 用 法: long atol(const char *nptr); 程序例: #include <stdlib.h> #include <stdio.h> int main(void){ long l; char *str = "98765432"; l = atol(lstr); printf("string= %s integer = %ld\n", str, l); return(0); }

 

4。对于一个频繁使用的短小函数,在C语言中应用什么实现,在C++中应用什么实现?

答案：c用宏定义，c++用inline

 

5。直接链接两个信令点的一组链路称作什么?

答案：PPP点到点连接

 

7。软件测试都有那些种类?

答案：黑盒：针对系统功能的测试    白合：测试函数功能，各函数接口

 

8。确定模块的功能和模块的接口是在软件设计的那个队段完成的?

答案：概要设计阶段

 

9。enum string    {   x1,    x2,    x3=10,   x4,    x5,    }x;    问x；

答案：取值在0。1。10。11。12中的一个

 

10。unsigned char *p1;    unsigned long*p2;    p1=(unsigned char *)0x801000;   p2=(unsigned long *)0x810000;    请问p1+5=  ;        p2+5= ;

答案：801005； 810014。不要忘记了这个是16进制的数字，p2要加20变为16进制就是

14

选择题: 

1.Ethternet链接到Internet用到以下那个协议? 

 A.HDLC;B.ARP;C.UDP;D.TCP;E.ID 

 

2.属于网络层协议的是: 

A.TCP;B.IP;C.ICMP;D.X.25 

 

3.Windows消息调度机制是: 

A.指令队列;B.指令堆栈;C.消息队列;D.消息堆栈; 答案：b，a，c

 

四.找错题: 

1.请问下面程序有什么错误?   

inta[60][250][1000],i,j,k;   

for(k=0;k <=1000;k++)   

for(j=0;j<250;j++)     

for(i=0;i<60;i++)     

a[i][j][k]=0;

答案：把循环语句内外换一下

 

2。以下是求一个数的平方的程序,请找出错误:   

#define SQUARE(a) ((a)*(a))   

int a=5;   

int b;   

b=SQUARE(a++);

答案：这个没有问题，s（a＋＋），就是（（a＋＋）×（a＋＋））唯一要注意的就是计算后a＝7了

 

3: typedef unsigned char BYTE

intexamply_fun(BYTE gt_len; BYTE *gt_code)

{

BYTE  *gt_buf;     

gt_buf=(BYTE )MALLOC(Max_GT_Length);  

    ......     

if(gt_len>Max_GT_Length)       

{       

return GT_Length_ERROR;     

}       

 .......    

}

答案：要释放内存问答题:

 

1.IP Phone的原理是什么?

答案：IPV6

2.TCP/IP通信建立的过程怎样，端口有什么作用？

答案：三次握手，确定是哪个应用程序使用该协议

（三）

1、局部变量能否和全局变量重名？

答案：能，局部会屏蔽全局。要用全局变量，需要使用"::" 局部变量可以与全局变量同名，在函数内引用这个变量时，会用到同名的局部变量，而不会用到全局变量。对于有些编译器而言，在同一个函数内可以定义多个同名的局部变量，比如在两个循环体内都定义一个同名的局部变量，而那个局部变量的作用域就在那个循环体内

 

2、如何引用一个已经定义过的全局变量？

答案：extern 可以用引用头文件的方式，也可以用extern关键字，如果用引用头文件方式来引用某个在头文件中声明的全局变理，假定你将那个变写错了，那么在编译期间会报错，如果你用extern方式引用时，假定你犯了同样的错误，那么在编译期间不会报错，而在连接期间报错

 

3、全局变量可不可以定义在可被多个.C文件包含的头文件中？为什么？

答案：可以，在不同的C文件中以static形式来声明同名全局变量。可以在不同的C文件中声明同名的全局变量，前提是其中只能有一个C文件中对此变量赋初值，此时连接不会出错

 

4、语句for( ；1 ；)有什么问题？它是什么意思？

答案：和while(1)相同。

 

5、do……while和while……do有什么区别？

答案：前一个循环一遍再判断，后一个判断以后再循环。

 

6、请写出下列代码的输出内容＃include <stdio.h> main() { int a,b,c,d; a=10; b=a++; c=++a;d=10*a++; printf("b，c，d：%d，%d，%d"，b，c，d）; return 0; }

答案：10，12，120  a=10;  b=a++;//a=11 b=10  c=++a;//a=12 c=12  d=10*a++;//a=13 d=120

 

高级题

1、static全局变量与普通的全局变量有什么区别？static局部变量和普通局部变量有什么区别？static函数与普通函数有什么区别？

答案：全局变量(外部变量)的说明之前再冠以static 就构成了静态的全局变量。全局变量本身就是静态存储方式，静态全局变量当然也是静态存储方式。这两者在存储方式上并无不同。这两者的区别虽在于非静态全局变量的作用域是整个源程序， 当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的。而静态全局变量则限制了其作用域，即只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域局限于一个源文件内，只能为该源文件内的函数公用，因此可以避免在其它源文件中引起错误。从以上分析可以看出，把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期。把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。 static函数与普通函数作用域不同。仅在本文件。只在当前源文件中使用的函数应该说明为内部函数(static)，内部函数应该在当前源文件中说明和定义。对于可在当前源文件以外使用的函数，应该在一个头文件中说明，要使用这些函数的源文件要包含这个头文件 static全局变量与普通的全局变量有什么区别：static全局变量只初使化一次，防止在其他文件单元中被引用; static局部变量和普通局部变量有什么区别：static局部变量只被初始化一次，下一次依据上一次结果值； static函数与普通函数有什么区别：static函数在内存中只有一份，普通函数在每个被调用中维持一份拷贝

 

2、程序的局部变量存在于（）中，全局变量存在于（）中，动态申请数据存在于（）中。

答案：栈；静态区；堆

 

3、设有以下说明和定义： typedef union {long i; int k[5]; char c;} DATE; struct data { intcat; DATE cow; double dog;} too; DATE max; 则语句 printf("%d",sizeof(too)+sizeof(max));的执行结果是：______ 答案：DATE是一个union, 变量公用空间. 里面最大的变量类型是int[5], 占用20个字节. 所以它的大小是20 data是一个struct, 每个变量分开占用空间. 依次为int4 + DATE20 + double8 = 32. 所以结果是 20 + 32 = 52. 当然...在某些16位编辑器下, int可能是2字节,那么结果是 int2 +DATE10 + double8 = 20

 

 

4、队列和栈有什么区别？

答案：队列先进先出，栈后进先出÷

 

6、已知一个单向链表的头，请写出删除其某一个结点的算法，要求，先找到此结点，然后删除。

答案：slnodetype*Delete(slnodetype *Head,int key){}中if(Head->number==key) { Head=Pointer->next; free(Pointer);break; } Back = Pointer;       Pointer=Pointer->next; if(Pointer->number==key){            Back->next=Pointer->next;free(Pointer); break; } void delete(Node* p) {    if(Head =Node)    while(p) }

 

7、请找出下面代码中的所以错误说明：以下代码是把一个字符串倒序，

如“abcd”倒序后变为“dcba”

1、＃include"string.h"

2、main()

3、{

4、 char*src="hello,world";

5、 char*dest=NULL;

6、 intlen=strlen(src);

7、 dest=(char*)malloc(len);

8、 char* d=dest;

9、 char* s=src[len];

10、 while(len--!=0)

11、 d++=s--;

12、 printf("%s",dest);

13、 return 0;

14、}

答案：还要加上＃include<stdio.h> int main(){ char* src = "hello,world"; int len =strlen(src); char* dest = (char*)malloc((len+1)*sizeof(char));  //要为\0分配一个空间 char* d = dest; char* s = &src[len-1]; //指向最后一个字符 while( len-- != 0 )*d++=*s--; *d = 0; //尾部要加\0 printf("%s\n",dest); free(dest);// 使用完，应当释放空间，以免造成内存汇泄露 return 0;}   

 

 华为笔试题（3） 2006-09-29 19:41

一、判断题（对的写T，错的写F并说明原因，每小题4分，共20分）

1、有数组定义int a[2][2]={{1},{2,3}};则a[0][1]的值为0。（   正确 ）

2、int (*ptr) (),则ptr是一维数组的名字。（错误 int (*ptr) ();定义一个指向函数的指针变量   ）

3、指针在任何情况下都可进行>, <,>=, <=,==运算。（  错误  ）

4、switch(c) 语句中c可以是int,long,char ,float ,unsigned int 类型。（  错，不能用实形 ）

 

二、填空题（共30分）

1、在windows下，写出运行结果，每空2分，共10分。 char str[ ]= ＂Hello＂; char *p=str; int n=10; sizeof(str)=(     ) sizeof(p)=(      )sizeof(n)=(      ) void func(charstr[100]){    } sizeof(str)=(    )  答案：6，4，4，4, 具体解释请参看我的空间里的“C/C++程序员应聘试题剖析”

 

2、void getmemory(char **p, int num) { *p=(char *) malloc(num);} voidtest(void) {  char *str=NULL;   getmemory(&str,100);    strcpy(str,＂hello＂);    printf(str); } 运行test函数有什么结果？（                               ）10分  答案：输出hello，但是发生内存泄漏。

 

3、设int arr[]={6,7,8,9,10};      int*ptr=arr;    *(ptr++)+=123;  printf(＂%d,%d＂,*ptr,*(++ptr));(                                 ) 10分答案：8，

 

8。这道题目的意义不大，因为在不同的编译器里printf的参数的方向是不一样的，在vc6.0下是从有到左，这里先*(++ptr) 后*pt，于是结果为8，8

 

三、编程题（第一小题20，第二小题30分）

1、  不使用库函数，编写函数int strcmp(char  *source, char *dest) 相等返回0，不等返回-1；

答案：一、 intstrcmp(char  *source, char *dest) { assert((source!=NULL)&&(dest!=NULL));  int i,j;  for(i=0;source[i]==dest[i]; i++)  {  if(source[i]=='\0' &&dest[i]=='\0')    return 0;  else    return-1;  } } 答案：二、 intstrcmp(char *source, char *dest) {    while ( (*source != '\0')&& (*source == *dest))    { source++;dest++;    }    return ( (*source) - (*dest) ) ?-1 : 0; }

2、  写一函数int fun(char *p)判断一字符串是否为回文，是返回1，不是返回0，出错返回-1 答案：一、 int fun(char *p) { if(p==NULL)  return -1;  else  {  int length = 0;  inti = 0;  int judge = 1;  length = strlen(p);  for(i=0; i<length/2; i++)  {    if(p[i]!=p[length-1-i])   judge = 0;    break;  }  if(judge ==0)    return 0;  else    return 1;  } }答案：二、 intfun(char *p){ int len = strlen(p) - 1; char *q = p + len; if (!p) return -1;while (p < q) { if ((*p++) != (*q--)) return 0; } return 1;} 

 

华为笔试网络题（3） 2006-09-30 12:48

1.在OSI 7 层模型中,网络层的功能有( )

A.确保数据的传送正确无误  B.确定数据包如何转发与路由 C.在信道上传送比特流   D.纠错与流控

2.FDDI 使用的是___局域网技术。( )

A.以太网;    B.快速以太网;    C.令牌环;    D.令牌总线。

3.下面那种LAN 是应用CSMA/CD协议的（)

A.令牌环    B.FDDI   C.ETHERNET    D.NOVELL

4.TCP 和UDP 协议的相似之处是 ( )

A.面向连接的协议    B.面向非连接的协议    C.传输层协议    D.以上均不对

5.应用程序PING 发出的是___报文.( )

 A.TCP 请求报文。    B.TCP 应答报文。    C.ICMP 请求报文。  D.ICMP 应答报文。

6.以下说法错误的是(多) ( )

A.中继器是工作在物理层的设备    B.集线器和以太网交换机工作在数据连路层 C.路由器是工作在网络层的设备   D.桥能隔离网络层广播

7.当桥接收的分组的目的MAC地址在桥的映射表中没有对应的表项时,采取的策略是( )

A.丢掉该分组  B.将该分组分片    C.向其他端口广播该分组    D.以上答案均不对

8.LAN Switch 在网络层次模型中的地位( )

A.物理层    B.链路层    C.网络层    D.以上都不是

9.小于___的TCP/UDP端口号已保留与现有服务一一对应,此数字以上的端口号可自由分配。( )A.199      B.100   C.1024      D.2048

10.当一台主机从一个网络移到另一个网络时,以下说法正确的是 ( )

A.必须改变它的IP 地址和MAC 地址    B.必须改变它的IP 地址,但不需改动MAC 地址

C.必须改变它的MAC 地址,但不需改动IP 地址    D.MAC 地址.IP 地址都不需改动

答案：1.B; 2.C;3.C; 4.C; 5.C; 6.BD; 7.C; 8.B; 9.C; 10.B. 

 

华为笔试题（4） 2006-09-30 13:00

1. 找错 void test1()

{   

char string[10];    char*str1="0123456789";   

strcpy(string, str1);

}

答：表面上并且编译都不会错误。但如果string数组原意表示的是字符串的话，那这个赋值就没有达到意图。最好定义为char string[11]，这样最后一个元素可以存储字符串结尾符'\0'; void test2() {    char string[10],str1[10];  for(int I=0; I <10;I++)  {    str1[I]='a';  }  strcpy(string, str1); } 答：strcpy使用错误，strcpy只有遇到字符串末尾的'\0'才会结束，而str1并没有结尾标志，导致strcpy函数越界访问，不妨让str1[9]='\0'，这样就正常了。 void test3(char* str1){    char string[10];    if(strlen(str1) <=10){    strcpy(string, str1); } } 答：这又会出现第一道改错题的错误了。strlen(str1)算出来的值是不包含结尾符'\0'的，如果str1刚好为10个字符＋1结尾符，string就得不到结尾符了。可将strlen(str1) <=10改为strlen(str1) <10。

 

2. 找错

#define MAX_SRM 256

DSN get_SRM_no()

{   

static int SRM_no;   

int I;   

for(I=0;I<MAX_SRM;I++,SRM_no++)

{

SRM_no %= MAX_SRM;   

if(MY_SRM.state==IDLE) 

{     

break;   

} 

} 

if(I>=MAX_SRM)   

return (NULL_SRM); 

else   

return SRM_no;

}

答：我不知道这段代码的具体功能，但明显有两个错误 1，SRM_no没有赋初值 2，由于static的声明，使该函数成为不可重入（即不可预测结果）函数，因为SRM_no变量放在程序的全局存储区中，每次调用的时候还可以保持原来的赋值。这里应该去掉static声明。

 

3. 写出程序运行结果

int sum(int a)

{   

auto int c=0;   

static int b=3; 

c+=1; 

b+=2; 

return(a+b+c);

} 

void main()

{   

int I; 

int a=2; 

for(I=0;I <5;I++) 

{   

printf("%d,", sum(a)); 

}

}

答：8,10,12,14,16该题比较简单。只要注意b声明为static静态全局变量，其值在下次调用时是可以保持住原来的赋值的就可以。

 

4. int func(int a)

{   

int b;   

switch(a)   

{       

case 1: b=30;       

case 2: b=20;       

case 3: b=16;       

default: b=0;   

}   

return b;

}

则func(1)=?

答：func(1)=0，因为没有break语句，switch中会一直计算到b=0。这是提醒我们不要忘了break。呵呵。

5: 

int a[3]; 

a[0]=0;

a[1]=1;

a[2]=2; 

int *p, *q; 

p=a; 

q=&a[2];

则a[q-p]=?

答：a[q-p]=a[2]=2;这题是要告诉我们指针的运算特点

 

6. 定义 int **a[3][4], 则变量占有的内存空间为：_____

答：此处定义的是指向指针的指针数组，对于32位系统，指针占内存空间4字节，因此总空间为3×4×4＝48。

7. 编写一个函数，要求输入年月日时分秒，输出该年月日时分秒的下一秒。如输入2004年12月31日23时59分59秒，则输出2005年1月1日0时0分0秒。

答： /*输入年月日时分秒，输出年月日时分秒的下一秒，输出仍然在原内存空间*/

void NextMinute(int *nYear,int *nMonth,int*nDate,int *nHour,int *nMinute,int *nSecond)

{ 

int nDays;  (*nSecond)++;  // 秒加1  if(*nSecond>=60) // 秒满60，做出特殊处理，下面时，日，月等类同 

{   

*nSecond=0;   

(*nMinute)++;   

if(*nMinute>=60)   

{     

*nMinute=0;     

 (*nHour)++;     

if(*nHour>=24)     

{       

*nHour=0;       

(*nDate)++;       

switch(*nMonth)       

{         

case1:         

case3:         

case5:         

case7:         

case8:         

case10:         

case12:           

nDays=31;         

break;         

case 2:// 判断闰年           

if(*nYear%400==0 ¦¦*nYear%100!=0&&*nYear%4==0)           

{           

nDays=29;           

} 

else           

{           

nDays=28;           

}         

break;         

default:           

nDays=30;         

break;       

}       

if(*nDate>nDays)       

{         

*nDate=1;         

(*nMonth)++;         

if(*nMonth>12)         

{         

*nMonth=1;         

(*nYear)++;         

}       

}     

}   

} 

}

} /*示例可运行代码*/

void main()

{ 

intnYear=2004,nMonth=12,nDate=31,nHour=59,nMinute=59,nSecond=59; 

NextMinute(&nYear,&nMonth,&nDate,&nHour,&nMinute,&nSecond); 

printf("The result:%d-%d-%d%d:%d:%d",nYear,nMonth,nDate,nHour,nMinute,nSecond);

}   

华为硬件笔试题2006-09-30 13:01

一 选择 13个题目,没有全部抄下来,涉及的课程有电路,模拟电路,数字电路,信号与系统,微机原理,网络,数字信号处理 有关于 1.微分电路2.CISC,RISC 3.数据链路层

二 填空 10个题目,没有全部抄下来,涉及的课程有电路,模拟电路,数字电路,信号与系统,微机原理,网络,数字信号处理 有关于

1.TIC6000 DSP 2.二极管 3.RISC 4.IIR

三 简答

1.x(t)的傅立叶变换为X(jw)=$(w)+$(w-PI)+$(w-5) h(t)=u(t)-u(t-2) 问: (1),x(t)是周期的吗? (2),x(t)*h(t)是周期的吗? (3),两个非周期的信号卷积后可周期吗? 2.简述分组交换的特点和不足四 分析设计 1.波形变换题目 从正弦波->方波->锯齿波->方波,设计电路 2.74161计数器组成计数电路,分析几进制的 3.用D触发器构成2分频电路 4.判断MCS-51单片机的指令正确还是错误,并指出错误原因 (1) MUL R0,R1 (2) MOV A,@R7(3) MOV A,#3000H (4) MOVC @A+DPTR,A (5) LJMP #1000H () 5.MCS-51单片机中,采用12Mhz时钟,定时器T0采用模式1(16位计数器),请问在下面程序中,p1.0的输出频率 MOV TMOD,#01H SETB TR0LOOP:MOV TH0,#0B1H MOV TL0,#0E0H LOOP1:JNB TF0,LOOP1 CLR TR0 CPL P1.0 SJMP LOOP     

华为硬件面试题2006-09-30 13:02 　　全都是几本模电数电信号单片机题目　　

1.用与非门等设计全加法器　　

2.给出两个门电路让你分析异同　　

3.名词:sram,ssram,sdram 　　

4.信号与系统:在时域与频域关系 　　

5.信号与系统:和4题差不多 　　

6.晶体振荡器,好像是给出振荡频率让你求周期(应该是单片机的,12分之一周期.. 　　..) 　　

7.串行通信与同步通信异同,特点,比较 　　

8.RS232c高电平脉冲对应的TTL逻辑是?(负逻辑?) 　　

9.延时问题,判错 　　

10.史密斯特电路,求回差电压 　　

11.VCO是什么,什么参数(压控振荡器?) 　　

12. 用D触发器做个二分颦的电路.又问什么是状态图

13. 什么耐奎斯特定律,怎么由模拟信号转为数字信号 　　

14. 用D触发器做个4进制的计数 　　

15.那种排序方法最快? 　　

一、 研发（软件）　　

用C语言写一个递归算法求N！； 　　给一个C的函数，关于字符串和数组，找出错误； 　　防火墙是怎么实现的？　　你对哪方面编程熟悉？ 

硬件： 1、继电器控制电路。 2、SDRAM是怎么工作的 3、写出逻辑表达式说明A2A1A0大于B2B1B0。 4、常用触发器有几种 5、示波器有几种触发方式，举出三种     

华为3COM数据通信工程师试题 2006-09-29 18:53

1 H.323协商答案：12个包协商，先H225然后H245，需要注意的是面试官可能会问到跟SIP的比较

2 ipsec为什么是三层的。L2tp为什么是二层的？ 答案：IPSec (Internet 协议安全)是一个工业标准网络安全协议，为 IP 网络通信提供透明的安全服务，保护 TCP/IP 通信免遭窃听和篡改，可以有效抵御网络攻击，同时保持易用性。IPSec有两个基本目标：1）保护IP数据包安全；2）为抵御网络攻击提供防护措施。 第三层保护的优点 　　通常IPSec提供的保护需要对系统做一定的修改。但是IPSec在IP传输层即第三层的"策略执行"（strategic implementation）几乎不需要什么额外开销就可以实现为绝大多数应用系统、服务和上层协议提供较高级别的保护；为现有的应用系统和操作系统配置IPSec几乎无须做任何修改，安全策略可以在Active Directory里集中定义也可以在某台主机上进行本地化管理。　　IPSec策略在ISO参考模型第三层即网络层上实施的安全保护，其范围几乎涵盖了TCP/IP协议簇中所有IP协议和上层协议，如TCP、UDP、ICMP，Raw（第255号协议）、甚至包括在网络层发送数据的客户自定义协议。在第三层上提供数据安全保护的主要优点就在于：所有使用IP协议进行数据传输的应用系统和服务都可以使用IPSec，而不必对这些应用系统和服务本身做任何修改。　　运作于第三层以上的其他一些安全机制，如安全套接层SSL，仅对知道如何使用SSL的应用系统（如Web浏览器）提供保护，这极大地限制了SSL的应用范围；而运作于第三层以下的安全机制，如链路层加密，通常只保护了特定链路间的数据传输，而无法做到在数据路径所经过的所有链路间提供安全保护，这使得链接层加密无法适用于 Internet 或路由 Intranet 方案中的端对端数据保护。 L2TP（第二层隧道协议）通过使用虚拟专用网 (VPN) 连接和第二层隧道协议 (L2TP)，可以通过 Internet 或其他公共网络访问专用网。L2TP 是一个工业标准Internet 隧道协议，它和点对点隧道协议(PPTP) 的功能大致相同。利用L2TP来构建企业的VPN，一样需要运营商支持，因为LAC一般是在传统电话交换网络中部署的，并且一个公司的分支机构以及移动办公的员工在地域上分布很广，所以需要各地的运营商都具备LAC才能够实现企业大范围构建VPN网络。当然企业也可以构建自己的基于L2TP的VPN网络在L2TP VPN中，用户端的感觉就像是利用PPP协议直接接到了企业总部的PPP端接设备上一样，其地址分配可以由企业通过DHCP来分配，认证方式可以沿用PPP一直沿用的各种认证方式，并且L2TP是IETF定义的，其MIB库也将定义出来从而可以实现全局的网络管理。

3 ospf中包的ttl值是多少？ 答案：1，因为224.0.0.5/224.0.0.6是本地链路组播

4 OSPF为什么要划分区域？答案：RD用于BGP区分VPN路由，RT用于在各VRF中导入或导出路由

5 MPLS VPN的标签一共有几层。内网的标签放在哪里。答案：如果没有流量工程则是2层，内网标签在隧道标签之后

6 MPLS中RD和RT的作用分别是什么？答案：减少CPU负载，区域间使用距离矢量算法，因此其它区域的泛洪不会影响区域的SPF运算，这里注意面试官可能会问OSPF多区域如何防止环路。(注意答本质而不是现象，免得面试官追问)

7 RR防止环路的机制。答案：RR中通过ORIGIN ID和CLUSTER ID防止环路，若RR收到带有自己CLUSTER ID的路由则丢弃

8 BGP控制out-bound用local-pre，控制进来的用med. 答案：正确

9 ospf是工作在哪个协议上的？答案：IP，OSPF协议号89

10 ospf的LSA类型。答案：1，2，3，4，5，6，7，没有什么好说的，注意考官问到第6类LSA，组播再准备多点

11 简述OSPF的基本工作机制。答案：这个没什么可以说了，把知道的都说出来就行了

12 ppp的lcp和ncp协商过程。答案：LCP过程协商二层链路相关参数，MTU/PPP压缩/认证协议类型等~~~NCP协商第三层协议，IP地址，IP压缩等等，这里记住最好不要说CDP

13 笔试中还有一道PSTN的信令控制有哪三种？答案：这个我只知道随路信令和共路信令，信工同学提供的答案是：监视\号码\音信号\，知道正确答案的朋友麻烦纠正一下

14sloari 8.0查看进程的命令是什么？linux 7.3查看IP的命令是什么？答案：不知道华为为什么问这个，第一个是PS吧？第二个是IFCONFIG/A

15 IP是5.32.0.0,掩码255.224.0.0。请问最大的有效地址是多少。答案：最大主机地址5。64。255。254

17 lx/lh的有效距离是多少？答案：？？？

18 IP 包头几个字节？加上数据部分几个字节答案：应该是问IPV4，一般20字节，加上源路由选择等后最大60字节，加上数据部分还是根据链路MTU决定

20 CQ能不能有一种流量dominate第二种流量? 答案：CQ不能有一种流量DOMINATE其它任何流量 21 FTP下载一个文件完成。有几个TCP连接答案：4个
