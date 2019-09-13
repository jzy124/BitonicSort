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


	//input 2
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
