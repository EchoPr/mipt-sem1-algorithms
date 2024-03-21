#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Heap {
	vector<int> data;
	int size;


	Heap(int size_) {
		size = 0;
		data.resize(size_);
	}

	Heap(vector<int> arr, int size_) {
		data = arr;
		make_heap(data.begin(), data.end(), std::greater<>{});

		size = size_;
	}

	void push(int v) {
		size++;
		data[size - 1] = v;

		
		sift_up(size - 1);
	}

	int pop() {
		int res = data[0];
		data[0] = data[size - 1];

		size--;
		sift_down(0);

		return res;
	}

	void sift_down(int i) {

		while (2 * i + 1 < size) {
			int l = 2 * i + 1;
			int r = 2 * i + 2;
			int tmp = l;

			if ((r < size) && (data[r] < data[l]))
				tmp = r;
			if (data[i] <= data[tmp])
				break;

			swap(data[i], data[tmp]);
			i = tmp;
		}
	}

	void sift_up(int i) {
		while (data[i] < data[(i - 1) / 2]) {
			swap(data[i], data[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	int top() {
		return data[0];
	}

};


int main() {
	int n;
	cin >> n;
	vector<int> a(n);

	for (int i = 0; i < n; i++)
		cin >> a[i];

	/*Heap h();
	for (int i = 0; i < n; i++)
		cout << h.pop() << " ";*/

	int k;
	cin >> k;
	
	Heap h(n);
	Heap del(n);
	

	for (int i = 0; i < k; i++) {
		h.push(a[i]);
	}


	cout << h.top() << " ";
	int shift = 0;

	while (k + shift < n) {
		del.push(a[shift]);
		h.push(a[k + shift]);
		
		while (h.top() == del.top()) {
			h.pop();
			del.pop();
		}

		cout << h.top() << ' ';
		shift++;
	}
}

/*
10
12 4 3 10 91 1 8 23 41 0
3
*/
