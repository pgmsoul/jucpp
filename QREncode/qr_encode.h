// QR_Encode.h : CQR_Encode クラス傚冱およびインタ�`フェイス協�x
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
#define AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// 協方

// �`り��屎レベル
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// デ�`タモ�`ド
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// バ�`ジョン(侏桑)グル�`プ
#define QR_VRESION_S	0 // 1 ゛ 9
#define QR_VRESION_M	1 // 10 ゛ 26
#define QR_VRESION_L	2 // 27 ゛ 40

#define MAX_ALLCODEWORD	 3706 // �tコ�`ドワ�`ド方恷寄��
#define MAX_DATACODEWORD 2956 // デ�`タコ�`ドワ�`ド恷寄��(バ�`ジョン40-L)
#define MAX_CODEBLOCK	  153 // ブロックデ�`タコ�`ドワ�`ド方恷寄��(ＲＳコ�`ドワ�`ドを根む)
#define MAX_MODULESIZE	  177 // 匯�xモジュ�`ル方恷寄��

// ビットマップ宙鮫�rマ�`ジン
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO {
	int ncRSBlock;		// ＲＳブロック方
	int ncAllCodeWord;	// ブロック坪コ�`ドワ�`ド方
	int ncDataCodeWord;	// デ�`タコ�`ドワ�`ド方(コ�`ドワ�`ド方 - ＲＳコ�`ドワ�`ド方)

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// QRコ�`ドバ�`ジョン(侏桑)�v�B秤��

typedef struct tagQR_VERSIONINFO {
	int nVersionNo;	   // バ�`ジョン(侏桑)桑催(1゛40)
	int ncAllCodeWord; // �tコ�`ドワ�`ド方

	// 參和塘双耶忖は�`り��屎楕(0 = L, 1 = M, 2 = Q, 3 = H) 
	int ncDataCodeWord[4];	// デ�`タコ�`ドワ�`ド方(�tコ�`ドワ�`ド方 - ＲＳコ�`ドワ�`ド方)

	int ncAlignPoint;	// アライメントパタ�`ン恙�吠�
	int nAlignPoint[6];	// アライメントパタ�`ン嶄伉恙��

	RS_BLOCKINFO RS_BlockInfo1[4]; // ＲＳブロック秤��(1)
	RS_BLOCKINFO RS_BlockInfo2[4]; // ＲＳブロック秤��(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR_Encode クラス

class CQR_Encode {
	// ���B/����
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// �`り��屎レベル
	int m_nVersion;		// バ�`ジョン(侏桑)
	BOOL m_bAutoExtent;	// バ�`ジョン(侏桑)徭������峺協フラグ
	int m_nMaskingNo;	// マスキングパタ�`ン桑催

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
	// bit5:�C嬬モジュ�`ル�┘泪好�ング���麝癸�フラグ
	// bit4:�C嬬モジュ�`ル宙鮫デ�`タ
	// bit1:エンコ�`ドデ�`タ
	// bit0:マスク瘁エンコ�`ド宙鮫デ�`タ
	// 20hとの��尖才により�C嬬モジュ�`ル登協、11hとの��尖才により宙鮫��恷�K議にはBOOL�ｻ���

private:
	int m_ncDataCodeWordBit; // デ�`タコ�`ドワ�`ドビット�L
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; // 秘薦デ�`タエンコ�`ドエリア

	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // �tコ�`ドワ�`ド方(ＲＳ�`り��屎デ�`タを根む)
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // �tコ�`ドワ�`ド麻竃エリア
	BYTE m_byRSWork[MAX_CODEBLOCK]; // ＲＳコ�`ドワ�`ド麻竃ワ�`ク

	// デ�`タエンコ�`ド�v�Bファンクション
public:
	//nLevel:樟危雫艶��0-3
	//nVersion:屈略鷹井云��1-40��屈略鷹蛍掩楕巷塀��(V-1)*4 + 21。
	//bAutoExtent:咀葎詰井埆詰云嬬校亟秘議忖憲方富��侭參泌惚坿方象忖憲方狛謹��緩歌方譜葎TRUE��氏徭強戻互井云��譜葎FALSE音徭強戻互井云��遇頁痕方氏払移。
	//nMaskingNo:譜葎 1.
	//lpsSource:勣園鷹議坪否猟云。
	BOOL EncodeData(int nLevel, int nVersion, BOOL bAutoExtent, int nMaskingNo, LPCSTR lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, LPCSTR lpsSource, int ncLength);
	BOOL EncodeSourceData(LPCSTR lpsSource, int ncLength, int nVerGroup);

	int GetBitLength(BYTE nMode, int ncData, int nVerGroup);

	int SetBitStream(int nIndex, WORD wData, int ncData);

	BOOL IsNumeralData(unsigned char c);
	BOOL IsAlphabetData(unsigned char c);
	BOOL IsKanjiData(unsigned char c1, unsigned char c2);

	BYTE AlphabetToBinaly(unsigned char c);
	WORD KanjiToBinaly(WORD wc);

	void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

	// モジュ�`ル塘崔�v�Bファンクション
private:
	void FormatModule();

	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
