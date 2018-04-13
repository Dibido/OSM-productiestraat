/*
 * IniParcer.h
 *
 *  Created on: 15 nov. 2017
 *      Author: dhnus
 */

#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>


#ifndef INIPARSER_H_
#define INIPARSER_H_
	/** 	 */
class IniParser {
public:
	/**
	 * @brief getInstance of itself, singleton pattern
	 */
	static IniParser& getInstance() {
		static IniParser instance;
		return instance;
	}
	/**
	 * @brief Functie whare u can set a file
	 * @param The location of the file
	 * @post U end up with the value
	 * @pre Thare is a file
	 */
	inline void setFile(std::string fileName){
		boost::property_tree::ini_parser::read_ini(fileName, file);
	}
	/**
	 * @brief Get a value from the file
	 * @param The location from the file
	 * @post U end up with the value
	 * @pre Thare is a correct location
	 * @return int
	 */
	inline int getInt(std::string Selection){
		int i = file.get<int>(Selection);
		return i;
	}
	/**
	 * @brief Get a value from the file
	 * @param The location from the file
	 * @pre Thare is a correct location
	 * @return string
	 */
	inline std::string getString(std::string Selection){
		std::string i = file.get<std::string>(Selection);
		return i;
	}

	/**
	 * @brief Get a value from the file
	 * @param Ini-key
	 * @return float
	 */
	inline float getFloat(std::string Selection){
		float i = file.get<float>(Selection);
		return i;
	}
private:
	/**
	 * @brief the constructor
	 */
	IniParser() {}
	/**
	 * @brief read the ini file
	 */
	boost::property_tree::ptree file;
public:
	/**
	 *
	 */
	IniParser(IniParser const&) = delete;
	/**
	 *
	 */
	void operator=(IniParser const&) = delete;
};
#endif /* INIPARCER_H_ */
