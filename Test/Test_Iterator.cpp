/**
* @brief	イテレータの単体テスト用
* @data		2022/10/04
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"
#include "TestHelper.h"

/**
* @namespace	ex02_Iterator
* @brief		イテレータのテスト
*/
namespace ex02_Iterator
{

//===== 型エイリアス =====

using IteratorIncrementF       = LinkedListTestFixture;
using IteratorDecrementF       = LinkedListTestFixture;
using IteratorCopyConstractorF = LinkedListTestFixture;
using IteratorCopyAssignmentF  = LinkedListTestFixture;
using IteratorCompareEQF       = LinkedListTestFixture;
using IteratorCompareNEF       = LinkedListTestFixture;

#pragma region ***** イテレータの指す要素を取得する *****

/**
* @brief	リストの参照がない状態で呼び出した際の挙動
* @details	ID:0
*			イテレータの指す要素を取得するテストです。
*			リストの参照がないイテレータから要素を取り出そうとした時の挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(GetIteratorData, InvalidReference)
{
#ifdef _DEBUG

	// 非コンストイテレータ
	LinkedList<ScoreData>::Iterator Itr;
	EXPECT_DEATH(*Itr, ".*Invalid Reference.*");

	// コンストイテレータ
	LinkedList<ScoreData>::ConstIterator ConstItr;
	EXPECT_DEATH(*ConstItr, ".*Invalid Reference.*");
#else
	SUCCEED();
#endif
}

/**
* @brief	Iteratorから取得した要素に対して、値の代入が行えるかをチェック
* @details	ID:1
*			イテレータの指す要素を取得するテストです。
*			イテレータから取得した要素に代入ができるかの確認をします。
*			値を代入したあと、再び取得した時にデータが変わっていたら成功です。
*/
TEST(GetIteratorData, AfterAssignment)
{
	// 1件データを追加しておく
	LinkedList<ScoreData> List;
	ScoreData Data{ 0, "Test0" };
	auto EndItr = List.GetEnd();
	List.Insert(EndItr, Data);

	// 値を代入する
	auto Itr = List.GetBegin();
	auto& Element = *Itr;
	Element = { 1, "Test1" };

	// イテレータを取得しなおして確認する
	Itr = List.GetBegin();
	auto& TestData = *Itr;
	EXPECT_EQ(1, TestData.Score);
	EXPECT_EQ("Test1", TestData.Name);
}

/**
* @brief	リストが空の際の、先頭イテレータに対して呼び出した際の挙動
* @details	ID:3
*			イテレータの指す要素を取得するテストです。
*			リストが空の時、先頭イテレータから要素を取り出そうとしたときの挙動の確認をします。
*			Assertが発生したら成功です。
*/
TEST(GetIteratorData, EmptyListBeginIterator)
{
#ifdef _DEBUG
	// 空のリストを用意する
	LinkedList<ScoreData> List;

	// 非コンストイテレータを取得して確認する
	auto Itr = List.GetBegin();
	EXPECT_DEATH(*Itr, ".*Reference To DummyNode.*");

	// コンストイテレータを取得して確認する
	auto ConstItr = List.GetConstBegin();
	EXPECT_DEATH(*ConstItr, ".*Reference To DummyNode.*");

#else
	SUCCEED();
#endif
}

/**
* @brief	末尾イテレータに対して呼び出した際の挙動
* @details	ID:4
*			イテレータの指す要素を取得するテストです。
*			リストが空の時、末尾イテレータから要素を取り出そうとしたときの挙動の確認をします。
*			Assertが発生したら成功です。
*/
TEST(GetIteratorData, EndIterator)
{
#ifdef _DEBUG
	// 空のリストを用意する
	LinkedList<ScoreData> List;

	// 非コンストイテレータを取得して確認する
	auto Itr = List.GetEnd();
	EXPECT_DEATH(*Itr, ".*Reference To DummyNode.*");

	// コンストイテレータを取得して確認する
	auto ConstItr = List.GetConstEnd();
	EXPECT_DEATH(*ConstItr, ".*Reference To DummyNode.*");
#else
	SUCCEED();
#endif
}

#pragma endregion

#pragma region ***** イテレータをリストの末尾に向かって一つ進める *****

/**
* @brief	リストの参照がない状態で呼び出した際の挙動
* @details	ID:5
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			リストの参照がないとき、末尾に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorIncrement, InvalidReference)
{
#ifdef _DEBUG

	// 非コンストイテレータ
	LinkedList<ScoreData>::Iterator Itr;
	EXPECT_DEATH(++Itr, ".*Invalid Reference.*");

	// コンストイテレータ
	LinkedList<ScoreData>::ConstIterator ConstItr;
	EXPECT_DEATH(++ConstItr, ".*Invalid Reference.*");

#else
	SUCCEED();
#endif
}

/**
* @brief	リストが空の際の、先頭イテレータに対して呼び出した際の挙動
* @details	ID:6
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			リストが空の時、末尾に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorIncrement, EmptyListBeginIterator)
{
#ifdef _DEBUG

	// 空のリストを用意する
	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	auto Itr = List.GetBegin();
	EXPECT_DEATH(++Itr, ".*This Iterator Is End.*");	// 要素数が0なら末尾イテレータが返るのを利用する

	// コンストイテレータ
	auto ConstItr = List.GetConstBegin();
	EXPECT_DEATH(++ConstItr, ".*This Iterator Is End.*");	// 要素数が0なら末尾イテレータが返るのを利用する

#else
	SUCCEED();
#endif
}

/**
* @brief	末尾イテレータに対して呼び出した際の挙動
* @details	ID:7
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			末尾イテレータを末尾に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorIncrement, EndIterator)
{
#ifdef _DEBUG

	// 空のリストを用意する
	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	auto Itr = List.GetEnd();
	EXPECT_DEATH(++Itr, ".*This Iterator Is End.*");

	// コンストイテレータ
	auto ConstItr = List.GetConstEnd();
	EXPECT_DEATH(++ConstItr, ".*This Iterator Is End.*");
#else
	SUCCEED();
#endif
}

/**
* @brief	リストに二つ以上の要素がある場合に呼び出した際の挙動
* @details	ID:8
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			先頭から末尾まで呼び出しを行い、期待される要素が入っているか確認します。
*			期待される要素が入っていれば成功です。
*/
TEST_F(IteratorIncrementF, BeginToEnd)
{
	ScoreData TestData[3] = {
		{ 0, "Test0" },
		{ 1, "Test1" },
		{ 2, "Test2" }
	};

	// コンストイテレータ
	auto Itr = pList->GetBegin();
	for (int i = 0; i < 3; ++i)
	{
		auto& Data = *Itr;

		// 正しいかチェック
		EXPECT_EQ(TestData[i].Score, Data.Score);
		EXPECT_EQ(TestData[i].Name, Data.Name);

		++Itr;
	}

	// 非コンストイテレータ
	auto ConstItr = pList->GetConstBegin();
	for (int i = 0; i < 3; ++i)
	{
		auto& Data = *ConstItr;

		// 正しいかチェック
		EXPECT_EQ(TestData[i].Score, Data.Score);
		EXPECT_EQ(TestData[i].Name, Data.Name);

		++ConstItr;
	}
}

/**
* @brief	前置インクリメントを行った際の挙動
* @details	ID:9
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			インクリメント時の値とインクリメント後の値を確認します。
*			次の要素を指していたら成功です。
*/
TEST_F(IteratorIncrementF, PrefixIncrement)
{
	// 非コンストイテレータ
	{
		// 先頭イテレータ
		auto Itr = pList->GetBegin();

		EXPECT_EQ(1, (*(++Itr)).Score);	// 前置インクリメントなので戻り値は変更後のはず
		EXPECT_EQ(1, (*Itr).Score);		// 次を指しているかチェック
	}

	// コンストイテレータ
	{
		// 先頭イテレータ
		auto ConstItr = pList->GetConstBegin();

		EXPECT_EQ(1, (*(++ConstItr)).Score);	// 前置インクリメントなので戻り値は変更後のはず
		EXPECT_EQ(1, (*ConstItr).Score);		// 次を指しているかチェック
	}
}

/**
* @brief	後置インクリメントを行った際の挙動
* @details	ID:10
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			インクリメント時の値とインクリメント後の値を確認します。
*			次の要素を指していたら成功です。
*/
TEST_F(IteratorIncrementF, PostfixIncrement)
{
	// 非コンストイテレータ
	{
		// 先頭イテレータ
		auto Itr = pList->GetBegin();

		EXPECT_EQ(0, (*(Itr++)).Score);	// 後置インクリメントなので戻り値は変更前のはず
		EXPECT_EQ(1, (*Itr).Score);		// 次を指しているかチェック
	}

	// コンストイテレータ
	{
		// 先頭イテレータ
		auto ConstItr = pList->GetConstBegin();

		EXPECT_EQ(0, (*(ConstItr++)).Score);	// 後置インクリメントなので戻り値は変更前のはず
		EXPECT_EQ(1, (*ConstItr).Score);		// 次を指しているかチェック
	}
}

#pragma endregion

#pragma region ***** イテレータをリストの先頭に向かって一つ進める *****

/**
* @brief	リストの参照がない状態で呼び出した際の挙動
* @details	ID:11
*			イテレータをリストの先頭に向かって一つ進めるテストです。
*			リストの参照がないとき、末尾に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorDecrement, InvalidReference)
{
#ifdef _DEBUG

	// 非コンストイテレータ
	LinkedList<ScoreData>::Iterator Itr;
	EXPECT_DEATH(--Itr, ".*Invalid Reference.*");

	// コンストイテレータ
	LinkedList<ScoreData>::ConstIterator ConstItr;
	EXPECT_DEATH(--ConstItr, ".*Invalid Reference.*");

#else
	SUCCEED();
#endif
}

/**
* @brief	リストが空の際の、末尾イテレータに対して呼び出した際の挙動
* @details	ID:12
*			イテレータをリストの末尾に向かって一つ進めるテストです。
*			リストが空の時、先頭に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorDecrement, EmptyListBeginIterator)
{
#ifdef _DEBUG
	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	auto Itr = List.GetEnd();
	EXPECT_DEATH(--Itr, ".*This Iterator Is Begin.*");

	// コンストイテレータ
	auto ConstItr = List.GetConstEnd();
	EXPECT_DEATH(--Itr, ".*This Iterator Is Begin.*");

#else
	SUCCEED();
#endif
}

/**
* @brief	先頭イテレータに対して呼び出した際の挙動
* @details	ID:13
*			イテレータをリストの先頭に向かって一つ進めるテストです。
*			先頭イテレータを先頭に向かって進めたときの挙動をチェックします。
*			Assertが発生したら成功です。
*/
TEST(IteratorDecrement, EndIterator)
{
#ifdef _DEBUG

	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	auto Itr = List.GetBegin();
	EXPECT_DEATH(--Itr, ".*This Iterator Is Begin.*");

	// コンストイテレータ
	auto ConstItr = List.GetConstBegin();
	EXPECT_DEATH(--ConstItr, ".*This Iterator Is Begin.*");

#else
	SUCCEED();
#endif
}

/**
* @brief	リストに二つ以上の要素がある場合に呼び出した際の挙動
* @details	ID:14
*			イテレータをリストの先頭に向かって一つ進めるテストです。
*			先頭から末尾まで呼び出しを行い、期待される要素が入っているか確認します。
*			期待される要素が入っていれば成功です。
*/
TEST_F(IteratorDecrementF, EndToBegin)
{
	ScoreData TestData[3] = {
		{ 2, "Test2" },
		{ 1, "Test1" },
		{ 0, "Test0" }
	};

	// 非コンストイテレータ
	{
		auto Itr = pList->GetEnd();
		for (int i = 0; i < 3; ++i)
		{
			--Itr;

			auto& Data = *Itr;

			// 正しいかチェック
			EXPECT_EQ(TestData[i].Score, Data.Score);
			EXPECT_EQ(TestData[i].Name, Data.Name);
		}
	}

	// コンストイテレータ
	{
		auto Itr = pList->GetConstEnd();
		for (int i = 0; i < 3; ++i)
		{
			--Itr;

			auto& Data = *Itr;
			EXPECT_EQ(TestData[i].Score, Data.Score);
			EXPECT_EQ(TestData[i].Name, Data.Name);
		}
	}
}

/**
* @brief	前置デクリメント行った際の挙動
* @details	ID:15
*			イテレータをリストの先頭に向かって一つ進めるテストです。
*			デクリメント時の値とデクリメント後の値を確認します。
*			前の要素を指していたら成功です。
*/
TEST_F(IteratorDecrementF, PrefixDecrement)
{
	// 非コンストな末尾イテレータ
	auto Itr = pList->GetEnd();

	EXPECT_EQ(2, (*(--Itr)).Score);	// 前置デクリメントなので戻り値は変更後のはず
	EXPECT_EQ(2, (*Itr).Score);		// 前を指しているかチェック

	// コンストな末尾イテレータ
	auto ConstItr = pList->GetConstEnd();

	EXPECT_EQ(2, (*(--ConstItr)).Score);	// 前置デクリメントなので戻り値は変更後のはず
	EXPECT_EQ(2, (*ConstItr).Score);		// 前を指しているかチェック
}

/**
* @brief	後置デクリメントを行った際の挙動
* @details	ID:16
*			イテレータをリストの先頭に向かって一つ進めるテストです。
*			デクリメント時の値とデクリメント後の値を確認します。
*			前の要素を指していたら成功です。
*/
TEST_F(IteratorDecrementF, PostfixDecrement)
{
	// 非コンストイテレータ
	{
		// 末尾イテレータ
		auto Itr = pList->GetEnd();

		--Itr;	// ここでデクリメントしておかないとダミーノードにアクセスしてしまう

		EXPECT_EQ(2, (*(Itr--)).Score);	// 後置デクリメントなので戻り値は変更前のはず
		EXPECT_EQ(1, (*Itr).Score);		// 前を指しているかチェック
	}

	// コンストイテレータ
	{
		// 末尾イテレータ
		auto ConstItr = pList->GetConstEnd();

		--ConstItr;	// ここでデクリメントしておかないとダミーノードにアクセスしてしまう

		EXPECT_EQ(2, (*(ConstItr--)).Score);	// 後置インクリメントなので戻り値は変更前のはず
		EXPECT_EQ(1, (*ConstItr).Score);		// 前を指しているかチェック
	}
}

#pragma endregion

#pragma region ***** イテレータのコピーを行う *****

/**
* @brief	コピーコンストラクト後の値がコピー元と等しいことをチェック
* @details	ID:18
*			コピーコンストラクタでコピーしたイテレータがコピー元と同一であることを確認するテストです。
*			コピーして作成したイテレータとコピー元が同一であれば成功です。
*/
TEST_F(IteratorCopyConstractorF, CopyConstractor)
{
	// 非コンストイテレータ
	{
		auto Itr = pList->GetBegin();

		// コピー
		LinkedList<ScoreData>::Iterator CopyItr(Itr);

		// チェック
		EXPECT_TRUE(CopyItr == Itr);
	}

	// コンストイテレータ
	{
		auto ConstItr = pList->GetConstBegin();

		// コピー
		LinkedList<ScoreData>::ConstIterator CopyItr(ConstItr);

		// チェック
		EXPECT_TRUE(CopyItr == ConstItr);
	}
}

#pragma endregion

#pragma region ***** イテレータの代入を行う *****

/**
* @brief	代入後の値がコピー元と等しいことをチェック
* @details	ID:20
*			コピー代入ででコピーしたイテレータがコピー元と同一であることを確認するテストです。
*			コピーして作成したイテレータとコピー元が同一であれば成功です。
*/
TEST_F(IteratorCopyAssignmentF, CopyAssignment)
{
	// 非コンストイテレータ
	{
		auto Itr = pList->GetBegin();

		// コピー
		LinkedList<ScoreData>::Iterator CopyItr;
		CopyItr = Itr;

		// チェック
		EXPECT_TRUE(CopyItr == Itr);
	}

	// コンストイテレータ
	{
		auto Itr = pList->GetConstBegin();

		// コピー
		LinkedList<ScoreData>::ConstIterator CopyItr;
		CopyItr = Itr;

		// チェック
		EXPECT_TRUE(CopyItr == Itr);
	}
}

#pragma endregion

#pragma region ***** 2つのイテレータが同一のものであるか比較を行う *****

/**
* @brief	リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
* @details	ID:21
*			空のリストから取得した先頭イテレータと末尾イテレータを比較するテストです。
*			trueが返れば成功です。
*/
TEST(IteratorCompareEQ, EmptyListBeginAndEnd)
{
	// 空のリストを用意する
	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	{
		auto BeginItr = List.GetBegin();
		auto EndItr = List.GetEnd();

		// 同一であるか確認
		EXPECT_TRUE(BeginItr == EndItr);
	}

	// コンストイテレータ
	{
		auto BeginItr = List.GetConstBegin();
		auto EndItr = List.GetConstEnd();

		// 同一であるか確認
		EXPECT_TRUE(BeginItr == EndItr);
	}
}

/**
* @brief	同一のイテレータを比較した際の挙動
* @details	ID:22
*			同一のイテレータどうしで比較した時の挙動をチェックします。
*			trueが返れば成功です。
*/
TEST_F(IteratorCompareEQF, SameIterator)
{
	// 非コンストイテレータ
	{
		auto BeginItr = pList->GetBegin();
		auto Itr = pList->GetBegin();

		// 同一であるか確認
		EXPECT_TRUE(BeginItr == Itr);
	}

	// コンストイテレータ
	{
		auto BeginItr = pList->GetConstBegin();
		auto Itr = pList->GetConstBegin();

		// 同一であるか確認
		EXPECT_TRUE(BeginItr == Itr);
	}
}

/**
* @brief	異なるイテレータを比較した際の挙動
* @details	ID:23
*			異なるイテレータどうしで比較した時の挙動をチェックします。
*			falseが返れば成功です。
*/
TEST_F(IteratorCompareEQF, DiffrentIterator)
{
	// 非コンストイテレータ
	{
		auto BeginItr = pList->GetBegin();
		auto Itr = pList->GetBegin();

		++Itr;	// ずらすことで別のイテレータにする

		// 同一であるか確認
		EXPECT_FALSE(BeginItr == Itr);
	}

	// コンストイテレータ
	{
		auto BeginItr = pList->GetConstBegin();
		auto Itr = pList->GetConstBegin();

		++Itr;	// ずらすことで別のイテレータにする

		// 同一であるか確認
		EXPECT_FALSE(BeginItr == Itr);
	}
}

#pragma endregion

#pragma region ***** 2つのイテレータが異なるのものであるか比較を行う *****

/**
* @brief	リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
* @details	ID:24
*			空のリストから取得した先頭イテレータと末尾イテレータを比較するテストです。
*			falseが返れば成功です。
*/
TEST(IteratorCompareNE, EmptyListBeginAndEnd)
{
	// 空のイテレータ
	LinkedList<ScoreData> List;

	// 非コンストイテレータ
	{
		auto BeginItr = List.GetBegin();
		auto EndItr = List.GetEnd();

		// 異なるか確認
		EXPECT_FALSE(BeginItr != EndItr);
	}

	// コンストイテレータ
	{
		auto BeginItr = List.GetConstBegin();
		auto EndItr = List.GetConstEnd();

		// 異なるか確認
		EXPECT_FALSE(BeginItr != EndItr);
	}
}

/**
* @brief	同一のイテレータを比較した際の挙動
* @details	ID:25
*			同一のイテレータどうしで比較した時の挙動をチェックします。
*			falseが返れば成功です。
*/
TEST_F(IteratorCompareNEF, SameIterator)
{
	// 非コンストイテレータ
	{
		auto BeginItr = pList->GetBegin();
		auto Itr = pList->GetBegin();

		// 異なるか確認
		EXPECT_FALSE(BeginItr != Itr);
	}

	// コンストイテレータ
	{
		auto BeginItr = pList->GetConstBegin();
		auto Itr = pList->GetConstBegin();

		// 異なるか確認
		EXPECT_FALSE(BeginItr != Itr);
	}
}

/**
* @brief	異なるイテレータを比較した際の挙動
* @details	ID:26
*			異なるイテレータどうしで比較した時の挙動をチェックします。
*			trueが返れば成功です。
*/
TEST_F(IteratorCompareNEF, DiffrentIterator)
{
	// コンストイテレータ
	{
		auto BeginItr = pList->GetBegin();
		auto Itr = pList->GetBegin();

		++Itr;	// ずらすことで別のイテレータにする

		// 異なるか確認
		EXPECT_TRUE(BeginItr != Itr);
	}

	// 非コンストイテレータ
	{
		auto BeginItr = pList->GetConstBegin();
		auto Itr = pList->GetConstBegin();

		++Itr;	// ずらすことで別のイテレータにする

		// 異なるか確認
		EXPECT_TRUE(BeginItr != Itr);
	}
}

#pragma endregion

}	// ex02_Iterator