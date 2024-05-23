#include <iostream>
#include <array>
#include <limits>
#include <climits>

class SubInfo {
public:
	SubInfo(int r1, int r2, int s) : rangeStart{r1}, rangeEnd{r2}, sum{s} {}
	int getRangeStart() { return rangeStart; } 
	int getRangeEnd() { return rangeEnd; } 
	int getSum() { return sum; }
private:
	int rangeStart;
	int rangeEnd;
	int sum;
};

template <typename Container>
SubInfo findMaxSubSum_n(const Container& container, int start, int end) {
	if (start > end) return SubInfo{-1, -1, 0};
    	auto cur_sum = typename Container::value_type{};
    	auto max_sum = std::numeric_limits<typename Container::value_type>::lowest();
	int leftIndex = start;
	int rightIndex = start;
    	int tempLeft = start;
    	
	for (int i = start; i <= end; ++i) {
		cur_sum += container[i];
		if (cur_sum > max_sum) {
			max_sum = cur_sum;
            		leftIndex = tempLeft;
            		rightIndex = i;
		}
		if (cur_sum < 0) {
			cur_sum = 0;
			tempLeft = i + 1;
		}
	}	
	
    	return SubInfo{leftIndex, rightIndex, max_sum};
}

template <typename Container>
SubInfo findMaxSubSum_nn(const Container& container, int start, int end) {
	if (start > end) return SubInfo{-1, -1, 0}; 
	int leftIndex = -1;
	int rightIndex = -1;
	int sum = INT_MIN;
	for (int i = start; i < end; ++i) {
		int tmpSum = 0;
		for (int j = i; j < end; ++j) {
			tmpSum += container[j];
			if (sum < tmpSum) {
				sum = tmpSum;
				leftIndex = i;
				rightIndex = j;
			}
		}
	}
	return SubInfo{leftIndex, rightIndex, sum};
}


template <typename Container>
SubInfo findMaxCrossSubSum(const Container& container, int start, int mid, int end) {
	int leftSum = INT_MIN;
	int mostLeftIndex = -1;
	int sum = 0;
	for (int i = mid; i >= start; --i) {
		sum += container[i];
		if (leftSum < sum) {
			leftSum = sum;
			mostLeftIndex = i;
		}
	}
	
	int rightSum = INT_MIN;
	int mostRightIndex = -1;
	sum = 0;
	for (int i = mid + 1; i <= end; ++i) {
		sum += container[i];
		if (rightSum < sum) {
			rightSum = sum;
			mostRightIndex = i;
		}
	}
	
	return SubInfo{mostLeftIndex, mostRightIndex, leftSum + rightSum};
}

template <typename Container>
SubInfo findMaxSubSum_nlgn(const Container& container, int start, int end) {
	if (start > end) return SubInfo{-1, -1, 0}; 
	if (start == end) { return SubInfo(start, end, container[start]); }
	else {
		int mid = start + ((end - start) / 2);
		SubInfo left = findMaxSubSum_nlgn(container, start, mid);
		SubInfo right = findMaxSubSum_nlgn(container, mid + 1, end);
		SubInfo cross = findMaxCrossSubSum(container,start,mid,end);
		
		if (left.getSum() >= right.getSum() && left.getSum() >= cross.getSum()) {
			return left;
		} else if (right.getSum() >= left.getSum() && right.getSum() >= cross.getSum()) { 
			return right;
		} else {
			return cross;
		}
	}
}
int main() {
	std::array arr {2, -4, 1, 3, -1, 2, -5, 2};
	SubInfo result = findMaxSubSum_nlgn(arr, 0, arr.size() - 1);
	if (result.getRangeStart() == -1 && result.getRangeEnd() == -1) {
        	std::cout << "Array is empty or no valid subarray found.\n";
    	}
	else {
		std::cout << "Max subarray sum: " << result.getSum() 
		<< ", starts at index " << result.getRangeStart() 
		<< ", ends at index " << result.getRangeEnd() << std::endl;
	}
	
	result = findMaxSubSum_nn(arr, 0, arr.size() - 1);
	if (result.getRangeStart() == -1 && result.getRangeEnd() == -1) {
        	std::cout << "Array is empty or no valid subarray found.\n";
    	}
	else {
		std::cout << "Max subarray sum: " << result.getSum() 
		<< ", starts at index " << result.getRangeStart() 
		<< ", ends at index " << result.getRangeEnd() << std::endl;
	}
	
	result = findMaxSubSum_n(arr, 0, arr.size() - 1);
	if (result.getRangeStart() == -1 && result.getRangeEnd() == -1) {
        	std::cout << "Array is empty or no valid subarray found.\n";
    	}
	else {
		std::cout << "Max subarray sum: " << result.getSum() 
		<< ", starts at index " << result.getRangeStart() 
		<< ", ends at index " << result.getRangeEnd() << std::endl;
	}
}
