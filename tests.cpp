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
//caclulate the total size of all of the dimensions flattened into one
    size_t expectedTotalSize=std::accumulate(extents.begin(),extents.end(),0);
//check taht the expected total size is what is returned by getTotatlSize
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

using fiveDimArrayType=boost::multi_array<std::shared_ptr<char>,numDims>;

TEST(MultiDimArraySATest,GetElement_fiveDims_works){
//for ease of syntax to access the number of dims
  const size_t numDims=5;
//create a boost multi array of shared pointers to characters. Using shared pointers so that the MDA can point to the same characters and so memmory management is handled automatically.
  fiveDimArrayType fiveDimArray(boost::extents[5][3][4][7][1]);
  std::vector<size_t> dimExtents{5,3,4,7,1};
  MultiDimArray<std::shared_ptr<char> > mDA(dimExtents);
  for(size_t curDim=0;curDim<numDims;++curDim){  
    for(size_t curIndex=0;curIndex<dimExtents[curDim];++curIndex){  
      //std::make_shared<char>('a');
      //mDA.getElement(
    }
  }
  //oneDim.getElement(0)=chPtr;
  //EXPECT_EQ(*(oneDim.getElement(0)),*chPtr);
}
void initializeFiveDimArrays(fiveDimArrayType fiveDimArray,MultiDimArray<std::shared_ptr<char> > mDA){}


int main(int argc, char** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
