/**
* @brief	成績データ定義
* @date		2022/10/06
*/

#pragma once

//===== インクルード =====
#include <string>

//===== 構造体定義 =====
/**
* @struct	ScoreData
* @brief	成績データ
*/
struct ScoreData
{
	int			Score;	//! スコア
	std::string	Name;	//! ユーザー名
};