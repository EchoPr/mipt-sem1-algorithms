#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int mbin_search(vector<int>& a, int left, int right,  int k) {
	int l = left, r = right;
	int mid;
	

	while (l < r) {
		mid = l + (r - l) / 2;

		if (a[mid] == k)
			return mid;

		if (a[mid] < k)
			l = mid + 1;
		else
			r = mid - 1;
	}

	return a[r] == k ? r : -1;
}

int cool_bin_search(vector<int>& a, int key) {
	int n = a.size();
	int step = 1;
	
	if (a[0] == key)
		return 0;

	// no more than log2(k)
	while (step <= n && a[step - 1] < key)
		step *= 2;

	return mbin_search(a, step / 2 - 1, min(step, n) - 1, key);

}

/*
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
*/

int main() {
	int n;
	cin >> n;
	vector<int> a(n);

	for (int i = 0; i < n; i++)
		cin >> a[i];

	int k;
	cin >> k;
	int res = cool_bin_search(a, k);

	cout << res << endl;
}