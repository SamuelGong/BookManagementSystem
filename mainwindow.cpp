#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    library = new myDB();
	status = visitor;
	win1_page = 0;
	win1_row = 0;
	win2_row = 0;
	win2_row2 = 0;
	win3_row = 0;
    setMainWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setMainWindow(){


    //window
    pal = new QPalette();
    window = new QWidget();
    window1 = new QWidget();
    window2 = new QWidget();
    window3 = new QWidget();
    window4 = new QWidget();

    // button
    loginBtn = new QPushButton(QStringLiteral("登录"));
    registerBtn = new QPushButton(QStringLiteral("注册"));
    logoutBtn = new QPushButton(QStringLiteral("注销"));


    registerBtn->setStyleSheet("background-color: rgb(255, 128, 64);");
    logoutBtn->setStyleSheet("background-color: rgb(255, 128, 64);");
    loginBtn->setStyleSheet("background-color: rgb(255, 128, 64);");

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(userLogin()));
	connect(logoutBtn, SIGNAL(clicked()), this, SLOT(userLogout()));
    connect(registerBtn, SIGNAL(clicked()), this, SLOT(userRegister()));

    //label
    titleImage = new QLabel();
    titleImage->resize(800,100);
    titleImage->setPixmap(QPixmap("E:\\My universe\\university\\Career\\Qt\\Book_Management_System\\titleImage.png"));

    loginLabel = new QLabel[3];
    loginLabel[0].setText(QStringLiteral("热烈祝贺浙江大学120周年校庆！"));
    loginLabel[1].setText(QStringLiteral("账户:"));
    loginLabel[2].setText(QStringLiteral("密码:"));

    //lineEdit
    nameLine = new QLineEdit();
    passwordLine = new QLineEdit();
    passwordLine->setEchoMode(QLineEdit::Password);

    //tabWidget
    tab = new QTabWidget();
    tab->addTab(window1, QStringLiteral("书目搜索"));
    tab->addTab(window2, QStringLiteral("借阅情况"));
	
    tab->addTab(window3, QStringLiteral("入库出库"));
	/*
    tab->addTab(window4, QStringLiteral("用户管理"));
	*/
    //layout
    gloginLayout = new QGridLayout();
    vloginLayout = new QVBoxLayout();
    hloginLayout = new QHBoxLayout();
    hpageLayout_1 = new QHBoxLayout();
    vrightLayout = new QVBoxLayout();
    htopLayout = new QHBoxLayout();
    vmainLayout = new QVBoxLayout();

    gloginLayout->addWidget(&loginLabel[1], 1, 1, Qt::AlignCenter);
    gloginLayout->addWidget(nameLine, 1, 2);
    gloginLayout->addWidget(&loginLabel[2], 2, 1, Qt::AlignCenter);
    gloginLayout->addWidget(passwordLine, 2, 2);

    hloginLayout->addWidget(loginBtn);
    hloginLayout->addWidget(logoutBtn);
    hloginLayout->addWidget(registerBtn);
    vloginLayout->addWidget(&loginLabel[0]);
    vloginLayout->addLayout(gloginLayout);
    vloginLayout->addLayout(hloginLayout);

    htopLayout->addWidget(titleImage);
    htopLayout->addLayout(vloginLayout);

    vmainLayout->addLayout(htopLayout);
    vmainLayout->addWidget(tab);

    //display
    window->setLayout(vmainLayout);
    window->setWindowTitle(QStringLiteral("JZF图书管理系统"));
    window->setFixedSize(910,600);

    window->setAutoFillBackground(true);
    QPalette p = window->palette();
    p.setColor(QPalette::Window,QColor("white"));
    window->setPalette(p);
    window->show();

    setWindow1();
    setWindow2();
    setWindow3();
    setWindow4();

	win3_fresh();
}

void MainWindow::setWindow1(){
    // const
    QString sort[22] = {QStringLiteral("A"),
                        QStringLiteral("B"),
                        QStringLiteral("C"),
                        QStringLiteral("D"),
                        QStringLiteral("E"),
                        QStringLiteral("F"),
                        QStringLiteral("G"),
                        QStringLiteral("H"),
                        QStringLiteral("I"),
                        QStringLiteral("J"),
                        QStringLiteral("K"),
                        QStringLiteral("N"),
                        QStringLiteral("O"),
                        QStringLiteral("P"),
                        QStringLiteral("Q"),
                        QStringLiteral("R"),
                        QStringLiteral("S"),
                        QStringLiteral("T"),
                        QStringLiteral("U"),
                        QStringLiteral("V"),
                        QStringLiteral("X"),
                        QStringLiteral("Z")};

    //widget
    image_1 = new QLabel();
    image_1->resize(150, 120);
    image_1->setPixmap(QPixmap("E:\\My universe\\university\\Career\\Qt\\Book_Management_System\\search.png"));

	
    //tableWidget
    result_1 = new QTableWidget();
    result_1->setFixedWidth(670);

    QStringList header;
    result_1->setRowCount(13);
    result_1->setColumnCount(9);
    header<<QStringLiteral("书名")<<QStringLiteral("ISBN")<<QStringLiteral("作者")<<QStringLiteral("出版社")<<QStringLiteral("类别");
    header<<QStringLiteral("年份")<<QStringLiteral("月份")<<QStringLiteral("在馆")<<QStringLiteral("借出");
    result_1->setHorizontalHeaderLabels(header);

	result_1->setColumnWidth(0, 150);
	result_1->setColumnWidth(1, 100);
	result_1->setColumnWidth(2, 80);
	result_1->setColumnWidth(3, 100);
	result_1->setColumnWidth(4, 40);
	result_1->setColumnWidth(5, 40);
	result_1->setColumnWidth(6, 40);
	result_1->setColumnWidth(7, 40);
	result_1->setColumnWidth(8, 40);

	result_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
	result_1->setSelectionBehavior(QAbstractItemView::SelectRows);

    //button
    searchBtn = new QPushButton(QStringLiteral("搜索"));
    clearBtn = new QPushButton(QStringLiteral("清除"));
    pageUpBtn = new QPushButton(QStringLiteral("上一页"));
    pageDownBtn = new QPushButton(QStringLiteral("下一页"));
    borrowBtn = new QPushButton(QStringLiteral("借阅"));
    reserveBtn = new QPushButton(QStringLiteral("预约"));
    reserveCancelBtn = new QPushButton(QStringLiteral("取消预约"));

    //comboBox
    yearBox_1 = new QComboBox();
    monthBox_1 = new QComboBox();
    sortBox_1 = new QComboBox();

    yearBox_1->addItem("    ");
    for(int i = 0; i < 60; i++)
        yearBox_1->addItem(QString::number(2017-i));

    monthBox_1->addItem("    ");
    for(int i = 1; i < 13; i++)
        monthBox_1->addItem(QString::number(i));

    sortBox_1->addItem("    ");
    for(int i = 0; i < 22; i++)
        sortBox_1->addItem(sort[i]);

    //lineEdit
    bookLine1 = new QLineEdit();
    authorLine1 = new QLineEdit();
    publisherLine1 = new QLineEdit();
    ISBNLine1 = new QLineEdit();

    //label
    book1 = new QLabel(QStringLiteral("书名"));
    author1 = new QLabel(QStringLiteral("作者"));
    publisher1 = new QLabel(QStringLiteral("出版社"));
    year1 = new QLabel(QStringLiteral("出版年份"));
    month1 = new QLabel(QStringLiteral("出版月份"));
    sort1 =new QLabel(QStringLiteral("图书类别"));
    ISBN1 = new QLabel(QStringLiteral("ISBN"));

    //layout
    hmainLayout_1 = new QHBoxLayout();
    vsearchLayout_1 = new QVBoxLayout();
    hsearchLayout_1 = new QHBoxLayout();
    gsearchLayout_1 = new QGridLayout();
    hpageLayout_1 = new QHBoxLayout();
    hborrowLayout_1 = new QHBoxLayout();

    gsearchLayout_1->addWidget(book1, 1, 1);
    gsearchLayout_1->addWidget(bookLine1, 1, 2);
    gsearchLayout_1->addWidget(ISBN1, 2, 1);
    gsearchLayout_1->addWidget(ISBNLine1, 2, 2);
    gsearchLayout_1->addWidget(author1, 3, 1);
    gsearchLayout_1->addWidget(authorLine1, 3, 2);
    gsearchLayout_1->addWidget(publisher1, 4, 1);
    gsearchLayout_1->addWidget(publisherLine1, 4, 2);
    gsearchLayout_1->addWidget(sort1, 5, 1);
    gsearchLayout_1->addWidget(sortBox_1, 5, 2);
    gsearchLayout_1->addWidget(year1, 6, 1);
    gsearchLayout_1->addWidget(yearBox_1, 6, 2);
    gsearchLayout_1->addWidget(month1, 7, 1);
    gsearchLayout_1->addWidget(monthBox_1, 7, 2);

    hsearchLayout_1->addWidget(searchBtn);
    hsearchLayout_1->addWidget(clearBtn);

    hborrowLayout_1->addWidget(borrowBtn);
    hborrowLayout_1->addWidget(reserveBtn);

    hpageLayout_1->addWidget(pageUpBtn);
    hpageLayout_1->addWidget(pageDownBtn);

    vsearchLayout_1->addWidget(image_1);
    vsearchLayout_1->addLayout(gsearchLayout_1);
    vsearchLayout_1->addLayout(hsearchLayout_1);
    vsearchLayout_1->addLayout(hborrowLayout_1);
    vsearchLayout_1->addWidget(reserveCancelBtn);
    vsearchLayout_1->addStretch();
    vsearchLayout_1->addLayout(hpageLayout_1);

    hmainLayout_1->addWidget(result_1);
    hmainLayout_1->addLayout(vsearchLayout_1);

	//connect
	connect(searchBtn, SIGNAL(clicked()), this, SLOT(win1_search()));
	connect(clearBtn, SIGNAL(clicked()), this, SLOT(win1_clear()));
	connect(borrowBtn, SIGNAL(clicked()), this, SLOT(win1_borrow()));
	connect(result_1, SIGNAL(cellClicked(int, int)), 
		this, SLOT(getItem(int, int)));

    window1->setLayout(hmainLayout_1);
	window->setAutoFillBackground(true);

}

void MainWindow::setWindow2(){
    //const
    QStringList header1;
	header1 << QStringLiteral("书名") << QStringLiteral("ISBN") << QStringLiteral("作者")
		<< QStringLiteral("出版社") << QStringLiteral("借阅日期")
		<< QStringLiteral("应还日期") << QStringLiteral("状态") << QStringLiteral("书本编号");

    QStringList header2;
	header2 << QStringLiteral("书名") << QStringLiteral("ISBN") << QStringLiteral("作者")
		<< QStringLiteral("出版社") << QStringLiteral("借阅日期") << QStringLiteral("归还日期") << QStringLiteral("欠费");


    //tableWidget
    currentTable_2 = new QTableWidget();
    historyTable_2 = new QTableWidget();
    currentTable_2->setRowCount(6);
    currentTable_2->setColumnCount(8);
    currentTable_2->setHorizontalHeaderLabels(header1);
    historyTable_2->setRowCount(6);
    historyTable_2->setColumnCount(7);
    historyTable_2->setHorizontalHeaderLabels(header2);
	currentTable_2->setColumnWidth(7, 80);
	currentTable_2->setColumnWidth(6, 80);

	currentTable_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	currentTable_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	historyTable_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	historyTable_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    //pushButton
    currentPageUp_2 = new QPushButton(QStringLiteral("上一页"));
    currentPageDown_2 = new QPushButton(QStringLiteral("下一页"));
    historyPageUp_2 = new QPushButton(QStringLiteral("上一页"));
    historyPageDown_2 = new QPushButton(QStringLiteral("下一页"));
    returnBtn_2 = new QPushButton(QStringLiteral("归还"));
    renewBtn_2 = new QPushButton(QStringLiteral("续借"));

    //Label
    current2 = new QLabel(QStringLiteral("当前状态"));
    history2 = new QLabel(QStringLiteral("借阅历史"));

    //layout

    vcurrentRight_2 = new QVBoxLayout();
    vhistoryRight_2 = new QVBoxLayout();
    hcurrent_2 = new QHBoxLayout();
    hhistory_2 = new QHBoxLayout();
    vcurrent_2 = new QVBoxLayout();
    vhistory_2 = new QVBoxLayout();
    vmainLayout_2 = new QVBoxLayout();

    vcurrentRight_2->addStretch();
    vcurrentRight_2->addWidget(returnBtn_2);
    vcurrentRight_2->addWidget(renewBtn_2);
    vcurrentRight_2->addWidget(currentPageUp_2);
    vcurrentRight_2->addWidget(currentPageDown_2);

    vhistoryRight_2->addStretch();
    vhistoryRight_2->addWidget(historyPageUp_2);
    vhistoryRight_2->addWidget(historyPageDown_2);

    hcurrent_2->addWidget(currentTable_2);
    hcurrent_2->addLayout(vcurrentRight_2);

    hhistory_2->addWidget(historyTable_2);
    hhistory_2->addLayout(vhistoryRight_2);

    vmainLayout_2->addWidget(current2);
    vmainLayout_2->addLayout(hcurrent_2);
    vmainLayout_2->addWidget(history2);
    vmainLayout_2->addLayout(hhistory_2);
	
	connect(returnBtn_2, SIGNAL(clicked()), this, SLOT(win2_return()));
	connect(renewBtn_2, SIGNAL(clicked()), this, SLOT(win2_renew()));
	connect(currentTable_2, SIGNAL(cellClicked(int, int)),
		this, SLOT(getItem_2(int, int)));

    window2->setLayout(vmainLayout_2);
    window2->setAutoFillBackground(true);

}

void MainWindow::setWindow3(){
    //const
    QString sort_3[22] = {QStringLiteral("A"),
                        QStringLiteral("B"),
                        QStringLiteral("C"),
                        QStringLiteral("D"),
                        QStringLiteral("E"),
                        QStringLiteral("F"),
                        QStringLiteral("G"),
                        QStringLiteral("H"),
                        QStringLiteral("I"),
                        QStringLiteral("J"),
                        QStringLiteral("K"),
                        QStringLiteral("N"),
                        QStringLiteral(""),
                        QStringLiteral("P"),
                        QStringLiteral("Q"),
                        QStringLiteral("R"),
                        QStringLiteral("S"),
                        QStringLiteral("T"),
                        QStringLiteral("U"),
                        QStringLiteral("V"),
                        QStringLiteral("X"),
                        QStringLiteral("Z")};
    QStringList header3;
    header3<<QStringLiteral("书名")<<QStringLiteral("ISBN")<<QStringLiteral("作者")<<QStringLiteral("出版社")<<QStringLiteral("年份");
	header3 << QStringLiteral("月份") << QStringLiteral("类别") << QStringLiteral("状态") << QStringLiteral("入库负责") << QStringLiteral("编号");

    multiText_3 = new QTextEdit();
    singleTable_3 = new QTableWidget();
    singleTable_3->setFixedWidth(700);
    singleTable_3->setRowCount(30);
    singleTable_3->setColumnCount(10);
    singleTable_3->setHorizontalHeaderLabels(header3);

	singleTable_3->setColumnWidth(0, 150);
	singleTable_3->setColumnWidth(1, 100);
	singleTable_3->setColumnWidth(2, 80);
	singleTable_3->setColumnWidth(3, 100);
	singleTable_3->setColumnWidth(4, 40);
	singleTable_3->setColumnWidth(5, 40);
	singleTable_3->setColumnWidth(6, 40);
	singleTable_3->setColumnWidth(7, 40);
	singleTable_3->setColumnWidth(8, 100);

	singleTable_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
	singleTable_3->setSelectionBehavior(QAbstractItemView::SelectRows);

    //lineEdit
    bookLine3 = new QLineEdit();
    authorLine3 = new QLineEdit();
    publisherLine3 = new QLineEdit();
    ISBNLine3 = new QLineEdit();
    numLine3 = new QLineEdit();

    //comboBox
    yearBox_3 = new QComboBox();
    monthBox_3 = new QComboBox();
    sortBox_3 = new QComboBox();

    yearBox_3->addItem("    ");
    for(int i = 0; i < 60; i++)
        yearBox_3->addItem(QString::number(2017-i));

    monthBox_3->addItem("    ");
    for(int i = 1; i < 13; i++)
        monthBox_3->addItem(QString::number(i));

    sortBox_3->addItem("        ");
    for(int i = 0; i < 22; i++)
        sortBox_3->addItem(sort_3[i]);


    //label
    book3 = new QLabel(QStringLiteral("书名"));
    author3 = new QLabel(QStringLiteral("作者"));
    publisher3 = new QLabel(QStringLiteral("出版社"));
    year3 = new QLabel(QStringLiteral("出版年份"));
    month3 = new QLabel(QStringLiteral("出版月份"));
    sort3 = new QLabel(QStringLiteral("图书类别"));
    ISBN3 = new QLabel(QStringLiteral("ISBN"));
    num3 = new QLabel(QStringLiteral("数量"));
    single3 = new QLabel(QStringLiteral("单册操作"));
    multi3 = new QLabel(QStringLiteral("多册操作"));

    //pushButton
    addBtn_3 = new QPushButton(QStringLiteral("添加"));
    deleteBtn_3 = new QPushButton(QStringLiteral("删除"));
    singlePageUpBtn_3 = new QPushButton(QStringLiteral("上一页"));
    singlePageDownBtn_3 = new QPushButton(QStringLiteral("下一页"));
    multiPageUpBtn_3 = new QPushButton(QStringLiteral("上一页"));
    multiPageDownBtn_3 =  new QPushButton(QStringLiteral("下一页"));
    importBtn_3 = new QPushButton(QStringLiteral("导入"));
    executeBtn_3 = new QPushButton(QStringLiteral("执行"));

    //layout
    gsingleUpLayout_3 = new QGridLayout();
    gsingleDownLayout_3 = new QGridLayout();
    vsingleRightLayout_3 = new QVBoxLayout();
    hsingleLayout_3 = new QHBoxLayout();
    vmultiRightLayout_3 = new QVBoxLayout();
    hmultiLayout_3 = new QHBoxLayout();
    vmainLayout_3 = new QVBoxLayout();

    gsingleUpLayout_3->addWidget(book3, 1, 1);
    gsingleUpLayout_3->addWidget(bookLine3, 1, 2);
    gsingleUpLayout_3->addWidget(ISBN3, 2, 1);
    gsingleUpLayout_3->addWidget(ISBNLine3, 2, 2);
    gsingleUpLayout_3->addWidget(author3, 3, 1);
    gsingleUpLayout_3->addWidget(authorLine3, 3, 2);
    gsingleUpLayout_3->addWidget(publisher3, 4, 1);
    gsingleUpLayout_3->addWidget(publisherLine3, 4, 2);

    gsingleUpLayout_3->addWidget(sort3, 5, 1);
    gsingleUpLayout_3->addWidget(sortBox_3, 5, 2);
    gsingleUpLayout_3->addWidget(year3, 6, 1);
    gsingleUpLayout_3->addWidget(yearBox_3, 6, 2);
    gsingleUpLayout_3->addWidget(month3, 7, 1);
    gsingleUpLayout_3->addWidget(monthBox_3, 7, 2);
    gsingleUpLayout_3->addWidget(num3, 8, 1);
    gsingleUpLayout_3->addWidget(numLine3, 8, 2);

    gsingleDownLayout_3->addWidget(addBtn_3, 1, 1);
    gsingleDownLayout_3->addWidget(deleteBtn_3, 1, 2);
    gsingleDownLayout_3->addWidget(singlePageUpBtn_3, 2, 1);
    gsingleDownLayout_3->addWidget(singlePageDownBtn_3, 2, 2);

    vsingleRightLayout_3->addLayout(gsingleUpLayout_3);
    vsingleRightLayout_3->addLayout(gsingleDownLayout_3);

    hsingleLayout_3->addWidget(singleTable_3);
    hsingleLayout_3->addLayout(vsingleRightLayout_3);

    vmultiRightLayout_3->addStretch();
    vmultiRightLayout_3->addWidget(importBtn_3);
    vmultiRightLayout_3->addWidget(executeBtn_3);
    vmultiRightLayout_3->addWidget(multiPageUpBtn_3);
    vmultiRightLayout_3->addWidget(multiPageDownBtn_3);

    hmultiLayout_3->addWidget(multiText_3);
    hmultiLayout_3->addLayout(vmultiRightLayout_3);

    vmainLayout_3->addWidget(single3);
    vmainLayout_3->addLayout(hsingleLayout_3);
    vmainLayout_3->addWidget(multi3);
    vmainLayout_3->addLayout(hmultiLayout_3);
	
	connect(addBtn_3, SIGNAL(clicked()), this, SLOT(win3_add()));
	connect(deleteBtn_3, SIGNAL(clicked()), this, SLOT(win3_delete()));
	connect(importBtn_3, SIGNAL(clicked()), this, SLOT(win3_import()));
	connect(executeBtn_3, SIGNAL(clicked()), this, SLOT(win3_execute()));
	connect(singleTable_3, SIGNAL(cellClicked(int, int)),
		this, SLOT(getItem_3(int, int)));


    window3->setLayout(vmainLayout_3);
    window3->setAutoFillBackground(true);

}

void MainWindow::setWindow4(){

    //const
    QStringList header4;
    header4<<QStringLiteral("用户名")<<QStringLiteral("密码")<<QStringLiteral("权限");

    //table
    userTable_4 = new QTableWidget();
    userTable_4 = new QTableWidget();
    userTable_4->setFixedWidth(560);
    userTable_4->setRowCount(13);
    userTable_4->setColumnCount(3);
    userTable_4->setHorizontalHeaderLabels(header4);

    //button
    authoriseBtn = new QPushButton(QStringLiteral("设置为管理员"));
    deriveBtn = new QPushButton(QStringLiteral("解除管理员权限"));

    //layout
    vrightLayout_4 = new QVBoxLayout();
    hmainLayout_4 = new QHBoxLayout();

    vrightLayout_4->addWidget(authoriseBtn);
    vrightLayout_4->addWidget(deriveBtn);
    vrightLayout_4->addStretch();

    hmainLayout_4->addWidget(userTable_4);
    hmainLayout_4->addLayout(vrightLayout_4);

    window4->setLayout(hmainLayout_4);
    window4->setAutoFillBackground(true);
}