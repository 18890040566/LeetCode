struct mid_value_t
{
    int mid;
    int flag;
    int count;
    int parity;
    int count1;
    int count2;

};

void find_mid(struct mid_value_t *mid_value, int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    while (mid_value->count < mid_value->mid)
    {
        if (nums1[mid_value->count1] <= nums2[mid_value->count2])
        {
            mid_value->count1++;
            mid_value->flag = 0;
        }
        else
        {
            mid_value->count2++;
            mid_value->flag = 2;
        }

        mid_value->count = mid_value->count1 + mid_value->count2;

        if (mid_value->count1 == nums1Size)
        {
            if (mid_value->count == mid_value->mid)
                break;

            mid_value->flag = 1;
            break;
        }
        else if (mid_value->count2 == nums2Size)
        {
            if (mid_value->count == mid_value->mid)
                break;

            mid_value->flag = 3;
            break;
        }
    }
}

void uneven_mid(struct mid_value_t *mid_value, int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    if (mid_value->flag == 1)
    {
        if (mid_value->count1 + mid_value->count2 + 2 == mid_value->mid)
        {
            mid_value->count1 =  nums2[mid_value->count2];
            mid_value->count2 =  mid_value->count1;
        }
        else
        {
            mid_value->count2 = mid_value->mid - mid_value->count1 - 2;
            mid_value->count1 =  nums2[mid_value->count2];
            mid_value->count2 =  mid_value->count1;
        }
    }
    else if (mid_value->flag == 3)
    {
        if (mid_value->count1 + mid_value->count2 + 2 == mid_value->mid)
        {
            mid_value->count1 =  nums1[mid_value->count1];
            mid_value->count2 =  mid_value->count1;
        }
        else
        {
            mid_value->count1 = mid_value->mid - mid_value->count2 - 2;
            mid_value->count1 =  nums1[mid_value->count1];
            mid_value->count2 =  mid_value->count1;
        }
    }
    else if (mid_value->flag == 0)
    {
        mid_value->count1 =  nums1[mid_value->count1];
        mid_value->count2 =  mid_value->count1;
    }
    else if (mid_value->flag == 2)
    {
        mid_value->count1 =  nums2[mid_value->count2];
        mid_value->count2 =  mid_value->count1;
    }
}

void even_mid(struct mid_value_t *mid_value, int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    if (mid_value->flag == 1)
    {
        if (mid_value->count1 + mid_value->count2 + 2 == mid_value->mid)
        {
            mid_value->count1 = nums2[mid_value->count2 + 1];
            mid_value->count2 = nums2[mid_value->count2];
        }
        else
        {
            mid_value->count2 = mid_value->mid - mid_value->count1 - 2;
            mid_value->count1 =  mid_value->count2;
            mid_value->count1 =  nums2[mid_value->count1];
            mid_value->count2 =  nums2[mid_value->count2 + 1];
        }
    }
    else if (mid_value->flag == 3)
    {
        if (mid_value->count1 + mid_value->count2 + 2 == mid_value->mid)
        {
            mid_value->count2 = nums1[mid_value->count1 + 1];
            mid_value->count1 = nums1[mid_value->count1];
        }
        else
        {
            mid_value->count1 = mid_value->mid - mid_value->count2 - 2;
            mid_value->count2 =  mid_value->count1;
            mid_value->count1 =  nums1[mid_value->count1];
            mid_value->count2 =  nums1[mid_value->count2 + 1];
        }
    }
    else if (mid_value->flag == 0)
    {
        if (mid_value->count1 == nums1Size - 1)
        {
            mid_value->count1 = nums1[mid_value->count1];
            mid_value->count2 = nums2[mid_value->count2];
        }
        else
        {
            mid_value->count2 = nums1[mid_value->count1 + 1] > nums2[mid_value->count2] ? \
                                nums2[mid_value->count2] : nums1[mid_value->count1 + 1];
            mid_value->count1 = nums1[mid_value->count1];
        }
    }
    else if (mid_value->flag == 2)
    {
        if (mid_value->count2 == nums2Size - 1)
        {
            mid_value->count1 = nums1[mid_value->count1];
            mid_value->count2 = nums2[mid_value->count2];
        }
        else
        {
            mid_value->count1 = nums1[mid_value->count1] > nums2[mid_value->count2 + 1] ? \
                                nums2[mid_value->count2 + 1] : nums1[mid_value->count1];
            mid_value->count2 = nums2[mid_value->count2];
        }
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    double value = 0;;
    struct mid_value_t mid_value;
    
    mid_value.flag = 0;
    mid_value.count = 0;
    mid_value.count1 = 0;
    mid_value.count2 = 0;
    mid_value.parity = (nums1Size + nums2Size) & 0x01;

    if (mid_value.parity)
        mid_value.mid = (nums1Size + nums2Size + 1) / 2;
    else
        mid_value.mid = (nums1Size + nums2Size) / 2;

    if (nums1Size == 0)
    {
        if (mid_value.parity)
            value = (double)nums2[mid_value.mid - 1];
        else
            value = (double)((double)((nums2[mid_value.mid - 1] + nums2[mid_value.mid])) / 2.0);
        return value;
    }
    else if (nums2Size == 0)
    {
        if (mid_value.parity)
            value = (double)(nums1[mid_value.mid - 1]);
        else
            value = (double)((double)((nums1[mid_value.mid - 1] + nums1[mid_value.mid])) / 2);
        return value;
    }

    find_mid(&mid_value, nums1, nums1Size, nums2, nums2Size);

    if (mid_value.flag == 0 || mid_value.flag == 1)
        mid_value.count1--;
    else if (mid_value.flag == 2 || mid_value.flag == 3)
        mid_value.count2--;

    if (mid_value.parity)
        uneven_mid(&mid_value, nums1, nums1Size, nums2, nums2Size);
    else
        even_mid(&mid_value, nums1, nums1Size, nums2, nums2Size);

    value = (double)((double)(mid_value.count1 + mid_value.count2) / 2.0);

    return value;
}
