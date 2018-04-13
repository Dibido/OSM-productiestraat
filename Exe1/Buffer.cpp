/*
 * Buffer.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Jacoline
 */

#include "Buffer.hpp"
#include <stdexcept>


Buffer::Buffer(int aNumberOfProducts, int aMaxBuffer, int anId)
	: numberOfProducts(0), maxBuffer(aMaxBuffer), id(anId)
{
	if(aNumberOfProducts<0){
		this->numberOfProducts = 0;
	}
	else if(aNumberOfProducts>maxBuffer){
		this->numberOfProducts = maxBuffer;
	}
	else{
		this->numberOfProducts = aNumberOfProducts;
	}
}

Buffer::~Buffer()
{
}

//cppcheck-suppress unusedFunction
int Buffer::checkBufferSpaceAvailable(int numberOfProducts, int maxBuffer) const{
	if(numberOfProducts<=maxBuffer){
		return maxBuffer-numberOfProducts;
	}
	else{
		return 0;
	}
}

int Buffer::getNumberOfProducts() const
{
	if(numberOfProducts>maxBuffer){
		throw std::invalid_argument("Buffer: " + std::to_string(id) + " Overflow numberOfProducts: " + std::to_string(numberOfProducts) + " maxBuffer: " + std::to_string(maxBuffer));
	}
	else if(numberOfProducts<0){
		throw std::invalid_argument("Negative number of products");
	}
	else{
		return numberOfProducts;
	}
}

//cppcheck-suppress unusedFunction
void Buffer::setNumberOfProducts(int numberOfProducts)
{
	if(numberOfProducts<0){
		this->numberOfProducts = 0;
	}
	else if(numberOfProducts>maxBuffer){
		this->numberOfProducts = maxBuffer;
	}
	else{
		this->numberOfProducts = numberOfProducts;
	}
}

int Buffer::getMaxBuffer() const
{
	return maxBuffer;
}

void Buffer::setMaxBuffer(int maxBuffer)
{
	if(maxBuffer<0){
		this->maxBuffer=0;
	}
	else{
		this->maxBuffer = maxBuffer;
	}
}

int Buffer::getId() const
{
	return id;
}

void Buffer::setId(int id)
{
	this->id = id;
}

void Buffer::operator+=(int a){
	if(numberOfProducts>maxBuffer){
		throw std::invalid_argument("Buffer: " + std::to_string(id) + " Overflow numberOfProducts: " + std::to_string(numberOfProducts) + " a: " + std::to_string(a) + " maxBuffer: " + std::to_string(maxBuffer));
	}
	else{
	numberOfProducts += a;
	}
}


void Buffer::operator-=(int a){
	if(numberOfProducts<0){
		throw std::invalid_argument("Negative number of products");
	}
	else{
		numberOfProducts -= a;
	}
}
