/**
* @brief	双方向リスト定義
* @date		2022/10/06
*/

#pragma once

/*
*   [参考にしたサイト]
* ・ https://qiita.com/omu58n/items/7794f097b2c569a469bc
* ・ https://daeudaeu.com/quicksort/
* ・ https://programming-place.net/ppp/contents/algorithm/sort/006.html
*/

//===== 定数・マクロ定義 =====
/**
* @brief	LinkedList<DataType>::Distanceに無効な参照を持つイテレータを渡した
* @note		別のリストのイテレータを渡した場合でも起こる
*/
#define LIST_DISTANCE_ERROR_INVALID_REFERENCE

/**
* @brief	LinkedList<DataType>::Distanceに不正なイテレータを渡した
*/
#define LIST_DISTANCE_ERROR_INVALID_ITERATOR

/**
* @brief	LinkedList<DataType>::Distanceに渡したイテレータの First から Last に到達できなかった
*/
#define LIST_DISTANCE_ERROR_UNREACHABLE

//===== クラス定義 =====
/**
* @brief	双方向リスト
* @tparam	DataType リストに格納したいデータ
*/
template<class DataType>
class LinkedList
{
	//=== 構造体定義
private:

	/**
	* @brief	双方向リストのノード
	*/
	struct Node
	{
		//! 前ノードへのポインタ
		Node* pPrev;

		//! 次ノードへのポインタ
		Node* pNext;

		//! データ
		DataType	Data;
	};

	//=== クラス定義
public:

	/**
	* @brief	双方向リストのコンストイテレータ
	*/
	class ConstIterator
	{
		//=== メンバ変数
	protected:

		//! このイテレータが現在参照しているノード
		LinkedList::Node* m_pCurrentNode;

		//! どのリストのイテレータか判別できるように
		const LinkedList* m_pList;

		//=== メンバ関数
	public:

		/**
		* @brief	デフォルトコンストラクタ
		*/
		ConstIterator(void);

		/**
		* @brief	リストの先頭に向かって1つ進む(前置デクリメント)
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator& operator--(void);

		/**
		* @brief	リストの末尾に向かって1つ進む(前置インクリメント)
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator& operator++(void);

		/**
		* @brief	リストの先頭に向かって1つ進む(後置デクリメント)
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator operator--(int);

		/**
		* @brief	リストの末尾に向かって1つ進む(後置インクリメント)
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator operator++(int);

		/**
		* @brief	イテレータが指す要素を取得する(コンスト版)
		* @return	このイテレータが指すデータへのコンストな左辺値参照
		*/
		const DataType& operator*(void) const;

		/**
		* @brief	イテレータのコピーを行う(コピーコンストラクタ)
		*/
		ConstIterator(const ConstIterator& ConstItr);

		/**
		* @brief	イテレータのコピー代入を行う
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator& operator=(const ConstIterator& Itr);

		/**
		* @brief	このイテレータと同一か比較する
		* @return	true	同一
		* @return	false	異なる
		*/
		bool operator==(const ConstIterator& Itr) const;

		/**
		* @brief	このイテレータと異なるか比較する
		* @retval	true	異なる
		* @retval	false	同一
		*/
		bool operator!=(const ConstIterator& Itr) const;

		/**
		* @brief	不正なイテレータでないことをチェックする。
		* @details	trueが返った場合、このイテレータを介してデータにアクセスできることを保証する。
		*			(リストからこのイテレータが指している要素が削除されていない限り)
		* @retval	true	正常
		* @retval	false	不正なイテレータ
		*/
		bool IsValid(void) const;

		/**
		* @brief	このイテレータが適切な参照を持っているかチェックする
		* @retval	true	適切に設定されている
		* @retval	false	不正な参照を持っている
		*/
		bool IsValidReference(void) const;

	protected:

		/**
		* @brief	このイテレータがダミーノードを指しているかチェックする。
		* @retval	true	ダミーノードを指している
		* @retval	false	ダミーノードを指していない
		*/
		bool IsDummy(void) const;

		friend LinkedList;
	};

	/**
	* @brief	双方向リストの非コンストイテレータ
	*/
	class Iterator : public ConstIterator
	{
		//=== メンバ関数
	public:

		/**
		* @brief	イテレータが指す要素を取得する(非コンスト版)
		* @return	このイテレータが指すデータへの左辺値参照
		*/
		DataType& operator*(void);
	};

	//=== メンバ変数
private:

	//! 要素数
	size_t	m_ElementCount;

	//! ダミーノード(Prevに末尾ノード、Nextに先頭ノード)
	Node*	m_pDummy;

	//=== メンバ関数
public:

	/**
	* @brief	デフォルトコンストラクタ
	*/
	LinkedList(void);

	/**
	* @brief	コピーコンストラクタ
	* @note		意図しないコピーを防ぐため、delete宣言しています。
	*/
	LinkedList(const LinkedList<DataType>& List) = delete;

	/**
	* @brief	ムーブコンストラクタ
	* @note		意図しないムーブを防ぐため、delete宣言しています。
	*/
	LinkedList(LinkedList<DataType>&& List) = delete;

	/**
	* @brief	デストラクタ
	*/
	virtual ~LinkedList(void);

	/**
	* @brief	データ数の取得
	* @return	データ件数
	*/
	size_t GetSize(void) const;

	/**
	* @brief		データの挿入
	* @param[in]	Itr		挿入したい位置
	* @param[in]	Data	新しく挿入したいデータ
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Insert(ConstIterator& Itr, const DataType& Data);

	/**
	* @brief		データの削除
	* @param[in]	Itr		削除したいデータ
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Delete(ConstIterator& Itr);

	/**
	* @brief		全てのデータの削除
	*/
	void Clear(void);

	/**
	* @brief	先頭のコンストなイテレータを取得
	* @return	先頭のコンストなイテレータ
	*/
	ConstIterator GetConstBegin(void) const;

	/**
	* @brief	先頭のイテレータを取得
	* @return	先頭のイテレータ
	*/
	Iterator GetBegin(void);

	/**
	* @brief	末尾のコンストなイテレータを取得
	* @return	末尾のコンストなイテレータ
	*/
	ConstIterator GetConstEnd(void) const;

	/**
	* @brief	末尾のイテレータを取得
	* @return	末尾のイテレータ
	*/
	Iterator GetEnd(void);

	/**
	* @brief		クイックソートを行う
	* @note			リスト全体をソートするには、FirstにGetBegin()で得たイテレータを、LastにGetEnd()で得たイテレータを渡してください。
	* @details		CompFuncでtrueが返されると要素の入れ替えを行います。(std::sortと同じ振る舞いをします)
	*				・昇順でソートする場合はstd::less<DataType>を
	*				・降順でソートする場合はstd::greater<DataType>を使用してください。
	*				・ラムダ式も受け取ることができるので、< 演算子や >演算子をオーバーロードしていない構造体・クラスでもソートすることができます。
	* @param[in]	First			ソートを行う範囲の先頭
	* @param[in]	Last			ソートを行う範囲の末尾(GetEnd(), GetConstEnd()で得られるイテレータを渡してもOK)
	* @param[in]	CompFunc		ソートを行う時に使う比較用関数オブジェクト(ラムダ式も可)
	* @tparam		CompareFunc		比較用関数オブジェクトの型	
	*/
	template<class CompareFunc = std::greater<DataType> >
	void Quicksort(ConstIterator First, ConstIterator Last,  CompareFunc CompFunc = std::greater<DataType>());

	/**
	* @brief	2つのイテレータの距離を計算して返す
	* @details	戻り値がINT_MAXを超えないことを保証する
	* @note		Firstに 末尾イテレータを指定すると LIST_DISTANCE_ERROR_INVALID_ITERATOR が返る
	* @retval	LIST_DISTANCE_ERROR_INVALID_ITERATOR	指定したイテレータが不正なイテレータだった
	* @retval	LIST_DISTANCE_ERROR_INVALID_REFERENCE	指定したイテレータがこのリストを参照していない
	* @retval	LIST_DISTANCE_ERROR_UNREACHABLE			FirstをインクリメントしてもLastに到達できなかった
	* @retval	0	First == Last が成立する時
	* @retval	0 > 2つのイテレータの距離(何回インクリメントしてLastに到達したか)  
	*/
	int Distance(const ConstIterator& First, const ConstIterator& Last) const;

private:

	/**
	* @brief		クイックソートを行う
	* @note			リスト全体をソートするには、FirstにGetBegin()で得たイテレータを、LastにGetEnd()で得たイテレータをデクリメントして渡してください。
	* @param[in]	First			ソートを行う範囲の先頭
	* @param[in]	Last			ソートを行う範囲の末尾(GetEnd(), GetConstEnd()で得られるイテレータを渡してもソートできません)
	* @param[in]	CompFunc		ソートを行う時に使う比較用関数オブジェクト(ラムダ式も可)
	* @tparam		CompareFunc	比較用関数オブジェクトの型
	*/
	template<class CompareFunc>
	void QuicksortImpl(const ConstIterator& First, const ConstIterator& Last, CompareFunc& CompFunc);

	/**
	* @brief	リスト内部のノードが持つ値を入れ替える
	* @details	ノードを入れ替えるのではなく、値だけを三角交換で入れ替える
	*/
	void SwapNode(Node* pLeft, Node* pRight);

	friend ConstIterator;
	friend Iterator;
};

//===== インクルード =====
#include "LinkedList.inl"
