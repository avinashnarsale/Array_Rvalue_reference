#ifndef CS540_ARRAY_HPP
#define CS540_ARRAY_HPP

#include <chrono>
#include <utility>
#include <initializer_list>

namespace cs540 {

class Array
{
	private: 
		MyInt *myArray;
		size_t arraySize;

	public:
	Array() : myArray(nullptr), arraySize(0) {}
	
	Array(std::initializer_list<int> init) {
		arraySize=init.size();
		int count=0;
		myArray=new MyInt[arraySize];
		for(auto itList = init.begin();itList != init.end();itList++){
			myArray[count++]=*itList;
		}
	}
	
	~Array(){
		delete [] myArray;
		myArray=nullptr;
	}
	
	Array(Array &array){
		arraySize=array.arraySize;
		myArray=new MyInt[array.arraySize];
		for(int i=0;i<arraySize;i++){
			myArray[i]=array.myArray[i];
		}
	}

	Array(Array &&array) : myArray(array.myArray), arraySize(array.arraySize){
		array.myArray=nullptr;
		array.arraySize=0;
	}
	
	Array &operator=(const Array &array){
		if(this!=&array){
			delete [] myArray;
			arraySize=array.arraySize;
			myArray=new MyInt[array.arraySize];
			for(int i=0;i<arraySize;i++){
				myArray[i]=array.myArray[i];
			}
			return *this;
		}
	}
	
	Array &operator=(Array &&array){
		if (this != &array){  
			delete [] myArray;
			arraySize=array.arraySize;
			myArray=array.myArray;
			array.myArray=nullptr;
			array.arraySize=0;
			return *this;
		} 
	}
	
	friend std::ostream &operator<<(std::ostream &os, const Array &ma) {
		int i=0;
		while(i<ma.arraySize-1){
		    os << ma.myArray[i] << ", " ;
			i++;
		}
		os << ma.myArray[i];
		return os;
	}
	
	static void move_performance_test(){
		fprintf(stderr,"Output - move_performance_test(): \n");

		using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
		using Milli = std::chrono::duration<double, std::ratio<1,1000>>;
		using namespace std::chrono;

		TimePoint start = system_clock::now();
		cs540::Array check1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200};
		TimePoint end = system_clock::now();
		Milli elapsed1 = end - start;
		//std::cout << "Inserting 200 records in " << elapsed1.count() << " ms" << std::endl;
		
		TimePoint start2 = system_clock::now();
		cs540::Array check2{check1};
		TimePoint end2 = system_clock::now();
		Milli elapsed2 = end2 - start2;
		fprintf(stderr, "Copy ctor - 200 records in %fl ms\n",elapsed2.count());

		TimePoint start1 = system_clock::now();
		cs540::Array check3{std::move(check2)};
		TimePoint end1 = system_clock::now();
		Milli elapsed3 = end1 - start1;
		fprintf(stderr, "Move ctor - 200 records in %fl ms\n",elapsed3.count());
		
		TimePoint start5 = system_clock::now();
		cs540::Array check4{1};
		check4 = check1;
		TimePoint end5 = system_clock::now();
		Milli elapsed4 = end5 - start5;
		fprintf(stderr, "Copy assignment - 200 records in %fl ms\n",elapsed4.count());

		TimePoint start4 = system_clock::now();
		cs540::Array check5{1};
		check5 = std::move(check4);
		TimePoint end4 = system_clock::now();
		Milli elapsed5 = end4 - start4;
		fprintf(stderr, "Move assignment - 200 records in %fl ms\n",elapsed5.count());
	}
};

}//namesapce

#endif