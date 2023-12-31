#include "sort_type.h"


void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}

void bubbleSort()
{
	bool swapped;
	for (int i = 0; i < numElements; i++)
	{
		swapped = false;
		for (int j = 0; j < numElements - i - 1; j++)
		{
			draw(j, j + 1);
			if (arrayElements[j] > arrayElements[j + 1])
			{
				swap(&arrayElements[j], &arrayElements[j + 1]);
				bool swapped = true;
				Sleep(sTime);
				draw(j, j + 1);
			}
			comparisons++;
		}
		isSorted[numElements - i - 1] = true;
		draw(-1, -1);
		if (swapped = false)
		{
			break;
		}
	}
}

void selectionSort()
{
	int i, j, min_index;
	for (i = 0; i < numElements - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < numElements; j++)
		{
			draw(min_index, j);
			if (arrayElements[j] < arrayElements[min_index])
			{
				min_index = j;
			}
			Sleep(sTime);
			comparisons++;
		}
		swap(&arrayElements[min_index], &arrayElements[i]);
		isSorted[i] = true;
		draw(-1, -1);
	}
	Sleep(sTime);
	isSorted[numElements - 1] = true;
	draw(-1, -1);
}

void insertionSort()
{
	int i, j, key;
	isSorted[0] = true;
	draw(-1, -1);
	for (i = 1; i < numElements; i++)
	{
		key = arrayElements[i];
		j = i - 1;
		Sleep(sTime);
		draw(i, j);
		comparisons++;
		while (j >= 0 && arrayElements[j] > key)
		{
			draw(j, j + 1);
			arrayElements[j + 1] = arrayElements[j];
			arrayElements[j] = key;
			Sleep(sTime);
			draw(j, j + 1);
			isSorted[i] = true;
			draw(-1, -1);
			j = j - 1;
			comparisons++;
		}
		isSorted[i] = true;
		draw(-1, -1);
	}
}

int partition(int l, int r)
{
	int pivot = arrayElements[r];
	comparisons++;
	int i = (l - 1);
	for (int j = l; j <= r - 1; j++)
	{
		draw(i, j);
		comparisons++;
		if (arrayElements[j] < pivot)
		{
			i++;
			swap(&arrayElements[i], &arrayElements[j]);
		}
		Sleep(sTime);
		draw(i, j);
	}
	draw(i + 1, r);
	swap(&arrayElements[i + 1], &arrayElements[r]);
	Sleep(sTime);
	draw(i + 1, r);
	return (i + 1);
}

void quickSort(int l, int r)
{
	if (l < r)
	{
		int p = partition(l, r);
		isSorted[p] = true;
		Sleep(sTime);
		draw(-1, 1);
		quickSort(l, p - 1);
		quickSort(p + 1, r);
	}
	else if (l == r) {
		isSorted[l] = true;
		draw(-1, -1);
	}
}

void merge(int l, int m, int r)
{
	int leftEnd = m - l + 1;
	int rightStart = r - m;
	std::vector<float> L(leftEnd), R(rightStart);

	for (int i = 0; i < leftEnd; i++)
		L[i] = arrayElements[l + i];
	for (int j = 0; j < rightStart; j++)
		R[j] = arrayElements[m + 1 + j];
	int i = 0, j = 0, k = l;

	while (i < leftEnd && j < rightStart)
	{
		if (L[i] <= R[j])
			arrayElements[k] = L[i++];
		else
			arrayElements[k] = R[j++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
	while (i < leftEnd) {
		arrayElements[k] = L[i++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
	while (j < rightStart) {
		arrayElements[k] = R[j++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
}

void mergeSort(int l, int r)
{
	if (l >= r) {
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(l, m);
	mergeSort(m + 1, r);
	merge(l, m, r);
}
