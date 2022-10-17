/**
* @brief	クイックソートのテスト
* @date		2022/10/13
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../ListQuicksort/LinkedList.h"
#include "../ListQuicksort/ScoreData.h"
#include "TestHelper.h"
#include <vector>
#include <algorithm>

//===== 名前空間 =====
/**
* @brief	クイックソートのテスト用名前空間
*/
namespace ex03_Quicksort
{

//===== 構造体定義 =====
/**
* @brief	安定したソートでないことを確認するための構造体
*/
struct ScoreData_US : public ScoreData
{
	int Element;	// 要素番号

	ScoreData_US() = default;

	ScoreData_US(int Score_, const std::string& Name_, int Element_)
		: Element(Element_)
	{
		Score = Score_;
		Name = Name_;
	}
};

//===== クラス定義 =====
/**
* @brief	ScoreDataをスコアで > 比較するための関数オブジェクト 
*/
class CompareFuncScoreGreater
{
public:

	/**
	* @brief		ScoreDataをスコアで > 比較する
	* @param[in]	Left	比較するデータ1
	* @param[in]	Right	比較するデータ2
	* @retval		true	データ1のスコアがデータ2のスコアより大きい時
	* @retval		false	データ1のスコアがデータ2のスコアより小さい時
	*/
	bool operator() (const ScoreData& Left, const ScoreData& Right)
	{
		return Left.Score > Right.Score;
	}

	/**
	* @brief		ScoreDataをスコアで > 比較する(qsort用)
	* @param[in]	pLeft	比較するデータ1
	* @param[in]	pRight	比較するデータ2
	* @retval		-1	データ1のスコアがデータ2のスコアより大きい時
	* @retval		0	データ1のスコアがデータ2のスコアと同じ時
	* @retval		1	データ1のスコアがデータ2のスコアより小さい時
	*/
	static int Comp(const void* pLeft, const void* pRight)
	{
		const ScoreData* Left  = static_cast<const ScoreData*>(pLeft);
		const ScoreData* Right = static_cast<const ScoreData*>(pRight);

		if (Left->Score > Right->Score)
			return -1;

		if (Left->Score == Right->Score)
			return 0;

		if (Left->Score < Right->Score)
			return 1;

		return 0;
	}
};

/**
* @brief	ScoreDataをスコアで < 比較するための関数オブジェクト
*/
class CompareFuncScoreLess
{
public:

	/**
	* @brief		ScoreDataをスコアで < 比較する
	* @param[in]	Left	比較するデータ1
	* @param[in]	Right	比較するデータ2
	* @retval		true	データ1のスコアがデータ2のスコアより小さい時
	* @retval		false	データ1のスコアがデータ2のスコアより大きい時
	*/
	bool operator() (const ScoreData& Left, const ScoreData& Right)
	{
		return Left.Score < Right.Score;
	}

	/**
	* @brief		ScoreDataをスコアで < 比較する(qsort用)
	* @param[in]	pLeft	比較するデータ1
	* @param[in]	pRight	比較するデータ2
	* @retval		-1	データ1のスコアがデータ2のスコアより小さい時
	* @retval		0	データ1のスコアがデータ2のスコアと同じ時
	* @retval		1	データ1のスコアがデータ2のスコアより大きい時
	*/
	static int Comp(const void* pLeft, const void* pRight)
	{
		if (!pLeft || !pRight)
			return 0;

		const ScoreData* Left = static_cast<const ScoreData*>(pLeft);
		const ScoreData* Right = static_cast<const ScoreData*>(pRight);

		if (Left->Score < Right->Score)
			return -1;

		if (Left->Score == Right->Score)
			return 0;

		if (Left->Score > Right->Score)
			return 1;

		return 0;
	}
};

/**
* @brief	ScoreDataをユーザー名で > 比較するための関数オブジェクト
*/
class CompareFuncNameGreater
{
public:

	/**
	* @brief		ScoreDataを名前で > 比較する
	* @param[in]	Left	比較するデータ1
	* @param[in]	Right	比較するデータ2
	* @retval		true	データ1の名前がデータ2の名前より大きい(文字コード的に後ろ)の時
	* @retval		false	データ1の名前がデータ2の名前より小さい(文字コード的に前)の時
	*/
	bool operator() (const ScoreData& Left, const ScoreData& Right)
	{
		return Left.Name > Right.Name;
	}

	/**
	* @brief		ScoreDataを名前で > 比較する(qsort用)
	* @param[in]	pLeft	比較するデータ1
	* @param[in]	pRight	比較するデータ2
	* @retval		-1	データ1の名前がデータ2の名前より大きい(文字コード的に後ろ)の時
	* @retval		0	データ1の名前がデータ2の名前と同じ時
	* @retval		1	データ1の名前がデータ2の名前より小さい(文字コード的に前)の時
	*/
	static int Comp(const void* pLeft, const void* pRight)
	{
		if (!pLeft || !pRight)
			return 0;

		const ScoreData* Left = static_cast<const ScoreData*>(pLeft);
		const ScoreData* Right = static_cast<const ScoreData*>(pRight);

		if (Left->Name > Right->Name)
			return -1;

		if (Left->Name == Right->Name)
			return 0;

		if (Left->Name < Right->Name)
			return 1;

		return 0;
	}
};

/**
* @brief	ScoreDataをユーザー名で < 比較するための関数オブジェクト
*/
class CompareFuncNameLess
{
public:

	/**
	* @brief		ScoreDataを名前で < 比較する
	* @param[in]	Left	比較するデータ1
	* @param[in]	Right	比較するデータ2
	* @retval		true	データ1の名前がデータ2の名前より小さい(文字コード的に前)の時
	* @retval		false	データ1の名前がデータ2の名前より大きい(文字コード的に後ろ)の時
	*/
	bool operator() (const ScoreData& Left, const ScoreData& Right)
	{
		return Left.Name < Right.Name;
	}

	/**
	* @brief		ScoreDataを名前で < 比較する(qsort用)
	* @param[in]	pLeft	比較するデータ1
	* @param[in]	pRight	比較するデータ2
	* @retval		-1	データ1の名前がデータ2の名前より小さい(文字コード的に前)の時
	* @retval		0	データ1の名前がデータ2の名前と同じ時
	* @retval		1	データ1の名前がデータ2の名前より大きい(文字コード的に後ろ)の時
	*/
	static int Comp(const void* pLeft, const void* pRight)
	{
		if (!pLeft || !pRight)
			return 0;

		const ScoreData* Left = static_cast<const ScoreData*>(pLeft);
		const ScoreData* Right = static_cast<const ScoreData*>(pRight);

		if (Left->Name < Right->Name)
			return -1;

		if (Left->Name == Right->Name)
			return 0;

		if (Left->Name > Right->Name)
			return 1;

		return 0;
	}
};

/**
* @brief	型付けテスト用のクラス
*/
template<class T>
class QuicksortTest : public ::testing::Test
{
};

//===== 型エイリアス =====
using DistanceF = LinkedListTestFixture;	// Distance()用フィクスチャ

typedef ::testing::Types<CompareFuncScoreGreater, CompareFuncScoreLess, CompareFuncNameGreater, CompareFuncNameLess> CompFuncs;
TYPED_TEST_CASE(QuicksortTest, CompFuncs);

#pragma region ***** クイックソート *****

/**
* @brief	要素を持たないリストにソートを実行した時の挙動
* @details	ID:0
*			クイックソートのテストです。
*			要素を持たないリストに対してソート実行した時、何も起こらないことを確認します。
*			要素数が0のまま、先頭イテレータ == 末尾イテレータ の式が成り立てば成功とします。
*/
TYPED_TEST(QuicksortTest, NoItem)
{
	LinkedList<ScoreData> List;		// リスト
	TypeParam Comp;					// 比較関数
	
	// ソート前にサイズとイテレータをチェック
	EXPECT_EQ(0, List.GetSize());
	EXPECT_TRUE(List.GetConstBegin() == List.GetConstEnd());

	// ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	// サイズとイテレータをチェック
	EXPECT_EQ(0, List.GetSize());
	EXPECT_TRUE(List.GetConstBegin() == List.GetConstEnd());
}

/**
* @brief	要素を1つだけ持つリストにソートを実行した時の挙動
* @details	ID:1
*			クイックソートのテストです。
*			要素を1つだけ持つリストに対してソート実行した時、何も起こらないことを確認します。
*			要素数が1のまま、先頭イテレータの次が末尾イテレータとなっていれば成功です。
*/
TYPED_TEST(QuicksortTest, OneItemExist)
{
	LinkedList<ScoreData> List;		// リスト
	TypeParam Comp;					// 比較関数

	// データを1件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, { 1, "Test1" });

	// ソート前にサイズとイテレータをチェック
	{
		auto Itr = List.GetConstBegin();
		++Itr;
		EXPECT_EQ(1, List.GetSize());
		EXPECT_TRUE(Itr == List.GetConstEnd());
	}

	// ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	// サイズとイテレータをチェック
	{
		auto Itr = List.GetConstBegin();
		++Itr;
		EXPECT_EQ(1, List.GetSize());
		EXPECT_TRUE(Itr == List.GetConstEnd());
	}
}

/**
* @brief	2つ以上要素を持つリストにソートを実行した時の挙動
* @details	ID:2
*			クイックソートのテストです。
*			要素を2つ以上持つリストに対してソート実行した時、適切にソート出来ていることを確認します。
*			要素が適切に並び変えられていれば成功です。
*/
TYPED_TEST(QuicksortTest, SomeItemExist)
{
	LinkedList<ScoreData> List;		// リスト
	TypeParam Comp;					// 比較関数

	// データを5件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, { 4, "Test4" });
	List.Insert(InsertItr, { 2, "Test2" });
	List.Insert(InsertItr, { 0, "Test0" });
	List.Insert(InsertItr, { 3, "Test3" });
	List.Insert(InsertItr, { 1, "Test1" });

	//*** ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	//*** 並び変えが出来ているか確認
	// std::sortを使ってソートする
	std::vector<ScoreData> TestVector;
	TestVector.push_back({ 4, "Test4"});
	TestVector.push_back({ 2, "Test2"});
	TestVector.push_back({ 0, "Test0"});
	TestVector.push_back({ 3, "Test3"});
	TestVector.push_back({ 1, "Test1"});
	std::sort(TestVector.begin(), TestVector.end(), Comp);

	// std::sortの結果と比較する
	auto Begin     = List.GetConstBegin();
	auto End       = List.GetConstEnd();
	auto TestBegin = TestVector.begin();
	auto TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		EXPECT_EQ(TestBegin->Score, Data.Score);
		EXPECT_EQ(TestBegin->Name, Data.Name);
	}
}

/**
* @brief	同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時の挙動
* @details	ID:3
*			クイックソートのテストです。
*			実装したクイックソートが安定したソート出ないことを確認します。
*			要素がソートされて並ぶが、同一要素の順序が変わっていれば成功です。
*/
TYPED_TEST(QuicksortTest, UnstableSort)
{
	LinkedList<ScoreData_US> List;		// リスト
	TypeParam Comp;					// 比較関数

	// データを5件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, ScoreData_US(4, "Test4", 5));
	List.Insert(InsertItr, ScoreData_US(2, "Test2", 3));
	List.Insert(InsertItr, ScoreData_US(0, "Test0", 1));
	List.Insert(InsertItr, ScoreData_US(3, "Test3", 4));
	List.Insert(InsertItr, ScoreData_US(0, "Test0", 0));
	List.Insert(InsertItr, ScoreData_US(1, "Test1", 2));

	//*** ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	//*** 並び変えが出来ているか確認
	// qsortを使ってソートする
	std::vector<ScoreData_US> TestVector;
	TestVector.push_back(ScoreData_US(4, "Test4", 5));
	TestVector.push_back(ScoreData_US(2, "Test2", 3));
	TestVector.push_back(ScoreData_US(0, "Test0", 1));
	TestVector.push_back(ScoreData_US(3, "Test3", 4));
	TestVector.push_back(ScoreData_US(0, "Test0", 0));
	TestVector.push_back(ScoreData_US(1, "Test1", 2));
	qsort(TestVector.data(), TestVector.size(), sizeof(ScoreData_US), Comp.Comp);

	// qsortの結果と比較する
	auto Begin     = List.GetConstBegin();
	auto End       = List.GetConstEnd();
	auto TestBegin = TestVector.begin();
	auto TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		EXPECT_EQ(TestBegin->Score, Data.Score);
		EXPECT_EQ(TestBegin->Name, Data.Name);
		EXPECT_EQ(TestBegin->Element, Data.Element);
	}
}

/**
* @brief	整列済みリストにソートを実行した時の挙動
* @details	ID:4
*			クイックソートのテストです。
*			既にソートされているリストに対してもう一度ソートした時に、要素の並びが変わっていないことを確認します。
*			1回目のソートの結果と2回目のソートの結果が変わらなければ成功です。
*/
TYPED_TEST(QuicksortTest, SortSecond)
{
	LinkedList<ScoreData> List;		// リスト
	TypeParam Comp;					// 比較関数

	// データを5件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, { 4, "Test4" });
	List.Insert(InsertItr, { 2, "Test2" });
	List.Insert(InsertItr, { 0, "Test0" });
	List.Insert(InsertItr, { 3, "Test3" });
	List.Insert(InsertItr, { 1, "Test1" });

	//*** ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	//*** 並び変えが出来ているか確認
	// std::sortを使ってソートする
	std::vector<ScoreData> TestVector;
	TestVector.push_back({ 4, "Test4" });
	TestVector.push_back({ 2, "Test2" });
	TestVector.push_back({ 0, "Test0" });
	TestVector.push_back({ 3, "Test3" });
	TestVector.push_back({ 1, "Test1" });
	std::sort(TestVector.begin(), TestVector.end(), Comp);

	// std::sortの結果と比較する
	auto Begin = List.GetConstBegin();
	auto End = List.GetConstEnd();
	auto TestBegin = TestVector.begin();
	auto TestEnd = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		ASSERT_EQ(TestBegin->Score, Data.Score);
		ASSERT_EQ(TestBegin->Name, Data.Name);
	}

	// もう一度ソートして確認する
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);
	Begin     = List.GetConstBegin();
	End       = List.GetConstEnd();
	TestBegin = TestVector.begin();
	TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		EXPECT_EQ(TestBegin->Score, Data.Score);
		EXPECT_EQ(TestBegin->Name, Data.Name);
	}
}

/**
* @brief	一度整列したリストの各所に挿入し、再度ソートを実行した時の挙動
* @details	ID:5
*			クイックソートのテストです。
*			ソートを実行したリストに対して、要素を挿入し、再びソートした時の挙動を確認します。
*			要素が適切に並び変えられていれば成功です。
*/
TYPED_TEST(QuicksortTest, SortInsert)
{
	LinkedList<ScoreData> List;		// リスト
	TypeParam Comp;					// 比較関数

	// データを5件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, { 4, "Test4" });
	List.Insert(InsertItr, { 2, "Test2" });
	List.Insert(InsertItr, { 0, "Test0" });
	List.Insert(InsertItr, { 3, "Test3" });
	List.Insert(InsertItr, { 1, "Test1" });

	//*** ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);

	//*** 並び変えが出来ているか確認
	// std::sortを使ってソートする
	std::vector<ScoreData> TestVector;
	TestVector.push_back({ 4, "Test4" });
	TestVector.push_back({ 2, "Test2" });
	TestVector.push_back({ 0, "Test0" });
	TestVector.push_back({ 3, "Test3" });
	TestVector.push_back({ 1, "Test1" });
	std::sort(TestVector.begin(), TestVector.end(), Comp);

	// std::sortの結果と比較する
	auto Begin     = List.GetConstBegin();
	auto End       = List.GetConstEnd();
	auto TestBegin = TestVector.begin();
	auto TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		ASSERT_EQ(TestBegin->Score, Data.Score);
		ASSERT_EQ(TestBegin->Name, Data.Name);
	}

	// 先頭、末尾、先頭の次にデータを追加する
	{
		auto InsertItr = List.GetConstBegin();
		List.Insert(InsertItr, { 20, "Test20" });
		
		++InsertItr;
		List.Insert(InsertItr, { 10, "Test10" });

		InsertItr = List.GetConstEnd();
		List.Insert(InsertItr, { 30, "Test30" });
	}

	// 同じようにテスト用のVectorに挿入
	{
		auto InsertItr = TestVector.cbegin();
		TestVector.insert(InsertItr, { 20, "Test20" });

		InsertItr = TestVector.cbegin();
		++InsertItr;
		TestVector.insert(InsertItr, { 10, "Test10" });

		InsertItr = TestVector.cend();
		TestVector.insert(InsertItr, { 30, "Test30" });
	}

	// もう一度ソートして確認する
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), Comp);
	std::sort(TestVector.begin(), TestVector.end(), Comp);

	Begin     = List.GetConstBegin();
	End       = List.GetConstEnd();
	TestBegin = TestVector.begin();
	TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		EXPECT_EQ(TestBegin->Score, Data.Score);
		EXPECT_EQ(TestBegin->Name, Data.Name);
	}
}

/**
* @brief	キー指定をしなかった(nullptrを渡した)時の挙動
* @details	ID:6
*			クイックソートのテストです。
*			キーの指定をしなかった場合にソートを実行した時の挙動を確認します。
*			要素が並び変えられていなければ成功です。
*/
TEST(Quicksort, NoKeySelected)
{
	LinkedList<ScoreData> List;		// リスト
	
	// データを5件追加する
	auto InsertItr = List.GetConstEnd();
	List.Insert(InsertItr, { 4, "Test4" });
	List.Insert(InsertItr, { 2, "Test2" });
	List.Insert(InsertItr, { 0, "Test0" });
	List.Insert(InsertItr, { 3, "Test3" });
	List.Insert(InsertItr, { 1, "Test1" });

	//*** ソート
	List.Quicksort(List.GetConstBegin(), List.GetConstEnd(), 
		[](const ScoreData&, const ScoreData&) 
		{
			return false; 
		});

	//*** 並び変えが出来ているか確認
	// std::sortを使ってソートする
	std::vector<ScoreData> TestVector;
	TestVector.push_back({ 4, "Test4" });
	TestVector.push_back({ 2, "Test2" });
	TestVector.push_back({ 0, "Test0" });
	TestVector.push_back({ 3, "Test3" });
	TestVector.push_back({ 1, "Test1" });

	// 変わってないことを確認する
	auto Begin     = List.GetConstBegin();
	auto End       = List.GetConstEnd();
	auto TestBegin = TestVector.begin();
	auto TestEnd   = TestVector.end();
	for (; Begin != End && TestBegin != TestEnd; ++Begin, ++TestBegin)
	{
		auto& Data = *Begin;
		EXPECT_EQ(TestBegin->Score, Data.Score);
		EXPECT_EQ(TestBegin->Name, Data.Name);
	}
}

#pragma endregion
#pragma region ***** イテレータ間の距離を測る ******

/**
* @brief	要素数が0の時、先頭イテレータと末尾イテレータを渡したときの挙動
* @details	ID:9
*			イテレータどうしの距離を測る機能のチェックです。
*			要素数が0の時、Distanceに先頭イテレータと末尾イテレータを渡した時の挙動を確認します。
*			エラー値 : 0未満(-3)が返れば成功です。
*/
TEST(Distance, NoItem)
{
	// リスト
	LinkedList<ScoreData> List;

	// 非コンストなイテレータ
	auto Dis = List.Distance(List.GetBegin(), List.GetEnd());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認

	// コンストなイテレータ
	Dis = List.Distance(List.GetConstBegin(), List.GetConstEnd());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認
}

/**
* @brief	要素数が0の時、先頭イテレータと末尾イテレータを逆にして渡したときの挙動
* @details	ID:10
*			イテレータどうしの距離を測る機能のチェックです。
*			要素数が0の時、Distanceに先頭イテレータと末尾イテレータを逆にして渡した時の挙動を確認します。
*			エラー値 : 0未満(-3)が返れば成功です。
*/
TEST(Distance, NoItemRev)
{
	// リスト
	LinkedList<ScoreData> List;

	// 非コンストなイテレータ
	auto Dis = List.Distance(List.GetEnd(), List.GetBegin());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認

	// コンストなイテレータ
	Dis = List.Distance(List.GetConstEnd(), List.GetConstBegin());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認
}

/**
* @brief	複数の要素を持つ時、先頭イテレータと末尾イテレータを渡したときの挙動
* @details	ID:11
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭イテレータと末尾イテレータを渡した時の挙動を確認します。
*			要素数と同じ値が返れば成功です。
*/
TEST_F(DistanceF, SomeItem)
{
	// 非コンストなイテレータ
	auto Dis = pList->Distance(pList->GetBegin(), pList->GetEnd());
	EXPECT_EQ(pList->GetSize(), Dis);		// 要素数と同じであることの確認

	// コンストなイテレータ
	Dis = pList->Distance(pList->GetConstBegin(), pList->GetConstEnd());
	EXPECT_EQ(pList->GetSize(), Dis);		// 要素数と同じであることの確認
}

/**
* @brief	複数の要素を持つ時、先頭イテレータと末尾イテレータを逆にして渡したときの挙動
* @details	ID:12
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭イテレータと末尾イテレータを逆にして渡した時の挙動を確認します。
*			エラー値 : 0未満(-3)が返れば成功です。
*/
TEST_F(DistanceF, SomeItemRev)
{
	// 非コンストなイテレータ
	auto Dis = pList->Distance(pList->GetEnd(), pList->GetBegin());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認

	// コンストなイテレータ
	Dis = pList->Distance(pList->GetConstEnd(), pList->GetConstBegin());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-3, Dis);		// -3であることの確認
}

/**
* @brief	複数の要素を持つ時、先頭イテレータと先頭でも末尾でもないイテレータを渡したときの挙動
* @details	ID:13
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭イテレータと先頭でも末尾でもないを渡した時の挙動を確認します。
*			先頭から該当イテレータまでインクリメントをし、それが戻り値と同じであれば成功です。
*/
TEST_F(DistanceF, BeginToCenter)
{
	// 非コンストなイテレータ
	{
		auto Itr = pList->GetBegin();
		++Itr;
		auto Dis = pList->Distance(pList->GetBegin(), Itr);
		EXPECT_EQ(1, Dis);		// 1回インクリメントしているので
	}

	// コンストなイテレータ
	{
		auto Itr = pList->GetConstBegin();
		++Itr;
		auto Dis = pList->Distance(pList->GetConstBegin(), Itr);
		EXPECT_EQ(1, Dis);		// 1回インクリメントしているので
	}
}

/**
* @brief	複数の要素を持つ時、先頭イテレータと先頭でも末尾でもないイテレータを逆にして渡したときの挙動
* @details	ID:14
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭イテレータと先頭でも末尾でもないを逆にして渡した時の挙動を確認します。
*			エラー値 : 0未満(-1)が返れば成功です。
*/
TEST_F(DistanceF, BeginToCenterRev)
{
	// 非コンストなイテレータ
	{
		auto Itr = pList->GetBegin();
		++Itr;
		auto Dis = pList->Distance(Itr, pList->GetBegin());
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-1, Dis);		// -1であることの確認
	}

	// コンストなイテレータ
	{
		auto Itr = pList->GetConstBegin();
		++Itr;
		auto Dis = pList->Distance(Itr, pList->GetConstBegin());
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-1, Dis);		// -1であることの確認
	}
}

/**
* @brief	複数の要素を持つ時、先頭でも末尾でもないイテレータと末尾イテレータを渡したときの挙動
* @details	ID:15
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭でも末尾でもないイテレータと末尾イテレータを渡した時の挙動を確認します。
*			末尾から該当イテレータまでデクリメントをし、それが戻り値と同じであれば成功です。
*/
TEST_F(DistanceF, CenterToEnd)
{
	// 非コンストなイテレータ
	{
		auto Itr = pList->GetEnd();
		--Itr;
		auto Dis = pList->Distance(Itr, pList->GetEnd());
		EXPECT_EQ(1, Dis);		// 1回デクリメントしているので
	}

	// コンストなイテレータ
	{
		auto Itr = pList->GetConstEnd();
		--Itr;
		auto Dis = pList->Distance(Itr, pList->GetConstEnd());
		EXPECT_EQ(1, Dis);		// 1回デクリメントしているので
	}
}

/**
* @brief	複数の要素を持つ時、先頭でも末尾でもないイテレータと末尾イテレータを逆にして渡したときの挙動
* @details	ID:16
*			イテレータどうしの距離を測る機能のチェックです。
*			複数の要素を持つ時、Distanceに先頭でも末尾でもないイテレータと末尾イテレータを逆にして渡した時の挙動を確認します。
*			エラー値 : 0未満(-3)が返れば成功です。
*/
TEST_F(DistanceF, CenterToEndRev)
{
	// 非コンストなイテレータ
	{
		auto Itr = pList->GetEnd();
		--Itr;
		auto Dis = pList->Distance(pList->GetEnd(), Itr);
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-3, Dis);		// -3であることの確認
	}

	// コンストなイテレータ
	{
		auto Itr = pList->GetConstEnd();
		--Itr;
		auto Dis = pList->Distance(pList->GetConstEnd(), Itr);
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-3, Dis);		// -3であることの確認
	}
}

/**
* @brief	Distanceに別のリストのイテレータを渡したときの挙動
* @details	ID:17
*			イテレータどうしの距離を測る機能のチェックです。
*			Distanceに別のリストのイテレータを渡したときの挙動を確認します。
*			エラー値 : 0未満(-2)が返れば成功です。
*/
TEST(Distance, DifferentListItr)
{
	LinkedList<ScoreData> List1;
	LinkedList<ScoreData> List2;

	auto Dis = List1.Distance(List2.GetBegin(), List2.GetEnd());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-2, Dis);		// -2であることの確認

	Dis = List1.Distance(List2.GetConstBegin(), List2.GetConstEnd());
	EXPECT_LT(Dis, 0);		// 0未満であることの確認
	EXPECT_EQ(-2, Dis);		// -2であることの確認
}

/**
* @brief	Distanceに不正なイテレータを渡したときの挙動
* @details	ID:18
*			イテレータどうしの距離を測る機能のチェックです。
*			Distanceに別のリストのイテレータを渡したときの挙動を確認します。
*			エラー値 : 0未満(-2)が返れば成功です。
*/
TEST(Distance, InvalidItr)
{
	LinkedList<ScoreData> List;

	// 非コンストなイテレータ
	{
		LinkedList<ScoreData>::Iterator InvalidItr1;
		LinkedList<ScoreData>::Iterator InvalidItr2;

		auto Dis = List.Distance(InvalidItr1, InvalidItr2);
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-2, Dis);		// -2であることの確認
	}

	// コンストなイテレータ
	{
		LinkedList<ScoreData>::Iterator ConstInvalidItr1;
		LinkedList<ScoreData>::Iterator ConstInvalidItr2;

		auto Dis = List.Distance(ConstInvalidItr1, ConstInvalidItr2);
		EXPECT_LT(Dis, 0);		// 0未満であることの確認
		EXPECT_EQ(-2, Dis);		// -2であることの確認
	}
}

#pragma endregion

}	// ex03_Quicksort
