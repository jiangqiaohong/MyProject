#pragma once
#include <cstddef>
#include <cstdint>

namespace RealEngine 
{
	struct BlockHeader{
		BlockHeader *pNext;
	};
	struct PageHeader {
		PageHeader *pNext;
		/*
		������this��������PageHeader��
		����this+1��������PageHeader��
		ָ��PageHeader֮��ĵ�һ���ֽڣ�
		Ҳ�������Page���е�һ��Block��ʼ�ĵط���
		Ȼ��ָ��ǿ��ת����BlockHeader*���ͷ��ء�
		�������嵽���ܾ��Ƿ��ص�ǰPage���е�һ��Block��ʼ�ĵ�ַ
		*/
		BlockHeader* Blocks() {
			return reinterpret_cast<BlockHeader*>(this + 1);
		}
	};

	class Allocator 
	{
	public:
		Allocator(size_t data_size, size_t page_size, size_t alignment);
		~Allocator();


		void* Allocate();
		void Free(void* p);
	private:
		BlockHeader* NextBlock(BlockHeader* pBlock);

		PageHeader* m_pPageList;
		BlockHeader* m_pFreeList;

		// �������ݵĴ�С
		size_t m_szDataSize;
		// ҳ�Ĵ�С
		size_t m_szPageSize;
		// ����Ĵ�С
		size_t m_szAlignmentSize;

		// block �Ĵ�С
		size_t m_szBlockSize;
		// ƽ��ÿ��page �Ĵ�С
		size_t m_nBlockPerPage;

		// ��ҳ��
		uint32_t m_nPages;
		// �ܿ���
		uint32_t m_nBlocks;
		// ���еĿ���
		uint32_t m_nFreeBlocks;

		Allocator(const Allocator& clone) = delete;
		Allocator& operator = (const Allocator &rhs) = delete;
	};
}