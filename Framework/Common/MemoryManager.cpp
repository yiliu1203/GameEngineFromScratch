#include <cassert>
#include <cstdlib>
#include <iostream>
#include "MemoryManager.hpp"

using namespace My;
using namespace std;

int MemoryManager::Initialize()
{
    return 0;
}

void MemoryManager::Finalize()
{
    assert(m_mapMemoryAllocationInfo.size() == 0);
}

void MemoryManager::Tick()
{
#if DEBUG
    static int count = 0;

    if (count++ == 3600)
    {
        for (auto info : m_mapMemoryAllocationInfo)
        {
            cerr << info.first << '\t';
            out << info.second.PageMemoryType;
            out << info.second.PageSize;
        }
    }
#endif
}

void* MemoryManager::AllocatePage(size_t size)
{
    uint8_t* p;

    p = static_cast<uint8_t*>(malloc(size));
    if (p)
    {
        MemoryAllocationInfo info = {size, MemoryType::CPU};
        m_mapMemoryAllocationInfo.insert({p, info});
    }

    return static_cast<void*>(p);
}

void MemoryManager::FreePage(void* p)
{
    auto it = m_mapMemoryAllocationInfo.find(p);
    if (it != m_mapMemoryAllocationInfo.end())
    {
        m_mapMemoryAllocationInfo.erase(it);
        free(p);
    }
}
