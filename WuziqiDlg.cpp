
// WuziqiDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Wuziqi.h"
#include "WuziqiDlg.h"
#include "Board.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*�ڿ����ͷ�ļ�*/
#include "iostream"
#include <io.h>    
#include <fcntl.h>  
#include <io.h>    
#include <fcntl.h> 

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
Board *CWuziqiDlg::p_Chess(nullptr);
//Board *q_Chess(nullptr);
static int Time = 0;//��¼����˳��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWuziqiDlg �Ի���


//ͼ��
CWuziqiDlg::CWuziqiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWuziqiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWuziqiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWuziqiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CWuziqiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWuziqiDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CWuziqiDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CWuziqiDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CWuziqiDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CWuziqiDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_RADIO1, &CWuziqiDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CWuziqiDlg::OnBnClickedRadio2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWuziqiDlg ��Ϣ�������

BOOL CWuziqiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//AfxGetApp()->SetWindowText(_T("��Ҫ��ʾ�Ķ������������ʾ�ÿվ���"));//����
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//m_Font->CreateFont		  (60,25,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,LPCTSTR("Arial"));
 //  //����߶ȣ������ȣ���������İ�����...,���������
 //  CEdit *m_Edit=(CEdit *)GetDlgItem(IDC_BUTTON3);
 //   m_Edit->SetFont(m_Font,FALSE);
 //   m_Edit->SetFont(m_Font);
	  //m_Font->CreatePointFont(150,_T("����"),NULL);
    //  GetDlgItem(IDC_STATIC_1)->SetFont(m_Font); 
	//����	
	SetWindowText(_T("���ݴ�ѧ������Ŀ--�����岩��ϵͳ"));

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*�Ի����С*/
	CRect temprect(0, 0, 1150, 820);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	/*��ʼ����־��*/
	m_pEngine = new CDialogEx();
	m_pEngine->Create(IDD_DIALOG1);
	Log_Open = false;//����δ��
	/*��ʼ����־��*/
	m_pEngine_2 = new CDialogEx();
	m_pEngine_2->Create(IDD_DIALOG1);
	Log_Open_2 = false;//����δ��
	/*��ѡ��*/
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);

	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWuziqiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWuziqiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//p_Chess = new Board;
		//p_Chess->Init_Board();	//��ʼ������
		//q_Chess = new Board;
		//q_Chess->Init_Board();
		//G_BOARD->Init_Board();
		//BackGround();	//���ر���ͼ
		//Show_Pieces();	//����
		//Show_Icon();	//����ͼ��
		//Init_Data();
		CDialogEx::OnPaint();

	}
	
	G_BOARD->Init_Board();
	BackGround();	//���ر���ͼ
	Show_Pieces();	//����
	Show_Icon();	//����ͼ��
}

/*###����Ϊ�û��Զ��庯��###*/
//���ر���ͼ
void CWuziqiDlg::BackGround()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BACKGROUND); //����λͼ
	//Out_of_Game.SendToBack();//

	int nBmpWidth, nBmpHeight;
	BITMAP bmInfo;
	bmp.GetBitmap(&bmInfo);
	nBmpWidth = bmInfo.bmWidth;
	nBmpHeight = bmInfo.bmHeight;  //��ȡλͼ��ʵ�ʴ�С


	CRect clientRC;
	GetClientRect(clientRC);  //��ȡ�ͻ�����Ĵ�С


	CDC *pDC = GetDC();  //��ĻDC
	CDC memDC;
	memDC.CreateCompatibleDC(pDC); //�ڴ�DC
	memDC.SelectObject(&bmp);
	pDC->StretchBlt(0, 0, clientRC.Width(), clientRC.Height(), &memDC, 0, 0, nBmpWidth, nBmpHeight, SRCCOPY);  //�ڴ��ڻ�ͼ

	memDC.DeleteDC();
	bmp.DeleteObject();
	ReleaseDC(pDC);//�ͷ�
}
//
void CWuziqiDlg::Show_Pieces()
{
	CPaintDC dc(this); 
	if(!png_pieces.IsNull()) 
		png_pieces.Destroy();
	png_pieces.Load(_T("picture\\����1.png"));                           //load���룬������ʾ
	Change_Style(&png_pieces);                               //����͸����������
	if(png_pieces.IsNull()) 
		png_pieces.Draw(dc.m_hDC, 80, 20);      //�����Ͻ�Ϊԭ�㣬��ԭʼ��С����(80,20)����ͼ

}
//
void CWuziqiDlg::Change_Style(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)  				//�������ش���
	{  
		for(int j = 0; j <png->GetHeight(); j++)  
		{  
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i , j));  
			pucColor[0] = pucColor[0] *pucColor[3] / 255;  
			pucColor[1] = pucColor[1] *pucColor[3] / 255;  
			pucColor[2] = pucColor[2] *pucColor[3] / 255;  
		}  
	}  
}
//��ʾ����
void CWuziqiDlg::Picture_Control_Show_White(int X)
{
	//LockWindowUpdate();
	CClientDC *pDC_1 = new CClientDC(GetDlgItem(X));
	CRect rect_1;
	Image image(_T("picture\\����1.png")); // Construct an image
	GetDlgItem(X)->GetWindowRect(&rect_1);
	Graphics graphics(pDC_1->m_hDC); // Create a GDI+ graphics object
	graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	delete pDC_1;	
	//UnlockWindowUpdate();
}
//��ʾ����
void CWuziqiDlg::Picture_Control_Show_Black(int X)
{
	//LockWindowUpdate();
	CClientDC *pDC_1 = new CClientDC(GetDlgItem(X));
	CRect rect_1;
	Image image(_T("picture\\����1.png")); // Construct an image
	GetDlgItem(X)->GetWindowRect(&rect_1);
	Graphics graphics(pDC_1->m_hDC); // Create a GDI+ graphics object
	graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	delete pDC_1;
	//UnlockWindowUpdate();
}
//����ض�ID��picture�ؼ���ͼƬ
void CWuziqiDlg::Picture_Control_Show_Empty(int X)
{
	//CClientDC *pDC_1 = new CClientDC(GetDlgItem(X));
	//CRect rect_1;
	//Image image(_T("picture\\�հ�.png")); // Construct an image
	//GetDlgItem(X)->GetWindowRect(&rect_1);
	//Graphics graphics(pDC_1->m_hDC); // Create a GDI+ graphics object
	//graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	//delete pDC_1;
	GetDlgItem(X)->ShowWindow(FALSE);
	GetDlgItem(X)->ShowWindow(TRUE);
	/*CStatic* pStatic = (CStatic*)GetDlgItem(X);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(), NULL);
	*/
}
//
void CWuziqiDlg::Init_Data()
{
	int x=1000;
	p_Chess->type_of_pieces = 0;

	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			p_Chess->Picture_Control_State[i][j] = 0;
			p_Chess->Picture_Control_ID[i][j] = x;
			x++;
		}
}
//��ʾͼ��
void CWuziqiDlg::Show_Icon()
{
	CClientDC *pDC_1 = new CClientDC(GetDlgItem(IDC_PLAYER_1));
	CRect rect_1;
	Image image_1(_T("picture\\ͼ����150.png")); // Construct an image
	GetDlgItem(IDC_PLAYER_1)->GetWindowRect(&rect_1);
	Graphics graphics_1(pDC_1->m_hDC); // Create a GDI+ graphics object
	graphics_1.DrawImage(&image_1, 0, 0, image_1.GetWidth(), image_1.GetHeight());
	delete pDC_1;

	CClientDC *pDC_2 = new CClientDC(GetDlgItem(IDC_PLAYER_2));
	CRect rect_2;
	Image image_2(_T("picture\\ͼ��Ů150.png")); // Construct an image
	GetDlgItem(IDC_PLAYER_2)->GetWindowRect(&rect_2);
	Graphics graphics_2(pDC_2->m_hDC); // Create a GDI+ graphics object
	graphics_2.DrawImage(&image_2, 0, 0, image_2.GetWidth(), image_2.GetHeight());
	delete pDC_2;

	CClientDC *pDC_3 = new CClientDC(GetDlgItem(IDC_Pieces_Black));
	CRect rect_3;
	Image image_3(_T("picture\\����1.png")); // Construct an image
	GetDlgItem(IDC_Pieces_Black)->GetWindowRect(&rect_3);
	Graphics graphics_3(pDC_3->m_hDC); // Create a GDI+ graphics object
	graphics_3.DrawImage(&image_3, 0, 0, image_3.GetWidth(), image_3.GetHeight());
	delete pDC_3;

	CClientDC *pDC_4 = new CClientDC(GetDlgItem(IDC_Pieces_White));
	CRect rect_4;
	Image image_4(_T("picture\\����1.png")); // Construct an image
	GetDlgItem(IDC_Pieces_White)->GetWindowRect(&rect_4);
	Graphics graphics_4(pDC_4->m_hDC); // Create a GDI+ graphics object
	graphics_4.DrawImage(&image_4, 0, 0, image_4.GetWidth(), image_4.GetHeight());
	delete pDC_4;
}
//������̣����ı�����
void CWuziqiDlg::Clear_Board()
{
	for(int i=0,j=0;i<15,j<15;i++,j++)
	{
		LockWindowUpdate();
		if(G_BOARD->Picture_Control_State[i][j] != 0)
		{
			G_BOARD->Picture_Control_State[i][j] = 0;
			//LockWindowUpdate();
			//GetDlgItem(G_BOARD->Picture_Control_ID[i][j])->ShowWindow(FALSE);
			//GetDlgItem(G_BOARD->Picture_Control_ID[i][j])->ShowWindow(TRUE);
			Picture_Control_Show_Empty(G_BOARD->Picture_Control_ID[i][j]);
			//UnlockWindowUpdate();
		}
		UnlockWindowUpdate();
	}
	//G_BOARD->Restart_Game = true;
}
//������̣����ı�����
void CWuziqiDlg::Empty()
{
	/*�ڿ���ʾ*/
	/*AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;*/



	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			LockWindowUpdate();
			if(G_BOARD->Picture_Control_State[i][j] != EMPTY)
			{
				//G_BOARD->Picture_Control_State[i][j] = 0;
				//LockWindowUpdate();
				//GetDlgItem(G_BOARD->Picture_Control_ID[i][j])->ShowWindow(FALSE);
				//GetDlgItem(G_BOARD->Picture_Control_ID[i][j])->ShowWindow(TRUE);
				//Picture_Control_Show_Empty(G_BOARD->Picture_Control_ID[i][j]);
				//UnlockWindowUpdate();

				CStatic* pStatic = (CStatic*)GetDlgItem(G_BOARD->Picture_Control_ID[i][j]);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(), RGB(240, 240, 240));
			}
			UnlockWindowUpdate();
		}

		LockWindowUpdate();
		UpdateWindow();
		UnlockWindowUpdate();

}
//����
void CWuziqiDlg::Back_Chess()
{
	int Late_Chess_Num = 0, Late_Chess_X = 0,Late_Chess_Y = 0;
	int Second_Late_Chess_Num = 0,Second_Late_Chess_X = 0,Second_Late_Chess_Y = 0;
	int Chess_Copy[15][15],Back_Chess_Copy[15][15];

	struct Chess{
		int Chess_x;	//���Ӻ�����
		int Chess_y;	//����������
		int type;		//��������
		Chess *next;		//��������˳��
	};
	Chess* P = new Chess();	//��ͷָ��

	for(int i = 0;i<15;i++)	//�������һ������
		for(int j = 0;j<15;j++)
		{
			Chess_Copy[i][j] = G_BOARD->Picture_Control_State[i][j];
			Back_Chess_Copy[i][j] = G_BOARD->Back_Chess[i][j];
			if(G_BOARD->Back_Chess[i][j] > Late_Chess_Num)
			{
				Second_Late_Chess_Num = Late_Chess_Num;
				Second_Late_Chess_X = Late_Chess_X;
				Second_Late_Chess_Y = Late_Chess_Y;
				Late_Chess_Num = G_BOARD->Back_Chess[i][j];
				Late_Chess_X = i;
				Late_Chess_Y = j;
			}
		}
		Time = Time-2;//��¼������˳��



		/*�ڿ���ʾ*/
		/*AllocConsole();
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long)handle, _O_TEXT);
		FILE * hf = _fdopen(hCrt, "w");
		*stdout = *hf;*/

		/*for(int i = 0;i<15;i++)
		for(int j = 0;j<15;j++)
		cout<<G_BOARD->Picture_Control_State[j][i]<<"\t";
		cout<<endl;*/

		//��������˳��
		Back_Chess_Copy[Late_Chess_X][Late_Chess_Y] = 0;
		Back_Chess_Copy[Second_Late_Chess_X][Second_Late_Chess_Y] = 0;
		//��������״̬
		//G_BOARD->Picture_Control_State[Late_Chess_X][Late_Chess_Y] = EMPTY;
		//G_BOARD->Picture_Control_State[Second_Late_Chess_X][Second_Late_Chess_Y] = EMPTY;
		Chess_Copy[Late_Chess_X][Late_Chess_Y] = EMPTY;
		Chess_Copy[Second_Late_Chess_X][Second_Late_Chess_Y] = EMPTY;

		Empty();
		UpdateWindow();


		for(int z=1;z<=Time;z++)
		{
			for(int i=0;i<15;i++)
			{
				for(int j=0;j<15;j++)
				{
					if(Back_Chess_Copy[i][j] == z)
					{
						Chess *Chess_Board = new Chess();
						Chess_Board->Chess_x = i;
						Chess_Board->Chess_y = j;
						Chess_Board->type = Chess_Copy[i][j];
						Chess_Board->next = NULL;
						Chess* Q = P;
						while(Q->next!=NULL)
						{
							Q = Q->next;
						}
						Q->next = Chess_Board;
						cout<<Back_Chess_Copy[i][j]<<endl;
						cout<<Chess_Board->Chess_x<<"**"<<Chess_Board->Chess_y<<endl;
					}
				}
			}
		}

		for(int i=0;i<15;i++)
			for(int j=0;j<15;j++)
			{
				G_BOARD->Back_Chess[i][j] = Back_Chess_Copy[i][j];
				G_BOARD->Picture_Control_State[i][j] = Chess_Copy[i][j];
			}


			P = P->next;
			while(P != NULL)
			{
				//G_BOARD->Set_Chess(P->Chess_x,P->Chess_y);
				together(P->type,P->Chess_x,P->Chess_y);
				P = P->next;
			}
			delete P;
			//UnlockWindowUpdate();
			/*cout<<"����701��";
			for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
			cout<<G_BOARD->Picture_Control_State[i][j];

			cout<<endl;*/

			/*for(int i = 0;i<15;i++)
			for(int j = 0;j<15;j++)
			cout<<G_BOARD->Picture_Control_State[j][i]<<"\t";
			cout<<endl;*/

			//UpdateWindow();

			//		for(int i = 0;i<15;i++)
			//	for(int j = 0;j<15;j++)
			//		cout<<G_BOARD->Picture_Control_State[j][i]<<"\t";
			//cout<<endl;

			//for(int x = 0;x<15;x++)
			//	for(int y = 0;y<15;y++)
			//	{
			//		//cout<<G_BOARD->Picture_Control_State[x][y];
			//		if(G_BOARD->Picture_Control_State[x][y] != 0)
			//		{
			//			/*LockWindowUpdate();
			//			together(G_BOARD->Picture_Control_State[i][j],i,j);
			//			UnlockWindowUpdate();*/
			//			//LockWindowUpdate();
			//			G_BOARD->Set_Chess(x,y);
			//			//UnlockWindowUpdate();
			//		}
			//	}
}
/*###����Ϊ�û��Զ��庯��###*/

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWuziqiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����������
void CWuziqiDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int X;
	int Y;
	if(point.x>32 && point.x<775 && point.y>25 && point.y<737 && (point.x%50 <= 15 || point.x%50>=35) && (point.y%48<=15 || (point.y%48>=33)))
	{
		//MessageBox(_T("ģ�����ɹ�!"));
		if(point.x<60)
		{
			X = 0;
		}
		else
		{
			if(point.x%50 < 15)
			{
				X = point.x/50-1;
			}
			else
			{
				X = point.x/50;
			}
		}

		if(point.y<60)
		{
			Y = 0;
		}
		else
		{
			if(point.y%49 < 15)
			{
				Y = point.y/49-1;
			}
			else
			{
				Y = point.y/49;
			}
		}
		//p_Chess->Set_Chess(X,Y);
		G_BOARD->last_X = X;
		G_BOARD->last_Y = Y;

		if(G_BOARD->type_of_pieces == WHITE)	//��һ������Ϊ����
		{
			G_BOARD->isEngine_1_Turn = true;
		}
		else
		{
			G_BOARD->isEngine_2_Turn = true;
		}

		if(G_BOARD->Picture_Control_State[X][Y] == 0)
		{
			Time++;
			G_BOARD->Back_Chess[X][Y] = Time;	//��¼����˳��

			if(G_BOARD->type_of_pieces == BLACK) //�º���
			{
				G_BOARD->Picture_Control_State[X][Y] = BLACK;
				//Picture_Control_Show_Black(p_Chess->Picture_Control_ID[Y][X]);
				together(G_BOARD->type_of_pieces,X,Y);
				if(G_BOARD->Check_If_Win(X,Y,G_BOARD->type_of_pieces))
				{
					
					G_BOARD->AI_Start_1 = false;
					G_BOARD->AI_Start_2	= false;
					MessageBox(_T("����ʤ����"));
				}
				G_BOARD->type_of_pieces = WHITE;

			}
			else //�°���
			{
				G_BOARD->Picture_Control_State[X][Y] = WHITE;
				//Picture_Control_Show_White(p_Chess->Picture_Control_ID[Y][X]);
				together(G_BOARD->type_of_pieces,X,Y);
				if(G_BOARD->Check_If_Win(X,Y,G_BOARD->type_of_pieces))
				{
					
					G_BOARD->AI_Start_1 = false;
					G_BOARD->AI_Start_2	= false;
					MessageBox(_T("����ʤ����"));
				}
				G_BOARD->type_of_pieces = BLACK;
			}

		}
		//MessageBox(_T("�㵽����ȷλ�ã�"));
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//��������һ
void CWuziqiDlg::OnBnClickedButton1()
{
	//CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի��� 
	CFileDialog dlg(TRUE,_T("exe"),NULL,OFN_EXPLORER|OFN_ENABLESIZING|OFN_OVERWRITEPROMPT,_T("exe files (*.exe)|*.exe||"),this);
	//dlg.m_ofn.lStructSize = 88;
	//CString OpenFilePath;
	if(dlg.DoModal()==IDOK) 
		OpenFilePath=dlg.GetPathName(); 
	GetDlgItem(IDC_PLAYER1_EDIT)->SetWindowTextW(OpenFilePath);
	_outputEngine = (CEdit *)m_pEngine->GetDlgItem(IDC_Log_1);
	//CEdit *_outputEngine = NULL;
	//Control_Center::Start_Monitor(OpenFilePath,_outputEngine);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��������������ӣ����������
	Control_Center *s_p;
	if(!s_p->isNewGame())
	{
		Clear_Board();
	}
}

//���������
void CWuziqiDlg::OnBnClickedButton2()
{
	CFileDialog dlg(TRUE,_T("exe"),NULL,OFN_EXPLORER|OFN_ENABLESIZING|OFN_OVERWRITEPROMPT,_T("exe files (*.exe)|*.exe||"),this);
	//dlg.m_ofn.lStructSize = 88;
	//CString OpenFilePath_2;
	if(dlg.DoModal()==IDOK) 
		OpenFilePath_2=dlg.GetPathName(); 
	GetDlgItem(IDC_PLAYER2_EDIT)->SetWindowTextW(OpenFilePath_2);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_outputEngine_2 = (CEdit *)m_pEngine->GetDlgItem(IDC_Log_2);
	//��������������ӣ����������
	Control_Center *s_p;
	if(!s_p->isNewGame())
	{
		Clear_Board();
	}
}

//��ʾ��־����
void CWuziqiDlg::OnBnClickedButton6()
{
	if(!Log_Open)
	{
		m_pEngine->ShowWindow(SW_SHOW);
		Log_Open = true;
	}
	else
	{
		m_pEngine->ShowWindow(SW_HIDE);
		Log_Open = false;
	}
	//Engine_Log Dlg;
	//Dlg.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//�������Ӵ���
void CWuziqiDlg::together(int type,int X,int Y)
{
	if(type == WHITE)
		Picture_Control_Show_White(G_BOARD->Picture_Control_ID[X][Y]);
	else
		Picture_Control_Show_Black(G_BOARD->Picture_Control_ID[X][Y]);

	/*if(G_BOARD->Check_If_Win(X,Y,type))
	{
	if(type == WHITE)
	MessageBox(_T("����ʤ����"));
	else
	MessageBox(_T("����ʤ����"));
	}*/
}

CWuziqiDlg *CWuziqiDlg::CWuziqi = NULL;

CWuziqiDlg *CWuziqiDlg::SetInstance()
{
	if (NULL == CWuziqi)
	{
		CWuziqi = new CWuziqiDlg();
	}
	return CWuziqi;
}

//��ʼ��Ϸ
void CWuziqiDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	G_BOARD->Start_Game = true;
	Control_Center::Start_Monitor_1(OpenFilePath,_outputEngine);
	if(((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())  //���ѡ�л�����ս�����������������Ϊ�˻���սģʽ�򲻼��������
		Control_Center::Start_Monitor_2(OpenFilePath_2,_outputEngine_2);
}

//���¿�ʼ
void CWuziqiDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int Check_Choose = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	int Check_Choose_2 = ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck();

	if(Check_Choose == 1 && Check_Choose_2 == 0)
	{
		G_BOARD->AI_To_People = true;
	}
	else
		G_BOARD->AI_To_People = false;

	G_BOARD->Restart_Game = true;
	G_BOARD->AI_Start_1 = false;
	G_BOARD->AI_Start_2	= false;
	Clear_Board();	//�������
}

//����
void CWuziqiDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*�ڿ���ʾ*/
	/*AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;*/
	/*for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
	{
	cout<<"����%��";
	cout<<"�������ͣ�"<<G_BOARD->Picture_Control_State[i][j];
	cout<<"����ID:"<<G_BOARD->Picture_Control_ID[i][j];
	cout<<"˳��"<<G_BOARD->Back_Chess[i][j];		
	cout<<endl;
	}*/

	Back_Chess();			
}


void CWuziqiDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	G_BOARD->AI_To_People = true;
}


void CWuziqiDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	G_BOARD->AI_To_People = false;
}


HBRUSH CWuziqiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//if (pWnd->GetDlgCtrlID() == IDC_STATIC)// IDC_DisplayΪ��ѡ�ı���ID

 //  {

 //      pDC->SetTextColor(RGB(255, 0, 0));//����������ɫ

 //      pDC->SetBkColor(RGB(0, 200, 100));//���ñ�����ɫ

 //      pDC->SetBkMode(TRANSPARENT);//���ñ���͸��

 //  }

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
