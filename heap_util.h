//
// Created by yueg on 9/18/15.
//

/**
 * 使用堆的思想，获得热度最大或者最小的n个文章的id
 */

#ifndef SORTNEWS_HEAPUTIL_H
#define SORTNEWS_HEAPUTIL_H
#include <map>
#include "article.h"


class HeapUtil
{
private:
    std::map<__int64_t, float> dataMap;     // 文章热度表
    __int64_t *heap;                        // 堆
    int heapSize;                     // 堆大小
    int heapMax;
public:
    /**
     * @param map<int, float> m 文章热度map
     * @param int heapSize 堆的大小
     * @param bool type true:得到热度最大的heapSize篇文章id; false:得到热度最小的heapSize篇文章id
     */
    HeapUtil(std::map<__int64_t, float> m, int heapSize, bool type);

    HeapUtil(int size);

    // 插入元素到堆
    __int64_t InsertIntoHeap(const Article *article, bool type);

    // 根据this->dataMap建堆
    void BuildHeap(int n, bool type);

    // 类似堆排序中调整堆的算法
    void AdjustHeap(int i, int size, bool type);

    // 获取堆指针
    __int64_t *GetHeap() const;

    // 获取堆大小
    int GetHeapSize() const;

    // 设置heap大小
    void SetHeapMaxSize(int size);
};


#endif //SORTNEWS_HEAPUTIL_H
