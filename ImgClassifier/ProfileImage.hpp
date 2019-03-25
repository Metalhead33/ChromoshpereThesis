#ifndef PROFILEIMAGE_HPP
#define PROFILEIMAGE_HPP
#include "Wrapper/MhImageWrapper.hpp"

// Mh::ImageWrapper convertToWeighedGreyscale(const Mh::ImageWrapper& img); //
// FreeImage does not use weighing when converting to greyscale
Mh::ImageWrapper produceSharpnessProfile( const Mh::ImageWrapper &img,
					  int blurRadius = 15,
					  float *fMin = nullptr,
					  float *fMax = nullptr,
					  float *fAvg = nullptr );
Mh::ImageWrapper sharpnessComposite( const Mh::ImageWrapper &originA,
					 const Mh::ImageWrapper &originB,
					 int blurRadius = 15 );

#endif // PROFILEIMAGE_HPP
