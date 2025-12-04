/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/


#include<bits/stdc++.h>

using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using namespace std;

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

//三数取中
/*

int retrieveMid(int *a, int l, int r) {
	int mid = (l + r) / 2;
	if (a[l] > a[mid])std::swap(a[l], a[mid]);
	if (a[r] < a[mid])std::swap(a[r], a[mid]);
	if (a[mid] < a[l])std::swap(a[l], a[mid]);
	return mid;
}

void quickSort(int *a, int l, int r) {
	if (l >= r)return;
	int mid = retrieveMid(a, l, r);
	std::swap(a[mid], a[l]);
	int low = l, high = r; int pivot = a[l];
	while (low < high) {
		while (high > low and a[high] >= pivot)high--;
		a[low] = a[high];
		while (low < high and a[low] <= pivot)low++;
		a[high] = a[low];
	}
	a[low] = pivot;
	quickSort(a, l, low - 1);
	quickSort(a, low + 1, r);
}
*/

void quickSort(int *a, int l, int r) {
	if (l >= r)return;
	int mid = (rand() % (r - l + 1)) + l;
	std::swap(a[mid], a[l]); int pivot = a[l];
	int lt = l, gt = r, i = lt + 1;
	while (i <= gt) {
		if (a[i] < pivot) {
			std::swap(a[i], a[lt]);
			i++; lt++;
		} else if (a[i] > pivot) {
			std::swap(a[i], a[gt]);
			gt--;
		} else {
			i++;
		}
	}
	quickSort(a, l, lt - 1);
	quickSort(a, gt + 1, r);
}




int a[1000005];

int main() {
	int n; std::cin >> n;
	for (int i = 1; i <= n; i++)std::cin >> a[i];
	quickSort(a, 1, n);
	for (int i = 1; i <= n; i++)std::cout << a[i] << " \n"[i == n];
	return 0;
}