#include <iostream>
#include <vector>
#include <cmath>         // Heap의 높이는 log2(n)에 bound 되기 때문에 log2 function을 이용하기 위해 사용
using namespace std;     

class Heap {
private:
	vector<int> heap;     // 배열 기반의 Heap을 구현하기 위하여 vector 사용
	int heap_size;        // Node의 총 개수 및 마지막 Node의 index 확인
	int totalSec;         // Algorithm에서 deleteMax()의 수행 시간을 분석하기 위한 변수 선언

public:
	Heap() {                    // Heap 초기화
		heap.push_back(-1);     // index 0에 -1(Dummy Value) 삽입
		this->heap_size = 0;    
		this->totalSec = 0;
	}

	bool isEmpty() {                             // Heap이 비어 있는지 확인하는 함수
		if (heap_size == 0) { return true; }
		else { return false; }
	}

	void insert(int data) {       // 생성된 Heap의 vector에 원소를 삽입 (push_back 이용)
		heap_size++;
		heap.push_back(data);     
	}

	void swap(int idx1, int idx2) {     // upheap과 downheap을 통해서 원소를 자주 바꾸게 되므로 두 원소를 swap하는 함수 선언
		int tmp = heap[idx1];
		heap[idx1] = heap[idx2];
		heap[idx2] = tmp;
	}

	int findHeight(int idx) {                                 // 한 Node의 높이를 찾기위한 함수
		return floor(log2(heap_size)) - floor(log2(idx));     // 전체 Heap의 높이에서 해당 Node의 높이를 빼도록 구현함
	}

	void constructHeap(int idx) {        // 입력된 Heap에 대하여 Heap 구조를 맞춰주기 위한 함수 (Max-Heap)
		int left = 2 * idx;
		int right = 2 * idx + 1;

		int height = findHeight(idx);

		int K;

		if (height > 0) {                // fixHeap 함수가 자식들과의 비교를 하는 함수이므로 해당 노드가 leaf Node이면 수행하지 않음
			constructHeap(left);         // main 함수에서 idx 값에 1을 대입하면서 Root 노드의 왼쪽 Subtree부터 Heap 구조를 만족하도록 함
			constructHeap(right);        // Root 노드의 왼쪽 Subtree의 구조가 만족한 이후, 오른쪽 Subtree를 만족하도록 함

			K = heap[idx];

			fixHeap(idx, K);             // Heap 구조를 만족시키기 위해서 fixHeap(int idx, int K) 함수 호출
		}
		return;
	}
	
	void fixHeap(int idx, int K) {     // idx : fixHeap을 진행하는 index 값, K : heap[idx] 값 (leaf가 아닌 Node의 Key 값)
		int left = 2 * idx;
		int right = 2 * idx + 1;

		if (left > heap_size) {     // leaf 노드인지 확인 (왼쪽 자식의 index값이 전체 Heap의 크기보다 크면 존재하지 않으므로 해당 노드는 leaf 노드가 된다.) 
			heap[idx] = K;          // leaf 노드인 경우 값이 변경되지 않고 종료
		}
		else {              // DownHeap 과정
			int bigger;     // 자신, 왼쪽 자식, 오른쪽 자식과의 Key값 비교를 통해 더 큰 Key값을 가진 노드의 index를 저장하는 변수

			if (left <= heap_size && heap[left] > heap[idx]) {          // 왼쪽 자식이 존재 & 왼쪽 자식의 Key값이 더 큼
				bigger = left;
			}
			else {                                                      // 왼쪽 자식이 존재 & 자신의 Key값이 더 큼
				bigger = idx;
			}
			if (right <= heap_size && heap[right] > heap[bigger]) {     // 오른쪽 자식이 존재 & 오른쪽 자식의 Key값이 왼쪽 자식 or 자신의 Key 값이 보다 큼
				bigger = right;
			}

			if (bigger != idx) {                                        // 자신의 Key값이 제일 큰 값이 아니라면 큰 값과 Swap
				swap(idx, bigger);
				fixHeap(bigger, heap[bigger]);
			}
		}
		return;
	}

	void fixHeap_vacant(int idx, int K) {     // fixHeapFast 과정에서 Heap의 height가 1 이하인 경우(원소가 3개 이하) 기존 fixHeap을 사용하기 위함
		int left = 2 * idx;                   // deleteMax()에서는 수행 시간 계산이 필요하기 때문에 기존 fixHeap에 수행 시간과 관련된 기능만 추가됨
		int right = 2 * idx + 1;

		if (left > heap_size) {               // leaf 노드인지 확인 (왼쪽 자식의 index값이 전체 Heap의 크기보다 크면 존재하지 않으므로 해당 노드는 leaf 노드가 된다.)
			heap[idx] = K;                    // leaf 노드인 경우 값이 변경되지 않고 종료
		}
		else {              // DownHeap 과정
			int bigger;     // 자신, 왼쪽 자식, 오른쪽 자식과의 Key값 비교를 통해 더 큰 Key값을 가진 노드의 index를 저장하는 변수

			if (left <= heap_size && heap[left] > heap[idx]) {          // 왼쪽 자식이 존재 & 왼쪽 자식의 Key값이 더 큼
				bigger = left;
			}
			else {                                                      // 왼쪽 자식이 존재 & 자신의 Key값이 더 큼
				bigger = idx;
			}
			if (right <= heap_size && heap[right] > heap[bigger]) {     // 오른쪽 자식이 존재 & 오른쪽 자식의 Key값이 왼쪽 자식 or 자신의 Key 값이 보다 큼
				bigger = right;
			}

			if (bigger != idx) {                                        // 자신의 Key값이 제일 큰 값이 아니라면 큰 값과 Swap
				swap(idx, bigger);
				totalSec++;                                             // vacant가 변경되었기 때문에 totalSec 1 증가
				fixHeap_vacant(bigger, heap[bigger]);
			}
		}
		return;
	}

	void deleteMax() {
		int N = heap_size;     // Heap을 생성할 때 구해진 Heap의 크기만큼 deleteMax를 수행하기 위해 따로 변수 선언

		for (int i = 0; i < N; i++) {
			
			if (heap_size == 1) {     // deleteMax()를 수행하면서 Node가 1개 남게 되면 자동적으로 Heap 구조를 만족하므로 종료하도록 함
				heap_size--;
				break;
			}
			swap(1, heap_size);
			totalSec++;            // vacant가 변경되었기 때문에 totalSec 1 증가

			heap_size--;

			fixHeapFast(1, heap[1], findHeight(1));     // Rightmost 원소와 Max 값이 변경되면서 Heap 구조를 만족하지 않게 되므로 Root 노드부터 Heap 구조를 맞추기 위함
		}
		cout << totalSec << "\n";
	}

	void fixHeapFast(int vacant, int K, int h) {      // vacant : fixHeapFast를 진행하면서 vacant가 되는 index 값, K : heap[vacant] 값, h : vacant를 루트로 하는 Heap의 높이
		if (h <= 1) {                                 // 높이가 1 이하인 경우는 Heap에 있는 노드가 1~3개 남아있는 경우로
			fixHeap_vacant(vacant, heap[vacant]);     // 높이의 반은 무조건 0이므로 Heap을 생성할 때 사용한 fixHeap을 사용하면 된다.
		}
		else {
			int hStop = findHeight(vacant) / 2;          // Heap의 높이의 절반만큼 진행
			int vacStop = promote(hStop, vacant, h);     // 더 큰 Key값을 가진 자식과 Swap하는 promote 함수 호출

			int vacParent = vacStop / 2;
			
			if (heap[vacParent] <= K) {                  // Heap의 높이의 절반만큼 진행한 후 vacant의 부모 노드와 비교해서 부모 노드가 더 작은 경우
				swap(vacStop, vacParent);                // Heap 구조를 맞추기 위해 다시 Swap
				totalSec++;                              // Swap 연산이 발생했으므로 totalSec 1 증가
				bubbleUpHeap(vacant, vacParent, K);      // Heap 구조를 맞추기 위해 vacant 값으로 upHeap을 수행
			}
			else {                                       // Heap의 높이의 절반만큼 진행한 후 vacant의 부모 노드와 비교해서 부모 노드가 더 큰 경우 (구조 O)
				fixHeapFast(vacStop, K, hStop);          // 재귀적으로 fixHeapFast를 호출하여 다시 vacant를 루트로 하는 Subtree에 대하여 수행
			}
		}
	}

	void bubbleUpHeap(int root, int vacant, int K) {     // root : Root 노드의 index 값(1), vacant : vacant의 index 값, K : heap[vacant] 값
		if (vacant == root) {     // upHeap을 진행하다가 vacant가 root까지 올라오면 upHeap이 완료된 것이므로
			heap[vacant] = K;     // 값을 그대로 저장함
		}
		else {                               
			int parent = vacant / 2;     // 부모 노드의 index 계산

			if (K <= heap[parent]) {     // 기존 vacant 값(K)이 부모 노드보다 작으면 Heap 구조를 만족하므로
				heap[vacant] = K;        // 값을 그대로 저장함
			}
			else {                                 // Heap 구조를 만족시키지 못하므로
				swap(vacant, parent);              // 부모 값과 vacant 값 Swap
				totalSec++;                        // Swap 연산이 발생했으므로 totalSec 1 증가
				bubbleUpHeap(root, parent, K);     // 기존 parent index부터 다시 upHeap 진행 (Heap 구조 만족을 위함)
			}
		}
	}

	int promote(int hStop, int vacant, int h) {     // 왼쪽 자식과 오른쪽 자식의 Key값을 비교하고 둘 중 큰 Key값을 가진 자식과 Swap하는 함수
		int left = 2 * vacant;                      // hStop : fixHeapFast를 수행하는 높이, vacant : vacant의 index 값, h : vacant index를 Root로 한 Subtree의 높이
		int right = 2 * vacant + 1;

		h = findHeight(vacant);

		int vacStop;

		if (h <= hStop) {         // 재귀적으로 호출하였을 때 h를 1씩 감소시키는 연산을 진행하였으므로 hStop과 같아지면 멈춤
			vacStop = vacant;     
		}
		else if (heap[left] <= heap[right]) {           // 오른쪽 자식의 Key값이 더 큼
			swap(vacant, right);
			totalSec++;                                 // Swap 연산이 발생했으므로 totalSec 1 증가
			vacStop = promote(hStop, right, h - 1);     // heap[vacant]의 index가 오른쪽 자식의 index로 바뀌었으므로 재귀적으로 호출하면서 다시 수행
		}
		else {                                          // 왼쪽 자식의 Key값이 더 큼
			swap(vacant, left);                         
			totalSec++;                                 // Swap 연산이 발생했으므로 totalSec 1 증가
			vacStop = promote(hStop, left, h - 1);      // heap[vacant]의 index가 왼쪽 자식의 index로 바뀌었으므로 재귀적으로 호출하면서 다시 수행
		}
		return vacStop;
	}	
	
	void print() {
		int N = heap_size;

		if (isEmpty()) { }
		else {
			for (int i = 1; i <= N; i++) {     // vector의 index 0을 사용하지 않았으므로 index 1부터 Heap의 크기만큼 반복해서 값을 출력
				cout << heap[i] << " ";
			}
		}
		cout << "\n";
	}
};

int main() {
	int T;      // Testcase의 개수
	int N;      // input의 개수
	int input;  // input

	cin >> T;

	while (T--) {
		Heap H;

		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> input;
			H.insert(input);
		}
		H.constructHeap(1);     // Root 노드부터 Heap 구조를 만족하기 위해서 idx에 1을 넣어서 시작
		H.print();
		H.deleteMax();
	}
	return 0;
}