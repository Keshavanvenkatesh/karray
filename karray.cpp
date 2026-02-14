#include <iostream>
#include <stdexcept>

class karray {

private:
	int p_max_size;
	int p_size=0;
	int* array;

public:

	karray(int s) {
		std::cout << "karray object is built\n";
		if (s>0){
			p_max_size = s;
			array = new int[p_max_size];

			for (int i = 0; i < p_max_size; i++) {
				*(array + i) = 0;
			}
		}
		else {
			throw std::runtime_error("CANNOT MAKE A ARRAY OF 0 SIZE");
		}
	}

	karray(int a[], int s) {	

		// s is the size of the array that is passed and the class will take that much memory and will write the contents of the argument 
		// to the array class

		std::cout << "karray object is built\n";
		if (a != nullptr && s > 0) {
			p_size = s;
			p_max_size = s;
			array = new int[p_size];

			for (int i = 0; i < p_size; i++) {
				*(array + i) = a[i];      
			}
		}
		else {
			throw std::runtime_error("INVALID ARGUMENTS!");
		}
	}

	karray(const karray& a) {
		array = new int[a.p_max_size];
		p_size = a.p_size;
		p_max_size = a.p_max_size;

		for (int i = 0; i < a.p_size; i++) {
			*(array + i) = *(a.array + i);
		}
	}

	~karray(){
		delete[] array;
	}

	const int* const get_array() const{
		return array;
	}

	void push_back(int element) {
		if (karray::is_full()) {
			throw std::runtime_error("THE ARRAY IS FULL!!");
		}
		else {
			array[p_size] = element;
			p_size += 1;
		}
	}

	void push_back(int* elements, int length) {
		if (length <= 0)
			throw std::runtime_error("Invalid length");

		if (p_size + length > p_max_size)
			throw std::runtime_error("Array full");

		for (int i = 0; i < length; i++) {
			array[p_size + i] = elements[i];
		}

		p_size += length;
	}

	void swap(int a, int b) {
		if (a >= 0 && a < p_size && b >= 0 && b < p_size){

			int temp = *(array + a);
			*(array + a) = *(array + b);
			*(array + b) = temp;

		}
		else {
			throw std::runtime_error("INDEX OUT OF BOUND!!");
		}
		
	}

	void fill(int a,int start,int end) {			// note the index to be filled is to be put here
		if (end <= p_max_size && start>=0) {
			for (int i = start; i <= end; i++) {
				array[i] = a;
			}
			p_size += end - start+1;					
		}
		else {
			throw std::runtime_error("INDEX OUT OF BOUND!!");
		}
	}

	void shrink_to_fit() {
		int* temp = new int[p_size];
		for (int i = 0; i < p_size; i++)
			temp[i] = array[i];

		delete[] array;
		array = temp;
		p_max_size = p_size;
	}

	int pop_back() {
		if (karray::is_empty()) {
			throw std::runtime_error("THE ARRAY IS EMPTY!!");
		}
		else {
			return array[--p_size];
		}
	}

	void show() const{
		std::cout << "[";
		for (int i = 0; i < p_size; i++) {
			std::cout << array[i] << ",";
		}
		std::cout << "]"<<std::endl;
	}

	int size() const{
		return p_size;
	}

	int max_size() const{
		return p_max_size;
	}

	bool is_full() const {
		if (p_size == p_max_size) {
			return true;
		}
		else {
			return false;
		}
	}
	bool is_empty() const {
		if (p_size == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void reverse() {
		if (!karray::is_empty()) {
			for (int i = 0; i < p_size / 2; i++) {
				int temp = array[i];
				array[i] = array[p_size - i - 1];
				array[p_size - i - 1] = temp;
			}
		}
		else {
			throw std::runtime_error("THE ARRAY IS EMPTY!!");
		}
		
	}

	int find(int target) {
		if (!karray::is_empty()) {
			for (int i = 0; i < p_size; i++) {
				if (array[i] == target) {
					return i;
				}
			}
		}
		else {
			throw std::runtime_error("THE ARRAY IS EMPTY!!");
		}
	}

	int count(int target) const{
		if (!karray::is_empty()) {

			int return_count=0;

			for (int i = 0; i < p_size; i++) {
				if (array[i] == target) {
					++return_count;
				}
			}
			return return_count;
		}
		else {
			std::cout<<"THE ARRAY IS EMPTY!!";
			return -1;
		}
	}

	int max() const{
		if (!karray::is_empty()) {

			int temp_max = array[0];

			for (int i = 1; i < p_size; i++) {
				if (array[i]>temp_max) {
					temp_max = array[i];
				}
			}
			return temp_max;
		}
		else {
			std::cout<<"THE ARRAY IS EMPTY!!";
			return -1;
		}
	}

	int min() const{
		if (!karray::is_empty()) {

			int temp_min = array[0];

			for (int i = 1; i < p_size; i++) {
				if (array[i] < temp_min) {
					temp_min = array[i];
				}
			}
			return temp_min;
		}
		else {
			std::cout << "THE ARRAY IS EMPTY!!";
			return -1;
		}
	}

	/*void insert(int index,int element){

		if (index >= 0 && index<p_size) {
			
		}
		else {
			std::cout << "cannot insert into negatice index";
		}
		
	}*/

	void resize(int new_size) {
		if (new_size <= 0)
			throw std::runtime_error("Invalid size");

		int* temp = new int[new_size];

		int copy_size = (new_size < p_size) ? new_size : p_size;

		for (int i = 0; i < copy_size; i++)
			temp[i] = array[i];

		delete[] array;
		array = temp;

		p_size = copy_size;
		p_max_size = new_size;
	}

	// ================================ operator overload ===================================================

	int& operator[](int i) {
		return array[i];
	}
};
