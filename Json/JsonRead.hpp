#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
#include "picojson.h"

using number = double;
using jsonArray =  picojson::array;
class JsonRead final
{
private:
	picojson::value v_;
public:
	JsonRead() = default;
	JsonRead(const std::string& path)
	{
		// JSONデータの読み込み。
		std::stringstream ss;
		std::ifstream ifs(path, std::ios::in);
		if (ifs.fail())
		{
			std::cerr << "failed to read json" << std::endl;
		}
		ss << ifs.rdbuf();
		ifs.close();

		//JSONデータを解析する。
		const std::string err = picojson::parse(v_, ss); 
		if (err.empty() == false)
		{
			std::cerr << err << std::endl;
		}
	}
	bool Load(const std::string& path)
	{
		// JSONデータの読み込み。
		std::stringstream ss;
		std::ifstream ifs(path, std::ios::in);
		if (ifs.fail())
		{
			return false;
		}
		ss << ifs.rdbuf();
		ifs.close();

		//JSONデータを解析する。
		const std::string err = picojson::parse(v_, ss);
		if (!err.empty())
		{
			return false;
		}
		return true;
	}

	template <class T>
	const T GetParameter(const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		return obj_[name].get<T>();
	}

	template <class T>
	const T GetParameter(const std::string& name, const size_t index)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>().at(index);
		return arr.get<T>();
	}

	template <class T>
	const void GetArrayParameter(const std::string& name, T* data, const size_t maxIndex)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>();
		assert(std::size(arr) == maxIndex);
		size_t i = 0;
		for (const auto& it_j : arr)
		{
			data[i] = it_j.get<T>();
			++i;
			if (i > maxIndex)
			{
				break;
			}
		}
	}

	template <class T>
	const T GetParameter(const std::string& objectName, const std::string& name)
	{
		picojson::object obj_ =  v_.get<picojson::object>()[objectName].get<picojson::object>();
		return obj_[name].get<T>();
	}


	template <class T>
	const T GetParameter(const std::string& objectName, const std::string& name, const size_t index)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>().at(index);
		return arr.get<T>();
	}

	template <class T>
	const void GetArrayParameter(const std::string& objectName, const std::string& name, T* data , const size_t maxIndex)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>();
		assert(std::size(arr) == maxIndex);
		size_t i = 0;
		for (const auto& it_j : arr)
		{
			data[i] = it_j.get<T>();
			++i;
			if (i > maxIndex)
			{
				break;
			}
		}
	}
};