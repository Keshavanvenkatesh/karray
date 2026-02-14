// #include <iostream>

// class person{
// public:
//     std::string name;
//     int age;

//     static int something;

//     person(std::string name1, int age1){
//         name=name1;
//         age=age1;
//     }

//     ~person(){
//         std::cout<<"this is deconstructor";
//     }

//     static void show_name(){
//         std::cout<<"this is a static function"<<'\n';
//     }
// };

// int person::something;

// void another(person& p){
//     std::cout<<p.name<<'\n';
//     p.age+=1;

//     std::cout<<p.age<<'\n';

// }

// int main(){

//     person keshavan=person("keshavan",18);

//     std::cout<<keshavan.name<<" "<<keshavan.age<<' '<<'\n';
//     person::show_name();

//     person::something = 420;
//     std::cout<<person::something;

//     return 0;
// }


// #include <iostream>

// void arrayprint(int a[],int s);

// int main(){

//     const int s = 5;
//     int a[s]={1,2,3,4,5};

//     arrayprint(a,s);

//     return 0;
// }

// void arrayprint(int a[],int s){
//     for(int i=0;i<s;i++){
//         std::cout<<a[i]<<std::endl;
//         // std::cout<<*(a+i)<<std::endl;
//     }
// }


// #include <iostream>

// void show_matrix(int size,int* matrix[]);

// int main(){

//     const int columns=5;
//     int mat1[]={1,3,4};
//     show_matrix(3,mat1);

//     return 0;
// }

// void show_matrix(int size,int* matrix[]){
//     for(int i =0 ;i<size;i++){
//         std::cout<<*(matrix+i)<<" ";
//     }
// }



#include <iostream>
#include <stdexcept>

class karray {

private:
	int p_max_size;
	int p_size=0;
	int* array;

	bool is_full() const {
		if (p_size == p_max_size) {
			return true;
		}
		else {
			return false;
		}
	}

public:
	// consturctor with only size <size>

	karray(int s) {
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
	// consturctor with only both array and size <array, size>

	karray(int a[], int s) {	

		// s is the size of the array that is passed and the class will take that much memory and will write the contents of the argument 
		// to the array class

		if (a != nullptr && s > 0) {
			p_size = s;
			p_max_size = s;
			array = new int[p_size];

			for (int i = 0; i < p_size; i++) {
				*(array + i) = a[i];       // changed from *(a+i) to a[i] if a array decays to a pointer when given to a function then what is the difference between deferenceing and accessing elemtnt by [] operator
			}
		}
		else {
			throw std::runtime_error("INVALID ARGUMENTS!");
		}
	}

	karray(karray& a) {
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

	bool is_empty() {
		if (p_size == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void push_back(int element) {
		if (karray::is_full()) {
			throw std::runtime_error("THE ARRAY IS FULL!!");
		}
		else {
			*(array + p_size-1) = element;
			p_size += 1;
		}
	}

	void push_back(int* elements,int length) {
		if (length <= 0) {
			throw std::runtime_error("LENGTH CANNOT BE NEGATIVE");
		}

		if (p_max_size - (length + p_size) >= 0) {
			for (int i = p_size; i < length; i++) {
				*(array + i) = *(elements + i);
			}
			p_size += length;
		}
		else {
			throw std::runtime_error("THE ARRAY IS FULL!!");
		}
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

	void fill(int a,int l) {
		if (l <= (p_max_size - p_size)) {
			for (int i = 0; i < l; i++) {
				*(array + i) = a;
			}
		}
		else {
			throw std::runtime_error("INDEX OUT OF BOUND!!");
		}
	}

	void shrink_to_fit() {
		if (p_size < p_max_size) {
			p_max_size = p_size;
		}
	}

	int pop_back() {
		if (karray::is_empty()) {
			throw std::runtime_error("THE ARRAY IS EMPTY!!");
		}
		else {
			int return_temp = *(array + p_size);
			int temp=array[p_size];

			for (int i = 1; i < (p_size - 1); i++) {
				*(array + (i - 1)) = *(array + i);
			}
			p_size -= 1;
			return temp;
		}
	}

	void show() {
		std::cout << "[";
		for (int i = 0; i < p_size; i++) {
			std::cout << *(array + i) << ",";
		}
		std::cout << "]"<<std::endl;
	}

	int size() {
		return p_size;
	}

	int max_size() {
		return p_max_size;
	}
};

int main() {
	int b[] = { 1,2,3 };
	karray a = karray(b, 3);
	karray c = karray(1);

	// c.push_back(67);
	c.show();

	// a.push_back(677);
	a.show();
	a.pop_back();

	a.shrink_to_fit();
	a.push_back(69);
	a.show();

	std::cout <<"size of a is"<< a.size()<<"\n";
	std::cout << "size of c is" << c.size()<<" "<<c.max_size();

	return 0;
}