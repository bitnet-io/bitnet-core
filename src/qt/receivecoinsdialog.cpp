// Copyright (c) 2011-2022 The Bitnet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.




#include <wallet/wallet.h>

#include <qt/receivecoinsdialog.h>
#include <qt/forms/ui_receivecoinsdialog.h>

#include <qt/addresstablemodel.h>
#include <qt/guiutil.h>
#include <qt/optionsmodel.h>
#include <qt/platformstyle.h>
#include <qt/receiverequestdialog.h>
#include <qt/recentrequeststablemodel.h>
#include <qt/walletmodel.h>

#include <QAction>
#include <QCursor>
#include <QMessageBox>
#include <QScrollBar>
#include <QSettings>
#include <QTextDocument>




#include <QDialog>
#include <QString>









#include <unistd.h>

#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>



#include <string>
#include <iostream>














using namespace std;

ReceiveCoinsDialog::ReceiveCoinsDialog(const PlatformStyle *_platformStyle, QWidget *parent) :
    QDialog(parent, GUIUtil::dialog_flags),
    ui(new Ui::ReceiveCoinsDialog),
    platformStyle(_platformStyle)
{
    ui->setupUi(this);

    if (!_platformStyle->getImagesOnButtons()) {
        ui->clearButton->setIcon(QIcon());
        ui->receiveButton->setIcon(QIcon());
        ui->showRequestButton->setIcon(QIcon());
        ui->removeRequestButton->setIcon(QIcon());
    } else {
        ui->clearButton->setIcon(_platformStyle->SingleColorIcon(":/icons/remove"));
        ui->receiveButton->setIcon(_platformStyle->SingleColorIcon(":/icons/receiving_addresses"));
        ui->showRequestButton->setIcon(_platformStyle->SingleColorIcon(":/icons/eye"));
        ui->removeRequestButton->setIcon(_platformStyle->SingleColorIcon(":/icons/remove"));
    }

    // context menu
    contextMenu = new QMenu(this);
    contextMenu->addAction(tr("Copy &URI"), this, &ReceiveCoinsDialog::copyURI);
    contextMenu->addAction(tr("&Copy address"), this, &ReceiveCoinsDialog::copyAddress);
//    copyLabelAction = contextMenu->addAction(tr("Copy &label"), this, &ReceiveCoinsDialog::copyLabel);
    copyMessageAction = contextMenu->addAction(tr("Copy &message"), this, &ReceiveCoinsDialog::copyMessage);
    copyAmountAction = contextMenu->addAction(tr("Copy &amount"), this, &ReceiveCoinsDialog::copyAmount);
    connect(ui->recentRequestsView, &QWidget::customContextMenuRequested, this, &ReceiveCoinsDialog::showMenu);

    connect(ui->clearButton, &QPushButton::clicked, this, &ReceiveCoinsDialog::clear);

    QTableView* tableView = ui->recentRequestsView;
    tableView->verticalHeader()->hide();
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    QSettings settings;
    if (!tableView->horizontalHeader()->restoreState(settings.value("RecentRequestsViewHeaderState").toByteArray())) {
        tableView->setColumnWidth(RecentRequestsTableModel::Date, DATE_COLUMN_WIDTH);
//        tableView->setColumnWidth(RecentRequestsTableModel::Label, LABEL_COLUMN_WIDTH);
        tableView->setColumnWidth(RecentRequestsTableModel::Amount, AMOUNT_MINIMUM_COLUMN_WIDTH);
        tableView->horizontalHeader()->setMinimumSectionSize(MINIMUM_COLUMN_WIDTH);
        tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

string generateRandomString(int length)
{
    // Define the list of possible characters
    const string CHARACTERS
        = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";

    const string base = "bit1qpsg60mumyf5dfaqvxewqhjsdnkg0y57gz690vh";

    // Create a random number generator
    random_device rd;
    mt19937 generator(rd());

    // Create a distribution to uniformly select from all
    // characters
    uniform_int_distribution<> distribution(
        0, CHARACTERS.size() - 1);

    // Generate the random string
    string random_string;
    for (int i = 0; i < length; ++i) {
        random_string
            += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

void ReceiveCoinsDialog::setModel(WalletModel *_model)
{
    this->model = _model;

    if(_model && _model->getOptionsModel())
    {
        _model->getRecentRequestsTableModel()->sort(RecentRequestsTableModel::Date, Qt::DescendingOrder);
        connect(_model->getOptionsModel(), &OptionsModel::displayUnitChanged, this, &ReceiveCoinsDialog::updateDisplayUnit);
        updateDisplayUnit();

        QTableView* tableView = ui->recentRequestsView;
        tableView->setModel(_model->getRecentRequestsTableModel());
        tableView->sortByColumn(RecentRequestsTableModel::Date, Qt::DescendingOrder);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged, this,
            &ReceiveCoinsDialog::recentRequestsView_selectionChanged);

        // Populate address type dropdown and select default
        auto add_address_type = [&](OutputType type, const QString& text, const QString& tooltip) {
            const auto index = ui->addressType->count();
            ui->addressType->addItem(text, (int) type);
            ui->addressType->setItemData(index, tooltip, Qt::ToolTipRole);
            if (model->wallet().getDefaultAddressType() == type) ui->addressType->setCurrentIndex(index);
        };
        add_address_type(OutputType::LEGACY, "Base58 (Legacy)", "Not recommended due to higher fees and less protection against typos.");
        add_address_type(OutputType::P2SH_SEGWIT, "Base58 (P2SH-SegWit)", "Generates an address compatible with older wallets.");
        add_address_type(OutputType::BECH32, "Bech32 (SegWit)", "Generates a native segwit address (BIP-173). Some old wallets don't support it.");
        if (model->wallet().taprootEnabled()) {
            add_address_type(OutputType::BECH32M, "Bech32m (Taproot)", "Bech32m (BIP-350) is an upgrade to Bech32, wallet support is still limited.");
        }

        // Set the button to be enabled or disabled based on whether the wallet can give out new addresses.
        ui->receiveButton->setEnabled(model->wallet().canGetAddresses());

        // Enable/disable the receive button if the wallet is now able/unable to give out new addresses.
        connect(model, &WalletModel::canGetAddressesChanged, [this] {
            ui->receiveButton->setEnabled(model->wallet().canGetAddresses());
        });
    }
}

ReceiveCoinsDialog::~ReceiveCoinsDialog()
{
    QSettings settings;
    settings.setValue("RecentRequestsViewHeaderState", ui->recentRequestsView->horizontalHeader()->saveState());
    delete ui;
}

void ReceiveCoinsDialog::clear()
{
    ui->reqAmount->clear();
    ui->reqLabel->setText("");
    ui->reqMessage->setText("");
    updateDisplayUnit();
}

void ReceiveCoinsDialog::reject()
{
    clear();
}

void ReceiveCoinsDialog::accept()
{
    clear();
}

void ReceiveCoinsDialog::updateDisplayUnit()
{
    if(model && model->getOptionsModel())
    {
         ui->reqAmount->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
    }
}
















void ReceiveCoinsDialog::setInfo(const SendCoinsRecipient &_info)
{

    int length = 25;
    std::string random_string = generateRandomString(length); 
    QString str = QString::fromLocal8Bit(random_string.c_str());


   QEventLoop *localLoop = new QEventLoop();

    this->info = _info;
		//   setWindowTitle(tr("Request payment to %1").arg(info.label.isEmpty() ? info.address : info.label));
    QString uri = GUIUtil::formatBitnetURI(info);

		//   ui->uri_content->setText("<a href=\"" + uri + "\">" + GUIUtil::HtmlEscape(uri) + "</a>");
		//   ui->address_content->setText(info.address);


#ifdef USE_QRCODE

    if (ui->qr_code->setQR(str, info.address)) {
		//        connect(ui->btnSaveAs, &QPushButton::clicked, ui->qr_code, &QRImageWidget::saveImage);
    } else {
    ui->qr_code->hide();
		//        ui->btnSaveAs->setEnabled(false);
    }


#else
		//    ui->btnSaveAs->hide();
    ui->qr_code->hide();
		//	}

		//}
#endif










//    if (!info.amount) {
//    } // Amount is set in updateDisplayUnit() slot.
//    updateDisplayUnit();


//    if (!info.message.isEmpty()) {
//    } else {
//    }

//    if (!model->getWalletName().isEmpty()) {
//    } else {
//    }


            usleep(100000);

    QTimer::singleShot(200, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();



}

void ReceiveCoinsDialog::setInfoReal(const SendCoinsRecipient &_info)
{


   QEventLoop *localLoop = new QEventLoop();

    this->info = _info;
		//   setWindowTitle(tr("Request payment to %1").arg(info.label.isEmpty() ? info.address : info.label));

    QString uri = GUIUtil::formatBitnetURI(info);
		//    ui->uri_content->setText("<a href=\"" + uri + "\">" + GUIUtil::HtmlEscape(uri) + "</a>");
		//    ui->address_content->setText(info.address);

		//    QString uri = QString::fromLocal8Bit(info);


#ifdef USE_QRCODE

    if (ui->qr_code->setQR(uri, info.address)) {
		//        connect(ui->btnSaveAs, &QPushButton::clicked, ui->qr_code, &QRImageWidget::saveImage);
    } else {
    ui->qr_code->hide();
		//        ui->btnSaveAs->setEnabled(false);
  }


#else
		//    ui->btnSaveAs->hide();
    ui->qr_code->hide();

#endif




          usleep(80000);

    QTimer::singleShot(100, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();



}













void ReceiveCoinsDialog::on_receiveButton_clicked()
{
    if(!model || !model->getOptionsModel() || !model->getAddressTableModel() || !model->getRecentRequestsTableModel())
        return;

    QString address;

    QString label = ui->reqLabel->text();
		//    label = new QLabel("default label");
		//    label = ui->reqLabel->text();


    /* Generate new receiving address */
    const OutputType address_type = (OutputType)ui->addressType->currentData().toInt();
    address = model->getAddressTableModel()->addRow(AddressTableModel::Receive, label, "", address_type);

    switch(model->getAddressTableModel()->getEditStatus())
    {
    case AddressTableModel::EditStatus::OK: {
        // Success


        SendCoinsRecipient info(address, label,
            ui->reqAmount->value(), ui->reqMessage->text());
        setAttribute(Qt::WA_DeleteOnClose);
        setInfo(info);
        model->getRecentRequestsTableModel()->addNewRequest(info);

	while (1 > 0) {


   QEventLoop *localLoop = new QEventLoop();

        setInfo(info);
            usleep(100000);
            setInfoReal(info);
            usleep(60000);
    QTimer::singleShot(500, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();




}

        /* Store request for later reference */


    }
	//    case AddressTableModel::EditStatus::WALLET_UNLOCK_FAILURE:
	//        QMessageBox::critical(this, windowTitle(),
	//            tr("Could not unlock wallet."),
	//            QMessageBox::Ok, QMessageBox::Ok);
	//        break;
	//    case AddressTableModel::EditStatus::KEY_GENERATION_FAILURE:
	//        QMessageBox::critical(this, windowTitle(),
	//            tr("Could not generate new %1 address").arg(QString::fromStdString(FormatOutputType(address_type))),
	//            QMessageBox::Ok, QMessageBox::Ok);
	//        break;


    // These aren't valid return values for our action
    case AddressTableModel::EditStatus::INVALID_ADDRESS:
    case AddressTableModel::EditStatus::DUPLICATE_ADDRESS:
    case AddressTableModel::EditStatus::NO_CHANGES:
        assert(false);
    }
    clear();
}

void ReceiveCoinsDialog::on_recentRequestsView_doubleClicked(const QModelIndex &index)
{
    const RecentRequestsTableModel *submodel = model->getRecentRequestsTableModel();

	while (1 > 0) {

   QEventLoop *localLoop = new QEventLoop();
        setInfo(info);
    setInfo(submodel->entry(index.row()).recipient);
    setAttribute(Qt::WA_DeleteOnClose);

            usleep(100000);
    setInfoReal(submodel->entry(index.row()).recipient);
            usleep(60000);
    QTimer::singleShot(500, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();
	}

}

void ReceiveCoinsDialog::recentRequestsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

//    // Enable Show/Remove buttons only if anything is selected.
    bool enable = !ui->recentRequestsView->selectionModel()->selectedRows().isEmpty();
    ui->showRequestButton->setEnabled(enable);
    ui->removeRequestButton->setEnabled(enable);
}

void ReceiveCoinsDialog::on_showRequestButton_clicked()
{
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();

    for (const QModelIndex& index : selection) {
        on_recentRequestsView_doubleClicked(index);
    }
}

void ReceiveCoinsDialog::on_removeRequestButton_clicked()
{
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if(selection.empty())
        return;
    // correct for selection mode ContiguousSelection
    QModelIndex firstIndex = selection.at(0);
    model->getRecentRequestsTableModel()->removeRows(firstIndex.row(), selection.length(), firstIndex.parent());
}

QModelIndex ReceiveCoinsDialog::selectedRow()
{
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return QModelIndex();
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if(selection.empty())
        return QModelIndex();
    // correct for selection mode ContiguousSelection
    QModelIndex firstIndex = selection.at(0);
    return firstIndex;
}

// copy column of selected row to clipboard
void ReceiveCoinsDialog::copyColumnToClipboard(int column)
{
    QModelIndex firstIndex = selectedRow();
    if (!firstIndex.isValid()) {
        return;
    }
    GUIUtil::setClipboard(model->getRecentRequestsTableModel()->index(firstIndex.row(), column).data(Qt::EditRole).toString());
}

// context menu
void ReceiveCoinsDialog::showMenu(const QPoint &point)
{
    const QModelIndex sel = selectedRow();
    if (!sel.isValid()) {
        return;
    }

    // disable context menu actions when appropriate
    const RecentRequestsTableModel* const submodel = model->getRecentRequestsTableModel();
    const RecentRequestEntry& req = submodel->entry(sel.row());
	//    copyLabelAction->setDisabled(req.recipient.label.isEmpty());
    copyMessageAction->setDisabled(req.recipient.message.isEmpty());
    copyAmountAction->setDisabled(req.recipient.amount == 0);

    contextMenu->exec(QCursor::pos());
}

// context menu action: copy URI
void ReceiveCoinsDialog::copyURI()
{
    QModelIndex sel = selectedRow();
    if (!sel.isValid()) {
        return;
    }

    const RecentRequestsTableModel * const submodel = model->getRecentRequestsTableModel();
    const QString uri = GUIUtil::formatBitnetURI(submodel->entry(sel.row()).recipient);
    GUIUtil::setClipboard(uri);
}

// context menu action: copy address
void ReceiveCoinsDialog::copyAddress()
{
    const QModelIndex sel = selectedRow();
    if (!sel.isValid()) {
        return;
    }

    const RecentRequestsTableModel* const submodel = model->getRecentRequestsTableModel();
    const QString address = submodel->entry(sel.row()).recipient.address;
    GUIUtil::setClipboard(address);
}

// context menu action: copy label
void ReceiveCoinsDialog::copyLabel()
{
    copyColumnToClipboard(RecentRequestsTableModel::Label);
}

// context menu action: copy message
void ReceiveCoinsDialog::copyMessage()
{
    copyColumnToClipboard(RecentRequestsTableModel::Message);
}

// context menu action: copy amount
void ReceiveCoinsDialog::copyAmount()
{
    copyColumnToClipboard(RecentRequestsTableModel::Amount);
}








