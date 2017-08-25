#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QString>
#include <QTextEdit>
#include <QTextCodec>
#include <QByteArray>
#include <QTime>
#include <QRegExp>
#include <QFileDialog>
#include <QTextStream>
#include <database.h>

enum loginStatus {
	visitor, user, administrator
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    myDB *library;
	loginStatus status;
	QString currentUser;
	QString win1_item;
	QString win2_item;
	QString win2_item2;
	QString win3_item;
	QString win3_item2;
	QStringList fileContent;
	int win1_row;
	int win1_page;
	int win2_row;
	int win2_row2;
	int win3_row;
    void setMainWindow();
    void setWindow1();
    void setWindow2();
    void setWindow3();
    void setWindow4();

    //mainwindow
    QTabWidget *tab;
    QPalette *pal;
    QGridLayout *gloginLayout;
    QPushButton *loginBtn, *registerBtn, *logoutBtn;
    QHBoxLayout *htopLayout, *hloginLayout;
    QVBoxLayout *vrightLayout, *vmainLayout, *vloginLayout;
    QWidget  *window, *window1, *window2, *window3, *window4;
    QLineEdit *nameLine, *passwordLine;
    QLabel *loginLabel, *titleImage;

    //window1
    QHBoxLayout *hmainLayout_1, *hsearchLayout_1, *hpageLayout_1, *hborrowLayout_1;
    QVBoxLayout *vsearchLayout_1;
    QGridLayout *gsearchLayout_1;

    QTableWidget *result_1;
    QLabel *image_1;
    QPushButton *searchBtn, *clearBtn, *pageUpBtn, *pageDownBtn, *borrowBtn, *reserveBtn, *reserveCancelBtn;


    QLineEdit *bookLine1, *authorLine1, *publisherLine1, *ISBNLine1;
    QComboBox *yearBox_1, *monthBox_1, *sortBox_1;

    QLabel *book1, *author1, *publisher1, *year1, *month1, *sort1, *ISBN1;

    //window2
    QTableWidget *currentTable_2, *historyTable_2;
    QLabel *current2, *history2;
    QPushButton *currentPageUp_2, *currentPageDown_2, *historyPageUp_2, *historyPageDown_2, *returnBtn_2, *renewBtn_2;

    QVBoxLayout *vcurrentRight_2, *vhistoryRight_2;
    QHBoxLayout *hcurrent_2, *hhistory_2;
    QVBoxLayout *vcurrent_2, *vhistory_2;
    QVBoxLayout *vmainLayout_2;

    //window3
    QLineEdit *bookLine3, *authorLine3, *publisherLine3, *ISBNLine3, *numLine3;
    QComboBox *yearBox_3, *monthBox_3, *sortBox_3;
    QLabel *book3, *author3, *publisher3, *year3, *month3, *sort3, *ISBN3, *num3, *single3, *multi3;
    QTableWidget *singleTable_3;
    QTextEdit *multiText_3;
    QGridLayout *gsingleUpLayout_3;
    QGridLayout *gsingleDownLayout_3;
    QVBoxLayout *vsingleRightLayout_3;
    QHBoxLayout *hsingleLayout_3;
    QVBoxLayout *vmultiRightLayout_3;
    QHBoxLayout *hmultiLayout_3;
    QVBoxLayout *vmainLayout_3;
    QPushButton *addBtn_3, *deleteBtn_3, *singlePageUpBtn_3, *singlePageDownBtn_3, *multiPageUpBtn_3, *multiPageDownBtn_3;
	QPushButton *importBtn_3, *executeBtn_3;
    //window4
    QTableWidget *userTable_4;
    QPushButton *authoriseBtn, *deriveBtn;
    QVBoxLayout *vrightLayout_4;
    QHBoxLayout *hmainLayout_4;

private slots:
    void userLogin();
    void userRegister();
	void userLogout();
	// tab1
	void win1_search();
	void win1_clear();
	void win1_borrow();
	void getItem(int row, int column);
	void win2_return();
	void win2_renew();
	void win2_fresh();
	void getItem_2(int row, int column);
	void win3_add();
	void win3_fresh();
	void win3_delete();
	void win3_import();
	void win3_execute();
	void getItem_3(int row, int column);
};

#endif // MAINWINDOW_H
