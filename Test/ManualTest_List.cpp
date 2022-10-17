/**
* @brief	双方向リスト 手動テスト
* @data		2022/10/04
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"
#include "ManualTest_List.h"

/**
* @namespace	ex01_LinkedList
* @brief		双方向リストのテスト
*/
namespace ex01_ManualTest
{

/**
* @brief	データ件数取得機能について、constのメソッドであるか
* @details	ID:8
*			データ件数取得のテストです。
*			constな関数であるか確認しています。
*			有効にした時、コンパイルが通れば成功です。
*/
TEST(GetDataNum, FunctionIsConst)
{
#ifdef LIST_GETSIZE_IS_CONST
	const LinkedList<ScoreData> List;
	EXPECT_EQ(0, List.GetSize());
#else
	SUCCEED();
#endif
}

/**
* @brief	データ挿入機能について、非constのメソッドであるか
* @details	ID:15
*			データ挿入取得のテストです。
*			非constな関数であるか確認しています。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(InsertData, FunctionIsNotConst)
{
#ifdef LIST_INSERT_IS_NOT_CONST
	
	const LinkedList<ScoreData> List;
	auto Itr = List.GetConstBegin();

	ScoreData Data;
	Data.Score = 15;
	Data.Name = "Test15";

	EXPECT_TRUE(List.Insert(Itr, Data));
#else
	SUCCEED();
#endif
}

/**
* @brief	データ削除機能について、非constのメソッドであるか
* @details	ID:22
*			データ削除取得のテストです。
*			非constな関数であるか確認しています。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(DeleteData, FunctionIsNotConst)
{
#ifdef LIST_DELETE_IS_NOT_CONST

	const LinkedList<ScoreData> List;
	auto Itr = List.GetConstBegin();
	EXPECT_TRUE(List.Delete(Itr));
#else
	SUCCEED();
#endif
}

/**
* @brief	constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
* @details	ID:28
*			先頭イテレータ取得のテストです。
*			非constな関数であるか確認しています。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(GetBeginIterator, FunctionIsNotConst)
{
#ifdef LIST_GETBEGIN_IS_NOT_CONST

	const LinkedList<ScoreData> List;
	List.GetBegin();

#else
	SUCCEED();
#endif
}

/**
* @brief	constな先頭イテレータ取得機能について、constな関数かチェック
* @details	ID:34
*			先頭イテレータ取得のテストです。
*			constな関数であるか確認しています。
*			有効にした時、コンパイルが通れば成功です。
*/
TEST(GetBeginConstIterator, FunctionIsConst)
{
#ifdef LIST_GETCONSTBEGIN_IS_CONST

	const LinkedList<ScoreData> List;
	List.GetConstBegin();

#else
	SUCCEED();
#endif
}

/**
* @brief	constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
* @details	ID:40
*			末尾イテレータ取得のテストです。
*			非constな関数であるか確認しています。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(GetEndIterator, FunctionIsNotConst)
{
#ifdef LIST_GETEND_IS_NOT_CONST

	const LinkedList<ScoreData> List;
	List.GetEnd();

#else
	SUCCEED();
#endif
}

/**
* @brief	constな先頭イテレータ取得機能について、constな関数かチェック
* @details	ID:34
*			末尾イテレータ取得のテストです。
*			constな関数であるか確認しています。
*			有効にした時、コンパイルが通れば成功です。
*/
TEST(GetEndConstIterator, FunctionIsConst)
{
#ifdef LIST_GETCONSTEND_IS_CONST

	const LinkedList<ScoreData> List;
	List.GetConstEnd();

#else
	SUCCEED();
#endif
}

/**
* @brief	リストをコピーできないことを確認する
* @details	ID:ex0
*			リストのコピーに関するテストです。
*			リストがコピー禁止になっていることを確認します。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(CopyList, NonCopyable)
{
#ifdef LIST_CANNOT_COPY
	
	LinkedList<ScoreData> List1;
	LinkedList<ScoreData> List2(List1);	// コピーコンストラクタ呼び出し

	// コピー代入も試してみる
	List2 = List1;

#else
	SUCCEED();
#endif
}

/**
* @brief	リストをムーブできないことを確認する
* @details	ID:ex1
*			リストのムーブに関するテストです。
*			リストがムーブ禁止になっていることを確認します。
*			有効にした時、コンパイルが通らなければ成功です。
*/
TEST(MoveList, NonMovable)
{
#ifdef LIST_CANNOT_MOVE

	LinkedList<ScoreData> List1;
	LinkedList<ScoreData> List2(std::move(List1));	// ムーブコンストラクタ呼び出し

	// ムーブ代入も試してみる
	List2 = std::move(List1);

#else
	SUCCEED();
#endif
}


}	// ex01_ManualTest