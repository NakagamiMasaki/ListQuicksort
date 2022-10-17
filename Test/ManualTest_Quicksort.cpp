/**
* @brief	クイックソートのテスト
* @date		2022/10/14
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"
#include "ManualTest_Quicksort.h"

//===== 名前空間 =====
/**
* @brief	クイックソートのテスト用名前空間
*/
namespace ex04_Quicksort
{

/**
* @brief	型などが不適切なキー指定が引数で渡された時の挙動
* @details	ID:7
*			クイックソートのテストです。
*			型が不適切な引数を渡したときにコンパイルエラーになることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(QuickSort, InvalidCompFuncType)
{
#ifdef LIST_QUICKSORT_INVALID_COMPFUNC_TYPE
	LinkedList<ScoreData> List;

	// 何も受け取らない、何も返さない関数オブジェクトを渡してみる
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), []() {});
#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID:8
*			クイックソートのテストです。
*			非コンストな関数であることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(QuickSort, QuicksortIsConst)
{
#ifdef LIST_QUICKSORT_IS_NOT_CONST
	const LinkedList<ScoreData> List;

	// constなリストから呼び出してみる
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd());
#else
	SUCCEED();
#endif
}

/**
* @brief	Distanceがconstのメソッドであるか
* @details	ID:19
*			クイックソートのテストです。
*			非コンストな関数であることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(Distance, IsConst)
{
#ifdef LIST_DISTANCE_IS_CONST
	const LinkedList<ScoreData> List;

	// constなリストから呼び出してみる
	List.Distance(List.GetConstBegin(), List.GetConstEnd());
#else
	SUCCEED();
#endif
}

}	// ex04_Quicksort
