/**
* @brief	双方向リスト実装
* @date		2022/10/06
*/

//===== インクルード =====
#include <assert.h>
#include "LinkedList.h"

//===== 関数定義 =====

//====== LinkedList::ConstIterator =====

template<class DataType>
LinkedList<DataType>::ConstIterator::ConstIterator(void)
	: m_pCurrentNode(nullptr)
	, m_pList(nullptr)
{
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator& LinkedList<DataType>::ConstIterator::operator--(void)
{
	// リストの先頭方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");									// リストを参照しているか？
	assert(m_pCurrentNode->pPrev != m_pList->m_pDummy && "This Iterator Is Begin");		// 先頭ノードを既に指しているのに、さらに前に進もうとしていないか？

	m_pCurrentNode = m_pCurrentNode->pPrev;
	return *this;
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator& LinkedList<DataType>::ConstIterator::operator++(void)
{
	// リストの末尾方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");						// リストを参照しているか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指しているのに、さらに進もうとしていないか？

	m_pCurrentNode = m_pCurrentNode->pNext;
	return *this;
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator LinkedList<DataType>::ConstIterator::operator--(int)
{
	// リストの先頭方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");									// リストを参照しているか？
	assert(m_pCurrentNode->pPrev != m_pList->m_pDummy && "This Iterator Is Begin");		// 先頭ノードを既に指しているのに、さらに前に進もうとしていないか？

	LinkedList::ConstIterator TempItr = *this;	// コピーする
	m_pCurrentNode = m_pCurrentNode->pPrev;

	return TempItr;
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator LinkedList<DataType>::ConstIterator::operator++(int)
{
	// リストの末尾方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");						// リストを参照しているか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指しているのに、さらに進もうとしていないか？

	LinkedList::ConstIterator TempItr = *this;	// コピーする
	m_pCurrentNode = m_pCurrentNode->pNext;

	return TempItr;
}

template<class DataType>
const DataType& LinkedList<DataType>::ConstIterator::operator*(void) const
{
	// 不正なイテレータでないことを確認する
	assert(IsValidReference() && "Invalid Reference");						// 適切な参照を持つか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指していないか？

	return m_pCurrentNode->Data;
}

template<class DataType>
LinkedList<DataType>::ConstIterator::ConstIterator(const ConstIterator& ConstItr)
	: m_pCurrentNode(ConstItr.m_pCurrentNode)
	, m_pList(ConstItr.m_pList)
{
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator& LinkedList<DataType>::ConstIterator::operator=(const ConstIterator& Itr)
{
	this->m_pCurrentNode = Itr.m_pCurrentNode;
	this->m_pList        = Itr.m_pList;
	return *this;
}

template<class DataType>
bool LinkedList<DataType>::ConstIterator::operator==(const ConstIterator& Itr) const
{
	return this->m_pCurrentNode == Itr.m_pCurrentNode;
}

template<class DataType>
bool LinkedList<DataType>::ConstIterator::operator!=(const ConstIterator& Itr) const
{
	return !(*this == Itr);
}

template<class DataType>
bool LinkedList<DataType>::ConstIterator::IsValid(void) const
{
	return IsValidReference() && !IsDummy();
}

template<class DataType>
bool LinkedList<DataType>::ConstIterator::IsValidReference(void) const
{
	return m_pList != nullptr && m_pCurrentNode != nullptr;
}

template<class DataType>
bool LinkedList<DataType>::ConstIterator::IsDummy(void) const
{
	if (!IsValidReference())
	{
		return false;
	}

	return m_pList->m_pDummy == m_pCurrentNode;		// 参照しているリストのダミーノードと一致しているか？
}

//====== LinkedList::Iterator =====

template<class DataType>
DataType& LinkedList<DataType>::Iterator::operator* (void)
{
	// 不正なイテレータでないことを確認する。
	assert(this->IsValidReference() && "Invalid Reference");						// 適切な参照を持つか？
	assert(!this->IsDummy() && "This Iterator Is End, Reference To DummyNode");		// ダミーノードを指していないか？

	return this->m_pCurrentNode->Data;
}

//===== LinkedList =====

template<class DataType>
LinkedList<DataType>::LinkedList(void)
	: m_ElementCount(0)
	, m_pDummy(nullptr)
{
	m_pDummy = new Node;
	m_pDummy->pNext = m_pDummy;
	m_pDummy->pPrev = m_pDummy;
}

template<class DataType>
LinkedList<DataType>::~LinkedList(void)
{
	Clear();

	// ダミーノードを解放する
	delete m_pDummy;
}

template<class DataType>
size_t LinkedList<DataType>::GetSize(void) const
{
	return m_ElementCount;
}

template<class DataType>
bool LinkedList<DataType>::Insert(ConstIterator& Itr, const DataType& Data)
{
	//*** イテレータの有効性をチェック
	if (!Itr.m_pCurrentNode || Itr.m_pList != this)
	{
		return false;
	}

	//*** 新しい要素を渡されたイテレータの前に挿入する
	// 新しいノードを作成する
	Node* pNode = new Node;		// 新しいノード

	// 初期化
	pNode->Data = Data;	// データを設定

	// ポインタを繋ぎなおす
	pNode->pPrev                     = Itr.m_pCurrentNode->pPrev;
	pNode->pNext                     = Itr.m_pCurrentNode;
	Itr.m_pCurrentNode->pPrev->pNext = pNode;
	Itr.m_pCurrentNode->pPrev        = pNode;

	// 要素数を更新
	++m_ElementCount;

	return true;
}

template<class DataType>
bool LinkedList<DataType>::Delete(ConstIterator& Itr)
{
	// 要素数のチェック
	if (m_ElementCount == 0)
	{
		return false;
	}

	// イテレータが不正でないことをチェック
	if (!Itr.m_pCurrentNode || Itr.m_pList != this)
	{
		return false;
	}

	// ダミーノードを指していないかチェック
	if (Itr.m_pCurrentNode == m_pDummy)
	{
		return false;
	}

	// ポインタを繋ぎなおす
	Itr.m_pCurrentNode->pPrev->pNext = Itr.m_pCurrentNode->pNext;
	Itr.m_pCurrentNode->pNext->pPrev = Itr.m_pCurrentNode->pPrev;

	// 解放
	delete Itr.m_pCurrentNode;
	Itr.m_pCurrentNode = nullptr;

	// 要素数を更新
	--m_ElementCount;

	return true;
}

template<class DataType>
void LinkedList<DataType>::Clear(void)
{
	// 全てのデータを削除する
	while (m_ElementCount > 0)
	{
		auto Itr = GetBegin();
		Delete(Itr);
	}
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator LinkedList<DataType>::GetConstBegin(void) const
{
	// 先頭のノードを指すイテレータを返す
	ConstIterator Itr;
	Itr.m_pCurrentNode = m_pDummy->pNext;
	Itr.m_pList        = this;

	return Itr;
}

template<class DataType>
typename LinkedList<DataType>::Iterator LinkedList<DataType>::GetBegin(void)
{
	// 先頭のノードを指すイテレータを返す
	Iterator Itr;
	Itr.m_pCurrentNode = m_pDummy->pNext;
	Itr.m_pList        = this;

	return Itr;
}

template<class DataType>
typename LinkedList<DataType>::ConstIterator LinkedList<DataType>::GetConstEnd(void) const
{
	// 常にダミーノードを指すイテレータを返す
	ConstIterator Itr;
	Itr.m_pCurrentNode = m_pDummy;
	Itr.m_pList        = this;

	return Itr;
}

template<class DataType>
typename LinkedList<DataType>::Iterator LinkedList<DataType>::GetEnd(void)
{
	// 常にダミーノードを指すイテレータを返す
	Iterator Itr;
	Itr.m_pCurrentNode = m_pDummy;
	Itr.m_pList        = this;

	return Itr;
}

template<class DataType>
template<class CompareFunc>
void LinkedList<DataType>::Quicksort(ConstIterator First, ConstIterator Last, CompareFunc CompFunc)
{
	//*** もしLastが末尾イテレータの場合、要素にアクセスできないのでデクリメントする
	// もし要素数が0なら、ソートもデクリメントもできないのでしない
	if (m_ElementCount < 1)
	{
		return;
	}
	if (Last == GetConstEnd())
	{
		--Last;
	}

	//*** ソート実行
	QuicksortImpl(First, Last, CompFunc);
}

template<class DataType>
int LinkedList<DataType>::Distance(const ConstIterator& First, const ConstIterator& Last) const
{
	//*** 引数のチェック
	// このリストへの参照を持っているか?
	if (First.m_pList != this || Last.m_pList != this)
	{
		return LIST_DISTANCE_ERROR_INVALID_REFERENCE;
	}
	// その他、不正なイテレータではないか？
	if (!First.IsValid())
	{
		return LIST_DISTANCE_ERROR_INVALID_ITERATOR;
	}

	int Count = 0;						// カウンタ
	ConstIterator CopiedFirst = First;	// コピーしておく
	ConstIterator EndItr = GetConstEnd();

	//*** インクリメントを何回したらLastに到達するかカウントする
	while (true)
	{
		// Lastと一致したか？
		if (CopiedFirst == Last)
		{
			break;
		}

		// 末尾に到達したか？
		if (CopiedFirst == EndItr)
		{
			return LIST_DISTANCE_ERROR_UNREACHABLE;
		}

		// カウンタがオーバーフローしないように止める
		// 要素数をsize_tで持っているので、指定範囲によってはオーバーフローを引き起こす可能性がある。
		if (Count == INT_MAX)
		{
			return Count;
		}

		// インクリメント
		++Count;
		++CopiedFirst;
	}

	// カウントした値を返す
	return Count;
}

template<class DataType>
template<class CompareFunc>
void LinkedList<DataType>::QuicksortImpl(const ConstIterator& First, const ConstIterator& Last, CompareFunc& CompFunc)
{
	//*** FirstとLastの距離を計算する
	{
		auto Dist = Distance(First, Last);
		if (Dist <= 0)
		{
			// -1の時はFirstとLastが逆転している
			// 0はFirst == Lastの時
			// どちらも値の入れ替えは不要
			return;
		}
	}

	auto Pivot                = *First;	// 閾値のコピー
	ConstIterator CopiedFirst = First;
	ConstIterator CopiedLast  = Last;

	while (true)
	{
		// 左から順に見ていって、pivotとCompFuncで比べた時に
		// 最初にtrueが返るものを見つける
		while (Last != CopiedFirst && CompFunc(*CopiedFirst, Pivot))
		{
			++CopiedFirst;
		}

		// 右から順に見ていって、pivotとCompFuncで比べた時に
		// 最初にfalseが返るものを見つける
		while (First != CopiedLast && !CompFunc(*CopiedLast, Pivot))
		{
			--CopiedLast;
		}

		// もし2つのイテレータが交差していたなら、
		// この集合のソートは完了している
		if (Distance(CopiedFirst, CopiedLast) <= 0)
		{
			break;
		}

		// 2つのイテレータの値を入れ替える
		SwapNode(CopiedFirst.m_pCurrentNode, CopiedLast.m_pCurrentNode);

		// 次の要素へ
		++CopiedFirst;
		--CopiedLast;
	}

	const auto Begin = GetConstBegin();
	const auto End   = GetConstEnd();

	// 左側の集合に対してソートを行う
	if (Begin != CopiedFirst)
	{
		// Begin == CopiedFirst が成立するとき
		// デクリメントをしてしまうとAssertが発生するので
		// if で囲んでいる
		Quicksort(First, --CopiedFirst, CompFunc);
	}

	// 右側の集合に対してソートを行う
	if (End != CopiedLast)
	{
		// End == CopiedLast が成立するとき
		// インクリメントをしてしまうとAssertが発生するので
		// if で囲んでいる
		Quicksort(++CopiedLast, Last, CompFunc);
	}
}

template<class DataType>
void LinkedList<DataType>::SwapNode(Node* pLeft, Node* pRight)
{
	//*** 三角交換を行う
	auto Copy      = pRight->Data;	// コピー
	pRight->Data   = pLeft->Data;
	pLeft->Data    = Copy;
}