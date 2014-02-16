#include "MultiDimArray.h"
#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <vector>
#include <memory>

TEST(MultiDimArraySATest,ConstructorWorks){
//the number of arrays to test as well as the greatest extent of dimensions and the greatest number of dimensions 
  size_t numArrays=6;
//vector for holding dimExtents to pass to MultiDimArray constructor
  std::vector<size_t> extents;
  for(size_t i=0;i<numArrays;++i){
//push current array num onto the vector of extents (O(n) but much easier to work with MDA args and ret values)
    extents.insert(extents.begin(),i);
//create MDA
    MultiDimArray<char*> mDA(extents);
//check that the number of dimensions is correct
    EXPECT_EQ(extents.size(),mDA.getNumDims());
//check that the dimensional extents are correct
    EXPECT_EQ(extents,mDA.getDimExtents());
//Calculate the total size of all of the dimensions flattened into one
    size_t expectedTotalSize=std::accumulate(extents.begin(),extents.end(),0);
//check that the expected total size is what is returned by getTotalSize
    EXPECT_EQ(expectedTotalSize,mDA.getTotalSize());
  }
}

TEST(MultiDimArraySATest,Constructor_nonTerminalZeroExtent_throwsException){
  std::vector<size_t> dimExtents{1,2,3,0};
  EXPECT_NO_THROW({MultiDimArray<char*> mDA(dimExtents);});
  dimExtents={1,2,0,3};
  EXPECT_THROW({MultiDimArray<char*> mDA(dimExtents);},MultiDimArrayException);
}

TEST(MultiDimArraySATest,GetElement_zeroDims_throwsException){
  std::vector<size_t> dimExtents;
  MultiDimArray<char*> zeroDim(dimExtents);
  EXPECT_THROW({zeroDim.getElement(0);},MultiDimArrayException);
}

//declare boost multi array type for shared pointers to characters
using fiveDimArrayType=boost::multi_array<std::shared_ptr<char>,numDims>;

TEST(MultiDimArraySATest,GetElement_fiveDims_works){
//for ease of syntax to access the number of dims
  const size_t numDims=5;
//create a boost multi array of shared pointers to characters. Using shared pointers so that the MDA can point to the same characters and so memory management is handled automatically.
//create instance of fiveDimArrayType
  fiveDimArrayType fiveDimArray(boost::extents[5][3][4][7][1]);
//create vector of extents for mDA
  std::vector<size_t> dimExtents{5,3,4,7,1};
//create mDA instance
  MultiDimArray<std::shared_ptr<char> > mDA(dimExtents);

  char charToStore='a';
  for(size_t curDim=0;curDim<numDims;++curDim){  

      fiveDimArray[][]=std::make_shared<char>(charToStore++);
      //mDA.getElement(
    }
  }
  //oneDim.getElement(0)=chPtr;
  //EXPECT_EQ(*(oneDim.getElement(0)),*chPtr);
}

/*
 * funciton to initialize a MultiDimArray.
 * template params:
 *  ElementType - type of element to be stored. Must implement the ++ operator.
 * params:
 *  mDA - instance of a MultiDimArray
 *  dimExtents - vector of the size of each dimension
 *  initialValue - what to start element at (will be incremented for each insertion)
*/
template <typename ElementType>
void populateMultiDimArray(MultiDimArry& mDA,
							const std::vector<size_t>& dimExtents,
							const elementType& initialValue){
	elementType element=initialValue;
//vector for index at which to start recursion
	std::vector<size_t> initialIndex{0};
	_populateMultiDimArrays_recurse(mDA,dimExtents,initialIndex,initialValue);
}

/*
 * recursive component function of populateMultiDimArray.
 * template params:
 *  ElementType - type of element to be stored. Must implement the ++ operator.
 * params:
 *  mDA - instance of a MultiDimArray
 *  dimExtents - vector of the size of each dimension
 *  currentIndexes - current index.
 *  element - the element to store in the mDA in the base case or increment and pass to next level of recursion in non-base case.
*/
template <typename elementType>
void _populateMultiDimArrays_recurse(MultiDimArry& mDA,
							 const std::vector<size_t>& dimExtents,
							 const std::vector<size_t>& currentIndexes,
							 elementType& element){
//if the number of indexes (number of dimension in which we have specified indexes) is less than the total number of dimensions, we are not in the base case
	if(currentIndex.size()<dimExtents.size()){
//loop through all indexes for current dimension and recurse on each one
		for(size_t currentIndex=0;currentIndex<dimExtents[curDim];++currentIndex){
			//create copy of currentIndexes for adding currentIndex and passing to recursion
			std::vector<size_t> nextIndexes=currentIndexes;
			//TODO add currentIndex to nextIndexes and to parameters for _populateMultiDimArrays_recurse
			//TODO increment element and add to params
			_populateMultiDimArrays_recurse(mDA,dimExtents)
		}
	}else{
//this is the base case, so we assign element
		//TODO assign element to mDA at currentIndexes
	}
}


int main(int argc, char** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
