#include "memory_resource.h"
#include "..\mutex.h"
#include <new> //for ::operator new/delete
#include <cstdint>

namespace Yupei
{


	memory_resource::~memory_resource()
	{
	}

	void * memory_resource::allocate(size_type bytes, size_type alignment)
	{
		return do_allocate(bytes, alignment);
	}

	void memory_resource::deallocate(void * p, size_type bytes, size_type alignment)
	{
		do_deallocate(p, bytes, alignment);
	}

	bool memory_resource::is_equal(const memory_resource & other) const noexcept
	{
		return do_is_equal(other);
	}

	class NewDeleteResource : public memory_resource
	{
	public:		
		void* do_allocate(size_type bytes, size_type alignment) override
		{
			return ::operator new(Internal::GetFinalSize(bytes, alignment));
		}

		void do_deallocate(void* p, size_type bytes, size_type alignment) override
		{
			return ::operator delete(p, Internal::GetFinalSize(bytes, alignment));
		}

		bool do_is_equal(const memory_resource& other) const noexcept override
		{
			return this == &other;
		}
	};

	class NullMemoryResource : public memory_resource
	{
	public:
		[[noreturn]]
		void* do_allocate(size_type bytes, size_type alignment) override
		{
			throw std::bad_alloc();
		}

		void do_deallocate(void* p, size_type bytes, size_type alignment) override
		{
			//no-op
		}

		bool do_is_equal(const memory_resource& other) const noexcept override
		{
			return this == &other;
		}
	};

	static NewDeleteResource newDeleteResource;
	static NullMemoryResource nullMemoryResource;
	static mutex memoryResourceLock;
	
	memory_resource* new_delete_resource() noexcept
	{
		return &newDeleteResource;
	}

	memory_resource* null_memory_resource() noexcept
	{
		return &nullMemoryResource;
	}

	static memory_resource* defaultMemoryResource = new_delete_resource();

	memory_resource* get_default_resource() noexcept
	{
		return defaultMemoryResource;
	}

	memory_resource* set_default_resource(memory_resource* r) noexcept
	{
		auto temp = defaultMemoryResource;
		lock_guard<mutex> guard{ memoryResourceLock };
		if (r == nullptr) defaultMemoryResource = new_delete_resource();
		else defaultMemoryResource = r;
		return temp;
	}

	namespace Internal
	{

		void* BufferManager::Allocate(size_type size, size_type alignment)
		{
			const auto offset = GetFinalOffset(static_cast<const void*>(buffer_ + cursor_), alignment);
			if (cursor_ + offset + size > bufferSize_) return nullptr;
			void* result = buffer_ + cursor_ + offset;
			cursor_ += (size + offset);
			return result;
		}

		auto BufferManager::ReplaceBuffer(void * newBuffer, size_type newBufferSize) -> ByteType*
		{
			auto oldBuffer = buffer_;
			buffer_ = static_cast<ByteType*>(newBuffer);
			bufferSize_ = newBufferSize;
			cursor_ = {};

			return oldBuffer;
		}

		void* SimplePoolManager::Allocate(size_type size, size_type alignment)
		{
			if (size == 0) return nullptr;

			const auto totalSize = size + sizeof(Block);

			auto block = static_cast<Block*>(upstream_->allocate(totalSize,alignment));

			block->nextBlock_ = headBlock_;
			block->blockSize_ = totalSize;
			headBlock_ = block;

			return static_cast<void*>(block + 1);

		}

		void SimplePoolManager::Release()
		{
			while (headBlock_)
			{
				auto nextBlock = headBlock_->nextBlock_;
				upstream_->deallocate(headBlock_,headBlock_->blockSize_);
				headBlock_ = nextBlock;
			}
		}
	}

}

