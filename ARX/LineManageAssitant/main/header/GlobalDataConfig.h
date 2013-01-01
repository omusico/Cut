#include "stdafx.h"
#include <string>

using namespace std;

namespace com
{

namespace guch
{

namespace assistent
{

namespace data
{

class GlobalData
{
public:
	
	/**
	* ��������
	**/
	static const wstring KIND_LINE;
	static const wstring KIND_SEPERATOR;

	/**
	* �ܵ�����
	**/
	static const wstring LINE_CATEGORY_SHANGSHUI;
	static const wstring LINE_CATEGORY_XIASHUI;
	static const wstring LINE_CATEGORY_NUANQI;
	static const wstring LINE_CATEGORY_DIANLAN;
	static const wstring LINE_CATEGORY_YUSUI;
	static const wstring LINE_CATEGORY_TONGXIN;

	/**
	* ���������
	**/
	static const wstring BLOCK_CATEGORY_WUSHUI;
	static const wstring BLOCK_CATEGORY_HANGDAO;
	static const wstring BLOCK_CATEGORY_NUANQIGUAN;
	static const wstring BLOCK_CATEGORY_GUODAO;
	static const wstring BLOCK_CATEGORY_CHEZHAN;

	/**
	* ��Խ����
	**/
	static const wstring BLOCK_CATEGORY_ABOVE;
	static const wstring BLOCK_CATEGORY_BELLOW;

	/**
	* �ܵ���״
	**/
	static const wstring LINE_SHAPE_CIRCLE;
	static const wstring LINE_SHAPE_SQUARE;

	/**
	* �ܵ���λ
	**/
	static const wstring LINE_UNIT_MM;
	static const wstring LINE_UNIT_CM;
	static const wstring LINE_UNIT_M;

	/**
	* �ַ�����
	**/
	static const UINT ITEM_TEXT_MAX_LENGTH;

	/**
	* ��������
	**/
	static const wstring ERROR_DIALOG_CAPTION;
};


} // end of data

} // end of assistant

} // end of guch

} // end of com