#include "mainwindow.h"

void MainWindow::userLogin() {
	QSqlQuery query;
	QString statement = "select * from user";
	QString name = nameLine->text();
	QString password = passwordLine->text();
	if (name.size() && password.size()) {
		statement += " where username = '" + name + "' and"
			+ " password = '" + password + "'";
		query.exec(statement);
		if (query.next()) {
			currentUser = query.value(2).toString();
			QString userLevel = query.value(3).toString();
			QMessageBox::information(0,
				QObject::tr("succeed"), QStringLiteral("登陆成功！"));
			if (userLevel == "1")
				status = user;
			else if(userLevel == "2")
				status = administrator;
			win2_fresh();
		}
		else {
			QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("用户不存在或密码错误！"));
			status = visitor;
		}
	}
	else {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("输入信息不完整！"));
		status = visitor;
	}
}

void MainWindow::userLogout() {
	status = visitor;
}

void MainWindow::userRegister() {
	QSqlQuery query;
	QString statement = "insert into user values";
	QString name = nameLine->text();
	QString password = passwordLine->text();
	if (name.size() && password.size()) {
		QString id;
		QString temp;
		for (int i = 1;; i++) {
			id = id.setNum(i, 10);
			temp = "select * from user where user_id = '"
				+ id + "'";
			query.exec(temp);
			if (!query.next())
				break;
		}
		statement += "('" + name + "', '"
			+ password + "', " + id + ", 1)";
		query.exec(statement);
		QMessageBox::information(0, QObject::tr("succeed"), QStringLiteral("创建成功！"));
	}
	else {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("输入信息不完整！"));
	}
}

void MainWindow::win1_search() {
	QSqlQuery query;
	QString statement;
	QString whereClause;
	if (bookLine1->text().size()) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " name = '" + bookLine1->text() + "'";
	}
	if (ISBNLine1->text().size()) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " ISBN = '" + ISBNLine1->text() + "'";
	}
	if (authorLine1->text().size()) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " author = '" + ISBNLine1->text() + "'";
	}
	if (publisherLine1->text().size()) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " publisher = '" + publisherLine1->text() + "'";
	}
	if (sortBox_1->currentText().compare("    ")) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " category = '" + sortBox_1->currentText() + "'";
	}
	if (yearBox_1->currentText().compare("    ")) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " year = '" + yearBox_1->currentText() + "'";
	}
	if (monthBox_1->currentText().compare("    ")) {
		if (whereClause.size())
			whereClause += " and";
		whereClause += " month = '" + monthBox_1->currentText() + "'";
	}

	statement = "select * from record";
	if (whereClause.size())
		whereClause.prepend(" where");
	statement += whereClause;
	query.exec(statement);

	win1_row = 0;
	result_1->clearContents();
	while (query.next()) {
		for (int i = 0; i <= 8; i++) {
			QString temp = query.value(i).toString();
			QTableWidgetItem *item = new QTableWidgetItem(temp);
			result_1->setItem(win1_row, i, item);
		}
		++win1_row;
	}
}

void MainWindow::win1_clear() {
	bookLine1->clear();
	ISBNLine1->clear();
	authorLine1->clear();
	publisherLine1->clear();
	sortBox_1->setCurrentIndex(0);
	yearBox_1->setCurrentIndex(0);
	monthBox_1->setCurrentIndex(0);
}

void MainWindow::win1_borrow() {
	QSqlQuery query;
	QString statement1;
	if (status == visitor) {
		QMessageBox::critical(0,
			QObject::tr("error"), QStringLiteral("游客无法借书, 请登录！"));
	}
	else if (win1_item.size()) {
		statement1 = "select * from book where status = 'in' and ISBN = '" +
			win1_item + "' limit 1";
		query.exec(statement1);
		if (query.next()) {
			QString book_id = query.value(0).toString();
			QString statement2 = "update book set";
			statement2 += " status = 'out' where book_id = '" + book_id + "'";
			query.exec(statement2);
			QMessageBox::information(0,
				QObject::tr("error"), QStringLiteral("借阅成功！"));
			win1_search();

			QDate today = QDate::currentDate();
			QDate returnDay = today.addDays(30);
			QString date = today.toString("yyyy-MM-dd");
			QString retDate = returnDay.toString("yyyy-MM-dd");
			QString statement3 = "insert into borrow values";
			statement3 += "('" + book_id + "', '" + currentUser
					+ "', '" + date + "', '" + retDate + "', null )";
			qDebug() << statement3;
			query.exec(statement3);
			qDebug() << query.isActive();
			win2_fresh();
		}
		else {
			QMessageBox::critical(0, 
				QObject::tr("error"), QStringLiteral("本馆已没有余量可借！"));
		}
	}
}

void MainWindow::getItem(int row, int column) {
	if (row < win1_row ) {
		win1_item = result_1->item(row, 1)->text();
	}
}

void MainWindow::win2_fresh() {
	if (status == visitor)
		return;
	QSqlQuery query;
	QString statement = "select * from borrowHistory";
	statement += " where user_id = '" + currentUser + "'";
	query.exec(statement);

	win2_row = 0;
	currentTable_2->clearContents();
	while (query.next()) {
		QString recDate = query.value(6).toString();
		if (recDate.size())
			continue;
		for (int i = 0; i <= 7; i++) {
			if (i != 6) {
				QString temp = query.value(i).toString();
				QTableWidgetItem *item = new QTableWidgetItem(temp);
				currentTable_2->setItem(win2_row, i, item);
			}
			else {
				QString temp = QStringLiteral("未还");
				QTableWidgetItem *item = new QTableWidgetItem(temp);
				currentTable_2->setItem(win2_row, i, item);
			}
		}
		++win2_row;
	}

	statement = "select * from borrowHistory";
	statement += " where user_id = '" + currentUser + "'";
	win2_row2 = 0;
	historyTable_2->clearContents();
	query.exec(statement);
	while (query.next()) {
		QString recDate = query.value(6).toString();
		if (!recDate.size())
			continue;
		for (int i = 0; i <= 6; i++) {
			if (i < 5) {
				QString temp = query.value(i).toString();
				QTableWidgetItem *item = new QTableWidgetItem(temp);
				historyTable_2->setItem(win2_row2, i, item);
			}
			else if (i == 5) {
				QTableWidgetItem *item = new QTableWidgetItem(recDate);
				historyTable_2->setItem(win2_row2, i, item);
			}
			else if (i == 6) {
				QString temp = query.value(5).toString();
				QStringList ddl = temp.split("-");
				bool ok;
				QString year1 = ddl[0];		int y1 = year1.toInt(&ok, 10);
				QString month1 = ddl[1];	int m1 = month1.toInt(&ok, 10);
				QString day1 = ddl[2];		int d1 = day1.toInt(&ok, 10);
				
				QStringList rec = recDate.split("-");
				QString year2 = rec[0];		int y2 = year2.toInt(&ok, 10);
				QString month2 = rec[1];	int m2 = month2.toInt(&ok, 10);
				QString day2 = rec[2];		int d2 = day2.toInt(&ok, 10);

				QDate date1(y1, m1, d1);
				QDate date2(y2, m2, d2);
				double cost;
				if (date1 >=date2) {
					cost = 0;
				}
				else {
					long int dd = date2.daysTo(date1);
					cost = dd * 0.1;
				}
				
				QString temp2;
				temp2 = temp2.setNum(cost);
				QTableWidgetItem *item = new QTableWidgetItem(temp2);
				historyTable_2->setItem(win2_row2, i, item);
			}
		}
		++win2_row2;
	}
}

void MainWindow::win2_return() {
	if (status == visitor)
		return;

	QSqlQuery query;
	QString statement1;
	if (win2_item.size()) {
		statement1 = "update book set status = 'in' where book_id = '" +
			win2_item + "'";
		qDebug() << statement1;
		query.exec(statement1);
		QMessageBox::information(0,
			QObject::tr("succeed"), QStringLiteral("归还成功！"));
		win1_search();

		QDate today = QDate::currentDate();
		QString retDate = today.toString("yyyy-MM-dd");
		statement1 = "update borrow set return_date = '" + retDate + "'"
			+ " where book_id = '" + win2_item + "'";
		qDebug() << statement1;
		query.exec(statement1);
		win2_fresh();
	}
}

void MainWindow::win2_renew() {
	if (status == visitor)
		return;

	QSqlQuery query;
	QString statement1;

	bool ok;
	QStringList oldDDLList = win2_item2.split("-");
	QString year1 = oldDDLList[0];		int y = year1.toInt(&ok, 10);
	QString month1 = oldDDLList[1];		int m = month1.toInt(&ok, 10);
	QString day1 = oldDDLList[2];		int d = day1.toInt(&ok, 10);
	QDate oldDDL(y, m, d);
	QDate newDDL = oldDDL.addDays(30);
	QString newDDLString = newDDL.toString("yyyy-MM-dd");

	statement1 = "update borrow set deadline = '"
		+ newDDLString + "' where book_id = '" + win2_item
		+ "' and return_date is null";
		qDebug() << statement1;
	QMessageBox::information(0,
		QObject::tr("succeed"), QStringLiteral("续借成功！"));

	query.exec(statement1);
	win2_fresh();
}

void MainWindow::getItem_2(int row, int column) {
	if (row < win2_row) {
		win2_item = currentTable_2->item(row, 7)->text();
		win2_item2 = currentTable_2->item(row, 5)->text();
	}
}

void MainWindow::win3_add() {
	if (status != administrator) {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("您无权操作！"));
		return;
	}
	QSqlQuery query;

	if (bookLine3->text().size()
		&& ISBNLine3->text().size()
		&& authorLine3->text().size()
		&& publisherLine3->text().size()
		&& sortBox_3->currentText().compare("    ") != 0
		&& yearBox_3->currentText().compare("    ") != 0
		&& monthBox_3->currentText().compare("    ") != 0
		&& numLine3->text().size()) {
		
		bool ok;
		int bookNum = numLine3->text().toInt(&ok, 10);

		while (bookNum--) {
			QString statement1 = "select * from book where book_id = '";
			QString index;
			for (int i = 0; ; i++) {
				
				index = index.setNum(i);
				QString statement2 = statement1 + index + "'";
				query.exec(statement2);
				if (!query.next())
					break;
			}
			QString statement3 = "insert into book values(";
			statement3 += "'" + index + "', ";
			statement3 += "'" + bookLine3->text() + "', ";
			statement3 += "'" + ISBNLine3->text() + "', ";
			statement3 += "'" + authorLine3->text() + "', ";
			statement3 += "'" + publisherLine3->text() + "', ";
			statement3 += "'" + sortBox_3->currentText() + "', ";
			statement3 += "'" + yearBox_3->currentText() + "', ";
			statement3 += "'" + monthBox_3->currentText() + "', ";
			statement3 += "'in')";	
			query.exec(statement3);

			QDate today = QDate::currentDate();
			QString date = today.toString("yyyy-MM-dd");
			QString statement4 = "insert into manage values(";
			statement4 += "'" + index + "', ";
			statement4 += "'" + currentUser + "', ";
			statement4 += "'" + date + "')";
			query.exec(statement4);

		}
		QMessageBox::information(0, QObject::tr("succeed"), QStringLiteral("添加成功！"));
		win1_search();
		win3_fresh();
	}
	else {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("输入信息不完整！"));
	}
}

void MainWindow::win3_fresh() {
	QSqlQuery query;
	QString statement = "select * from manageHistory";
	query.exec(statement);

	win3_row = 0;
	singleTable_3->clearContents();
	while (query.next()) {
		for (int i = 0; i <= 9; i++) {
			QString temp = query.value(i).toString();
			QTableWidgetItem *item = new QTableWidgetItem(temp);
			singleTable_3->setItem(win3_row, i, item);
		}
		++win3_row;
	}
}

void MainWindow::win3_delete() {
	if (status != administrator) {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("您无权操作！"));
		return;
	}
	if (win3_item2 == "out") {
		QMessageBox::critical(0, 
			QObject::tr("error"), QStringLiteral("书本未归还，不能出库！"));
		return;
	}

	if (win3_item.size() == 0) {
		QMessageBox::critical(0,
			QObject::tr("error"), QStringLiteral("未选中任何单册！"));
		return;
	}

	QSqlQuery query;

	QString statement = "delete from manage where book_id = '";
	statement += win3_item + "'";
	query.exec(statement);

	statement = "delete from borrow where book_id = '";
	statement += win3_item + "'";
	query.exec(statement);

	statement = "delete from book where book_id = '";
	statement += win3_item + "'";
	query.exec(statement);
	
	QMessageBox::information(0,
		QObject::tr("succeed"), QStringLiteral("删除单册成功！"));
	win1_search();
	win3_fresh();
}

void MainWindow::win3_import() {
	if (status != administrator) {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("您无权操作！"));
		return;
	}

	QString path = QFileDialog::getOpenFileName(this, "Import File",
		".", "Test case Files(*.txt *.in)");

	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}

		QTextStream in(&file);
		QString rawString = in.readAll();

		while (fileContent.size()) {
			fileContent.removeAt(0);
		}

		fileContent = rawString.split("\n");
		multiText_3->setText(rawString);
	}

}

void MainWindow::win3_execute() {
	if (status != administrator) {
		QMessageBox::critical(0, QObject::tr("error"), QStringLiteral("您无权操作！"));
		return;
	}

	QStringList::ConstIterator iter = fileContent.constBegin();
	QString temp = *iter++;
	bool ok;
	int count = temp.toInt(&ok, 10);
	QSqlQuery query;
	QString statement;
	while (count) {
		QString name = *iter++;
		QString ISBN = *iter++;
		QString author = *iter++;
		QString publisher = *iter++;
		QString category = *iter++;
		QString year = *iter++;
		QString month = *iter++;

		while (count--) {
			QString statement2 = "select * from book where book_id = '";
			QString index;
			for (int i = 0; ; i++) {
				index = index.setNum(i);
				QString statement3 = statement2 + index + "'";
				query.exec(statement3);
				if (!query.next())
					break;
			}
			statement = "insert into book values(";
			statement += "'" + index + "', ";
			statement += "'" + name + "', ";
			statement += "'" + ISBN + "', ";
			statement += "'" + author + "', ";
			statement += "'" + publisher + "', ";
			statement += "'" + category + "', ";
			statement += "'" + year + "', ";
			statement += "'" + month + "', ";
			statement += "'in')";
			query.exec(statement);

			QDate today = QDate::currentDate();
			QString date = today.toString("yyyy-MM-dd");
			QString statement4 = "insert into manage values(";
			statement4 += "'" + index + "', ";
			statement4 += "'" + currentUser + "', ";
			statement4 += "'" + date + "')";
			query.exec(statement4);
		}

		temp = *iter++;
		count = temp.toInt(&ok, 10);
	}
	QMessageBox::information(0, QObject::tr("succeed"), QStringLiteral("批量录入成功！"));
	win1_search();
	win3_fresh();
}

void MainWindow::getItem_3(int row, int column) {
	if (row < win3_row) {
		win3_item = singleTable_3->item(row, 9)->text();
		win3_item2 = singleTable_3->item(row, 7)->text();
	}
}