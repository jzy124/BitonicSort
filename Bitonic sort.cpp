#include <iostream>
using namespace std;

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {

	for (int seg_num = 0; seg_num < m; seg_num++)
	{
		float *seg = &data[seg_start[seg_num]];
		int *order_id = &seg_id[seg_start[seg_num]]; //��¼ÿ��������������
		int seg_len = seg_start[seg_num + 1] - seg_start[seg_num];

		//ȷ�������� ��1��0
		for (int i = 0; i < seg_len; i++) {
			order_id[i] = order_id[i] << 1 | 0x01; //���һ������Ϊ����
		}
		int bitonic_flag = 1;
		int order_start = 0;
		int i, order_len, order_mid;
		while (bitonic_flag) {
			bitonic_flag = 0;
			for (i = order_start; i < seg_len && order_id[i] == order_id[order_start]; i++);// �ҳ���ǰ��һ��ͬ���Ӷ�
			order_len = i - order_start;
			order_mid = order_len / 2;
			if (order_len >= 2) {
				bitonic_flag = 1;
				// �ֳ�����
				for (i = order_start; i < order_start + order_mid; i++) {
					order_id[i] = order_id[i] << 1 | !(order_id[i] & 0x01); // ����һ��˳���෴
				}
				for (i = order_start + order_mid; i < order_start + order_len; i++) {
					order_id[i] = order_id[i] << 1 | (order_id[i] & 0x01); // ����һ��˳����ͬ
				}
			}

			order_start = order_start + order_len;
			if (order_start == seg_len)
				order_start = 0; // ������һ�飬��ʼ������һ�飬ֱ�������������γ�<=2ֹ
		}

		// ����order_id��ȷ����˳���������n��˫������
		int s = 1;
		float t;
		int direction, offset;
		for (order_start = 0; order_len < seg_len;) {

			for (i = order_start; i < seg_len && order_id[i] == order_id[order_start]; i++);
			// ������㿪ʼ���� �ҳ�order_idҪ��˳����ͬ��һ��
			order_len = i - order_start;
			if (order_len >= 2) {
				// Ѱ�ҵ�ǰBM�ζ�ӦBp�Ĵ�С
				while (s < order_len) {
					s *= 2;
				}
			}

			direction = (order_id[order_start] & 0x01);
			// �ǵݹ��˫������
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
			// ɾ���Ѿ���ɵ�˳��
			for (i = order_start; i < order_start + order_len; i++) {
				order_id[i] = order_id[i] >> 1;
			}
			order_start = order_start + order_len; //��ʼͬ�����һ��
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
