#pragma once

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"

//===== クラス定義 =====
/**
* @class	LinkedListTestFixture
* @brief	複数要素が既に入っているリストの準備を簡略化するためのフィクスチャ
*/
class LinkedListTestFixture : public ::testing::Test
{
	//=== メンバ変数
protected:

	LinkedList<ScoreData>* pList;	// リスト

	//=== メンバ関数
protected:

	virtual void SetUp(void)
	{
		pList = new LinkedList<ScoreData>;
		ScoreData Data;

		//*** データを3件末尾に挿入する
		Data.Score = 0;
		Data.Name = "Test0";
		auto Itr = pList->GetEnd();
		pList->Insert(Itr, Data);

		Data.Score = 1;
		Data.Name = "Test1";
		Itr = pList->GetEnd();
		pList->Insert(Itr, Data);

		Data.Score = 2;
		Data.Name = "Test2";
		Itr = pList->GetEnd();
		pList->Insert(Itr, Data);
	}

	virtual void TearDown(void)
	{
		delete pList;
	}
};

//===== 関数定義 =====

/**
* @fn		TestListItem(LinkedList<ScoreData>&, ScoreData*, size_t)
* @brief	リスト内にデータが順番に入っているかチェックする。
*/
inline void TestListItem(LinkedList<ScoreData>& List, ScoreData* pData, size_t DataCount)
{
	ASSERT_TRUE(List.GetSize() == DataCount);
	ASSERT_TRUE(pData);
	ASSERT_GT(DataCount, 0u);

	//*** 先頭から順番に確認していく
	auto Itr = List.GetBegin();
	for (decltype(DataCount) i = 0; i < DataCount; ++i)
	{
		// 正しいかチェック
		auto& Data = *Itr;
		EXPECT_EQ(pData[i].Score, Data.Score);
		EXPECT_EQ(pData[i].Name, Data.Name);

		++Itr;
	}
}
