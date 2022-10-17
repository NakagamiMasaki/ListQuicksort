/**
* @brief	双方向リスト イテレータ 手動テスト
* @data		2022/10/04
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"
#include "ManualTest_Iterator.h"

/**
* @namespace	ex02_Iterator
* @brief		イテレータのテスト
*/
namespace ex02_Iterator
{

/**
* @brief	イテレータの指す要素を取得する機能について、constのメソッドであるか
* @details	ID:2
*			イテレータの指す要素を取得する機能のテストです。
*			constな関数であるか確認しています。
*			有効にした時、コンパイルに失敗したら成功です。
*/
TEST(ConstIteratorAssign, FunctionIsConst)
{
#ifdef CAN_NOT_ASSIGN_TO_CONSTITERATOR_ELEMENT
	LinkedList<ScoreData> List;
	auto Itr = List.GetConstBegin();

	auto& Data = *Itr;
	Data.Score = 100;

	EXPECT_EQ(0, List.GetSize());
#else
	SUCCEED();
#endif
}

/**
* @brief	コンストなイテレータから非コンストなイテレータを作成できないことをチェック
* @details	ID:17
*			イテレータのコピー機能のテストです。
*			コンストなイテレータから非コンストなイテレータを作成できないことを確認しています。
*			有効にした時、コンパイルに失敗したら成功です。
*/
TEST(MakeIterator, FromConstIterator)
{
#ifdef CAN_NOT_COPY_FROM_CONST_ITERATOR
	
	LinkedList<ScoreData> List;
	auto ConstItr = List.GetConstBegin();

	LinkedList<ScoreData>::Iterator Itr(ConstItr);

	EXPECT_EQ(0, List.GetSize());
#else
	SUCCEED();
#endif
}

/**
* @brief	非コンストなイテレータにコンストなイテレータを代入できないことをチェック
* @details	ID:19
*			イテレータのコピー機能のテストです。
*			非コンストなイテレータにコンストなイテレータを代入できないことを確認しています。
*			有効にした時、コンパイルに失敗したら成功です。
*/
TEST(AssignIterator, FromConstIterator)
{
#ifdef CAN_NOT_ASSIGN_CONST_ITERATOR_TO_ITERATOR

	LinkedList<ScoreData> List;
	auto ConstItr = List.GetConstBegin();

	LinkedList<ScoreData>::Iterator Itr;
	Itr = ConstItr;

	EXPECT_EQ(0, List.GetSize());
#else
	SUCCEED();
#endif
}

}	// ex02_Iterator