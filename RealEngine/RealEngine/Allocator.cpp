#include "Allocator.h"

RealEngine::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
	:m_pFreeList(nullptr),m_pPageList(nullptr)
{
	Reset(data_size, page_size, alignment);
}
RealEngine::Allocator::~Allocator()
{
	Clear();
}

void RealEngine::Allocator::Reset(size_t data_size, size_t page_size, size_t alignment)
{
	Clear();

	m_szDataSize = data_size;
	m_szPageSize = page_size;

	// ���ݴ�С�Ƿ񳬹���С��Ĵ�С
	size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;

	//����������Ҫ������ݿ���С�ߴ�
	m_szBlockSize = (minimal_size + alignment - 1)& ~(alignment - 1);

	// ��������˷ѵĴ�С
	m_szAlignmentSize = m_szBlockSize - minimal_size;

	m_nBlockPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

void RealEngine::Allocator::Clear()
{
	PageHeader* pPage = m_pPageList;
	while (pPage)
	{
		PageHeader* _p = pPage;
		pPage = pPage->pNext;

		delete[] reinterpret_cast<uint8_t*>(_p);
	}
	m_pPageList = nullptr;
	m_pFreeList = nullptr;

	m_nPages = 0;
	m_nBlocks = 0;
	m_nFreeBlocks = 0;
}

void* RealEngine::Allocator::Allocate()
{
	// û�п����ڴ�
	if (!m_pFreeList) 
	{
		// ������һҳ
		PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
		++m_nPages;

		m_nBlocks += m_nBlockPerPage;
		m_nFreeBlocks += m_nBlockPerPage;

		// ����ҳ����
		if (m_pPageList)
		{
			pNewPage->pNext = m_pPageList;
		}
		m_pPageList = pNewPage;

		// ��ҳ�����С�ֿ�
		BlockHeader* pBlock = pNewPage->Blocks();
		for (uint32_t i = 0; i < m_nBlockPerPage - 1; i++) 
		{
			pBlock->pNext = NextBlock(pBlock);
			pBlock = NextBlock(pBlock);
		}
		pBlock->pNext = nullptr;

		m_pFreeList = pNewPage->Blocks();
	}

	BlockHeader* freeBlock = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	--m_nFreeBlocks;

	return reinterpret_cast<void*>(freeBlock);
}

void RealEngine::Allocator::Free(void* p) 
{
	BlockHeader* pBlock = reinterpret_cast<BlockHeader*>(p);

	pBlock->pNext = m_pFreeList;
	m_pFreeList = pBlock;

	++m_nFreeBlocks;
}

RealEngine::BlockHeader* RealEngine::Allocator::NextBlock(BlockHeader* pBlock)
{
	return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*> (pBlock) + m_szBlockSize);
}