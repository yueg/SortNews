//
// Created by yueg on 9/18/15.
//

/**
 * 使用堆的思想，获得热度最大或者最小的n个文章的id
 */

#ifndef SORTNEWS_HEAPUTIL_H
#define SORTNEWS_HEAPUTIL_H
#include <map>


class HeapUtil
{
private:
    std::map<int, float> dataMap;     // 文章热度表
    int *heap;                   // 堆
    int heapSize;                // 堆大小
public:
    /**
     * @param map<int, float> m 文章热度map
     * @param int heapSize 堆的大小
     * @param bool type true:得到热度最大的heapSize篇文章id; false:得到热度最小的heapSize篇文章id
     */
    HeapUtil(std::map<int, float> m, int heapSize, bool type);

    // 根据this->dataMap建堆
    void BuildHeap(int n, bool type);

    // 类似堆排序中调整堆的算法
    void AdjustHeap(int i, int size, bool type);

    // 获取堆指针
    int *GetHeap() const;

    // 获取堆大小
    int GetHeapSize() const;
};


#endif //SORTNEWS_HEAPUTIL_H
