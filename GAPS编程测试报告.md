#  GAPS编程测试报告

提交者：江朝昀

时间：2019.09.14

[TOC]

## 问题说明 

> ------
>
> 给出分成m段的n个浮点数，输入数据已按段号有序，但每段内部无序。用C/C++编写一个分段双调排序(Bitonic sort)函数，对每一段内部的浮点数进行排序，但 不要改变段间的位置。 
>
> ##### 接口方式： 
>
> ------
>
> ```C++
> void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m);
> ```
>
> 输入数据中，data包含需要分段排序的n个float值，seg_id给出data中n个元素各 自所在的段编号。seg_start共有m+1个元素，前m个分别给出0..m-1共m个段的起始位置，seg_start[m]保证等于n。seg_id中的元素保证单调不下降，即对任意的i<j，seg_id[i]<=seg_id[j]。 seg_id所有元素均在0到m-1范围内。 输出结果覆盖data，保证每一段内排序，但不改变段间元素的顺序。 
>
> ##### 注意： 
>
> ------
>
> 1. 必须使用双调排序算法进行排序。 
> 2. 可以直接使用从网上下载的双调排序代码，但须注明出处。 
>
> ##### 样例输入： 
>
> ------
>
> ```C++
> float data[5]={0.8, 0.2, 0.4, 0.6, 0.5};
> int seg_id[5]={0,   0,   1,   1,   1}
> int seg_start[3]={0,2,5};
> int n=5;
> int m=2; 
> ```
>
> ##### 样例输出： 
>
> ------
>
> ```C++
> float data[5]={0.2, 0.8, 0.4, 0.5, 0.6}; 
> ```
>
> ##### 加分挑战（非必需）： 
>
> ------
>
> 1. 不递归：segmentedBitonicSort函数及其所调用的任何其他函数都不得直接或 间接地进行递归。 
> 2. 不调用函数：segmentedBitonicSort不调用除标准库函数外的任何其他函数。 
> 3. 内存高效：segmentedBitonicSort及其所调用的任何其他函数都不得进行动态内存分配，包括malloc、new和静态定义的STL容器。
> 4. 可并行：segmentedBitonicSort涉及到的所有时间复杂度O(n)以上的代码都写 在for循环中，而且每个这样的for循环内部的循环顺序可以任意改变，不影响程序结果。注：自己测试时可以用rand()决定循环顺序。
> 5. 不需内存：segmentedBitonicSort不调用任何函数（包括C/C++标准库函数），不使用全局变量，所有局部变量都是int、float或指针类型，C++程序不使用new关键字。 
> 6. 绝对鲁棒：在输入数据中包含NaN时（例如sqrt(-1.f)），保证除NaN以外 的数 据正确排序，NaN的个数保持不变。  
>
> 你的程序每满足以上的一个条件都可以获得额外的加分。
>
> ##### 应提交的结果：
>
> ------
>
> a) 算法描述； 
> b) 尝试过和完成了的加分挑战；
> c) 可以独立运行的源代码； 
> d) 测试数据； 
> e) 性能分析； 
> f) 测试的起始和完成时间以及实际使用的时间。
>
> ##### 提示： 
>
> ------
>
> 1. 利用好网上资源。 
> 2. 尽量利用输入中的冗余信息。
> 3. 利用好位操作。 



## a) 算法描述

问题的核心是双调排序（bitonic sort），属于排序网络(Sorting Network）的一种。1968年Batcher提出了两个著名的排序方法，其中一个就是双调排序。它有两个重要相关概念，双调序列和Batcher定理。

1. **双调序列**

   所谓双调序列(Bitonic Sequence)是指由一个非严格增序列X和非严格减序列Y构成的序列，比如序列（23,10,8,3,5,7,11,78）。

   定义:一个序列a1,a2,…,an是双调序列(Bitonic Sequence)，如果：

    (1) 存在一个ak(1≤k≤n), 使得a1≥…≥ak≤…≤an成立；或者

    (2) 序列能够循环移位满足条件(1)

2. **Batcher定理**

   将任意一个长为2n的双调序列A分为等长的两半X和Y，将X中的元素与Y中的元素一一按原序比较，即a[i]与a[i+n]（i<n）比较，将较大者放入MAX序列，较小者放入MIN序列。则得到的MAX和MIN序列仍然是双调序列，并且MAX序列中的任意一个元素不小于MIN序列中的任意一个元素。

**双调排序**

根据上述两个概念就可以对双调序列进行双调排序。对于一个长度为n=2^k的双调序列，根据Batcher定理可以将其等长的单调增序列和单调减序列经过按序比较和交换后均分别划分成新的双调序列，得到的双调序列可以继续递归划分，直到子序列长度为1。如果需要将一个双调序列排序为一个单调增序列，在将其子序列按原序比较过程中，若后半序列的数值比对应的前半序列数值要小，则二者要进行交换，比较完成后，根据Batcher定理，后半序列中的任意一个元素不小于MIN序列中的任意一个元素；子序列长度不断二分，直到进行到子序列长度为1时，就可以得到一个升序序列。

如图是一个长度为16的双调序列的排序过程。

![](https://img-blog.csdn.net/20170730230343427?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveGJpbndvcmxk/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)



**任意序列的双调排序**

1. **长度为2的幂次序列**

   根据上述原理，首先想到的就是将原序列排序为双调序列，这个过程与bitonic sort的思路相反，叫做Bitonic merge。将两个相邻的，单调性相反的长度为n（n初始值为1）的单调序列看作一个双调序列，然后进行双调排序；保证双调排序后生成的相邻单调序列单调性相反，就可以构成一个长度为2n的双调序列，然后继续重复上述步骤。设原序列长度为p=2^k，当n=p/2时，最后进行一次单方向排序即可。

2. **长度非2的幂次序列**

   比较容易想到的方法是padding，在原序列中添加足够大的数Maxnum使序列长度补足到2^k。在排序结束后再删除这些Maxnum即可。在序列长度未知时，padding所需要的空间不能确定，有时候填充长度很大，会浪费很多空间。在下文我将这种方法称为基本双调排序。

   

   还有一种对长度非2的幂次序列直接操作的方法，在Flensburg大学[《Bitonic sorting network for n not a power of 2》](http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/oddn.htm)中有详细的介绍和证明。主要过程是，首先对序列进行二分划分，分为长度（n div 2）段和（n-n div 2）段，继续划分直到长度为1时停止。对于每一段，记录其在每一层排序时是增序或是降序。需要考虑升降序的问题是本方法的核心，这是由于序列长度非2次幂造成的。要想理解这个问题，首先要明确两个概念，参考Flensburg给出的证明，以0-1序列为例:

   >如果a序列依次由一个清洁的0序列、一个清洁的1序列和一个清洁的0序列构成，那么我们称a序列双调递增，即a0,…,a(k-1)= 0, ak,…,a(m-1) = 1, am,…,a(n-1) = 0.
   >
   >如果a序列依次由一个清洁的1序列、一个清洁的0序列和一个清洁的1序列构成，那么我们称a序列双调递减，即a0,…,a(k-1)= 1, ak,…,a(m-1) = 0, am,…,a(n-1) = 1.

   在本方法中，如果需要对一个双调序列排序形成一个单调升序列，那么这个双调序列需是双调递减序列；同样的，如果需要排序形成一个单调减序列，那么原双调序列需是双调递增序列。如下图所示。

   ![](https://hellolzc.github.io/assets/2018-04-25-bitonicsort/pic6.png)

   在对其中的非2次幂长度双调序列进行排序时，方法如下：

   假设要将长度为n的双调增序列排序为单调减序列，首先将双调序列分为两部分，第一部分长度为2^k，其中2^k是小于n的最大2次幂，第二部分长度为（n-2^k），将两部分按位比较，如果第一部分数值小于第二部分对应数值，则交换两个数，直到第二部分数全部比较完毕，此时第一部分和第二部分分别成为双调序列（单调序列是特殊的双调序列），重复上述步骤对双调子序列继续排序，最终就可以得到长度为n的单调减序列。

   以将长度为13的序列排序为升序列为例：

   ![](https://github.com/jzy124/BitonicSort/raw/master/1-5.jpg)

   这种方法在设置每段的升降序上花费了一定的时间，但是相比于padding方法，节省了不少空间。针对本道题目，也更好的利用了输入的冗余。

## b) 尝试过和完成了的加分挑战

>1. 不递归：segmentedBitonicSort函数及其所调用的任何其他函数都不得直接或 间接地进行递归。 
>2. 不调用函数：segmentedBitonicSort不调用除标准库函数外的任何其他函数。 
>3. 内存高效：segmentedBitonicSort及其所调用的任何其他函数都不得进行动态内存分配，包括malloc、new和静态定义的STL容器。
>4. 可并行：segmentedBitonicSort涉及到的所有时间复杂度O(n)以上的代码都写 在for循环中，而且每个这样的for循环内部的循环顺序可以任意改变，不影响程序结果。注：自己测试时可以用rand()决定循环顺序。
>5. 不需内存：segmentedBitonicSort不调用任何函数（包括C/C++标准库函数），不使用全局变量，所有局部变量都是int、float或指针类型，C++程序不使用new关键字。 
>6. 绝对鲁棒：在输入数据中包含NaN时（例如sqrt(-1.f)），保证除NaN以外 的数 据正确排序，NaN的个数保持不变。  

因为在阅读题目的时候就浏览了加分项，所以在理解了双调排序原理并且查找了相关参考资料后，我决定直接开始写不进行递归的基本双调排序法，完成了第一个版本：

```c++
#include <iostream>
using namespace std;

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {

	for (int seg_num = 0; seg_num < m; seg_num++)
	{
		int seg_len = seg_start[seg_num + 1] - seg_start[seg_num];
		int sort_len = 1;

		while (sort_len < seg_len) {
			sort_len *= 2;
		}

		float seg[99999] = { 0 };
		float max = 99999999;

		for (int i = 0; i < sort_len; i++) {
			if (i < seg_len) {
				seg[i] = data[i + seg_start[seg_num]];
			}
			else {
				seg[i] = max;
			}
		}

		float t;
		for (int s = 2; s <= sort_len; s *= 2) {

			for (int step = s / 2; step > 0; step /= 2){

				for (int i = 0; i < sort_len; i += s * 2) {

					for (int j = 0; j < s; j += step * 2) {

						for (int k = 0; k < step; k++) {

							if ((seg[i + j + k] > seg[i + j + k + step])||(seg[i + j + k + step] != seg[i + j + k + step])) {
								t = seg[i + j + k];
								seg[i + j + k] = seg[i + j + k + step];
								seg[i + j + k + step] = t;
							}
							if (s < sort_len) {

								if ((seg[i + j + k + s] < seg[i + j + k + step + s])||(seg[i + j + k + step] != seg[i + j + k + step])) {
									t = seg[i + j + k + s];
									seg[i + j + k + s] = seg[i + j + k + step + s];
									seg[i + j + k + step + s] = t;
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < seg_len; i++) {
			data[i + seg_start[seg_num]] = seg[i];
		}		
	}
}

int main() {

	float data[5] = { 0.8, 0.2, 0.4, 0.6, 0.5 };
	int seg_id[5] = { 0,   0,   1,   1,   1 };
	int seg_start[3] = { 0,2,5 };
	int n = 5;
	int m = 2;

	segmentedBitonicSort(data, seg_id, seg_start, n, m);

	for (int i = 0; i < n; i++) {
		cout << data[i] << " ";
	}

	return 0;
}

```

不使用递归时，加分项**1. 不递归**和**4.可并行**可以满足，**2.不调用函数**也很容易就可以达到，没有进行动态内存分配所以**3.内存高效**也满足，**6.绝对鲁棒**只要通过NaN!=NaN的性质将其识别出来，在排序时特殊处理就可以。

但是对于**5.不需内存**这一条，这个方法是有缺陷的。因为padding需要填充原序列，就要声明一个新的数组存放这个序列，但是由于不知道序列的长度且不使用动态内存分配的方法，只能直接声明一个比较大的静态数组，在很多情况下这是一种浪费，而且不能保证规模足够。

从另外一个角度来看，题目的提示中提到了“尽量利用输入中的冗余信息”，输入中确实有一个看起来很多余的信息，并且这种方法里完全没有用到，就是数组seg_id。提示里还说要“利用好位操作”，显然我之前也没有用到。于是我开始思考用什么方法可以利用上seg_id这个数组，解决需要声明静态数组的问题。因为没有什么头绪，我开始查找更多关于双调排序的资料，最终找到了任意长度序列双调排序方法的相关内容，通过学习参考资料完成了最终的版本。最终代码放在下一个模块中。这个方法最核心的部分就是利用seg_id这个数组和位操作记录每层排序时每段是升序还是降序，是非常巧妙的方法；非递归的双调排序部分与padding方法中基本一致。由于不需要对序列进行填充，也就不用声明静态数组了，**5.不需内存**加分项也得到解决。



## c) 可以独立运行的源代码

```c++
#include <iostream>
using namespace std;

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {

	for (int seg_num = 0; seg_num < m; seg_num++)
	{
		float *seg = &data[seg_start[seg_num]];
		int *order_id = &seg_id[seg_start[seg_num]]; //记录每段排序的升降情况
		int seg_len = seg_start[seg_num + 1] - seg_start[seg_num];

		//确定升降序 升1降0
		for (int i = 0; i < seg_len; i++) {
			order_id[i] = order_id[i] << 1 | 0x01; //最后一次排序为升序
		}
		int bitonic_flag = 1;
		int order_start = 0;
		int i, order_len, order_mid;
		while (bitonic_flag) {
			bitonic_flag = 0;
			for (i = order_start; i < seg_len && order_id[i] == order_id[order_start]; i++);// 找出当前层一段同序子段
			order_len = i - order_start;
			order_mid = order_len / 2;
			if (order_len >= 2) {
				bitonic_flag = 1;
				// 分成两段
				for (i = order_start; i < order_start + order_mid; i++) {
					order_id[i] = order_id[i] << 1 | !(order_id[i] & 0x01); // 与上一层顺序相反
				}
				for (i = order_start + order_mid; i < order_start + order_len; i++) {
					order_id[i] = order_id[i] << 1 | (order_id[i] & 0x01); // 与上一层顺序相同
				}
			}

			order_start = order_start + order_len;
			if (order_start == seg_len)
				order_start = 0; // 划分完一遍，开始划分下一遍，直到划分完最深层段长<=2止
		}

		// 按照order_id中确定的顺序进行任意n的双调排序
		int s = 1;
		float t;
		int direction, offset;
		for (order_start = 0; order_len < seg_len;) {

			for (i = order_start; i < seg_len && order_id[i] == order_id[order_start]; i++);
			// 从最深层开始处理 找出order_id要求顺序相同的一段
			order_len = i - order_start;
			if (order_len >= 2) {
				// 寻找当前BM段对应Bp的大小
				while (s < order_len) {
					s *= 2;
				}
			}

			direction = (order_id[order_start] & 0x01);
			// 非递归的双调排序
			for (int step = s / 2; step > 0; step /= 2) {

				for (int j = 0; j < s; j += step * 2) {

					for (int k = 0; k < step; k++) {
						if (j + k + step >= order_len)
							continue;
						offset = order_start + j + k;
						if ((direction == (seg[offset] > seg[offset + step])) || (seg[offset + step] != seg[offset + step])) {
								t = seg[offset];
								seg[offset] = seg[offset + step];
								seg[offset + step] = t;
						}
					}
				}
			}
			// 删除已经完成的顺序
			for (i = order_start; i < order_start + order_len; i++) {
				order_id[i] = order_id[i] >> 1;
			}
			order_start = order_start + order_len; //开始同层的下一段
			if (order_start == seg_len)
				order_start = 0; 
		}
	}
}



int main() {

	//input 1
	float data[5] = { 0.8, 0.2, 0.4, 0.6, 0.5 };
	int seg_id[5] = { 0,   0,   1,   1,   1 };
	int seg_start[3] = { 0,2,5 };
	int n = 5;
	int m = 2;


	////input 2
	//float data[11] = { 0.8, 0.2, 0.4, sqrt(-1.f), 0.6, 0.5, sqrt(-1.f), 0.2, 0.1, sqrt(-1.f), 0.01 }; 
	//int seg_id[11] = { 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2 }; 
	//int seg_start[4] = { 0, 2, 6, 11 }; 
	//int n = 11; 
	//int m = 3; 


	////input 3
	//float data[12] = { 0.8,-1,sqrt(-1.f),0.5,100,2324,-1,sqrt(-1.f),sqrt(-1.f),0,-1,0 };
	//int seg_id[12] = { 0,0,0,0,1,1,1,1,1,1,2,2 };
	//int n = 12;
	//int m = 3;
	//int seg_start[4] = { 0,4,10,12 };

	segmentedBitonicSort(data, seg_id, seg_start, n, m);

	for (int i = 0; i < n; i++) {
		cout << data[i] << " ";
	}

	return 0;
}

```



## d) 测试数据

1. 样例数据

   ```c++
   float data[5] = { 0.8, 0.2, 0.4, 0.6, 0.5 };
   int seg_id[5] = { 0,   0,   1,   1,   1 };
   int seg_start[3] = { 0,2,5 };
   int n = 5;
   int m = 2;
   ```

   输出：

   ![](https://github.com/jzy124/BitonicSort/raw/master/test1.png)

2. 测试数据1

   ```c++
   float data[11] = { 0.8, 0.2, 0.4, sqrt(-1.f), 0.6, 0.5, sqrt(-1.f), 0.2, 0.1, sqrt(-1.f), 0.01 }; 
   int seg_id[11] = { 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2 }; 
   int seg_start[4] = { 0, 2, 6, 11 }; 
   int n = 11; 
   int m = 3; 
   ```

   输出：

   ![](https://github.com/jzy124/BitonicSort/raw/master/test2.png)

3. 测试数据2

   ```c++
   float data[12] = { 0.8,-1,sqrt(-1.f),0.5,100,2324,-1,sqrt(-1.f),sqrt(-1.f),0,-1,0 };
   int seg_id[12] = { 0,0,0,0,1,1,1,1,1,1,2,2 };
   int n = 12;
   int m = 3;
   int seg_start[4] = { 0,4,10,12 };
   ```

   输出：

   ![](https://github.com/jzy124/BitonicSort/raw/master/test3.png)



（测试数据均来自参考资料）

## e) 性能分析 

双调排序的时间复杂度为O(n*(logn)^2)，许多参考资料里都会把它和快速排序的时间复杂度O(nlogn)进行比较。但这是其串行运算的时间复杂度，由于双调排序是一种可以并行计算的排序算法，在并行运算时时间复杂度可以降低。本题中的分段双调排序法在改进后，空间复杂度较低，内存高效，可并行；任意长度双调排序的方法花费了一定的时间去标定排序的升降序，但是节省了不必要的内存浪费。

## f) 测试的起始和完成时间以及实际使用的时间

测试开始时间：2019.09.12  16:30

测试结束时间：2019.09.13   23:30 （发送邮件时间）

9月12日16:30开始查找资料、写程序，约在23:00完成第一版本。

9月13日8:30开始思考对方法进行改进并且查找资料，14:00左右开始研究算法并写第二版本程序，约17:30完成。剩下的时间在整理报告。

## 参考资料

三十分钟理解：双调排序Bitonic Sort，适合并行计算的排序算法 https://blog.csdn.net/xbinworld/article/details/76408595

分段双调排序实现 https://blog.csdn.net/u014226072/article/details/56840243

双调排序的并行实现 https://hellolzc.github.io/2018/04/bitonic-sort-without-padding/

Bitonic sorting network for n not a power of 2 http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/oddn.htm

n!=2^k的双调排序网络 https://blog.csdn.net/ljiabin/article/details/8630627

双调排序 百度百科 https://baike.baidu.com/item/%E5%8F%8C%E8%B0%83%E6%8E%92%E5%BA%8F/9598017

##  结语

在过程中我学习和参考了很多内容，加上自己的一些思考，虽然不是很容易，也花费了比较长的时间，最终还是完成了题目。在第一天晚上完成第一个版本之后，我没有办法说服自己提交，因为对于这个方法，对比题目中的一些要求，我总觉得不是一个理想的方法。第二天上午想过很多办法去解决需要声明静态数组的问题，也尝试改变算法，但是没有找到好的解决方案。因为坚持想要更好的方法，我找到了n!=2^k的双调排序法相关资料，完善了程序。由于本科不是计算机专业，我自知编程水平和很多大神有挺大差距，这次的测试对我来说更像是一次探索和学习，我觉得收获很多。





