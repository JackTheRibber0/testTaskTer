#ifndef TS_VECTORFILE_H
#define TS_VECTORFILE_H


#include "common.h"

// RUDIMENT

namespace ds
{
	template<typename T>
	class thread_safe_vector
	{

	public:

		virtual ~thread_safe_vector() { clear(); }

		T& operator[](int32_t number)
		{
			std::scoped_lock lock(muxVector_);
			return data_[number];
		}



		void push_back(const T& _data)
		{
			std::scoped_lock lock(muxVector_);
			data_.push_back(_data);
		}

		void pop_back()
		{
			std::scoped_lock lock(muxVector_);
			data_.pop_back();
		}

		void erase(size_t position)
		{
			std::scoped_lock lock(muxVector_);
			data_.erase(position);
		}

		void erase(T* begin, T* end)
		{
			std::scoped_lock lock(muxVector_);
			data_.erase(begin, end);
		}

		void erase(T* pointer)
		{
			std::scoped_lock lock(muxVector_);
			data_.erase(pointer);
		}

		size_t max_size() const
		{
			std::scoped_lock lock(muxVector_);
			return data_.max_size();
		}

		size_t size() const
		{
			std::scoped_lock lock(muxVector_);
			return data_.size();
		}

		T* end() const
		{
			std::scoped_lock lock(muxVector_);
			return data_.end();
		}

		T* begin() const
		{
			std::scoped_lock lock(muxVector_);
			return data_.begin();
		}

		uint8_t empty() const
		{
			std::scoped_lock lock(muxVector_);
			return data_.empty();
		}

		void clear()
		{
			std::scoped_lock lock(muxVector_);
			data_.clear();
		}

	private:

		std::vector<T> data_;
		std::mutex muxVector_;
	};
}

#endif