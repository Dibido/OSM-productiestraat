/*
 * Buffer.hpp
 *
 *  Created on: 17 nov. 2017
 *      Author: Jacoline
 */

#ifndef EXE1_BUFFER_HPP_
#define EXE1_BUFFER_HPP_

class Buffer
{
public:

	/*
	 * @brief Constructor initialises the Buffer
	 * @param aNumberOfProducts is an int, maxBuffer is an int, id is an int
	 */
	Buffer(int aNumberOfProducts, int aMaxBuffer, int anId);

	/*
	 * @brief Destructor of Buffer
	 */
	virtual ~Buffer();

	/*
	 * @brief Returns the number of available spaces in the Buffer
	 * @param numberOfProducts is an int, maxBuffer is an int
	 * @return int
	 */
	int checkBufferSpaceAvailable(int numberOfProducts, int maxBuffer) const;

	/*
	 * @brief Returns the number of products currently in the Buffer
	 * @return int
	 */
	int getNumberOfProducts() const;

	/*
	 * @brief Sets the number of products
	 * @param numberOfProducts is an int
	 */
	void setNumberOfProducts(int numberOfProducts);

	/*
	 * @brief Returns the maximum Buffer size
	 * @return int
	 */
	int getMaxBuffer() const;

	/*
	 * @brief Sets the maximum Buffer size
	 * @param maxBuffer is an int
	 */
	void setMaxBuffer(int maxBuffer);

	/*
	 * @brief Returns the id of the buffer
	 * @return int
	 */
	int getId() const;

	/*
	 * @brief Sets the id of the buffer
	 * @param id is an int
	 */
	void setId(int id);

	/*
	 * @brief Adds to current value
	 * @param a is an int
	 */
	void operator+=(int a);

	/*
	 * @brief Subtracts from current value
	 * @param a is an int
	 */
	void operator-=(int a);


private:
	int numberOfProducts;
	int maxBuffer;
	int id;
};

#endif /* EXE1_BUFFER_HPP_ */
