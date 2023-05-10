#include <iostream>
#include <vector>
#include <cmath>         // Heap�� ���̴� log2(n)�� bound �Ǳ� ������ log2 function�� �̿��ϱ� ���� ���
using namespace std;     

class Heap {
private:
	vector<int> heap;     // �迭 ����� Heap�� �����ϱ� ���Ͽ� vector ���
	int heap_size;        // Node�� �� ���� �� ������ Node�� index Ȯ��
	int totalSec;         // Algorithm���� deleteMax()�� ���� �ð��� �м��ϱ� ���� ���� ����

public:
	Heap() {                    // Heap �ʱ�ȭ
		heap.push_back(-1);     // index 0�� -1(Dummy Value) ����
		this->heap_size = 0;    
		this->totalSec = 0;
	}

	bool isEmpty() {                             // Heap�� ��� �ִ��� Ȯ���ϴ� �Լ�
		if (heap_size == 0) { return true; }
		else { return false; }
	}

	void insert(int data) {       // ������ Heap�� vector�� ���Ҹ� ���� (push_back �̿�)
		heap_size++;
		heap.push_back(data);     
	}

	void swap(int idx1, int idx2) {     // upheap�� downheap�� ���ؼ� ���Ҹ� ���� �ٲٰ� �ǹǷ� �� ���Ҹ� swap�ϴ� �Լ� ����
		int tmp = heap[idx1];
		heap[idx1] = heap[idx2];
		heap[idx2] = tmp;
	}

	int findHeight(int idx) {                                 // �� Node�� ���̸� ã������ �Լ�
		return floor(log2(heap_size)) - floor(log2(idx));     // ��ü Heap�� ���̿��� �ش� Node�� ���̸� ������ ������
	}

	void constructHeap(int idx) {        // �Էµ� Heap�� ���Ͽ� Heap ������ �����ֱ� ���� �Լ� (Max-Heap)
		int left = 2 * idx;
		int right = 2 * idx + 1;

		int height = findHeight(idx);

		int K;

		if (height > 0) {                // fixHeap �Լ��� �ڽĵ���� �񱳸� �ϴ� �Լ��̹Ƿ� �ش� ��尡 leaf Node�̸� �������� ����
			constructHeap(left);         // main �Լ����� idx ���� 1�� �����ϸ鼭 Root ����� ���� Subtree���� Heap ������ �����ϵ��� ��
			constructHeap(right);        // Root ����� ���� Subtree�� ������ ������ ����, ������ Subtree�� �����ϵ��� ��

			K = heap[idx];

			fixHeap(idx, K);             // Heap ������ ������Ű�� ���ؼ� fixHeap(int idx, int K) �Լ� ȣ��
		}
		return;
	}
	
	void fixHeap(int idx, int K) {     // idx : fixHeap�� �����ϴ� index ��, K : heap[idx] �� (leaf�� �ƴ� Node�� Key ��)
		int left = 2 * idx;
		int right = 2 * idx + 1;

		if (left > heap_size) {     // leaf ������� Ȯ�� (���� �ڽ��� index���� ��ü Heap�� ũ�⺸�� ũ�� �������� �����Ƿ� �ش� ���� leaf ��尡 �ȴ�.) 
			heap[idx] = K;          // leaf ����� ��� ���� ������� �ʰ� ����
		}
		else {              // DownHeap ����
			int bigger;     // �ڽ�, ���� �ڽ�, ������ �ڽİ��� Key�� �񱳸� ���� �� ū Key���� ���� ����� index�� �����ϴ� ����

			if (left <= heap_size && heap[left] > heap[idx]) {          // ���� �ڽ��� ���� & ���� �ڽ��� Key���� �� ŭ
				bigger = left;
			}
			else {                                                      // ���� �ڽ��� ���� & �ڽ��� Key���� �� ŭ
				bigger = idx;
			}
			if (right <= heap_size && heap[right] > heap[bigger]) {     // ������ �ڽ��� ���� & ������ �ڽ��� Key���� ���� �ڽ� or �ڽ��� Key ���� ���� ŭ
				bigger = right;
			}

			if (bigger != idx) {                                        // �ڽ��� Key���� ���� ū ���� �ƴ϶�� ū ���� Swap
				swap(idx, bigger);
				fixHeap(bigger, heap[bigger]);
			}
		}
		return;
	}

	void fixHeap_vacant(int idx, int K) {     // fixHeapFast �������� Heap�� height�� 1 ������ ���(���Ұ� 3�� ����) ���� fixHeap�� ����ϱ� ����
		int left = 2 * idx;                   // deleteMax()������ ���� �ð� ����� �ʿ��ϱ� ������ ���� fixHeap�� ���� �ð��� ���õ� ��ɸ� �߰���
		int right = 2 * idx + 1;

		if (left > heap_size) {               // leaf ������� Ȯ�� (���� �ڽ��� index���� ��ü Heap�� ũ�⺸�� ũ�� �������� �����Ƿ� �ش� ���� leaf ��尡 �ȴ�.)
			heap[idx] = K;                    // leaf ����� ��� ���� ������� �ʰ� ����
		}
		else {              // DownHeap ����
			int bigger;     // �ڽ�, ���� �ڽ�, ������ �ڽİ��� Key�� �񱳸� ���� �� ū Key���� ���� ����� index�� �����ϴ� ����

			if (left <= heap_size && heap[left] > heap[idx]) {          // ���� �ڽ��� ���� & ���� �ڽ��� Key���� �� ŭ
				bigger = left;
			}
			else {                                                      // ���� �ڽ��� ���� & �ڽ��� Key���� �� ŭ
				bigger = idx;
			}
			if (right <= heap_size && heap[right] > heap[bigger]) {     // ������ �ڽ��� ���� & ������ �ڽ��� Key���� ���� �ڽ� or �ڽ��� Key ���� ���� ŭ
				bigger = right;
			}

			if (bigger != idx) {                                        // �ڽ��� Key���� ���� ū ���� �ƴ϶�� ū ���� Swap
				swap(idx, bigger);
				totalSec++;                                             // vacant�� ����Ǿ��� ������ totalSec 1 ����
				fixHeap_vacant(bigger, heap[bigger]);
			}
		}
		return;
	}

	void deleteMax() {
		int N = heap_size;     // Heap�� ������ �� ������ Heap�� ũ�⸸ŭ deleteMax�� �����ϱ� ���� ���� ���� ����

		for (int i = 0; i < N; i++) {
			
			if (heap_size == 1) {     // deleteMax()�� �����ϸ鼭 Node�� 1�� ���� �Ǹ� �ڵ������� Heap ������ �����ϹǷ� �����ϵ��� ��
				heap_size--;
				break;
			}
			swap(1, heap_size);
			totalSec++;            // vacant�� ����Ǿ��� ������ totalSec 1 ����

			heap_size--;

			fixHeapFast(1, heap[1], findHeight(1));     // Rightmost ���ҿ� Max ���� ����Ǹ鼭 Heap ������ �������� �ʰ� �ǹǷ� Root ������ Heap ������ ���߱� ����
		}
		cout << totalSec << "\n";
	}

	void fixHeapFast(int vacant, int K, int h) {      // vacant : fixHeapFast�� �����ϸ鼭 vacant�� �Ǵ� index ��, K : heap[vacant] ��, h : vacant�� ��Ʈ�� �ϴ� Heap�� ����
		if (h <= 1) {                                 // ���̰� 1 ������ ���� Heap�� �ִ� ��尡 1~3�� �����ִ� ����
			fixHeap_vacant(vacant, heap[vacant]);     // ������ ���� ������ 0�̹Ƿ� Heap�� ������ �� ����� fixHeap�� ����ϸ� �ȴ�.
		}
		else {
			int hStop = findHeight(vacant) / 2;          // Heap�� ������ ���ݸ�ŭ ����
			int vacStop = promote(hStop, vacant, h);     // �� ū Key���� ���� �ڽİ� Swap�ϴ� promote �Լ� ȣ��

			int vacParent = vacStop / 2;
			
			if (heap[vacParent] <= K) {                  // Heap�� ������ ���ݸ�ŭ ������ �� vacant�� �θ� ���� ���ؼ� �θ� ��尡 �� ���� ���
				swap(vacStop, vacParent);                // Heap ������ ���߱� ���� �ٽ� Swap
				totalSec++;                              // Swap ������ �߻������Ƿ� totalSec 1 ����
				bubbleUpHeap(vacant, vacParent, K);      // Heap ������ ���߱� ���� vacant ������ upHeap�� ����
			}
			else {                                       // Heap�� ������ ���ݸ�ŭ ������ �� vacant�� �θ� ���� ���ؼ� �θ� ��尡 �� ū ��� (���� O)
				fixHeapFast(vacStop, K, hStop);          // ��������� fixHeapFast�� ȣ���Ͽ� �ٽ� vacant�� ��Ʈ�� �ϴ� Subtree�� ���Ͽ� ����
			}
		}
	}

	void bubbleUpHeap(int root, int vacant, int K) {     // root : Root ����� index ��(1), vacant : vacant�� index ��, K : heap[vacant] ��
		if (vacant == root) {     // upHeap�� �����ϴٰ� vacant�� root���� �ö���� upHeap�� �Ϸ�� ���̹Ƿ�
			heap[vacant] = K;     // ���� �״�� ������
		}
		else {                               
			int parent = vacant / 2;     // �θ� ����� index ���

			if (K <= heap[parent]) {     // ���� vacant ��(K)�� �θ� ��庸�� ������ Heap ������ �����ϹǷ�
				heap[vacant] = K;        // ���� �״�� ������
			}
			else {                                 // Heap ������ ������Ű�� ���ϹǷ�
				swap(vacant, parent);              // �θ� ���� vacant �� Swap
				totalSec++;                        // Swap ������ �߻������Ƿ� totalSec 1 ����
				bubbleUpHeap(root, parent, K);     // ���� parent index���� �ٽ� upHeap ���� (Heap ���� ������ ����)
			}
		}
	}

	int promote(int hStop, int vacant, int h) {     // ���� �ڽİ� ������ �ڽ��� Key���� ���ϰ� �� �� ū Key���� ���� �ڽİ� Swap�ϴ� �Լ�
		int left = 2 * vacant;                      // hStop : fixHeapFast�� �����ϴ� ����, vacant : vacant�� index ��, h : vacant index�� Root�� �� Subtree�� ����
		int right = 2 * vacant + 1;

		h = findHeight(vacant);

		int vacStop;

		if (h <= hStop) {         // ��������� ȣ���Ͽ��� �� h�� 1�� ���ҽ�Ű�� ������ �����Ͽ����Ƿ� hStop�� �������� ����
			vacStop = vacant;     
		}
		else if (heap[left] <= heap[right]) {           // ������ �ڽ��� Key���� �� ŭ
			swap(vacant, right);
			totalSec++;                                 // Swap ������ �߻������Ƿ� totalSec 1 ����
			vacStop = promote(hStop, right, h - 1);     // heap[vacant]�� index�� ������ �ڽ��� index�� �ٲ�����Ƿ� ��������� ȣ���ϸ鼭 �ٽ� ����
		}
		else {                                          // ���� �ڽ��� Key���� �� ŭ
			swap(vacant, left);                         
			totalSec++;                                 // Swap ������ �߻������Ƿ� totalSec 1 ����
			vacStop = promote(hStop, left, h - 1);      // heap[vacant]�� index�� ���� �ڽ��� index�� �ٲ�����Ƿ� ��������� ȣ���ϸ鼭 �ٽ� ����
		}
		return vacStop;
	}	
	
	void print() {
		int N = heap_size;

		if (isEmpty()) { }
		else {
			for (int i = 1; i <= N; i++) {     // vector�� index 0�� ������� �ʾ����Ƿ� index 1���� Heap�� ũ�⸸ŭ �ݺ��ؼ� ���� ���
				cout << heap[i] << " ";
			}
		}
		cout << "\n";
	}
};

int main() {
	int T;      // Testcase�� ����
	int N;      // input�� ����
	int input;  // input

	cin >> T;

	while (T--) {
		Heap H;

		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> input;
			H.insert(input);
		}
		H.constructHeap(1);     // Root ������ Heap ������ �����ϱ� ���ؼ� idx�� 1�� �־ ����
		H.print();
		H.deleteMax();
	}
	return 0;
}