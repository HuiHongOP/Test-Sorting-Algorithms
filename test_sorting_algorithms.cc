// Homework 5 (csci335)
// Testing Sorting Algorithms
// Huihong Zheng
//This .cc file will run InsertionSort, HeapSort, MergeSort, and QuickSort (Medianof3 , first element selection , middle element selection) to see the difference between
#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm> 
#include <functional>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

/*
void TestingTiming() 
{
  cout << "Testing Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}*/


// Generates and returns random vector of size @size_of_vector.
//this function will generate random numbers with the size of size_of_vector
// Return the vector of integers stored inside
vector<int> GenerateRandomVector(size_t size_of_vector) 
{
  vector<int> storage ;
  int counterSize = 0; 
  while( size_of_vector> counterSize) 
  {
      storage.push_back(rand()); 
      counterSize++;
  }
  return storage;
}


// Generate and returns sorted vector of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
//Starts from 1 ( if small to larger order)
//Starts from given size to smaller (if greater to smaller order)
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) 
{
  vector<int> SortedVector;
  int SizeVector= size_of_vector;
  if(smaller_to_larger) 
  {
  	for(unsigned int x = 1 ; SizeVector + 1 > x ; ++x)
  	{
  		SortedVector.push_back(x); 
  	}
  }
  else
  {
  	for( unsigned int a = SizeVector ; a > 0; --a)
  	{
  		SortedVector.push_back(a);
  	}
  }
  return SortedVector;
}

// Verifies that a vector is sorted given a comparator
//@return true if the vector is sorted in a given comparator order
//else false
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) 
{
	int StorageSize = input.size(); 
	if(StorageSize != 0 || StorageSize > 1)
	{
		int x = 0;
		while(input.size()-1 > x) 
		{
			if(less_than(input[x+1],input[x])) 
			{
				return false; 
			}
			++x; 
		}	
	}
	else if (StorageSize == 1) 
	{
		return true; 
	}
	return true; 
}

// Computes duration given a start time and a stop time in nano seconds
//Function will print the Runtime in nano seconds
//It's an auto function
//it could be void/string/ int and etc
auto ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) 
{
  cout <<"Runtime: <"<< chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "> ns" << endl;
}



// Wrapper function to test the different sorting algorithms
int sortTestingWrapper(int argc, char **argv) 
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") 
  {
    cout << "Invalid input type" << endl;
    return 0;
  }
  if (input_size <= 0) 
  {
    cout << "Invalid size" << endl;
    return 0;
  }
  if (comparison_type != "less" && comparison_type != "greater") 
  {
    cout << "Invalid comparison type" << endl;
    return 0;
  }
  
  // This block of code to be removed for your final submission.
  // TestingTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " " << comparison_type <<endl;
  vector<int> input_vector;
  
  cout<<endl;
  // Generate random vector
  // @input_vector: stores the random generated vector( not sorted)
  if (input_type == "random") 
  {
    input_vector = GenerateRandomVector(input_size);
  }
  //Generate sorted vector (from small to greater)
  //@input_vector: stores the sorted vector
  else if(input_type == "sorted_small_to_large" ) 
  {
  	   input_vector = GenerateSortedVector(input_size,true);
  }
  //Generate sorted vector (large to small)
  //@input_vector: stores the sorted vector
  else if(input_type =="sorted_large_to_small") 
  {
           input_vector = GenerateSortedVector(input_size,false); 
  }

  //This one is slightly different but same result as the previous functions
  //@generate sorted vector
  //@input_vector: stores the sorted vector
  else if (input_type =="sorted")//sorted is being use as input type and using the Comparision_type Comparator
  {
  	
  	//****************  This is sorted using less<int>{} comparator ************************************************************

  	if(comparison_type == "less" ) // if the sorted is using less 
  	{
  		input_vector = GenerateSortedVector(input_size,true); 
  	}
  	
  	//****************  This is sorted using greater<int{} comparator ************************************************************
    //Generate sorted vector (large to small)
    //@input_vector: stores the sorted vector
  	else 
  	{
  		input_vector = GenerateSortedVector(input_size,false); 
  	}		  
  } 

  //Comparator is less<int>{}

  if(comparison_type  == "less") 
  {

	
       //The reason why delcare a new int type vector to Store the input_vector because once input_vector is being used
       // the Input_vector is already Sorted in that partically sort way and might causes different errors araise as being used be other Sort algorithms.
       
       
       //***********************************This is HeapSort**********************************
       //declare a new int type vector (InputForHeap) to store the input_vector
       vector<int> InputForHeap = input_vector;
       
       //declare const auto heapBegin to store the time it started the Heapsort
       const auto heapBegin = chrono::high_resolution_clock::now();
       
       //Calls the HeapSort and pass Input vector, and less of int 
       //It Run the Function and sort it by HeapSort with small to larger order
       HeapSort(InputForHeap,less<int>{});
       
       //declare const auto HeapEnd to store the end time after HeapSorted is done with the Input Vector small to larger integers
       const auto heapEnd = chrono::high_resolution_clock::now();

       cout<<"HeapSort"<<endl<<endl;
       
       //Pass the Start time and End time stored variables into the Compute Duration function
       //It will display out the run time in nano seconds and expected outputs
       ComputeDuration(heapBegin,heapEnd);
       
       //It will calls on the Function VerifyOrder with two parameter passed by (inputvector) being sorted by HeapSort and in a less Order
       //Prints out the output and return 1 for true and 0 for false 
       cout<<"Verified: "<<VerifyOrder(InputForHeap,less<int>{})<<endl<<endl;
       
       
       
       //*******************************This is MergeSort*********************************
       //delcare new int type vector ( InputForMerge) that stores the input_vector
       vector<int>InputForMerge= input_vector;
       
       //declare const auto For MergeSortBegin that will store the time now ( time that started before doing the mergesort)
       const auto MergeSortBegin = chrono::high_resolution_clock::now();
       
       //Calls in the MergeSort function and pass the two parameter ( Input of the vector and less ( from small to large sort))
       MergeSort(InputForMerge,less<int>{});
       
       //declare const auto variable to store the end of the time after MergeSort is done
       const auto MergeSortEnd = chrono::high_resolution_clock::now();
       
       //print out the output and skip two lines
       cout<<"MergeSort"<<endl<<endl;
       
       //Calls in the ComputeDuration with 2 parameter and pass the time with begin and end time
       //It will display the runtime in nano seconds of how long it took
       ComputeDuration(MergeSortBegin,MergeSortEnd);
       
       //prints out the output and check to see if the MergeSort sorted the input vector in a small to larger order
       //return 1 if it's true and return 0 false if not
       cout<<"Verified: "<<VerifyOrder(InputForMerge,less<int>{})<<endl<<endl;
       
       
       //**********************THIS IS QUICKSORT***********************************
       //declare int type vector InputForQuick1 to store the variables of input_vector
       vector<int> InputForQuick1 = input_vector;
       
       //declare const auto QuickSortBegin to store the current time Before starting the QuickSort
       const auto QuickSortBegin = chrono::high_resolution_clock::now();
       
       //Calls in the QuickSort and pass the InputForQuick1 vector and bool less function as int type
       QuickSort(InputForQuick1 ,less<int>{});
       
       //declare const auto QuickSortEnd that will store the end it ended on after the QuickSort
       const auto QuickSortEnd = chrono::high_resolution_clock::now();
       
       cout<<"QuickSort"<<endl<<endl;
       
       //Calls in the ComputeDuration and pass in the QuickSortedBegin(Time that Begin) and the time that the sort Ended
       //prints out the Runtime for QuickSort
       ComputeDuration(QuickSortBegin,QuickSortEnd );
       
       //prints output and calls in the function to verify The InputForQuick1 and bool less function of int type 
       //It will return true if the vector is in sorted order of small to large
       cout<<"Verified: "<<VerifyOrder(InputForQuick1,less<int>{})<<endl<<endl;
       
       
       
       
       //**************************************This is the MedianOfThree, First, and Middle Element for QuickSort*****************
       
       cout<<"Testing Quicksort Pivot Implementations" <<endl<<endl;
       
       
       


       
       //*****************************This is Median of Three ************************************************************************
       
       
       //declare int type vector InPutForQuickMedian to store the input_vector
       vector<int> InputForQuickMedian = input_vector;
       
       //declare const auto QuickSortMedianBegin to store the  current time it started before QuickSort
       const auto QuickSortMedianBegin = chrono::high_resolution_clock::now();
       
       //Calls in the QuickSort Function and pass In the QuickSortMedian and less int type 
       QuickSort(InputForQuickMedian ,less<int>{});
       
       //declare const auto QuickSortMedianEnd to store the current time after the QuickSort Ended
       const auto QuickSortMedianEnd = chrono::high_resolution_clock::now();
       
       //prints out the type of sort and skip 2 lines 
       cout<<"Median of Three"<<endl<<endl;
       
       // Calls in the ComputeDuration that will pass on the start and end time to computer it's run time 
       // Output the runtime 
       ComputeDuration(QuickSortMedianBegin ,QuickSortMedianEnd);
       
       //Prints out the output and pass on the InputForQuickMedian Vector  and bool less function  int type ( small to large)
       //Will return 1 as true and return 0 as false if the vector isn't sorted in that order ( small to large)
       cout<<"Verified: "<<VerifyOrder(InputForQuickMedian,less<int>{})<<endl<<endl;
       
       
       //**************************************This is Middle Element QuickSort2 *************************************************************************
       
       //declare int type vector InputForQuick2 that store the Input_vector
       vector<int> InputForQuick2 = input_vector;
       
       //declare const auto QuickSort2begin to store the current time it started with 
       const auto QuickSort2Begin = chrono::high_resolution_clock::now();
       
       //Call on the QuickSort2 and pass on the InputForQuick2 and bool less function int type ( small to large) 
       QuickSort2(InputForQuick2 ,less<int>{});
       
       //declare const auto QuickSort2End to store the current time after QuickSort2 function is done
       const auto QuickSort2End = chrono::high_resolution_clock::now();
       
       //print the type of Quicksort and skip 2 lines
       cout<<"Middle"<<endl<<endl;
       
       //Calls in the ComputeDuration function and pass the start time and end time 
       //It will compute the Runtime of that QuickSort2  took from start to finish
       ComputeDuration(QuickSort2Begin,QuickSort2End  );
       
       //print out the output and calls in the VerifyOrder function that will pass on the InputForQuick2 and bool less function int type( small to large)
       // then skip 2lines
       cout<<"Verified: "<<VerifyOrder(InputForQuick2,less<int>{})<<endl<<endl;
	
	
	
	//***********************************This is First Element QuickSort3**************************************************************
	
	//Declare int type vector InputFor3Quick that stores the input_vector
       vector<int> InputForQuick3 = input_vector;
       
       //Declare const auto QuickSort3Beign to store the current time before it started the QuickSort3
       const auto QuickSort3Begin = chrono::high_resolution_clock::now();
       
       //This Function will sort the InputForQuick3 vector by using First element pivot to QuickSort
       //Calls on QuickSort3 and pass the InputForQuick3 and less int type ( small to large) 
       QuickSort3(InputForQuick3 ,less<int>{});
       
       //Delcare const auto QuickSort3End to store the current time now for end time after finished QuickSort3
       const auto QuickSort3End = chrono::high_resolution_clock::now();
       
       //Print out the type of QuickSort and skip 2 lines
       cout<<"First"<<endl<<endl;
       
       //Calls in the ComputeDuration Function and pass the start time and end time 
       //It will compute the runtime in nano seconds
       ComputeDuration(QuickSort3Begin,QuickSort3End  );
       
       //Prints the output and calls the verifyOrder to check if InputForQuick3 is sorted in small to large order after the QuickSort3
       cout<<"Verified: "<<VerifyOrder(InputForQuick3,less<int>{})<<endl<<endl;  
       
  }
  else // This is when greater is being call by Comparsion_type
  {
	
       //The reason why delcare a new int type vector to Store the input_vector because once input_vector is being used
       // the Input_vector is already Sorted in that partically sort way and might causes different errors araise as being used be other Sort algorithms.
       
       
       //***********************************This is HeapSort**********************************
       //Declare a new int type vector (InputForHeap) to store the input_vector
       vector<int> InputForHeap = input_vector;
       
       //Declare const auto heapBegin to store the time it started the Heapsort
       const auto heapBegin = chrono::high_resolution_clock::now();
       
       //Calls the HeapSort and pass Input vector, and less of int 
       //It Run the Function and Sort it by HeapSort. With larger to smaller bool integers order
       HeapSort(InputForHeap,greater<int>{});
       
       //Declare const auto HeapEnd to store the end time after HeapSorted is done with the Input Vector larger to smaller integers
       const auto heapEnd = chrono::high_resolution_clock::now();
       //Print out the output ( HeapSort)
       cout<<"HeapSort"<<endl<<endl;
       
       //Passes the Start time and End time variables into the Compute Duration function
       //It will prints out the run time in nano seconds and expected outputs
       ComputeDuration(heapBegin,heapEnd);
       
       //It will calls on the Function VerifyOrder with two parameter passed by (inputvector) being sorted by HeapSort and in a greater Order
       //Prints out the output and return 1 for true and 0 for false 
       cout<<"Verified: "<<VerifyOrder(InputForHeap,greater<int>{})<<endl<<endl;
       
       
       
       //*******************************THIS IS MergeSort*********************************
       //Delcare new int type vector ( InputForMerge) that stores the input_vector
       vector<int>InputForMerge= input_vector;
       
       //Declare const auto For MergeSortBegin that will store the time now ( time that started before doing the mergesort)
       const auto MergeSortBegin = chrono::high_resolution_clock::now();
       
       //Calls in the MergeSort function and pass the two parameter ( Input of the vector and greater ( larger to smaller))
       MergeSort(InputForMerge,greater<int>{});
       
       //Declare const auto variable to store the end of the time after MergeSort is done
       const auto MergeSortEnd = chrono::high_resolution_clock::now();
       
       //Print out the output 
       cout<<"MergeSort"<<endl<<endl;
       
       //Calls in the ComputeDuration with 2 parameter and pass the time with begin and end time
       //It will output the runtime in nano seconds of how long it took
       ComputeDuration(MergeSortBegin,MergeSortEnd);
       
       //Prints out the output and check to see if the MergeSort Sorted the input vector in a larger to smaller order
       //return 1 if it's true and return 0 false if not
       cout<<"Verified: "<<VerifyOrder(InputForMerge,greater<int>{})<<endl<<endl;
       
       
       //**********************THIS IS QUICKSORT***********************************
       //Declare int type vector InputForQuick1 to store the variables of input_vector
       vector<int> InputForQuick1 = input_vector;
       
       //Declare const auto QuickSortBegin to store the current time Before starting the QuickSort
       const auto QuickSortBegin = chrono::high_resolution_clock::now();
       
       //Calls in the QuickSort and pass the InputForQuick1 vector and bool less function as int type
       QuickSort(InputForQuick1 ,greater<int>{});
       
       //Declare const auto QuickSortEnd that will store the end it ended on after the QuickSort
       const auto QuickSortEnd = chrono::high_resolution_clock::now();
       
       //Prints out the output and skip 2 lines
       cout<<"QuickSort"<<endl<<endl;
       
       //Calls in the ComputeDuration and pass in the QuickSortedBegin(Time that Begin) and the time that the sort Ended
       //Prints out the Runtime for QuickSort
       ComputeDuration(QuickSortBegin,QuickSortEnd );
       
       //Prints output and calls in the function to verify The InputForQuick1 and bool greater function of int type 
       //It will return true if the vector is in sorted order of larger to smaller
       cout<<"Verified: "<<VerifyOrder(InputForQuick1,greater<int>{})<<endl<<endl;
       
       
       
       
       //**************************************This is the MedianOfThree, First, and Middle Element for QuickSort*****************
       
       //prints out the Output and skip 2 lines
       cout<<"Testing Quicksort Pivot Implementations" <<endl<<endl;
       
       
       
       
       //*****************************This is Median of Three ************************************************************************
       
       
       //Declare int type vector InPutForQuickMedian to store the input_vector
       vector<int> InputForQuickMedian = input_vector;
       
       //Declare const auto QuickSortMedianBegin to store the  current time it started before QuickSort
       const auto QuickSortMedianBegin = chrono::high_resolution_clock::now();
       
       //Calls in the QuickSort Function and pass In the QuickSortMedian and less int type 
       QuickSort(InputForQuickMedian ,greater<int>{});
       
       //Declare const auto QuickSortMedianEnd to store the current time after the QuickSort Ended
       const auto QuickSortMedianEnd = chrono::high_resolution_clock::now();
       
       //Prints out the type of sort and skip 2 lines 
       cout<<"Median of Three"<<endl<<endl;
       
       //Calls in the ComputeDuration that will pass on the start and end time to computer it's run time 
       //Output the runtime 
       ComputeDuration(QuickSortMedianBegin ,QuickSortMedianEnd);
       
       //Prints out the output and pass on the InputForQuickMedian Vector  and bool less function  int type (larger to smaller)
       //Will return 1 as true and return 0 as false if the vector isn't sorted in that order (larger to smaller)
       cout<<"Verified: "<<VerifyOrder(InputForQuickMedian,greater<int>{})<<endl<<endl;
       
       
       //**************************************This is Middle Element QuickSort2 *************************************************************************
       
       //Declare int type vector InputForQuick2 that store the Input_vector
       vector<int> InputForQuick2 = input_vector;
       
       //Declare const auto QuickSort2begin to store the current time it started with 
       const auto QuickSort2Begin = chrono::high_resolution_clock::now();
       
       //Call on the QuickSort2 and pass on the InputForQuick2 and bool greater function int type (larger to smaller) 
       QuickSort2(InputForQuick2 ,greater<int>{});
       
       //Declare const auto QuickSort2End to store the current time after QuickSort2 function is done
       const auto QuickSort2End = chrono::high_resolution_clock::now();
       
       //Print the type of Quicksort and skip 2 lines
       cout<<"Middle"<<endl<<endl;
       
       //Calls in the ComputeDuration function and pass the start time and end time 
       //It will compute the Runtime of that QuickSort2  took from start to finish
       ComputeDuration(QuickSort2Begin,QuickSort2End  );
       
       //Print out the output and calls in the VerifyOrder function that will pass on the InputForQuick2 and bool greater function int type(larger to smaller)
       cout<<"Verified: "<<VerifyOrder(InputForQuick2,greater<int>{})<<endl<<endl;
	
	
	
	//***********************************This is First Element QuickSort3**************************************************************
	
	//Declare int type vector InputFor3Quick that stores the input_vector
       vector<int> InputForQuick3 = input_vector;
       
       //Declare const auto QuickSort3Beign to store the current time before it started the QuickSort3
       const auto QuickSort3Begin = chrono::high_resolution_clock::now();
       
       //This Function will sort the InputForQuick3 vector by using First element pivot to QuickSort
       //Calls on QuickSort3 and pass the InputForQuick3 and bool greater function int type (larger to smaller) 
       QuickSort3(InputForQuick3 ,greater<int>{});
       
       //Declare const auto QuickSort3End to store the current time now for end time after finished QuickSort3
       const auto QuickSort3End = chrono::high_resolution_clock::now();
       
       //Print out the type of QuickSort and skip 2 lines
       cout<<"First"<<endl<<endl;
       
       //Calls in the ComputeDuration Function and pass the start time and end time 
       //It will compute the runtime in nano seconds
       ComputeDuration(QuickSort3Begin,QuickSort3End  );
       
       //Prints the output and calls the verifyOrder to check if InputForQuick3 is sorted in larger to smaller order after the QuickSort3
       cout<<"Verified: "<<VerifyOrder(InputForQuick3,greater<int>{})<<endl<<endl;  
       
  }	
  return 0;
}

// Do not change anything below

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  sortTestingWrapper(argc, argv);

  return 0;
}
