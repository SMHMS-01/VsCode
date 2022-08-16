#include "__malloc_alloc_template.hpp"
#include "_default_alloc_temp.hpp"
//空间配置函式allocate()
// n must be > 0

#if 0
static void *allocate(size_t n)
{
    obj *volatile *my_free_list;
    obj *result;
    // 大於 128 就呼叫第㆒級配置器
    if (n > (size_t)__MAX_BYTES)
        return (malloc_alloc::allocate(n));
    // 尋找 16 個 free lists ㆗適當的㆒個
    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;
    if (result == 0)
    {
        // 沒找到可用的 free list，準備重新填充 free list
        void *r = refill(ROUND_UP(n));
        // ㆘節詳述
        return r;
    }
    // 調整 free list
    *my_free_list = result->free_list_link;
    return (result);
};

#endif
// 空間釋還函式 deallocate()
// 身為一個配置器，__default_alloc_template 擁有配置器標準介面函式
// deallocate()。此函式首先判斷區塊大小，大於128 bytes就呼叫第一級配置器，
// 小於 128 bytes 就找出對應的free list，將區塊回收。
#if 0
// p 不可以是 0
static void deallocate(void *p, size_t n)
{
    obj *q = (obj *)p;
    obj *volatile *my_free_list;
    // 大於 128 就呼叫第㆒級配置器
    if (n > (size_t)__MAX_BYTES)
    {
        malloc_alloc::deallocate(p, n);
        return;
    }
    // 尋找對應的 free list
    my_free_list = free_list + FREELIST_INDEX(n);
    // 調整 free list，回收區塊
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

#endif

//重新充填 free lists
// 傳回㆒個大小為 n 的物件，並且有時候會為適當的 free list 增加節點.
// 假設 n 已經適當㆖調至 8 的倍數。
#if 0
template <bool threads, int inst>
void *__default_alloc_template<threads, inst>::refill(size_t n)
{
    int nobjs = 20;
    // 呼叫 chunk_alloc()，嘗試取得 nobjs 個區塊做為 free list 的新節點。
    // 注意參數 nobjs 是 pass by reference。
    char *chunk = chunk_alloc(n, nobjs); // 下節詳述
    obj *volatile *my_free_list;
    obj *result;
    obj *current_obj, *next_obj;
    int i;
    // 如果只獲得㆒個區塊，這個區塊就撥給呼叫者用，free list 無新節點。
    if (1 == nobjs)
        return (chunk);
    // 否則準備調整 free list，納入新節點。
    my_free_list = free_list + FREELIST_INDEX(n);
    // 以㆘在 chunk 空間內建立 free list
    result = (obj *)chunk;
    // 這㆒塊準備傳回給客端
    // 以㆘導引 free list 指向新配置的空間（取自記憶池）
    *my_free_list = next_obj = (obj *)(chunk + n);
    // 以㆘將 free list 的各節點串接起來。
    for (i = 1;; i++)
    {
        // 從 1 開始，因為第 0 個將傳回給客端
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        if (nobjs - 1 == i)
        {
            current_obj->free_list_link = 0;
            break;
        }
        else
        {
            current_obj->free_list_link = next_obj;
        }
    }
    return (result);
}
#endif

//記憶池（memory pool）
// 從記憶池㆗取空間給 free list 使用，是 chunk_alloc() 的工作：
// 假設 size 已經適當㆖調至 8 的倍數。
// 注意參數 nobjs 是 pass by reference。
#if 0
template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::
    chunk_alloc(size_t size, int &nobjs)
{
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free; // 記憶池剩餘空間
    if (bytes_left >= total_bytes)
    {
        // 記憶池剩餘空間完全滿足需求量。
        result = start_free;
        start_free += total_bytes;
        return (result);
    }
    else if (bytes_left >= size)
    {
        // 記憶池剩餘空間不能完全滿足需求量，但足夠供應㆒個（含）以㆖的區塊。
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return (result);
    }
    else
    {
        // 記憶池剩餘空間連㆒個區塊的大小都無法提供。
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        // 以㆘試著讓記憶池㆗的殘餘零頭還有利用價值。
        if (bytes_left > 0)
        {
            // 記憶池內還有㆒些零頭，先配給適當的 free list。
            // 首先尋找適當的 free list。
            obj *volatile *my_free_list =
                free_list + FREELIST_INDEX(bytes_left);
            // 調整 free list，將記憶池㆗的殘餘空間編入。
            ((obj *)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }
        // 配置 heap 空間，用來挹注記憶池。
        start_free = (char *)malloc(bytes_to_get);
        if (0 == start_free)
        {
            // heap 空間不足，malloc() 失敗。
            int i;
            obj *volatile *my_free_list, *p;
            // 試著檢視我們手㆖擁有的東西。這不會造成傷害。我們不打算嘗試配置
            // 較小的區塊，因為那在多行程（multi-process）機器㆖容易導致災難
            // 以㆘搜尋適當的 free list，
            // 所謂適當是指「尚有未用區塊，且區塊夠大」之 free list。
            for (i = size; i <= __MAX_BYTES; i += __ALIGN)
            {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p)
                { // free list 內尚有未用區塊。
                    // 調整 free list 以釋出未用區塊
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    // 遞迴呼叫自己，為了修正 nobjs。
                    return (chunk_alloc(size, nobjs));
                    // 注意，任何殘餘零頭終將被編入適當的 free-list ㆗備用。
                }
            }
            end_free = 0; // 如果出現意外（山窮水盡，到處都沒記憶體可用了）
            // 呼叫第㆒級配置器，看看 out-of-memory 機制能否盡點力
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
            // 這會導致擲出異常（exception），或記憶體不足的情況獲得改善。}
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            // 遞迴呼叫自己，為了修正 nobjs。
            return (chunk_alloc(size, nobjs));
        }
    }
#endif